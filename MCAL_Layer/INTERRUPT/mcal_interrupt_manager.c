/* 
 * File:   mcal_interrupt_manager.c
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on June 19, 2024, 12:00 PM
 */

#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_FLAG = 1;
static volatile uint8 RB5_FLAG = 1;
static volatile uint8 RB6_FLAG = 1;
static volatile uint8 RB7_FLAG = 1;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 

void __interrupt() InterruptMangerHighPriority(void)
{
    if ( (INTERRUPT_ENABLE == INTCONbits.INT0IE ) && (INTERRUPT_OCCUR == INTCONbits.INT0IF) )
    {
        INT0_ISR();
    }
    else
    {
        /* Nothing */
    }
	
	if ( (INTERRUPT_ENABLE == INTCON3bits.INT2IE ) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF) )
    {
        INT2_ISR();
    }
    else
    {
        /* Nothing */
    }
	
}

void __interrupt(low_priority) InterruptMangerLowPriority(void)
{
    if ( (INTERRUPT_ENABLE == INTCON3bits.INT1IE ) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF) )
    {
        INT1_ISR();
    }
    else
    {
        /* Nothing */
    }
	
}
#else

void __interrupt() InterruptMangerHighPriority(void)
{
    /* INT0*/
	
    if ( (INTERRUPT_ENABLE == INTCONbits.INT0IE ) && (INTERRUPT_OCCUR == INTCONbits.INT0IF) )
    {
        INT0_ISR();
    }
    else { /* Nothing */}
	
	
    /* INT1*/ 
    
    if ( (INTERRUPT_ENABLE == INTCON3bits.INT1IE ) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF) )
    {
        INT1_ISR();
    }
    else { /* Nothing */}
    
	
	
    /* INT2*/   
    
    if ( (INTERRUPT_ENABLE == INTCON3bits.INT2IE ) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF) )
    {
        INT2_ISR();
    }
    else { /* Nothing */}
	

    /* RB4*/ 
	
	if ( (INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF )
		&& (PORTBbits.RB4 == HIGH) && (RB4_FLAG == 1) )
    {
		RB4_FLAG = 0;
		
        RB4_ISR_HIGH();
        
    }
    else { /* Nothing */}
    
    if ( (INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF )
		&& (PORTBbits.RB4 == LOW) && (RB4_FLAG == 0))
    {
		RB4_FLAG = 1;
		
        RB4_ISR_LOW();
        
    }
    else { /* Nothing */}
	
	
	/* RB5*/ 
	
	if ( (INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF )
		&& (PORTBbits.RB5 == HIGH) && (RB5_FLAG == 1) )
    {
		RB5_FLAG = 0;
		
        RB5_ISR_HIGH();
        
    }
    else { /* Nothing */}
    
    if ( (INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF )
		&& (PORTBbits.RB5 == LOW) && (RB5_FLAG == 0))
    {
		RB5_FLAG = 1;
		
        RB5_ISR_LOW();
        
    }
    else { /* Nothing */}
	
	
	
	/* RB6*/ 
	
	if ( (INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF )
		&& (PORTBbits.RB6 == HIGH) && (RB6_FLAG == 1) )
    {
		RB6_FLAG = 0;
		
        RB6_ISR_HIGH();
        
    }
    else { /* Nothing */}
    
    if ( (INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF )
		&& (PORTBbits.RB6 == LOW) && (RB6_FLAG == 0))
    {
		RB6_FLAG = 1;
		
        RB6_ISR_LOW();
        
    }
    else { /* Nothing */}
	
	/* RB7*/ 
	
	if ( (INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF )
		&& (PORTBbits.RB7 == HIGH) && (RB7_FLAG == 1) )
    {
		RB7_FLAG = 0;
		
        RB7_ISR_HIGH();
        
    }
    else { /* Nothing */}
    
    if ( (INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF )
		&& (PORTBbits.RB7 == LOW) && (RB7_FLAG == 0))
    {
		RB7_FLAG = 1;
		
        RB7_ISR_LOW();
        
    }
    else { /* Nothing */}
	
	
	/* ADC Module */
    if ( (INTERRUPT_ENABLE == PIE1bits.ADIE ) && (INTERRUPT_OCCUR == PIR1bits.ADIF ) )
	{
        ADC_ISR();
    }
    else 
    {
        /* Nothing */
    }
    
    
    /* Timer0 Module*/
    if ( (INTERRUPT_ENABLE ==  INTCONbits.TMR0IE) && (INTERRUPT_OCCUR ==  INTCONbits.TMR0IF) )
	{
        Timer0_ISR();
    }
    else 
    {
        /* Nothing */
    }
    
    
    /* Timer1 Module*/
    if ( (INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF) )
	{
        Timer1_ISR();
    }
    else 
    {
        /* Nothing */
    }
    
    /* Timer2 Module*/
    if ( (INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF) )
	{
        Timer2_ISR();
    }
    else 
    {
        /* Nothing */
    }
    
    
    /* Timer3 Module*/
    if ( (INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF) )
	{
        Timer3_ISR();
    }
    else 
    {
        /* Nothing */
    }
    
    
    /* CCP1 Module*/
    if ( (INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF) )
	{
        CCP1_ISR();
    }
    else 
    {
        /* Nothing */
    }
    
    
    /* CCP2 Module*/
    if ( (INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF) )
	{
        CCP2_ISR();
    }
    else 
    {
        /* Nothing */
    }
    
    
    
    /* EUSART RX Module*/
    if ( (INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_OCCUR == PIR1bits.RCIF) )
	{
        EUSART_RX_ISR();
    }
    else 
    {
        /* Nothing */
    }
    
    /* EUSART TX Module*/
    if ( (INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCUR == PIR1bits.TXIF) )
	{
        EUSART_TX_ISR();
    }
    else 
    {
        /* Nothing */
    }
    
    /* MSSP I2C Module*/
    if ( (INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_OCCUR == PIR1bits.SSPIF) )
	{
        MSSP_I2C_ISR();
    }
    else 
    {
        /* Nothing */
    }
    
    /* MSSP I2C Bus Collision Module*/
    if ( (INTERRUPT_ENABLE == PIE2bits.BCLIE) && (INTERRUPT_OCCUR == PIR2bits.BCLIF) )
	{
        MSSP_I2C_BC_ISR();
    }
    else 
    {
        /* Nothing */
    }
    
}

#endif