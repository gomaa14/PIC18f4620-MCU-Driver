/* 
 * File:   hal_timer0.c
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on July 8, 2024, 5:21 AM
 */

#include "hal_timer0.h"

#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

static void (* Timer0_InterruptHandler) (void) = NULL;
  
#endif

static uint16 Preload_Value = ZERO_INIT;


static void Timer0_Prescaler_Config(const timer0_t* _timer);
static void Timer0_Edge_Config(const timer0_t* _timer);
static void Timer0_Mode_Config(const timer0_t* _timer);
static void Timer0_Size_Config(const timer0_t* _timer);
static void Timer0_Interrupt_Config(const timer0_t* _timer);

/**
 * 
 * @param _timer
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType Timer0_Init(const timer0_t* _timer)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable Timer0 Module*/
        TIMER0_MODULE_DISABLE();
        /* Configuration Register size  */
        Timer0_Size_Config(_timer);
        
        /* Configuration mode and  Edge Select*/
        Timer0_Mode_Config(_timer);
        
        /* Configuration Pre-scaler    */
        Timer0_Prescaler_Config(_timer);
        
        /* Configuration Interrupt */
        Timer0_Interrupt_Config(_timer);
        
		/* Initialize Timer0 Register with Preload Value */
		TMR0H = (uint8)((_timer->timer0_preload_value) >> 8);
		TMR0L = (uint8)((_timer->timer0_preload_value) & 0x0f);
		Preload_Value = _timer->timer0_preload_value;
		
        /* Enable Timer0 Module*/
        TIMER0_MODULE_ENABLE();
        
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
Std_ReturnType Timer0_DeInit(const timer0_t* _timer)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable Timer0 Module */
        TIMER0_MODULE_DISABLE();
		/* Disable Interrupt */
        #if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		TIMER0_INTERRUPT_DISABLE();
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
Std_ReturnType Timer0_Write_Value(const timer0_t* _timer, uint16 _value)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR0H = (uint8)((_value) >> 8);
		TMR0L = (uint8)((_value) & 0x0f);
        
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
Std_ReturnType Timer0_Raed_Value(const timer0_t* _timer, uint16* _value)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_timer0l =ZERO_INIT, l_timer0h = ZERO_INIT;
    
    if( (NULL == _timer) || (NULL == _value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        l_timer0l = TMR0L;
        l_timer0h = TMR0H;
        
        *_value = (uint16)((l_timer0h<<8) + l_timer0l);
        
        ret = E_OK;
    }
    
    return ret;
    
}



void Timer0_ISR(void)
{
    /* Clear Flag */
    TIMER0_INTERRUPT_Clear_FLAG();
    
	/* Initialize Timer0 Register with Pre load Value */
	TMR0H = (uint8)((Preload_Value) >> 8);
	TMR0L = (uint8)((Preload_Value) & 0x0f);
    
    /* CallBack */
    
    if(Timer0_InterruptHandler)
    {
        Timer0_InterruptHandler();
    }
    
}



static void Timer0_Prescaler_Config(const timer0_t* _timer)
{
    if( TIMER0_ENABLE_PRESCALER_CFG == _timer->timer0_Prescaler_Enable )
    {
        TIMER0_PRESCALER_ENABLE();
		TIMER0_PRESCALER_CONFIGURATION(_timer->Prescaler_Value);
    }
    else if(TIMER0_DISABLE_PRESCALER_CFG == _timer->timer0_Prescaler_Enable )
    {
        TIMER0_PRESCALER_DISABLE();
    } 
    else
    {/* Nothing*/}
}


static void Timer0_Edge_Config(const timer0_t* _timer)
{
    if( TIMER0_RISING_EDGE_CFG == _timer->counter_edge_select )
    {
        TIMER0_RISING_EDGE_SELECT();
    }
    else if(TIMER0_FALLING_EDGE_CFG == _timer->counter_edge_select )
    {
        TIMER0_FALLING_EDGE_SELECT();
    }
    else
    {/* Nothing*/}
}


static void Timer0_Mode_Config(const timer0_t* _timer)
{
    if( TIMER0_TIMER_MODE_CFG == _timer->timer0_mode )
    {
        TIMER0_TIMER_MODE_SOURCE();
    }
    else if(TIMER0_COUNTER_MODE_CFG == _timer->timer0_mode )
    {
        TIMER0_COUNTER_MODE_SOURCE();
		Timer0_Edge_Config(_timer);
    }
	else
    {/* Nothing*/}
}

static void Timer0_Size_Config(const timer0_t* _timer)
{
    if( TIMER0_8_BIT_REGISTER_MODE == _timer->timer0_register_size)
    {
        TIMER0_CONFIGURE_8_BIT();
        
    }
    else if( TIMER0_16_BIT_REGISTER_MODE == _timer->timer0_register_size)
    {
        TIMER0_CONFIGURE_16_BIT();
    }
    else
    {/* Nothing*/}
    
}


static void Timer0_Interrupt_Config(const timer0_t* _timer)
{
	
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
    TIMER0_INTERRUPT_Clear_FLAG();
    TIMER0_INTERRUPT_ENABLE(); 
	/* Initialize CallBack */
    Timer0_InterruptHandler = _timer->timer0_intrrupt_handler;
	
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    Interrupt_Priority_Level_Enable();
    if(_timer->priority == INTERRUPT_LOW_PRIORITY)
    {
        INTERRUPT_GlobalInterruptEnableLOW();
        TIMER0_INTERRUPT_LOW_PRIORITY();
    }
    else if(_timer->priority == INTERRUPT_HIGH_PRIORITY)
    {
        INTERRUPT_GlobalInterruptEnableHigh();
        TIMER0_INTERRUPT_HIGH_PRIORITY();
    }
    else{ /* Nothing */ }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
#endif
#endif
	
	
}


