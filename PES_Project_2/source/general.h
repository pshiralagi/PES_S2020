

#define FB_RUN 1	//Non - debug program run natively on the board
//#define FB_DEBUG 1	//Debug version of FB_RUN, includes print statements
//#define PC_RUN 1	//Not run on the board, run on the PC where statements are printed to the debug console
//#define PC_DEBUG 1	//Debug version of PC_RUN with a lot more debug statements

#ifdef PC_RUN
#include <stdint.h>
#endif

#include <stdio.h>
#ifdef FB_DEBUG
#define FB_RUN
#endif
#ifdef PC_DEBUG
#define PC_RUN
#endif


#ifdef FB_RUN
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#endif

/* TODO: insert other include files here. */
#include "led.h"
#include "cap_touch.h"
#include "time.h"
/* TODO: insert other definitions and declarations here. */


