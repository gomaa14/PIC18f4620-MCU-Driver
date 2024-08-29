/* 
 * File:   mcal_interrupt_config.h
 * 
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on June 19, 2024, 11:58 AM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/*******************Section :: Includes***********************************/

#include "pic18f4620.h"

#include "../mcal_std_types.h"

#include "../GPIO/hal_gpio.h"


#include "mcal_interrupt_gen_cfg.h"


/************Section :: Macro Declaration *************************/

#define INTERRUPT_ENABLE      1
#define INTERRUPT_DISABLE     0

#define INTERRUPT_OCCUR       1
#define INTERRUPT_NOT_OCCUR   0

#define INTERRUPT_PRIORITY_ENABLE  1
#define INTERRUPT_PRIORITY_DISABLE 0


/************Section :: Macro Function Declaration ****************/

/* This Macro Will Enable Priority Interrupt */
#define Interrupt_Priority_Level_Enable()  (RCONbits.IPEN = 1)

/* This Macro Will Disable Priority Interrupt */
#define Interrupt_Priority_Level_Disable() (RCONbits.IPEN = 0)


#if INTERRUPT_PRIORITY_LEVELS_ENABLE  == INTERRUPT_FEATURE_ENABLE

/* This Macro Will Enable High Priority Global Interrupt */
#define INTERRUPT_GlobalInterruptEnableHigh()   (INTCONbits.GIEH =1)
/* This Macro Will Disable High Priority Global Interrupt */
#define INTERRUPT_GlobalInterruptDisableHigh()  (INTCONbits.GIEH =0)

/* This Macro Will Enable Low Priority Global Interrupt */
#define INTERRUPT_GlobalInterruptEnableLOW()    (INTCONbits.GIEL =1)

/* This Macro Will Disable Low Priority Global Interrupt */
#define INTERRUPT_GlobalInterruptDisableLOW()   (INTCONbits.GIEL =0)



#else


/* This Macro Will Enable High Global Interrupt*/
#define INTERRUPT_GlobalInterruptEnable()        (INTCONbits.GIE  =1)

/* This Macro Will Disable High Global Interrupt*/
#define INTERRUPT_GlobalInterruptDisable()       (INTCONbits.GIE  =0)

/* This Macro Will Enable Peripheral Global Interrupt*/
#define INTERRUPT_PeripheralInterruptEnable()    (INTCONbits.PEIE =1)

/* This Macro Will Disable Peripheral Global Interrupt*/
#define INTERRUPT_peripheralInterruptDisable()   (INTCONbits.PEIE =0)


#endif


/************Section :: User Define Data Type *********************/

typedef enum
{
	INTERRUPT_LOW_PRIORITY,
	INTERRUPT_HIGH_PRIORITY
}interrupt_priority_t;

/************Section :: Function Prototype  *********************/



#endif	/* MCAL_INTERRUPT_CONFIG_H */

