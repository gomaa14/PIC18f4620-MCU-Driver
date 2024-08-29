/* 
 * File:   hal_timer3.c
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on July 12, 2024, 10:22 AM
 */


#include "hal_timer3.h"


#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

static void (* Timer3_InterruptHandler) (void) = NULL;
  
#endif

static uint16 Preload_Value = ZERO_INIT;


static void Timer3_Mode_Config(const timer3_t* _timer);
static void Timer3_Reg_Config(const timer3_t* _timer);
static void Timer3_Prescaler_Config(const timer3_t* _timer);
static void Timer3_Interrupt_Config(const timer3_t* _timer);

/**
 * 
 * @param _timer
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType Timer3_Init(const timer3_t* _timer)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable Timer3 Module*/
		TIMER3_MODULE_DISABLE();
		/* Configuration mode */
		Timer3_Mode_Config(_timer);
		/* Configuration Register Read/Write  */
		Timer3_Reg_Config(_timer);
		/* Configuration Pre-scaler    */
		Timer3_Prescaler_Config(_timer);
		/* Configuration Interrupt */
        Timer3_Interrupt_Config(_timer);
		/* Initialize Timer1 Register with Pre-load Value */
		TMR3H = (uint8)((_timer->timer3_preload_value) >> 8);
		TMR3L = (uint8)((_timer->timer3_preload_value) & 0x0f);
		Preload_Value = _timer->timer3_preload_value;
		
		/* Enable Timer1 Module*/
		TIMER3_MODULE_ENABLE();
        
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
Std_ReturnType Timer3_DeInit(const timer3_t* _timer)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable Timer3 Module */
        TIMER3_MODULE_DISABLE();
		/* Disable Interrupt */
        #if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		TIMER3_INTERRUPT_DISABLE();
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
Std_ReturnType Timer3_Write_Value(const timer3_t* _timer, uint16 _value)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR3H = (uint8)((_value) >> 8);
		TMR3L = (uint8)((_value) & 0x0f);
        
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
Std_ReturnType Timer3_Raed_Value(const timer3_t* _timer, uint16* _value)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_timer3l =ZERO_INIT, l_timer3h = ZERO_INIT;
    if((NULL == _timer) || (NULL == _value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        l_timer3l = TMR3L;
        l_timer3h = TMR3H;
        
        *_value = (uint16)((l_timer3h<<8) + l_timer3l);
        
        ret = E_OK;
    }
    
    
    return ret ;
    
}

void Timer3_ISR(void)
{
    
    /* Clear Flag */
    TIMER3_INTERRUPT_Clear_FLAG();
	/* Initialize Timer1 Register with Pre load Value */
	TMR3H = (uint8)((Preload_Value) >> 8);
	TMR3L = (uint8)((Preload_Value) & 0x0f);
    /* CallBack */
    
    if (Timer3_InterruptHandler)
    {
        Timer3_InterruptHandler();
    }
    
}


static void Timer3_Mode_Config(const timer3_t* _timer)
{
	if(TIMER3_TIMER_MODE_CFG == (_timer->timer3_mode))
	{
		TIMER3_TIMER_MODE();
	}
	else if(TIMER3_COUNTER_MODE_CFG == (_timer->timer3_mode))
	{
		TIMER3_COUNTER_MODE();
		
		if(TIMER3_COUNTER_MODE_SYNCHRONIZE_CFG == (_timer->timer3_counter_mode))
		{
			TIMER3_COUNTER_MODE_SYNCHRONIZE();
		}
		else if(TIMER3_COUNTER_MODE_NOT_SYNCHRONIZE_CFG == (_timer->timer3_counter_mode))
		{
			TIMER3_COUNTER_MODE_NOT_SYNCHRONIZE();
		}
		else {/* Nothing*/ }
		
	}
	else {/* Nothing*/ }
		
}
static void Timer3_Reg_Config(const timer3_t* _timer)
{
	if(TIMER3_16_BIT_READ_WRITE_MODE_CFG == (_timer->timer3_rw_mode))
	{
		TIMER3_16_BIT_READ_WRITE_MODE();
	}
	else if(TIMER3_8_BIT_READ_WRITE_MODE_CFG == (_timer->timer3_rw_mode))
	{
		TIMER3_8_BIT_READ_WRITE_MODE();
	}
	else { /* Nothing */}
}
static void Timer3_Prescaler_Config(const timer3_t* _timer)
{
	TIMER3_PRESCALER_CONFIGURATION(_timer->timer3_prescaler);
}
static void Timer3_Interrupt_Config(const timer3_t* _timer)
{
	
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
    TIMER3_INTERRUPT_Clear_FLAG();
    TIMER3_INTERRUPT_ENABLE(); 
	/* Initialize CallBack */
    Timer3_InterruptHandler = _timer->timer3_intrrupt_handler;
	
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    Interrupt_Priority_Level_Enable();
    if(_timer->priority == INTERRUPT_LOW_PRIORITY)
    {
        INTERRUPT_GlobalInterruptEnableLOW();
        TIMER3_INTERRUPT_LOW_PRIORITY();
    }
    else if(_timer->priority == INTERRUPT_HIGH_PRIORITY)
    {
        INTERRUPT_GlobalInterruptEnableHigh();
        TIMER3_INTERRUPT_HIGH_PRIORITY();
    }
    else{ /* Nothing */ }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
#endif
#endif	
	
}




