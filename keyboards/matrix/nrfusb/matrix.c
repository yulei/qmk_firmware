/**
 * @file matrix.c
 */

#include <stdint.h>
#include <string.h>
#include "hal.h"
#include "quantum.h"
#include "printf.h"
#include "matrix.h"
#include "host.h"
#include "flash_stm32.h"

#include "rtt/SEGGER_RTT.h"

#if defined(KEYBOARD_SHARED_EP)
#error "do not support keyboard shared ep"
#endif

#define QUEUE_ITEM_SIZE   KEYBOARD_REPORT_SIZE      // maximum size of the queue item
typedef struct {
    uint32_t    type;                               // type of the item
    uint8_t     data[QUEUE_ITEM_SIZE];
} report_item_t;

#define QUEUE_SIZE      64
typedef struct {
    report_item_t   items[QUEUE_SIZE];
    uint32_t        head;
    uint32_t        tail;
} report_queue_t;

static report_queue_t report_queue;


static bool report_queue_empty(report_queue_t* queue)
{
    return queue->head == queue->tail;
}

static bool report_queue_full(report_queue_t* queue)
{
    return ((queue->tail + 1) % QUEUE_SIZE) == queue->head;
}

static void report_queue_init(report_queue_t* queue)
{
    memset(&queue->items[0], 0, sizeof(queue->items));
    queue->head = queue->tail = 0;
}

static bool report_queue_put(report_queue_t* queue, report_item_t* item)
{
    if (report_queue_full(queue)) {
        return false;
    }
    queue->items[queue->tail] = *item;
    queue->tail = (queue->tail + 1) % QUEUE_SIZE;
    return true;
}

static report_item_t* report_queue_get(report_queue_t* queue)
{
    report_item_t *item = NULL;
    if (!report_queue_empty(queue)) {
        item = &queue->items[queue->head];
        queue->head = (queue->head + 1) % QUEUE_SIZE;
    }
    return item;
}

// uart communication definitions
#define CONFIG_USER_START 0x0800FC00
#define CONFIG_USER_SIZE 0x00000400
#define CONFIG_JUMP_TO_APP_OFFSET 0x09
#define CMD_MAX_LEN 64
#define SYNC_BYTE_1 0xAA
#define SYNC_BYTE_2 0x55
#define RECV_DELAY 100

static void process_data(uint8_t d);
static void enqueue_command(uint8_t *cmd);
static void process_command(report_item_t *item);
static uint8_t compute_checksum(uint8_t *data, uint32_t size);
static void clear_jump_to_app(void);

static void rxerr(UARTDriver *uartp, uartflags_t e)
{
    (void)uartp;
    (void)e;
    SEGGER_RTT_printf(0, "rxerror");
}

static void rxchar(UARTDriver *uartp, uint16_t c)
{
    (void)uartp;
    SEGGER_RTT_printf(0, "rxchar: 0x%x", c);
    process_data((uint8_t)c);
}

static void rxend(UARTDriver *uartp)
{
    (void)uartp;
    SEGGER_RTT_printf(0, "rxend");
}

/*
 * UART driver configuration structure.
 */
static UARTConfig uart1_cfg = {
    NULL,
    NULL,
    rxend,
    rxchar,
    rxerr,
    115200,
    0,
    0,
    0,
};

typedef enum
{
  CMD_KEY_REPORT,
  CMD_MOUSE_REPORT,
  CMD_SYSTEM_REPORT,
  CMD_CONSUMER_REPORT,
  CMD_RESET_TO_BOOTLOADER,
} command_t;

static uint8_t command_buf[CMD_MAX_LEN];

static void process_data(uint8_t d)
{
    //SEGGER_RTT_printf(0, "received: %d\n", d);
    static uint32_t count = 0;
    if (count == 0 && d != SYNC_BYTE_1) {
        SEGGER_RTT_printf(0, "SYNC BYTE 1: %x\n", d);
        return;
    } else if (count == 1 && d != SYNC_BYTE_2) {
        count = 0;
        SEGGER_RTT_printf(0, "SYNC BYTE 2: %x\n", d);
        return;
    }

    command_buf[count] = d;
    count++;
    if ((count > 2) && (count == (command_buf[2] + 2))) {
        // full packet received
        enqueue_command(&command_buf[2]);
        count = 0;
    }
}

static void enqueue_command(uint8_t *cmd)
{
    SEGGER_RTT_printf(0, "Enqueue Command: %d\n", cmd[2]);
    uint8_t checksum = compute_checksum(cmd + 2, cmd[0] - 2);
    if (checksum != cmd[1]) {
        // invalid checksum
        SEGGER_RTT_printf(0, "Checksum: SRC:%x, CUR:%x\n", cmd[1], checksum);
        return;
    }

    report_item_t item;
    item.type = cmd[2];
    memcpy(&item.data[0], &cmd[3], cmd[0]-2);
    osalSysLockFromISR();
    //osalSysLock();
    report_queue_put(&report_queue, &item);
    //osalSysUnlock();
    osalSysUnlockFromISR();
}

static void process_command(report_item_t *item)
{
    switch (item->type) {
    case CMD_KEY_REPORT: {
        static report_keyboard_t report;
        SEGGER_RTT_printf(0, "Send key report\n");
        for (uint32_t i = 0; i < QUEUE_ITEM_SIZE; i++) {
            SEGGER_RTT_printf(0, " 0x%x", item->data[i]);
        }
        SEGGER_RTT_printf(0, "\n");

        memcpy(&report.raw[0], &item->data[0], sizeof(report));
        host_keyboard_send(&report);
    } break;
#ifdef MOUSE_ENABLE
    case CMD_MOUSE_REPORT: {
        static report_mouse_t report;
        SEGGER_RTT_printf(0, "Send mouse report\n");
        for (uint32_t i = 0; i < QUEUE_ITEM_SIZE; i++) {
            SEGGER_RTT_printf(0, " 0x%x", item->data[i]);
        }

        memcpy(&report, &item->data[0], sizeof(report));
        host_mouse_send(&report);
    } break;
#endif
#ifdef EXTRAKEY_ENABLE
    case CMD_SYSTEM_REPORT: {
        static uint16_t report;
        SEGGER_RTT_printf(0, "Send system report\n");
        for (uint32_t i = 0; i < QUEUE_ITEM_SIZE; i++) {
            SEGGER_RTT_printf(0, " 0x%x", item->data[i]);
        }
        memcpy(&report, &item->data[0], sizeof(report));
        host_system_send(report);

    } break;
    case CMD_CONSUMER_REPORT: {
        static uint16_t report;
        SEGGER_RTT_printf(0, "Send consumer report\n");
        for (uint32_t i = 0; i < QUEUE_ITEM_SIZE; i++) {
            SEGGER_RTT_printf(0, " 0x%x", item->data[i]);
        }
        memcpy(&report, &item->data[0], sizeof(report));
        host_consumer_send(report);
    } break;
#endif
    case CMD_RESET_TO_BOOTLOADER:
        clear_jump_to_app();
        NVIC_SystemReset();
        break;
    default:
        break;
    }
}

static uint8_t compute_checksum(uint8_t *data, uint32_t size)
{
    uint8_t checksum = 0;
    for (uint32_t i = 0; i < size; i++) {
        checksum += data[i];
    }
    return checksum;
}

static void clear_jump_to_app(void)
{
    static uint8_t buf[CONFIG_USER_SIZE];
    uint32_t i = 0;
    uint16_t *pBuf = (uint16_t *)(&(buf[0]));
    uint16_t *pSrc = (uint16_t *)(CONFIG_USER_START);
    for (i = 0; i < CONFIG_USER_SIZE / 2; i++) {
        pBuf[i] = pSrc[i];
    }
    if (buf[CONFIG_JUMP_TO_APP_OFFSET] != 0) {
        buf[CONFIG_JUMP_TO_APP_OFFSET] = 0;
        FLASH_Unlock();
        FLASH_ErasePage(CONFIG_USER_START);
    }

    for (i = 0; i < CONFIG_USER_SIZE / 2; i++) {
        FLASH_ProgramHalfWord((uint32_t)(pSrc + i), pBuf[i]);
    }
    FLASH_Lock();
}

/**
 * NRF USB, get usb report through the UART1
 */
static matrix_row_t matrix[MATRIX_ROWS];

void matrix_init(void)
{
    memset(&matrix[0], 0, sizeof(matrix));
    report_queue_init(&report_queue);
    uartStart(&UARTD1, &uart1_cfg);
}

uint8_t matrix_scan(void)
{
    osalSysLock();
    while (!report_queue_empty(&report_queue)) {
        report_item_t *item = report_queue_get(&report_queue);
        process_command(item);
    }
    osalSysUnlock();
    return 1;
}
matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }
void matrix_print(void)
{
    printf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        printf("%X0: ", row);
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col))
                printf("1");
            else
                printf("0");
        }
        printf("\n");
    }
}
