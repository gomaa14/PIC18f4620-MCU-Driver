/* 
 * File:   mcal_internal_interrupt.h
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on June 19, 2024, 12:05 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H



/*******************Section :: Includes***********************************/

#include "mcal_interrupt_config.h"


/************Section :: Macro Declaration *************************/




/************Section :: Macro Function Declaration ****************/

/* ADC */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine Disable Flag for ADC conversion */
#define ADC_CONVERTER_INTERRUPT_Clear_FLAG()         (PIR1bits.ADIF = 0)
/* This routine Disable  for ADC conversion */
#define ADC_CONVERTER_INTERRUPT_DISABLE()            (PIE1bits.ADIE = 0)
/* This routine Enable for ADC conversion */
#define ADC_CONVERTER_INTERRUPT_ENABLE()             (PIE1bits.ADIE = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine ADC Converter Interrupt  High Priority */
#define ADC_CONVERTER_INTERRUPT_HIGH_PRIORITY()       (IPR1bits.ADIP = 1)
/* This routine ADC Converter Interrupt  Low Priority */
#define ADC_CONVERTER_INTERRUPT_LOW_PRIORITY()        (IPR1bits.ADIP = 0)

#endif

#endif



/* Timer0 */
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine Disable Flag for Timer0 */
#define TIMER0_INTERRUPT_Clear_FLAG()         (INTCONbits.TMR0IF = 0)
/* This routine Disable  for Timer0 */
#define TIMER0_INTERRUPT_DISABLE()            (INTCONbits.TMR0IE = 0)
/* This routine Enable for Timer0 */
#define TIMER0_INTERRUPT_ENABLE()             (INTCONbits.TMR0IE = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine Timer0 Interrupt  High Priority */
#define TIMER0_INTERRUPT_HIGH_PRIORITY()       (INTCON2bits.TMR0IP = 1)
/* This routine Timer0 Interrupt  Low Priority */
#define TIMER0_INTERRUPT_LOW_PRIORITY()        (INTCON2bits.TMR0IP = 0)

#endif

#endif





/* Timer1 */
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine Disable Flag for Timer1 */
#define TIMER1_INTERRUPT_Clear_FLAG()         (PIR1bits.TMR1IF = 0)
/* This routine Disable  for Timer1 */
#define TIMER1_INTERRUPT_DISABLE()            (PIE1bits.TMR1IE = 0)
/* This routine Enable for Timer1 */
#define TIMER1_INTERRUPT_ENABLE()             (PIE1bits.TMR1IE = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine Timer1 Interrupt  High Priority */
#define TIMER1_INTERRUPT_HIGH_PRIORITY()       (IPR1bits.TMR1IP = 1)
/* This routine Timer1 Interrupt  Low Priority */
#define TIMER1_INTERRUPT_LOW_PRIORITY()        (IPR1bits.TMR1IP = 0)

#endif

#endif




/* Timer2 */
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine Disable Flag for Timer2 */
#define TIMER2_INTERRUPT_Clear_FLAG()         (PIR1bits.TMR2IF = 0)
/* This routine Disable  for Timer2 */
#define TIMER2_INTERRUPT_DISABLE()            (PIE1bits.TMR2IE = 0)
/* This routine Enable for Timer2 */
#define TIMER2_INTERRUPT_ENABLE()             (PIE1bits.TMR2IE = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine Timer2 Interrupt  High Priority */
#define TIMER2_INTERRUPT_HIGH_PRIORITY()       (IPR1bits.TMR2IP = 1)
/* This routine Timer2 Interrupt  Low Priority */
#define TIMER2_INTERRUPT_LOW_PRIORITY()        (IPR1bits.TMR2IP = 0)

#endif

#endif



/* Timer3 */
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine Disable Flag for Timer3 */
#define TIMER3_INTERRUPT_Clear_FLAG()         (PIR2bits.TMR3IF = 0)
/* This routine Disable  for Timer3 */
#define TIMER3_INTERRUPT_DISABLE()            (PIE2bits.TMR3IE = 0)
/* This routine Enable for Timer3 */
#define TIMER3_INTERRUPT_ENABLE()             (PIE2bits.TMR3IE = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine Timer3 Interrupt  High Priority */
#define TIMER3_INTERRUPT_HIGH_PRIORITY()       (IPR2bits.TMR3IP = 1)
/* This routine Timer3 Interrupt  Low Priority */
#define TIMER3_INTERRUPT_LOW_PRIORITY()        (IPR2bits.TMR3IP = 0)

#endif

#endif




/* CCP1 */
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine Disable Flag for CCP1 */
#define CCP1_INTERRUPT_Clear_FLAG()         (PIR1bits.CCP1IF = 0)
/* This routine Disable  for CCP1 */
#define CCP1_INTERRUPT_DISABLE()            (PIE1bits.CCP1IE = 0)
/* This routine Enable for CCP1 */
#define CCP1_INTERRUPT_ENABLE()             (PIE1bits.CCP1IE = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine CCP1 Interrupt  High Priority */
#define CCP1_INTERRUPT_HIGH_PRIORITY()       (IPR1bits.CCP1IP = 1)
/* This routine CCP1 Interrupt  Low Priority */
#define CCP1_INTERRUPT_LOW_PRIORITY()        (IPR1bits.CCP1IP = 0)

#endif

#endif


/* CCP2 */
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine Disable Flag for CCP2 */
#define CCP2_INTERRUPT_Clear_FLAG()         (PIR2bits.CCP2IF = 0)
/* This routine Disable  for CCP2 */
#define CCP2_INTERRUPT_DISABLE()            (PIE2bits.CCP2IE = 0)
/* This routine Enable for CCP2 */
#define CCP2_INTERRUPT_ENABLE()             (PIE2bits.CCP2IE = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine CCP2 Interrupt  High Priority */
#define CCP2_INTERRUPT_HIGH_PRIORITY()       (IPR2bits.CCP2IP = 1)
/* This routine CCP2 Interrupt  Low Priority */
#define CCP2_INTERRUPT_LOW_PRIORITY()        (IPR2bits.CCP2IP = 0)

#endif

#endif




/* TX */
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine Disable  for EUSART TX */
#define EUSART_TX_INTERRUPT_DISABLE()                (PIE1bits.TXIE = 0)
/* This routine Enable for EUSART TX */
#define EUSART_TX_INTERRUPT_ENABLE()                 (PIE1bits.TXIE = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine EUSART TX Interrupt  High Priority */
#define EUSART_TX_INTERRUPT_HIGH_PRIORITY()       (IPR1bits.TXIP = 1)
/* This routine EUSART TX Interrupt  Low Priority */
#define EUSART_TX_INTERRUPT_LOW_PRIORITY()        (IPR1bits.TXIP = 0)

#endif

#endif




/* RX */
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine Disable  for EUSART TX */
#define EUSART_RX_INTERRUPT_DISABLE()                (PIE1bits.RCIE = 0)
/* This routine Enable for EUSART TX */
#define EUSART_RX_INTERRUPT_ENABLE()                 (PIE1bits.RCIE = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine EUSART RX Interrupt  High Priority */
#define EUSART_RX_INTERRUPT_HIGH_PRIORITY()       (IPR1bits.RCIP = 1)
/* This routine EUSART RX Interrupt  Low Priority */
#define EUSART_RX_INTERRUPT_LOW_PRIORITY()        (IPR1bits.RCIP = 0)

#endif

#endif



/* MSSP */
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine Disable Flag for MSSP I2C */
#define MSSP_I2C_INTERRUPT_Clear_FLAG()          (PIR1bits.SSPIF = 0)
/* This routine Disable Flag for Bus Collision  */
#define MSSP_I2C_BUS_COL_INTERRUPT_Clear_FLAG()          (PIR2bits.BCLIF = 0)

/* This routine Disable  for MSSP I2C */
#define MSSP_I2C_INTERRUPT_DISABLE()             (PIE1bits.SSPIE = 0)
/* This routine Disable  for Bus Collision   */
#define MSSP_I2C_BUS_COL_INTERRUPT_DISABLE()             (PIE2bits.BCLIE = 0)

/* This routine Enable for MSSP I2C */
#define MMSSP_I2C_INTERRUPT_ENABLE()             (PIE1bits.SSPIE = 1)
/* This routine Enable for Bus Collision   */
#define MMSSP_I2C_BUS_COL_INTERRUPT_ENABLE()             (PIE2bits.BCLIE = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine MSSP I2C Interrupt  High Priority */
#define MSSP_I2C_INTERRUPT_HIGH_PRIORITY()       (IPR1bits.SSPIP = 1)
/* This routine Bus Collision Interrupt  High Priority */
#define MSSP_I2C_BUS_COL_INTERRUPT_HIGH_PRIORITY()       (IPR2bits.BCLIP = 1)

/* This routine MSSP I2C Interrupt  Low Priority */
#define MSSP_I2C_INTERRUPT_LOW_PRIORITY()        (IPR1bits.SSPIP = 0)
/* This routine Bus Collision Interrupt  Low Priority */
#define MSSP_I2C_BUS_COL_INTERRUPT_LOW_PRIORITY()        (IPR2bits.BCLIP = 0)


#endif

#endif



/************Section :: User Define Data Type *********************/



/************Section :: Function Prototype  *********************/




#endif	/* MCAL_INTERNAL_INTERRUPT_H */

