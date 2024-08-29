/* 
 * File:   hal_timer0.h
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on July 8, 2024, 5:21 AM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H


/************Section :: Includes***********************************/

#include "../mcal_std_types.h"

#include "pic18f4620.h"

#include "../GPIO/hal_gpio.h"

#include "../INTERRUPT/mcal_internal_interrupt.h"


/************Section :: Macro Declaration *************************/



#define TIMER0_ENABLE_PRESCALER_CFG         1
#define TIMER0_DISABLE_PRESCALER_CFG        0

#define TIMER0_RISING_EDGE_CFG              1
#define TIMER0_FALLING_EDGE_CFG             0

#define TIMER0_TIMER_MODE_CFG               1
#define TIMER0_COUNTER_MODE_CFG             0

#define TIMER0_8_BIT_REGISTER_MODE          1
#define TIMER0_16_BIT_REGISTER_MODE         0



/************Section :: Macro Function Declaration ****************/

#define TIMER0_MODULE_ENABLE()		    	(T0CONbits.TMR0ON = 1)
#define TIMER0_MODULE_DISABLE()				(T0CONbits.TMR0ON = 0)

#define TIMER0_CONFIGURE_8_BIT()			(T0CONbits.T08BIT = 1)
#define TIMER0_CONFIGURE_16_BIT()    		(T0CONbits.T08BIT = 0)

#define TIMER0_TIMER_MODE_SOURCE()		    (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_SOURCE()		(T0CONbits.T0CS = 1)

#define TIMER0_RISING_EDGE_SELECT()			(T0CONbits.T0SE = 0)
#define TIMER0_FALLING_EDGE_SELECT()		(T0CONbits.T0SE = 1)


#define TIMER0_PRESCALER_ENABLE()			(T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()			(T0CONbits.PSA = 1)


#define TIMER0_PRESCALER_CONFIGURATION(__CONFG) (T0CONbits.T0PS = __CONFG)

/************Section :: User Define Data Type *********************/

typedef enum
{
	TIMER0_PRESCALE_DIV_BY_2 = 0,
	TIMER0_PRESCALE_DIV_BY_4,
	TIMER0_PRESCALE_DIV_BY_8,
	TIMER0_PRESCALE_DIV_BY_16,
	TIMER0_PRESCALE_DIV_BY_32,
	TIMER0_PRESCALE_DIV_BY_64,
	TIMER0_PRESCALE_DIV_BY_128,
	TIMER0_PRESCALE_DIV_BY_256
	
}Timer0_Prescaler_Select_t;

typedef struct 
{
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*timer0_intrrupt_handler) (void);
    interrupt_priority_t priority;     
#endif
    uint16 timer0_preload_value;
    uint8  timer0_register_size      :1;
    uint8  timer0_mode               :1;
    uint8  counter_edge_select       :1;
    uint8  timer0_Prescaler_Enable   :1;
    uint8  timer0_Reserved           :4;
    Timer0_Prescaler_Select_t Prescaler_Value;
    
}timer0_t;

/************Section :: Function Prototype  *********************/


Std_ReturnType Timer0_Init(const timer0_t* _timer);

Std_ReturnType Timer0_DeInit(const timer0_t* _timer);

Std_ReturnType Timer0_Write_Value(const timer0_t* _timer, uint16 _value);

Std_ReturnType Timer0_Raed_Value(const timer0_t* _timer, uint16* _value);




#endif	/* HAL_TIMER0_H */

