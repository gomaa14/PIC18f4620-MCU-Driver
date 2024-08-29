/* 
 * File:   hal_timer1.h
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on July 9, 2024, 3:12 AM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H


/************Section :: Includes***********************************/

#include "../mcal_std_types.h"

#include "pic18f4620.h"

#include "../GPIO/hal_gpio.h"

#include "../INTERRUPT/mcal_internal_interrupt.h"


/************Section :: Macro Declaration *************************/

#define TIMER1_TIMER_MODE_CFG                      0
#define TIMER1_COUNTER_MODE_CFG                    1

#define TIMER1_COUNTER_MODE_SYNCHRONIZE_CFG         0
#define TIMER1_COUNTER_MODE_NOT_SYNCHRONIZE_CFG     1


#define TIMER1_OSCILLATOR_IS_ENABLED_CFG            1
#define TIMER1_OSCILLATOR_IS_DISABLED_CFG           0


#define TIMER1_16_BIT_READ_WRITE_MODE_CFG           1
#define TIMER1_8_BIT_READ_WRITE_MODE_CFG            0

/************Section :: Macro Function Declaration ****************/

#define TIMER1_MODULE_ENABLE()                   (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()                  (T1CONbits.TMR1ON = 0)

#define TIMER1_TIMER_MODE()                      (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE()                    (T1CONbits.TMR1CS = 1)

#define TIMER1_COUNTER_MODE_SYNCHRONIZE()        (T1CONbits.T1SYNC = 0)
#define TIMER1_COUNTER_MODE_NOT_SYNCHRONIZE()    (T1CONbits.T1SYNC = 1)

#define TIMER1_OSCILLATOR_IS_ENABLED()           (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSCILLATOR_IS_SHUT_OFF()          (T1CONbits.T1OSCEN = 0)

#define TIMER1_SYSTEM_CLOCK_STATUS()             (T1CONbits.T1RUN)

#define TIMER1_16_BIT_READ_WRITE_MODE()          (T1CONbits.RD16 = 1)
#define TIMER1_8_BIT_READ_WRITE_MODE()           (T1CONbits.RD16 = 0)

#define TIMER1_PRESCALER_CONFIGURATION(__CONFIG) (T1CONbits.T1CKPS = __CONFIG)

/************Section :: User Define Data Type *********************/

typedef enum
{
    TIMER1_PRESCALE_DIV_BY_1 = 0,
    TIMER1_PRESCALE_DIV_BY_2,
    TIMER1_PRESCALE_DIV_BY_4,
    TIMER1_PRESCALE_DIV_BY_8
    
}Timer1_Prescaler_Select_t;


typedef struct 
{
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE	
	void (*timer1_intrrupt_handler) (void);
    interrupt_priority_t priority;  
#endif
	
	uint16 timer1_preload_value;
	uint8  timer1_mode       		 :1;
	uint8  timer1_counter_mode       :1;
	uint8  timer1_osc_config         :1;
	uint8  timer1_rw_mode			 :1;
	uint8  timer1_reserved           :4;
	Timer1_Prescaler_Select_t timer1_prescaler;
	
}timer1_t;


/************Section :: Function Prototype  *********************/

Std_ReturnType Timer1_Init(const timer1_t* _timer);

Std_ReturnType Timer1_DeInit(const timer1_t* _timer);

Std_ReturnType Timer1_Write_Value(const timer1_t* _timer, uint16 _value);

Std_ReturnType Timer1_Raed_Value(const timer1_t* _timer, uint16* _value);

#endif	/* HAL_TIMER1_H */

