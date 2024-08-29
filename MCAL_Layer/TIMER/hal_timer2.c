/* 
 * File:   hal_timer2.c
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on July 12, 2024, 5:18 AM
 */


#include "hal_timer2.h"


#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

static void (* Timer2_InterruptHandler) (void) = NULL;
  
#endif

static uint8 Preload_Value = ZERO_INIT;

static void Timer2_Interrupt_Config(const timer2_t* _timer);

/**
 * 
 * @param _timer
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType Timer2_Init(const timer2_t* _timer)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable Timer2 Module*/
        TIMER2_MODULE_DISABLE();
        /* Configuration Pre-scaler    */
		TIMER2_CLOCK_PRESCALE_SELECT(_timer->timer2_prescaler);
		/* Configuration Post-scaler    */
        TIMER2_OUTPUT_POSTSCALE_SELECT(_timer->timer2_postscaler);
        
        /* Configuration Interrupt*/
        Timer2_Interrupt_Config(_timer);
        
		/* configure pre-load value */
		TMR2 = _timer->timer2_preload_value;
        Preload_Value = _timer->timer2_preload_value;
        
		
        /* Enable Timer2 Module*/
        TIMER2_MODULE_ENABLE();
		
		
        ret = E_OK;
    }
    
    
    return ret ;
    
}


/**
 * 
 * @param _timer
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType Timer2_DeInit(const timer2_t* _timer)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable Timer2 Module*/
        TIMER2_MODULE_DISABLE();
        
		/* Disable Interrupt */
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_INTERRUPT_DISABLE();
#endif
        ret = E_OK;
    }
    
    
    return ret ;
    
}


/**
 * 
 * @param _timer
 * @param _value
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType Timer2_Write_Value(const timer2_t* _timer, uint8 _value)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        TMR2 = _value;
        
        ret = E_OK;
    }
    
    
    return ret ;
    
}


/**
 * 
 * @param _timer
 * @param _value
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType Timer2_Raed_Value(const timer2_t* _timer, uint8* _value)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if((NULL == _timer) || (NULL == _value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        *_value = TMR2;
        
        ret = E_OK;
    }
    
    
    return ret ;
    
}

void Timer2_ISR(void)
{
    /*  Clear Flag */
    
    TIMER2_INTERRUPT_Clear_FLAG();
    
    /* Initialize TIMR2*/
    
     TMR2 = Preload_Value;
    /* CallBack */
    
    if(Timer2_InterruptHandler)
    {
        Timer2_InterruptHandler();
    }
}

static void Timer2_Interrupt_Config(const timer2_t* _timer)
{
	
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
    TIMER2_INTERRUPT_Clear_FLAG();
    TIMER2_INTERRUPT_ENABLE(); 
	/* Initialize CallBack */
    Timer2_InterruptHandler = _timer->timer2_intrrupt_handler;
	
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    Interrupt_Priority_Level_Enable();
    if(_timer->priority == INTERRUPT_LOW_PRIORITY)
    {
        INTERRUPT_GlobalInterruptEnableLOW();
        TIMER2_INTERRUPT_LOW_PRIORITY();
    }
    else if(_timer->priority == INTERRUPT_HIGH_PRIORITY)
    {
        INTERRUPT_GlobalInterruptEnableHigh();
        TIMER2_INTERRUPT_HIGH_PRIORITY();
    }
    else{ /* Nothing */ }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
#endif
#endif

}
	
