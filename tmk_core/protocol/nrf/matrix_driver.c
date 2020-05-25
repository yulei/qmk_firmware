/**
 * matrix_driver.c
 * default matrix implementation
 */

#include "matrix_driver.h"


#if defined(MATRIX_USE_GPIO)
typedef void (*matrix_trigger_start_f)(void);
typedef void (*matrix_trigger_stop_f)(void);

typedef void (*matrix_scan_start_f)(void);
typedef void (*matrix_scan_stop_f)(void);

typedef void (*matrix_scan_init_f)(void);
typedef void (*matrix_scan_task_f)(void);

typedef struct {
    matrix_trigger_start_f  trigger_start;
    matrix_trigger_stop_f   trigger_stop;
    matrix_scan_start_f     scan_start;
    matrix_scan_stop_f      scan_stop;
    matrix_scan_init_f      scan_init;
    matrix_scan_task_f      scan_task;
} matrix_driver_t;

#elif defined(MATRIX_USE_TC6424)

#else
// custom implementation

#endif
extern matrix_driver_t matrix_driver;
