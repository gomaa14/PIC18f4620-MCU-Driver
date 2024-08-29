/* 
 * File:   hal_timer3.h
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on July 12, 2024, 10:22 AM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/************Section :: Includes***********************************/

#include "../mcal_std_types.h"

#include "pic18f4620.h"

#include "../GPIO/hal_gpio.h"

#include "../INTERRUPT/mcal_internal_interrupt.h"

/************Section :: Macro Declaration *************************/

#define TIMER3_TIMER_MODE_CFG                       0
#define TIMER3_COUNTER_MODE_CFG                     1

#define TIMER3_COUNTER_MODE_SYNCHRONIZE_CFG         0
#define TIMER3_COUNTER_MODE_NOT_SYNCHRONIZE_CFG     1


#define TIMER3_16_BIT_READ_WRITE_MODE_CFG           1
#define TIMER3_8_BIT_READ_WRITE_MODE_CFG            0


#define TIMER3_PRESCALE_DIV_BY_1					0
#define TIMER3_PRESCALE_DIV_BY_2					1
#define TIMER3_PRESCALE_DIV_BY_4					2
#define TIMER3_PRESCALE_DIV_BY_8					3



/************Section :: Macro Function Declaration ****************/

#define TIMER3_MODULE_ENABLE()                   (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE()                  (T3CONbits.TMR3ON = 0)

#define TIMER3_TIMER_MODE()                      (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE()                    (T3CONbits.TMR3CS = 1)

#define TIMER3_COUNTER_MODE_SYNCHRONIZE()        (T3CONbits.T3SYNC = 0)
#define TIMER3_COUNTER_MODE_NOT_SYNCHRONIZE()    (T3CONbits.T3SYNC = 1)

#define TIMER3_16_BIT_READ_WRITE_MODE()          (T3CONbits.RD16 = 1)
#define TIMER3_8_BIT_READ_WRITE_MODE()           (T3CONbits.RD16 = 0)


#define TIMER3_PRESCALER_CONFIGURATION(__CONFIG) 		(T3CONbits.T3CKPS = __CONFIG)



/************Section :: User Define Data Type *********************/

typedef struct 
{
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE	
	void (*timer3_intrrupt_handler) (void);
    interrupt_priority_t priority;  
#endif
	
	uint16 timer3_preload_value;
	uint8  timer3_prescaler          :2;
	uint8  timer3_mode       		 :1;
	uint8  timer3_counter_mode       :1;
	uint8  timer3_rw_mode			 :1;
	uint8  timer3_reserved           :3;
	
}timer3_t;

/************Section :: Function Prototype  *********************/


Std_ReturnType Timer3_Init(const timer3_t* _timer);

Std_ReturnType Timer3_DeInit(const timer3_t* _timer);

Std_ReturnType Timer3_Write_Value(const timer3_t* _timer, uint16 _value);

Std_ReturnType Timer3_Raed_Value(const timer3_t* _timer, uint16* _value);

#endif	/* HAL_TIMER3_H */

