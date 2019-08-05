/**
 * flash_stm32f4.c
 */

#if defined(EEPROM_EMU_STM32F411xE)
    #define STM32F411xE
    #include "stm32f4xx.h"
#else
    #error "not implemented."
#endif

#include "flash_stm32f4.h"

/* Delay definition */
#define EraseTimeout        ((uint32_t)0x00000FFF)
#define ProgramTimeout      ((uint32_t)0x0000001F)

#define FLASH_PSIZE_BYTE    0
#define FLASH_PSIZE_WORD    FLASH_CR_PSIZE_1
#define FLASH_CR_SNB_Pos    3
#define FLASH_KEY1          0x45670123
#define FLASH_KEY2          0xCDEF89AB

#define ASSERT(exp) (void)((0))

/**
  * @brief  Inserts a time delay.
  * @param  None
  * @retval None
  */
static void delay(void)
{
    __IO uint32_t i = 0;
    for(i = 0xFF; i != 0; i--) { }
}

/**
  * @brief  Returns the FLASH Status.
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
  *   FLASH_ERROR_WRP or FLASH_COMPLETE
  */
FLASH_Status FLASH_GetStatus(void)
{
    if ((FLASH->SR & FLASH_SR_BSY) == FLASH_SR_BSY)
        return FLASH_BUSY;

    if ((FLASH->SR & (FLASH_SR_PGSERR|FLASH_SR_PGPERR|FLASH_SR_PGAERR)) != 0)
        return FLASH_ERROR_PG;

    if ((FLASH->SR & FLASH_SR_WRPERR) != 0 )
        return FLASH_ERROR_WRP;

    if ((FLASH->SR & FLASH_SR_SOP) != 0 )
        return FLASH_ERROR_OPT;

    return FLASH_COMPLETE;
}

/**
  * @brief  Waits for a Flash operation to complete or a TIMEOUT to occur.
  * @param  Timeout: FLASH progamming Timeout
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *   FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout)
{
    FLASH_Status status;

    /* Check for the Flash Status */
    status = FLASH_GetStatus();
    /* Wait for a Flash operation to complete or a TIMEOUT to occur */
    while ((status == FLASH_BUSY) && (Timeout != 0x00))
    {
        delay();
        status = FLASH_GetStatus();
        Timeout--;
    }
    if (Timeout == 0)
        status = FLASH_TIMEOUT;
    /* Return the operation status */
    return status;
}

/**
  * @brief  Erases a specified FLASH page.
  * @param  Sector: The sector index to be erased.
  * @retval FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
  *   FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ErasePage(uint32_t Sector)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    ASSERT(IS_FLASH_SECTOR(Sector));
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    if(status == FLASH_COMPLETE)
    {
        /* if the previous operation is completed, proceed to erase the page */
        CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
        FLASH->CR |= FLASH_PSIZE_WORD;
        CLEAR_BIT(FLASH->CR, FLASH_CR_SNB);
        FLASH->CR |= FLASH_CR_SER | (Sector << FLASH_CR_SNB_Pos);
        FLASH->CR |= FLASH_CR_STRT;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(EraseTimeout);
        if(status != FLASH_TIMEOUT)
        {
            /* if the erase operation is completed, disable the PER Bit */
            FLASH->CR &= ~FLASH_CR_SNB;
            FLASH->CR &= ~FLASH_CR_SER;
        }

        FLASH->SR = (FLASH_SR_EOP | FLASH_SR_SOP | FLASH_SR_WRPERR);
    }
    /* Return the Erase Status */
    return status;
}

/**
  * @brief  Programs byte at a specified address.
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *   FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ProgramByte(uint32_t Address, uint8_t Data)
{
    FLASH_Status status = FLASH_BAD_ADDRESS;

    if (IS_FLASH_ADDRESS(Address))
    {
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);
        if(status == FLASH_COMPLETE)
        {
            // set size to byte
            FLASH->CR &= ~FLASH_CR_PSIZE;
            FLASH->CR |= FLASH_PSIZE_BYTE;
            FLASH->CR |= FLASH_CR_PG;

            *(__IO uint8_t*)Address = Data;
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(ProgramTimeout);
            if(status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the PG Bit */
                FLASH->CR &= ~FLASH_CR_PG;
            }
            FLASH->SR = (FLASH_SR_EOP | FLASH_SR_SOP | FLASH_SR_PGSERR | FLASH_SR_PGPERR | FLASH_SR_PGAERR | FLASH_SR_WRPERR);
        }
    }
    return status;
}

FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
    FLASH_Status status = FLASH_BAD_ADDRESS;

    if (IS_FLASH_ADDRESS(Address))
    {
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);
        if(status == FLASH_COMPLETE)
        {
            // set size to word
            FLASH->CR &= ~FLASH_CR_PSIZE;
            FLASH->CR |= FLASH_PSIZE_WORD;
            FLASH->CR |= FLASH_CR_PG;

            *(__IO uint32_t*)Address = Data;
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(ProgramTimeout);
            if(status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the PG Bit */
                FLASH->CR &= ~FLASH_CR_PG;
            }
            FLASH->SR = (FLASH_SR_EOP | FLASH_SR_SOP | FLASH_SR_PGSERR | FLASH_SR_PGPERR | FLASH_SR_PGAERR | FLASH_SR_WRPERR);
        }
    }
    return status;
}

/**
  * @brief  Unlocks the FLASH Program Erase Controller.
  * @param  None
  * @retval None
  */
void FLASH_Unlock(void)
{
    /* Authorize the FPEC Access */
    if ((FLASH->CR & FLASH_CR_LOCK) != 0)
    {
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
    }
}

/**
  * @brief  Locks the FLASH Program Erase Controller.
  * @param  None
  * @retval None
  */
void FLASH_Lock(void)
{
    /* Set the Lock Bit to lock the FPEC and the FCR */
    FLASH->CR |= FLASH_CR_LOCK;
}

/**
  * @brief  Clears the FLASH's pending flags.
  * @param  FLASH_FLAG: specifies the FLASH flags to clear.
  *   This parameter can be any combination of the following values:
  *     @arg FLASH_FLAG_PGERR: FLASH Programming error flag flag
  *     @arg FLASH_FLAG_WRPERR: FLASH Write protected error flag
  *     @arg FLASH_FLAG_EOP: FLASH End of Programming flag
  * @retval None
  */
void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
    /* Clear the flags */
    FLASH->SR = FLASH_FLAG;
}
