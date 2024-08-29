/* 
 * File:   hal_timer1.c
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on July 9, 2024, 3:12 AM
 */


#include "hal_timer1.h"

#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

static void (* Timer1_InterruptHandler) (void) = NULL;
  
#endif

static uint16 Preload_Value = ZERO_INIT;


static void Timer1_Mode_Config(const timer1_t* _timer);
static void Timer1_Reg_Config(const timer1_t* _timer);
static void Timer1_Prescaler_Config(const timer1_t* _timer);
static void Timer1_Interrupt_Config(const timer1_t* _timer);

/**
 * 
 * @param _timer
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType Timer1_Init(const timer1_t* _timer)
{
	Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
		/* Disable Timer1 Module*/
		TIMER1_MODULE_DISABLE();
		/* Configuration mode */
		Timer1_Mode_Config(_timer);
		/* Configuration Register Read/Write  */
		Timer1_Reg_Config(_timer);
		/* Configuration Pre-scaler    */
		Timer1_Prescaler_Config(_timer);
		/* Configuration Interrupt */
        Timer1_Interrupt_Config(_timer);
		/* Initialize Timer1 Register with Pre-load Value */
		TMR1H = (uint8)((_timer->timer1_preload_value) >> 8);
		TMR1L = (uint8)((_timer->timer1_preload_value) & 0x0f);
		Preload_Value = _timer->timer1_preload_value;
		
		/* Enable Timer1 Module*/
		TIMER1_MODULE_ENABLE();
		
		ret = E_OK;
		
	}
	
	return ret;
	
}

/**
 * 
 * @param _timer
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType Timer1_DeInit(const timer1_t* _timer)
{
	Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
		/* Disable Timer1 Module */
        TIMER1_MODULE_DISABLE();
		/* Disable Interrupt */
        #if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		TIMER1_INTERRUPT_DISABLE();
        #endif
		
		ret = E_OK;
		
	}
	
	return ret;
	
}


/**
 * 
 * @param _timer
 * @param _value
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType Timer1_Write_Value(const timer1_t* _timer, uint16 _value)
{
	Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR1H = (uint8)((_value) >> 8);
		TMR1L = (uint8)((_value) & 0x0f);
		
		ret = E_OK;
		
	}
	
	return ret;
	
}


/**
 * 
 * @param _timer
 * @param _value
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType Timer1_Raed_Value(const timer1_t* _timer, uint16* _value)
{
	Std_ReturnType ret = E_NOT_OK;
    uint8 l_timer1l =ZERO_INIT, l_timer1h = ZERO_INIT;
	
    if( (NULL == _timer) || (NULL == _value))
    {
        ret = E_NOT_OK;
    }
    else
    {
		l_timer1l = TMR1L;
        l_timer1h = TMR1H;
        
        *_value = (uint16)((l_timer1h<<8) + l_timer1l);
		
		ret = E_OK;
		
	}
	
	return ret;
	
}

static void Timer1_Mode_Config(const timer1_t* _timer)
{
	
	if(TIMER1_TIMER_MODE_CFG == (_timer->timer1_mode))
	{
		TIMER1_TIMER_MODE();
	}
	else if(TIMER1_COUNTER_MODE_CFG == (_timer->timer1_mode))
	{
		TIMER1_COUNTER_MODE();
		
		if(TIMER1_COUNTER_MODE_SYNCHRONIZE_CFG == (_timer->timer1_counter_mode))
		{
			TIMER1_COUNTER_MODE_SYNCHRONIZE();
		}
		else if(TIMER1_COUNTER_MODE_NOT_SYNCHRONIZE_CFG == (_timer->timer1_counter_mode))
		{
			TIMER1_COUNTER_MODE_NOT_SYNCHRONIZE();
		}
		else {/* Nothing*/ }
		
	}
	else {/* Nothing*/ }
	
}


static void Timer1_Reg_Config(const timer1_t* _timer)
{
	if(TIMER1_16_BIT_READ_WRITE_MODE_CFG == (_timer->timer1_rw_mode))
	{
		TIMER1_16_BIT_READ_WRITE_MODE();
	}
	else if(TIMER1_8_BIT_READ_WRITE_MODE_CFG == (_timer->timer1_rw_mode))
	{
		TIMER1_8_BIT_READ_WRITE_MODE();
	}
	else { /* Nothing */}
}

static void Timer1_Prescaler_Config(const timer1_t* _timer)
{
	TIMER1_PRESCALER_CONFIGURATION(_timer->timer1_prescaler);	
}

static void Timer1_Interrupt_Config(const timer1_t* _timer)
{
	
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
    TIMER1_INTERRUPT_Clear_FLAG();
    TIMER1_INTERRUPT_ENABLE(); 
	/* Initialize CallBack */
    Timer1_InterruptHandler = _timer->timer1_intrrupt_handler;
	
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    Interrupt_Priority_Level_Enable();
    if(_timer->priority == INTERRUPT_LOW_PRIORITY)
    {
        INTERRUPT_GlobalInterruptEnableLOW();
        TIMER1_INTERRUPT_LOW_PRIORITY();
    }
    else if(_timer->priority == INTERRUPT_HIGH_PRIORITY)
    {
        INTERRUPT_GlobalInterruptEnableHigh();
        TIMER1_INTERRUPT_HIGH_PRIORITY();
    }
    else{ /* Nothing */ }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
#endif
#endif
	
}

void Timer1_ISR(void)
{
    /* Clear Flag */
    TIMER1_INTERRUPT_Clear_FLAG();
	/* Initialize Timer1 Register with Pre load Value */
	TMR1H = (uint8)((Preload_Value) >> 8);
	TMR1L = (uint8)((Preload_Value) & 0x0f);
    /* CallBack */
    
    if (Timer1_InterruptHandler)
    {
        Timer1_InterruptHandler();
    }
	
}


