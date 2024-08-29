/* 
 * File:   mcal_external_interrupt.h
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on June 19, 2024, 12:03 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H


/*******************Section :: Includes***********************************/

#include "mcal_interrupt_config.h"



/************Section :: Macro Declaration *************************/



/************Section :: Macro Function Declaration ****************/


#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

                         /* INT0 */
/* This Macro Will Enable INT0 External Interrupt  */
#define INT0_External_Interrupt_Enable()       (INTCONbits.INT0IE = 1)

/* This Macro Will Disable INT0 External Interrupt  */
#define INT0_External_Interrupt_Disable()      (INTCONbits.INT0IE = 0)

/* This Macro Will Clear Flag For INT0 External Interrupt  */
#define INT0_External_Interrupt_Flag_Clear()  (INTCONbits.INT0IF = 0)

/* This Macro Will Select The Rising Edge For  INT0 External Interrupt  */
#define  External_Interrupt_0_Rising_Edge_Select()    (INTCON2bits.INTEDG0 = 1) 

/* This Macro Will Select The Falling Edge For  INT0 External Interrupt  */
#define  External_Interrupt_0_Falling_Edge_Select()   (INTCON2bits.INTEDG0 = 0) 

                             /* INT1*/


/* This Macro Will Enable INT1 External Interrupt  */
#define INT1_External_Interrupt_Enable() (INTCON3bits.INT1IE = 1)

/* This Macro Will Disable INT1 External Interrupt  */
#define INT1_External_Interrupt_Disable() (INTCON3bits.INT1IE = 0)


/* This Macro Will Clear Flag For INT1 External Interrupt  */
#define INT1_External_Interrupt_Flag_Clear()  (INTCON3bits.INT1IF = 0)



/* This Macro Will Select The Rising Edge For  INT1 External Interrupt  */
#define  External_Interrupt_1_Rising_Edge_Select()   (INTCON2bits.INTEDG1 = 1) 

/* This Macro Will Select The Falling Edge For  INT1 External Interrupt  */
#define  External_Interrupt_1_Falling_Edge_Select()   (INTCON2bits.INTEDG1 = 0)


                                   /* INT2 */


/* This Macro Will Enable INT2 External Interrupt  */
#define INT2_External_Interrupt_Enable()   (INTCON3bits.INT2IE = 1)

/* This Macro Will Disable INT2 External Interrupt  */
#define INT2_External_Interrupt_Disable()   (INTCON3bits.INT2IE = 0)



/* This Macro Will Clear Flag For INT2 External Interrupt  */
#define INT2_External_Interrupt_Flag_Clear()    (INTCON3bits.INT2IF = 0)


/* This Macro Will Select The Rising Edge For  INT2 External Interrupt  */
#define  External_Interrupt_2_Rising_Edge_Select()  (INTCON2bits.INTEDG2 = 1)

/* This Macro Will Select The Falling Edge For  INT2 External Interrupt  */
#define  External_Interrupt_2_Falling_Edge_Select()  (INTCON2bits.INTEDG2 = 0)



#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

                  /* INT1*/
/* This Macro Will Select High Priority for  INT1 External Interrupt  */
#define  INT1_External_Interrupt_High_Priority() (INTCON3bits.INT1IP = 1)

/* This Macro Will Select Low Priority for  INT1 External Interrupt  */
#define  INT1_External_Interrupt_Low_Priority()  (INTCON3bits.INT1IP = 0)
			  
                  /* INT2*/

/* This Macro Will Select High Priority for  INT2 External Interrupt  */
#define  INT2_External_Interrupt_High_Priority()   (INTCON3bits.INT2IP = 1)


/* This Macro Will Select Low Priority for  INT2 External Interrupt  */
#define  INT2_External_Interrupt_Low_Priority()    (INTCON3bits.INT2IP = 0)  

#endif

#endif


#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This Macro Will Enable RB Port Change External Interrupt  */
#define  RB_Port_Change_Interrupt_Enable()       (INTCONbits.RBIE = 1)

/* This Macro Will Disable RB Port Change External Interrupt  */
#define RB_Port_Change_Interrupt_Disable()      (INTCONbits.RBIE = 0)

/* This Macro Will Clear Flag For RB Port Change External Interrupt  */
#define  RB_Port_Change_Interrupt_Flag_Clear()  (INTCONbits.RBIF = 0)


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This Macro Will Select High Priority for  RB Port Change External Interrupt  */
#define   RB_Port_Change_Interrupt_High_Priority()   (INTCON2bits.RBIP = 1)


/* This Macro Will Select Low Priority for  RB Port Change External Interrupt  */
#define  RB_Port_Change_Interrupt_LOw_Priority()     (INTCON2bits.RBIP = 0) 


#endif


#endif

/************Section :: User Define Data Type *********************/


typedef void (* InterruptHandler) (void);


typedef enum
{
	INTERRUT_INT0,
	INTERRUT_INT1,
	INTERRUT_INT2
}INTx_src_t;

typedef enum
{
	INTERRUT_FALLING_EDGE,
	INTERRUT_RISING_EDGE
}INTx_edge_t;


typedef struct 
{
	void (* Eternal_InterruptHandler)(void);
	pin_config_t mcu_pin;
	INTx_src_t  source ;
	INTx_edge_t edge ;
	interrupt_priority_t priority;	
	
}INTx_interrupt_t;

typedef struct 
{
	void (* Eternal_InterruptHandler_High)(void);
	void (* Eternal_InterruptHandler_Low)(void);
	pin_config_t mcu_pin;
	interrupt_priority_t priority;	
	
}RBx_interrupt_t;

/************Section :: Function Prototype  *********************/

Std_ReturnType Initialize_INTx_interrupt(const INTx_interrupt_t* int_obj);

Std_ReturnType Deinitialize_INTx_interrupt(const INTx_interrupt_t* int_obj);




Std_ReturnType Initialize_RBx_interrupt(const RBx_interrupt_t* int_obj);

Std_ReturnType Deinitialize_RBx_interrupt(const RBx_interrupt_t* int_obj);




#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

