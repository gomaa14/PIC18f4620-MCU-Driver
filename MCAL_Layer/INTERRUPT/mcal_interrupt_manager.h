/* 
 * File:   mcal_interrupt_manager.h
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on June 19, 2024, 12:00 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H


/*******************Section :: Includes***********************************/

#include "mcal_interrupt_config.h"




/************Section :: Macro Declaration *************************/



/************Section :: Macro Function Declaration ****************/


/************Section :: User Define Data Type *********************/



/************Section :: Function Prototype  *********************/

void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR_HIGH(void);
void RB4_ISR_LOW(void);

void RB5_ISR_HIGH(void);
void RB5_ISR_LOW(void);

void RB6_ISR_HIGH(void);
void RB6_ISR_LOW(void);

void RB7_ISR_HIGH(void);
void RB7_ISR_LOW(void);

void ADC_ISR(void);

void Timer0_ISR(void);
void Timer1_ISR(void);
void Timer2_ISR(void);
void Timer3_ISR(void);

void CCP1_ISR(void);
void CCP2_ISR(void);

void EUSART_RX_ISR(void);
void EUSART_TX_ISR(void);


void MSSP_I2C_ISR(void);
void MSSP_I2C_BC_ISR(void);



#endif	/* MCAL_INTERRUPT_MANAGER_H */

