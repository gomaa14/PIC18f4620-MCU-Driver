/* 
 * File:   hal_usart.c
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on August 4, 2024, 5:45 AM
 */


#include "hal_usart.h"

static Std_ReturnType EUSART_Baud_Rate_Calculation(const usart_t* eusart_obj);
static Std_ReturnType EUSART_TX_Init(const usart_t* eusart_obj);
static Std_ReturnType EUSART_RX_Init(const usart_t* eusart_obj);
static Std_ReturnType Init_Interrupt(const usart_t* eusart_obj);
static Std_ReturnType EUSART_TX_Interrupt_Init(const usart_t* eusart_obj);
static Std_ReturnType EUSART_RX_Interrupt_Init(const usart_t* eusart_obj);

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
static void (*EUSART_TX_InterruptHandler)(void) = NULL;
#endif
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
static void (*EUSART_RX_InterruptHandler)(void) = NULL;
static void (*EUSART_FramingError_InterruptHandler)(void) = NULL;
static void (*EUSART_OverrunError_InterruptHandler)(void) = NULL;
#endif



/**
 * 
 * @param eusart_obj
 * @return 
 */
Std_ReturnType EUSART_ASYNC_Init(const usart_t* eusart_obj)
{
    Std_ReturnType Ret = E_NOT_OK;
    if(NULL == eusart_obj)
    {
        Ret = E_NOT_OK;
    }
    else 
    {
        /* Disable EUSART Module */
        EUSART_SERIAL_PORT_DISABLED();
		
		/* Initialize RX and TX to be Input */
		SET_BIT(TRISC, _TRISC_RC6_POSN); //TRISCbits.RC6 = 1;
		SET_BIT(TRISC, _TRISC_RC7_POSN); //TRISCbits.RC7 = 1;
		
        
		/* Initialize the SPBRGH:SPBRG registers for the appropriate baud rate */
		Ret = EUSART_Baud_Rate_Calculation(eusart_obj);
        
        /*  Initialize TX */
        Ret |= EUSART_TX_Init(eusart_obj);
		/*  Initialize RX */
        Ret |= EUSART_RX_Init(eusart_obj);
        
        /* Enable EUSART Module */
		EUSART_SERIAL_PORT_ENABLED();
        
		
    }
    
    return Ret;
    
}


/**
 * 
 * @param eusart_obj
 * @return 
 */
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t* eusart_obj)
{
    Std_ReturnType Ret = E_NOT_OK;
    if(NULL == eusart_obj)
    {
        Ret = E_NOT_OK;
    }
    else 
    {
        /* Disable Interrupt for TX*/
        if ( EUSART_TX_INTERRUPT_ENABLED_CFG == eusart_obj->usart_tx_cfg.usart_tx_interrupt_enable)
        {
            EUSART_TX_INTERRUPT_DISABLE();
        }
        else { /* Nothing */}
        
        /* Disable Interrupt for RX*/
        if ( EUSART_RX_INTERRUPT_ENABLED_CFG == eusart_obj->usart_rx_cfg.usart_rx_interrupt_enable)
        {
            EUSART_RX_INTERRUPT_DISABLE();
        }
        else { /* Nothing */}
        
        /* Disable EUSART Module */
        EUSART_SERIAL_PORT_DISABLED();
        
        Ret = E_OK;
    }
    
    return Ret;
    
}


/**
 * 
 * @param eusart_obj
 * @param _data
 * @return 
 */
Std_ReturnType EUSART_ASYNC_Read_Byte_Blocking(const usart_t* eusart_obj, uint8* _data)
{
    Std_ReturnType Ret = E_NOT_OK;
    if((NULL == eusart_obj) || (NULL == _data))
    {
        Ret = E_NOT_OK;
    }
    else 
    {
        
        while( PIR1bits.RCIF == 0);
      
        *_data = RCREG;
        
        Ret = E_OK;
    }
    
    return Ret;
    
}

/**
 * 
 * @param eusart_obj
 * @param _data
 * @return 
 */
Std_ReturnType EUSART_ASYNC_Read_Byte_NON_Blocking(const usart_t* eusart_obj, uint8* _data )
{
    Std_ReturnType Ret = E_NOT_OK;
    if((NULL == eusart_obj) || (NULL == _data))
    {
        Ret = E_NOT_OK;
    }
    else 
    {
        if (PIR1bits.RCIF == 1)
        { 
            *_data = RCREG;
            Ret = E_OK;
        }
        else {/* Nothing */}  
        
    }
    
    return Ret;
    
}



/**
 * 
 * @param eusart_obj
 * @param _data
 * @return 
 */
Std_ReturnType EUSART_ASYNC_Write_Byte_Blocking(const usart_t* eusart_obj, uint8 _data)
{
    Std_ReturnType Ret = E_NOT_OK;
    if(NULL == eusart_obj)
    {
        Ret = E_NOT_OK;
    }
    else 
    {
        while(EUSART_TRANSMIT_SHIFT_REGISTER_STATUS() == 0);
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE        
        EUSART_TX_INTERRUPT_ENABLE();
#endif        
        TXREG = _data;
        
        Ret = E_OK;
    }
    
    return Ret;
    
}


/**
 * 
 * @param eusart_obj
 * @param _data
 * @return 
 */
Std_ReturnType EUSART_ASYNC_Write_String_Blocking(const usart_t* eusart_obj, uint8* _data )
{
    Std_ReturnType Ret = E_NOT_OK;
    uint8 l_counter =ZERO_INIT;
    
    if(NULL == eusart_obj)
    {
        Ret = E_NOT_OK;
    }
    else 
    {
        while(_data[l_counter] != '\0')
        { 
            EUSART_ASYNC_Write_Byte_Blocking(eusart_obj, _data[l_counter]);
            l_counter++;  
        }
        
        Ret = E_OK;
    }
    
    return Ret;
      
}


/**
 * 
 * @param eusart_obj
 * @param _data
 * @return 
 */
Std_ReturnType EUSART_ASYNC_Write_Byte_NON_Blocking(const usart_t* eusart_obj, uint8 _data )
{
    
    Std_ReturnType Ret = E_NOT_OK;
    if((NULL == eusart_obj) )
    {
        Ret = E_NOT_OK;
    }
    else 
    {
        if (PIR1bits.TXIF == 1)
        {
            TXREG = _data;
            Ret = E_OK;
        }
        else {/* Nothing */}  
        
    }
    
    return Ret;
    
}


/**
 * 
 * @param eusart_obj
 * @param _data
 * @return 
 */
Std_ReturnType EUSART_ASYNC_Write_String_NON_Blocking(const usart_t* eusart_obj, uint8* _data )
{
    Std_ReturnType Ret = E_NOT_OK;
    uint8 l_counter = 0;
    
    if((NULL == eusart_obj) || (NULL == _data))
    {
        Ret = E_NOT_OK;
    }
    else 
    {
        while(_data[l_counter] != '\0')
        {
            Ret = EUSART_ASYNC_Write_Byte_NON_Blocking(&eusart_obj, _data[l_counter]);
            if(Ret == E_OK)
            {
                l_counter++;
            }
            else
            {/* Nothing */}
        }
        
    }
    
    return Ret;
    
    
}
    
    
    

void EUSART_TX_ISR(void)
{
    /* Disable Interrupt  */
    EUSART_TX_INTERRUPT_DISABLE();
    
    if (EUSART_TX_InterruptHandler)
    {
        EUSART_TX_InterruptHandler();
    }
    else{ /* Nothing*/ }
    
    
}
void EUSART_RX_ISR(void)
{
    /* Disable Interrupt  */
    //EUSART_RX_INTERRUPT_DISABLE();
    
    
    if (EUSART_RX_InterruptHandler)
    {
        EUSART_RX_InterruptHandler();
    }
    else{ /* Nothing*/ }
    
    if (EUSART_FramingError_InterruptHandler)
    {
        EUSART_FramingError_InterruptHandler();
    }
    else{ /* Nothing*/ }
    
    if (EUSART_OverrunError_InterruptHandler)
    {
        EUSART_OverrunError_InterruptHandler();
    }
    else{ /* Nothing*/ }
    
    
}


/* ----------------------------Static Function ------------------------------ */


static Std_ReturnType EUSART_Baud_Rate_Calculation(const usart_t* eusart_obj)
{
	Std_ReturnType Ret = E_NOT_OK;
    if(NULL == eusart_obj)
    {
        Ret = E_NOT_OK;
    }
    else 
    {
        if(eusart_obj->baud_rate_gen_config  == BAUDRAT_ASYN_8_BIT_LOW_SPEED)
        {
            EUSART_ASYNCHRONOUS_LOW_BAUD_RATE();
            EUSART_ASYNCHRONOUS_MODE();
            EUSART_08_BIT_BAUD_RATE_GENERATOR();
            
            SPBRG = (uint8) (((_XTAL_FREQ/(eusart_obj->BaudRate))/64) -1 );
        }
        else if(eusart_obj->baud_rate_gen_config == BAUDRAT_ASYN_8_BIT_HIGH_SPEED)
        {
            EUSART_ASYNCHRONOUS_HIGH_BAUD_RATE();
            EUSART_ASYNCHRONOUS_MODE();
            EUSART_08_BIT_BAUD_RATE_GENERATOR();
            
            SPBRG = (uint8) (((_XTAL_FREQ/(eusart_obj->BaudRate))/16) -1 );
        }
        else if(eusart_obj->baud_rate_gen_config == BAUDRAT_ASYN_16_BIT_LOW_SPEED)
        {
            EUSART_ASYNCHRONOUS_LOW_BAUD_RATE();
            EUSART_ASYNCHRONOUS_MODE();
            EUSART_16_BIT_BAUD_RATE_GENERATOR();
            
            uint16 Temp_Var = (uint16)(((_XTAL_FREQ/(eusart_obj->BaudRate))/16) -1 );
            SPBRG = (uint8)(Temp_Var);
            SPBRGH = (uint8)(Temp_Var>>8);
        }
        else if(eusart_obj->baud_rate_gen_config == BAUDRAT_ASYN_16_BIT_HIGH_SPEED)
        {
            EUSART_ASYNCHRONOUS_HIGH_BAUD_RATE();
            EUSART_ASYNCHRONOUS_MODE();
            EUSART_16_BIT_BAUD_RATE_GENERATOR();
            
            uint16 Temp_Var = (uint16)(((_XTAL_FREQ/(eusart_obj->BaudRate))/4) -1 );
            SPBRG = (uint8)(Temp_Var);
            SPBRGH = (uint8)(Temp_Var>>8);
        }
        else if(eusart_obj->baud_rate_gen_config == BAUDRAT_SYN_8_BIT)
        {
            EUSART_SYNCHRONOUS_MODE();
            EUSART_08_BIT_BAUD_RATE_GENERATOR();
            
            SPBRG = (uint8) (((_XTAL_FREQ/(eusart_obj->BaudRate))/4) -1 );
        }
        else if(eusart_obj->baud_rate_gen_config == BAUDRAT_SYN_16_BIT)
        {
            EUSART_SYNCHRONOUS_MODE();
            EUSART_16_BIT_BAUD_RATE_GENERATOR();
            
            uint16 Temp_Var = (uint16)(((_XTAL_FREQ/(eusart_obj->BaudRate))/4) -1 );
            SPBRG = (uint8)(Temp_Var);
            SPBRGH = (uint8)(Temp_Var>>8);
        }
        else
        { /* Nothing */ }
        
        Ret = E_OK;
    }
    
    return Ret;
	
}

static Std_ReturnType EUSART_TX_Init(const usart_t* eusart_obj)
{
    Std_ReturnType Ret = E_NOT_OK;
    if(NULL == eusart_obj)
    {
        Ret = E_NOT_OK;
    }
    else 
    {
        
        /* Enable transmission */
		if (eusart_obj->usart_tx_cfg.usart_tx_enable == EUSART_ASYNCHRONOUS_TX_ENABLED_CFG)
		{
            EUSART_TRANSMIT_ENABLED();
            
            /* EUSART Interrupt Enable TX Configuration  */
            if(EUSART_TX_INTERRUPT_ENABLED_CFG == (eusart_obj->usart_tx_cfg.usart_tx_interrupt_enable))
            {
                Ret = EUSART_TX_Interrupt_Init(eusart_obj);
            }
            else if(EUSART_TX_INTERRUPT_DISABLEd_CFG == (eusart_obj->usart_tx_cfg.usart_tx_interrupt_enable))
            {
                EUSART_TX_INTERRUPT_DISABLE();
            }
            else { /* Nothing */}
            
            /* 9_bit transmission */
            if (eusart_obj->usart_tx_cfg.usart_tx_9_bit_enable == EUSART_SELECTS_9_BIT_TX_CFG)
            {
                EUSART_SELECTS_9_BIT_TRANSMISSION();
            }
            else if (eusart_obj->usart_tx_cfg.usart_tx_9_bit_enable == EUSART_SELECTS_8_BIT_TX_CFG)
            {
                EUSART_SELECTS_8_BIT_TRANSMISSION();
            }
            else
            {/* Nothing */  }
        
            
        }
		else if (eusart_obj->usart_tx_cfg.usart_tx_enable == EUSART_ASYNCHRONOUS_TX_DISABLEd_CFG)
		{
            EUSART_TRANSMIT_DISABLED();
        }
        else
        {/* Nothing */  }
        
        
        Ret = E_OK;
        
    }
    
    
    return Ret;
    
}

static Std_ReturnType EUSART_RX_Init(const usart_t* eusart_obj)
{
    Std_ReturnType Ret = E_NOT_OK;
    if(NULL == eusart_obj)
    {
        Ret = E_NOT_OK;
    }
    else 
    {
        /* Enable Receive */
		if (eusart_obj->usart_rx_cfg.usart_rx_enable == EUSART_ASYNCHRONOUS_RX_ENABLED_CFG)
		{
            EUSART_ASYNCHRONOUS_ENABLE_RECEIVER();
            
            /* 9_bit reception  */
            if (eusart_obj->usart_rx_cfg.usart_rx_9_bit_enable == EUSART_SELECTS_9_BIT_RX_CFG)
            {
                EUSART_SELECTS_9_BIT_RECEPTION();
            }
            else if (eusart_obj->usart_rx_cfg.usart_rx_9_bit_enable == EUSART_SELECTS_8_BIT_RX_CFG)
            {
                EUSART_SELECTS_8_BIT_RECEPTION();
            }
            else {/* Nothing */  }
        
            
            /* EUSART Interrupt Enable RX Configuration  */
            if(EUSART_RX_INTERRUPT_ENABLED_CFG == (eusart_obj->usart_rx_cfg.usart_rx_interrupt_enable))
            {
                Ret = EUSART_RX_Interrupt_Init(eusart_obj);
            }
            else if(EUSART_RX_INTERRUPT_DISABLEd_CFG == (eusart_obj->usart_rx_cfg.usart_rx_interrupt_enable))
            {
                EUSART_RX_INTERRUPT_DISABLE();
            }
            else { /* Nothing */}      
        }
        
		else if (eusart_obj->usart_rx_cfg.usart_rx_enable == EUSART_ASYNCHRONOUS_RX_DISABLEd_CFG)
		{
            EUSART_ASYNCHRONOUS_DISABLE_RECEIVER();  
        }
        else
        {/* Nothing */  }
        
        Ret = E_OK;
        
    }
    
    return Ret;
}



static Std_ReturnType EUSART_TX_Interrupt_Init(const usart_t* eusart_obj)
{
    Std_ReturnType Ret = E_NOT_OK;
    if(NULL == eusart_obj)
    {
        Ret = E_NOT_OK;
    }
    else 
    {
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
    //TIMER0_INTERRUPT_Clear_FLAG();
    EUSART_TX_INTERRUPT_ENABLE(); 
	/* Initialize CallBack */
    EUSART_TX_InterruptHandler = eusart_obj->EUSART_TX_Default_Interrupt_Handler;
	
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    Interrupt_Priority_Level_Enable();
    if( eusart_obj->EUSART_TX_priority == INTERRUPT_LOW_PRIORITY)
    {
        INTERRUPT_GlobalInterruptEnableLOW();
        EUSART_TX_INTERRUPT_LOW_PRIORITY();
    }
    else if(eusart_obj->EUSART_TX_priority == INTERRUPT_HIGH_PRIORITY)
    {
        INTERRUPT_GlobalInterruptEnableHigh();
        EUSART_TX_INTERRUPT_HIGH_PRIORITY();
    }
    else{ /* Nothing */ }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
#endif
#endif
        
        
        Ret = E_OK;
        
    }
    
    
    return Ret;
}

static Std_ReturnType EUSART_RX_Interrupt_Init(const usart_t* eusart_obj)
{
    Std_ReturnType Ret = E_NOT_OK;
    if(NULL == eusart_obj)
    {
        Ret = E_NOT_OK;
    }
    else 
    {
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
    //TIMER0_INTERRUPT_Clear_FLAG();
    EUSART_RX_INTERRUPT_ENABLE(); 
	/* Initialize CallBack */
    EUSART_RX_InterruptHandler = eusart_obj->EUSART_RX_Default_Interrupt_Handler;
	EUSART_FramingError_InterruptHandler = eusart_obj->EUSART_FramingError_Handler;
    EUSART_OverrunError_InterruptHandler = eusart_obj->EUSART_overrunError_Handler;
    
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    Interrupt_Priority_Level_Enable();
    if( eusart_obj->EUSART_RX_priority == INTERRUPT_LOW_PRIORITY)
    {
        INTERRUPT_GlobalInterruptEnableLOW();
        EUSART_RX_INTERRUPT_LOW_PRIORITY();
    }
    else if(eusart_obj->EUSART_RX_priority == INTERRUPT_HIGH_PRIORITY)
    {
        INTERRUPT_GlobalInterruptEnableHigh();
        EUSART_RX_INTERRUPT_HIGH_PRIORITY();
    }
    else{ /* Nothing */ }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
#endif
#endif
        
        Ret = E_OK;
    }
    
    
    return Ret;
}
