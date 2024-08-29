/* 
 * File:   hal_adc.c
 * Author: Gomaa Ayman Gomaa
 *
 * Created on July 1, 2024, 12:02 AM
 */


#include "hal_adc.h"

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*ADC_Interrupt_Handler) (void) = NULL;
#endif

static void adc_input_Channel_port_config(adc_channel_select_t channel);
static void adc_configure_result_format(const adc_confg_t* _adc);
static void adc_configure_Voltage_reference(const adc_confg_t* _adc);



/**
 * @breif      :: Initialize ADC Module 
 * @param _adc :: Pointer to ADC Configuration
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType ADC_Init(const adc_confg_t* _adc)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable ADC*/
		ADC_CONVERTER_DISABLE();
		/* Configure the Acquisition Time */
		ADCON2bits.ACQT = _adc->acquisition_time;
		/* Configure the Conversion Clock */
		ADCON2bits.ADCS = _adc->conversion_clock;
		/* Configure the Default Channel and configure as input  */
		ADCON0bits.CHS = _adc->channel_select;
		adc_input_Channel_port_config(_adc->channel_select);
		/* Configure the Interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		ADC_CONVERTER_INTERRUPT_Clear_FLAG();
		ADC_CONVERTER_INTERRUPT_ENABLE();
		ADC_Interrupt_Handler = _adc->ADC_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        Interrupt_Priority_Level_Enable();
		if(INTERRUPT_LOW_PRIORITY == _adc->priority)
		{
            INTERRUPT_GlobalInterruptEnableLOW();
            ADC_CONVERTER_INTERRUPT_LOW_PRIORITY();
        }
        else if(INTERRUPT_HIGH_PRIORITY == _adc->priority)
		{
            INTERRUPT_GlobalInterruptEnableHigh();
            ADC_CONVERTER_INTERRUPT_HIGH_PRIORITY();
        }
        else { /* Nothing*/  }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif	
		/* Configure the Result Format */
		adc_configure_result_format(_adc);
		/* Configure the Voltage Reference */
		adc_configure_Voltage_reference(_adc);
        /* Enable ADC*/
		ADC_CONVERTER_ENABLE();
		
		ret = E_OK;
        
    }
    
    
    return ret;
    
}


/**
 * @brief      :: DeInitialize the ADC 
 * @param _adc :: Pointer to ADC Configuration
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType ADC_DeInit(const adc_confg_t* _adc)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable ADC*/
		ADC_CONVERTER_DISABLE();
        /* Configure the Interrupt */
		#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		ADC_CONVERTER_INTERRUPT_DISABLE();
		#endif
        
        ret = E_OK;
    }
    
    
    return ret;
    
}


/**
 * @brief          :: Select Channel to conversion for ADC
 * @param _adc     :: Pointer to ADC Configuration
 * @param channel  :: Channel that you select it 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType ADC_SelectChannel(const adc_confg_t* _adc, adc_channel_select_t channel)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Configure the Channel and configure as input  */
		ADCON0bits.CHS = channel;
		adc_input_Channel_port_config(channel);
        
        
        ret = E_OK;
    }
    
    
    return ret;
    
}


/**
 * @brief      :: Start ADC conversion 
 * @param _adc :: Pointer to ADC Configuration
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType ADC_StartConversion(const adc_confg_t* _adc)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
		/* Start A/D Conversion */
        ADC_CONVERSION_START();
        
        
        ret = E_OK;
    }
    
    
    return ret;
    
}



/**
 * @brief      :: check if conversion is completed" = A/D Idle " or not" A/D conversion in progress "  
 * @param _adc :: Pointer to ADC Configuration
 * @param conversion_Status :: Status of conversion
 *                true    :: if the conversion is completed 
 *                false   :: if the conversion is not  completed 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType ADC_IsConversionDone(const adc_confg_t* _adc, uint8* conversion_Status)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if( (NULL == _adc) || (NULL == conversion_Status))
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        *conversion_Status = (uint8)(!(ADC_CONVERSION_STATUS()));
        
        ret = E_OK;
    }
    
    
    return ret;
    
}



/**
 * @brief        :: Calcute the result from ADC conversion
 * @param _adc   :: Pointer to ADC Configuration
 * @param result :: Pointer to result from ADC conversion
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType ADC_GetConversionResult(const adc_confg_t* _adc, adc_result_t* result)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if( (NULL == _adc)  || (NULL == result))
    {
        ret = E_NOT_OK;
    }
    else
    {
        if (ADC_RESULT_RIGHT == _adc->result_formate)
		{
			*result = (uint16)((ADRESH << 8) + ADRESL);
        }
		else if(ADC_RESULT_LEFT == _adc->result_formate)
		{
			*result = (uint16)((((ADRESH << 8) + ADRESL) >> 6) & 0x3F);
		}
		else
		{
			*result = (uint16)((ADRESH << 8) + ADRESL);
		}			
        
        
        ret = E_OK;
    }
    
    
    return ret;
    
}



/**
 * @brief         :: Select ADC channel, Start ADC conversion and Read the result of conversion 
 * @param _adc    :: Pointer to ADC Configuration
 * @param channel :: Pointer to ADC channel
 * @param result  :: Pointer to result of conversion 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType ADC_GetConversion_Blocking(const adc_confg_t* _adc, adc_channel_select_t channel,
								 adc_result_t* result)
{
    Std_ReturnType ret = E_NOT_OK;
	
    if( (NULL == _adc) || (NULL == result))
    {
        ret = E_NOT_OK;
    }
    else
    {
		/* Select ADC channel */
        ret  = ADC_SelectChannel(_adc, channel);
		/* Start ADC conversion */
        ret &= ADC_StartConversion(_adc);
		/* Check the ADC conversion completed or not */
		while(ADCON0bits.GODONE); 
		/* Read the result of conversion */
		ret &= ADC_GetConversionResult(_adc, result);	
    }
    
    
    return ret;
    
}


/**
 * 
 * @brief         :: Select ADC channel, Start ADC conversion and Read the result of conversion  at Interrupt
 * @param _adc    :: Pointer to ADC Configuration
 * @param channel :: Pointer to ADC channel
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType ADC_StartConversion_Interrupt(const adc_confg_t* _adc, adc_channel_select_t channel)
{
    
    Std_ReturnType ret = E_NOT_OK;
	
    if( (NULL == _adc) )
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Select ADC channel */
        ret  = ADC_SelectChannel(_adc, channel);
		/* Start ADC conversion */
        ret &= ADC_StartConversion(_adc);
             
    }
    
    return ret;
    
}

static void adc_input_Channel_port_config(adc_channel_select_t channel)
{
    
    switch(channel)
    {
        case ADC_CHANNEL_AN0 : SET_BIT(TRISA, _TRISA_TRISA0_POSN);	break;
        case ADC_CHANNEL_AN1 : SET_BIT(TRISA, _TRISA_TRISA1_POSN);  break;
        case ADC_CHANNEL_AN2 : SET_BIT(TRISA, _TRISA_TRISA2_POSN);  break;
        case ADC_CHANNEL_AN3 : SET_BIT(TRISA, _TRISA_TRISA3_POSN);  break;
        case ADC_CHANNEL_AN4 : SET_BIT(TRISA, _TRISA_TRISA5_POSN);	break;
        case ADC_CHANNEL_AN5 : SET_BIT(TRISE, _TRISE_TRISE0_POSN);	break;
        case ADC_CHANNEL_AN6 : SET_BIT(TRISE, _TRISE_TRISE1_POSN);	break;
        case ADC_CHANNEL_AN7 : SET_BIT(TRISE, _TRISE_TRISE2_POSN);	break;
        case ADC_CHANNEL_AN8 : SET_BIT(TRISB, _TRISB_TRISB2_POSN);	break;
        case ADC_CHANNEL_AN9 : SET_BIT(TRISB, _TRISB_TRISB3_POSN);	break;
        case ADC_CHANNEL_AN10 :SET_BIT(TRISB, _TRISB_TRISB1_POSN);	break;
        case ADC_CHANNEL_AN11 :SET_BIT(TRISB, _TRISB_TRISB4_POSN);	break;
        case ADC_CHANNEL_AN12 :SET_BIT(TRISB, _TRISB_TRISB0_POSN);	break;
		default : /* Nothing */;
		
    }
}

static void adc_configure_result_format(const adc_confg_t* _adc)
{
    if ( ADC_RESULT_RIGHT == _adc->result_formate)
    {
        ADC_RESULT_RIGHT_FORMAT();
    }
    else if ( ADC_RESULT_LEFT == _adc->result_formate)
    {
        ADC_RESULT_LEFT_FORMAT();
    }
    else
    {
        ADC_RESULT_RIGHT_FORMAT();
    }
}

static void adc_configure_Voltage_reference(const adc_confg_t* _adc)
{
    if ( ADC_VOLTAGE_REFRENCE_ENABLED == _adc->voltage_reference)
    {
        ADC_ENABLE_VOLATAGE_REFRENCE();
    }
    else if ( ADC_VOLTAGE_REFRENCE_DISABLED == _adc->voltage_reference)
    {
        ADC_DISABLE_VOLATAGE_REFRENCE();
    }
    else
    {
        ADC_DISABLE_VOLATAGE_REFRENCE();
    }
}


void ADC_ISR(void)
{
    /* Clear Flag */
    ADC_CONVERTER_INTERRUPT_Clear_FLAG();
    
    /* Execute Interrupt Service  Routine*/
    if (ADC_Interrupt_Handler)
    {
        ADC_Interrupt_Handler();
    }
    else
    {
        /* Nothing */
    }
}


