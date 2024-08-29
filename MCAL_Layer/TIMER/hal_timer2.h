/* 
 * File:   hal_timer2.h
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on July 12, 2024, 5:18 AM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/************Section :: Includes***********************************/

#include "../mcal_std_types.h"

#include "pic18f4620.h"

#include "../GPIO/hal_gpio.h"

#include "../INTERRUPT/mcal_internal_interrupt.h"

/************Section :: Macro Declaration *************************/

/* Pre-scaler */
#define TIMER2_PRESCALE_DIV_BY_1				0
#define TIMER2_PRESCALE_DIV_BY_4				1
#define TIMER2_PRESCALE_DIV_BY_16				2

/* Post-scaler*/
#define TIMER2_POSTSCALE_DIV_BY_1				0
#define TIMER2_POSTSCALE_DIV_BY_2				1
#define TIMER2_POSTSCALE_DIV_BY_3				2
#define TIMER2_POSTSCALE_DIV_BY_4				3
#define TIMER2_POSTSCALE_DIV_BY_5				4
#define TIMER2_POSTSCALE_DIV_BY_6				5
#define TIMER2_POSTSCALE_DIV_BY_7				6
#define TIMER2_POSTSCALE_DIV_BY_8				7
#define TIMER2_POSTSCALE_DIV_BY_9				8
#define TIMER2_POSTSCALE_DIV_BY_10				9
#define TIMER2_POSTSCALE_DIV_BY_11				10
#define TIMER2_POSTSCALE_DIV_BY_12				11
#define TIMER2_POSTSCALE_DIV_BY_13				12
#define TIMER2_POSTSCALE_DIV_BY_14				13
#define TIMER2_POSTSCALE_DIV_BY_15				14
#define TIMER2_POSTSCALE_DIV_BY_16				15


/*Enable and Disable */

#define TIMER2_MODULE_ENABLE_CFG				1
#define TIMER2_MODULE_DISABLE_CFG				0


/************Section :: Macro Function Declaration ****************/


#define  TIMER2_CLOCK_PRESCALE_SELECT(__CONFIG) (T2CONbits.T2CKPS = __CONFIG)

#define TIMER2_MODULE_ENABLE()                   (T2CONbits.TMR2ON = 1)
#define TIMER2_MODULE_DISABLE()                  (T2CONbits.TMR2ON = 0)

#define  TIMER2_OUTPUT_POSTSCALE_SELECT(__CONFIG) (T2CONbits.TOUTPS = __CONFIG)



/************Section :: User Define Data Type *********************/

typedef struct 
{
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE	
	void (*timer2_intrrupt_handler) (void);
    interrupt_priority_t priority;  
#endif
	uint8 timer2_preload_value;
	uint8 timer2_prescaler  :2;
	uint8 timer2_postscaler :4;
	uint8 timer2_reserved   :2;
	
}timer2_t;

/************Section :: Function Prototype  *********************/


Std_ReturnType Timer2_Init(const timer2_t* _timer);

Std_ReturnType Timer2_DeInit(const timer2_t* _timer);

Std_ReturnType Timer2_Write_Value(const timer2_t* _timer, uint8 _value);

Std_ReturnType Timer2_Raed_Value(const timer2_t* _timer, uint8* _value);



#endif	/* HAL_TIMER2_H */

