/* 
 * File:   hal_ccp.c
 * Author: Gomaa Ayman Gomaa
 *
 * Created on July 16, 2024, 10:47 AM
 */
 
 
 
#include "hal_ccp.h"




#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (* CCP1_InterruptHandler) (void) = NULL;
#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (* CCP2_InterruptHandler) (void) = NULL;
#endif
 
static Std_ReturnType Select_Mode(const ccp_t * ccp_obj);
static Std_ReturnType CCP_Interrupt_Config(const ccp_t * ccp_obj);
static Std_ReturnType CCP_Capture_Mode_Timer_Select(const ccp_t * ccp_obj);




 /**
 * 
 * @param ccp_obj
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
*/
Std_ReturnType CCP_Init(const ccp_t * ccp_obj)
{
	Std_ReturnType ret = E_OK;
    
    if( NULL == ccp_obj )
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        /* CCP Module Disable */
        if(ccp_obj->ccp_inst == CCP1_INST)
        {
            CCP1_SELECT_MODE_CONFIGURATION(CCP_MODULE_DISABLE);
        }
        else if(ccp_obj->ccp_inst == CCP2_INST)
        {
            CCP2_SELECT_MODE_CONFIGURATION(CCP_MODULE_DISABLE);
        }
        
		
        /* Initialize The Mode Select , Pin Configuration  and Timer3 and Timer1 to CCPx Enable  */
        ret = Select_Mode(ccp_obj);
        /* Interrupt Configuration */
        ret = CCP_Interrupt_Config(ccp_obj);
		
        
        
		/* CCP1 Module Enable */
        
        
	}
	
	return ret;
	
}

/**
 * 
 * @param ccp_obj
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType CCP_DeInit(const ccp_t * ccp_obj)
{
	Std_ReturnType ret = E_OK;
    
    if( NULL == ccp_obj )
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        if(CCP1_INST == ccp_obj->ccp_inst)
        {
            /* CCP1 Module Disable */
            CCP1_SELECT_MODE_CONFIGURATION(CCP_MODULE_DISABLE);
            /* Disable Interrupt */
        #if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 		
            CCP1_INTERRUPT_DISABLE();
        #endif
        }
        else if (CCP2_INST == ccp_obj->ccp_inst)
        {
           /* CCP2 Module Disable */
            CCP2_SELECT_MODE_CONFIGURATION(CCP_MODULE_DISABLE);
            /* Disable Interrupt */
        #if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 		
            CCP2_INTERRUPT_DISABLE();
        #endif 
        }

		ret = E_OK;
	}
	
	return ret;
	
}

void CCP1_ISR(void)
{
    /* Clear Flag */
    CCP1_INTERRUPT_Clear_FLAG();
    
    
	if(CCP1_InterruptHandler)
	{
		CCP1_InterruptHandler();
	}
    
}

void CCP2_ISR(void)
{
    /* Clear Flag */
    CCP2_INTERRUPT_Clear_FLAG();
    
    
	if(CCP2_InterruptHandler)
	{
		CCP2_InterruptHandler();
	}
    
}


#if CCP_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED  

/**
 * 
 * @param ccp_obj
 * @param _duty
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType CCP_ISCaptureDataReady(uint8* _Capture_Status)
{
	Std_ReturnType ret = E_OK;
    
    if( NULL == _Capture_Status )
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        if (CCP_CAPTURE_READY == (PIR1bits.CCP1IF))
        {
            *_Capture_Status = CCP_CAPTURE_READY;
            /* Clear Flag */
            CCP1_INTERRUPT_Clear_FLAG();
            
        }
        else
        {
            *_Capture_Status = CCP_CAPTURE_NOT_READY;
        }
        
		ret = E_OK;
	}
	
	return ret;
	
}


/**
 * 
 * @param ccp_obj
 * @param _duty
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType CCP_Capture_Mode_Read_Value(uint16* Capture_Value)
{
	Std_ReturnType ret = E_OK;
    CCP_REG_T Capture_Temp_Value = {.ccpr_16Bit = ZERO_INIT };
    
    if( NULL == Capture_Value )
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        Capture_Temp_Value.ccpr_low  = CCPR1L;
        Capture_Temp_Value.ccpr_high = CCPR1H;
        *Capture_Value = Capture_Temp_Value.ccpr_16Bit;
        
		ret = E_OK;
	}
	
	return ret;
	
}


#endif




#if CCP_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED  


/**
 * 
 * @param ccp_obj
 * @param _duty
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType CCP_ISCompareComplete(uint8* _Compare_Status)
{
	Std_ReturnType ret = E_OK;
    
    if( NULL == _Compare_Status )
    {
        ret = E_NOT_OK;
    }
    
    else
    {
		if (CCP_COMPARE_READY == (PIR1bits.CCP1IF))
        {
            *_Compare_Status = CCP_COMPARE_READY;
            /* Clear Flag */
            CCP1_INTERRUPT_Clear_FLAG();
            
        }
        else
        {
            *_Compare_Status = CCP_COMPARE_NOT_READY;
        }
		ret = E_OK;
	}
	
	return ret;
	
}



/**
 * 
 * @param ccp_obj
 * @param _duty
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_t * ccp_obj, uint16 Compare_Value)
{
	
	Std_ReturnType ret = E_OK;
	if( NULL == ccp_obj )
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        CCP_REG_T Comp_Temp_Value = {.ccpr_16Bit = Compare_Value};
        
        if( CCP1_INST == ccp_obj->ccp_inst)
        {
            CCPR1L = Comp_Temp_Value.ccpr_low;
            CCPR1H = Comp_Temp_Value.ccpr_high;
        }
        else if( CCP2_INST == ccp_obj->ccp_inst)
        {
            CCPR2L = Comp_Temp_Value.ccpr_low;
            CCPR2H = Comp_Temp_Value.ccpr_high;
        }
        else 
        { /* Nothing */  }
        ret = E_OK;
    }
	
	return ret;
}

#endif


#if CCP_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED  

/**
 * 
 * @param ccp_obj
 * @param _duty
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t * ccp_obj, const uint8 _duty)
{
	
	Std_ReturnType ret = E_OK;
    uint16 l_temp_reg = ZERO_INIT;
    if( NULL == ccp_obj )
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        l_temp_reg = (uint16)((PR2+1)*(_duty/100.0)*4);
        if(ccp_obj->ccp_inst == CCP1_INST)
        { 
            CCP1CONbits.DC1B = (uint8)(l_temp_reg & (0x0003));
            CCPR1L = (uint8)(l_temp_reg >> 2);        
        }
        else if(ccp_obj->ccp_inst == CCP2_INST)
        {
            CCP2CONbits.DC2B = (uint8)(l_temp_reg & (0x0003));
            CCPR2L = (uint8)(l_temp_reg >> 2);
        }

        ret = E_OK;
    }
	
	return ret;
}

/**
 * 
 * @param ccp_obj
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType CCP_PWM_Start(const ccp_t * ccp_obj)
{
	
	Std_ReturnType ret = E_OK;
    
    if( NULL == ccp_obj )
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        if(ccp_obj->ccp_inst == CCP1_INST)
        {
            CCP1_SELECT_MODE_CONFIGURATION(CCP_PWM_MODE_SEL);
        }
        else if(ccp_obj->ccp_inst == CCP2_INST)
        {
            CCP2_SELECT_MODE_CONFIGURATION(CCP_PWM_MODE_SEL);
        }
        
        ret = E_OK;
    }
	
	return ret;
}



/**
 * 
 * @param ccp_obj
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType CCP_PWM_Stop(const ccp_t * ccp_obj)
{
	
	Std_ReturnType ret = E_OK;
    
    if( NULL == ccp_obj )
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        if(ccp_obj->ccp_inst == CCP1_INST)
        {
            CCP1_SELECT_MODE_CONFIGURATION(CCP_MODULE_DISABLE);
        }
        else if(ccp_obj->ccp_inst == CCP2_INST)
        {
            CCP2_SELECT_MODE_CONFIGURATION(CCP_MODULE_DISABLE);
        }
        
        ret = E_OK;
    }
	
	return ret;
    
}

#endif





static Std_ReturnType Select_Mode(const ccp_t * ccp_obj)
{
	Std_ReturnType ret = E_OK;
    
    if( NULL == ccp_obj )
    {
        ret = E_NOT_OK;
    }
    
    else
    {
		if( CCP_CAPUTR_MODE == (ccp_obj->ccp_mode) && (ccp_obj->ccp_inst == CCP1_INST) )
        {
            /* Capture Mode Timer  Configuration */
            ret = CCP_Capture_Mode_Timer_Select(ccp_obj);
            
			switch(ccp_obj->ccp_mode_variant)
			{
				case CCP_CAPTURE_EVERY_FALLING : 
					CCP1_SELECT_MODE_CONFIGURATION(CCP_CAPTURE_EVERY_FALLING);
				break;
				
				case CCP_CAPTURE_EVERY_RISING : 
					CCP1_SELECT_MODE_CONFIGURATION(CCP_CAPTURE_EVERY_RISING);
				break;
				
				case CCP_CAPTURE_EVERY_4TH_RISING : 
					CCP1_SELECT_MODE_CONFIGURATION(CCP_CAPTURE_EVERY_4TH_RISING);	 					
				break;
				
				case CCP_CAPTURE_EVERY_16TH_RISING : 
					CCP1_SELECT_MODE_CONFIGURATION(CCP_CAPTURE_EVERY_16TH_RISING);	 					
				break;
                
				default : 	ret = E_NOT_OK;											
				break;
			}
			
			/* Pin Configuration */
			ret = gpio_pin_direction_initialize(&(ccp_obj->pin_mcu));
			
		}
        else if(CCP_COMPARE_MODE == (ccp_obj->ccp_mode) && (ccp_obj->ccp_inst == CCP1_INST))
		{
            /* Capture Mode Timer  Configuration */
            ret = CCP_Capture_Mode_Timer_Select(ccp_obj);
            
			switch(ccp_obj->ccp_mode_variant)
			{
				case CCP_COMPARE_MODE_TOGGLE_OUTPUT : 
					CCP1_SELECT_MODE_CONFIGURATION(CCP_COMPARE_MODE_TOGGLE_OUTPUT);
				break;
				
				case CCP_COMPARE_MODE_SET_PIN_HIGH : 
					CCP1_SELECT_MODE_CONFIGURATION(CCP_COMPARE_MODE_SET_PIN_HIGH);
				break;
				
				case CCP_COMPARE_MODE_SET_PIN_LOW : 
					CCP1_SELECT_MODE_CONFIGURATION(CCP_COMPARE_MODE_SET_PIN_LOW);	 					
				break;
				
				case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : 
					CCP1_SELECT_MODE_CONFIGURATION(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);	 					
				break;
                
                case CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT : 
					CCP1_SELECT_MODE_CONFIGURATION(CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT);	 					
				break;
                
				default : 	ret = E_NOT_OK;											
				break;
			}
			
			/* Pin Configuration to be output */
			ret = gpio_pin_initialize(&(ccp_obj->pin_mcu));
			
		}
        else if(CCP_PWM_MODE == (ccp_obj->ccp_mode) && (ccp_obj->ccp_inst == CCP1_INST))
		{
            if ( CCP_PWM_MODE_SEL == ccp_obj->ccp_mode_variant )
            {
                CCP1_SELECT_MODE_CONFIGURATION(CCP_PWM_MODE_SEL);
            }
			else { /* Nothing */}
            
            /* Pin Configuration to be output */
			ret = gpio_pin_initialize(&(ccp_obj->pin_mcu));
			
#if CCP_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED			
			/* Initialize PR2 Register "PWM Frequency" */
			
			PR2 = (uint8)((_XTAL_FREQ / (4.0 * ccp_obj->PWM_Frequency * ccp_obj->timer2_prescaler * ccp_obj->timer2_postscaler ) ) - 1); 
#endif
			
			
		}
        else if( CCP_CAPUTR_MODE == (ccp_obj->ccp_mode) && (ccp_obj->ccp_inst == CCP2_INST) )
        {
            /* Capture Mode Timer  Configuration */
            ret = CCP_Capture_Mode_Timer_Select(ccp_obj);
        
			switch(ccp_obj->ccp_mode_variant)
			{
				case CCP_CAPTURE_EVERY_FALLING : 
					CCP2_SELECT_MODE_CONFIGURATION(CCP_CAPTURE_EVERY_FALLING);
				break;
				
				case CCP_CAPTURE_EVERY_RISING : 
					CCP2_SELECT_MODE_CONFIGURATION(CCP_CAPTURE_EVERY_RISING);
				break;
				
				case CCP_CAPTURE_EVERY_4TH_RISING : 
					CCP2_SELECT_MODE_CONFIGURATION(CCP_CAPTURE_EVERY_4TH_RISING);	 					
				break;
				
				case CCP_CAPTURE_EVERY_16TH_RISING : 
					CCP2_SELECT_MODE_CONFIGURATION(CCP_CAPTURE_EVERY_16TH_RISING);	 					
				break;
                
				default : 	ret = E_NOT_OK;											
				break;
			}
			
			/* Pin Configuration */
			ret = gpio_pin_direction_initialize(&(ccp_obj->pin_mcu));
			
		}
        else if(CCP_COMPARE_MODE == (ccp_obj->ccp_mode) && (ccp_obj->ccp_inst == CCP2_INST))
		{
            /* Capture Mode Timer  Configuration */
            ret = CCP_Capture_Mode_Timer_Select(ccp_obj);
        
			switch(ccp_obj->ccp_mode_variant)
			{
				case CCP_COMPARE_MODE_TOGGLE_OUTPUT : 
					CCP2_SELECT_MODE_CONFIGURATION(CCP_COMPARE_MODE_TOGGLE_OUTPUT);
				break;
				
				case CCP_COMPARE_MODE_SET_PIN_HIGH : 
					CCP2_SELECT_MODE_CONFIGURATION(CCP_COMPARE_MODE_SET_PIN_HIGH);
				break;
				
				case CCP_COMPARE_MODE_SET_PIN_LOW : 
					CCP2_SELECT_MODE_CONFIGURATION(CCP_COMPARE_MODE_SET_PIN_LOW);	 					
				break;
				
				case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : 
					CCP2_SELECT_MODE_CONFIGURATION(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);	 					
				break;
                
                case CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT : 
					CCP2_SELECT_MODE_CONFIGURATION(CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT);	 					
				break;
                
				default : 	ret = E_NOT_OK;											
				break;
			}
			
			/* Pin Configuration to be output */
			ret = gpio_pin_initialize(&(ccp_obj->pin_mcu));
			
		}
        else if(CCP_PWM_MODE == (ccp_obj->ccp_mode) && (ccp_obj->ccp_inst == CCP2_INST))
		{
            if ( CCP_PWM_MODE_SEL == ccp_obj->ccp_mode_variant)
            {
                CCP2_SELECT_MODE_CONFIGURATION(CCP_PWM_MODE_SEL);
            }
			else { /* Nothing */}
            
            /* Pin Configuration to be output */
			ret = gpio_pin_initialize(&(ccp_obj->pin_mcu));
			
#if CCP_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED			
			/* Initialize PR2 Register "PWM Frequency" */
			
			PR2 = (uint8)((_XTAL_FREQ / (4.0 * ccp_obj->PWM_Frequency * ccp_obj->timer2_prescaler * ccp_obj->timer2_postscaler ) ) - 1); 
#endif
			
			
		}
		else { /* Nothing */}
		
	}
	
	return ret;
	
}

static Std_ReturnType CCP_Interrupt_Config(const ccp_t * ccp_obj)
{
	Std_ReturnType ret = E_OK;
    
    if( NULL == ccp_obj )
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        if(CCP1_INST == ccp_obj->ccp_inst)
		{
        #if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
            CCP1_INTERRUPT_Clear_FLAG();
            CCP1_INTERRUPT_ENABLE(); 
            /* Initialize CallBack */
            CCP1_InterruptHandler = ccp_obj->ccp1_intrrupt_handler;
	
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
            Interrupt_Priority_Level_Enable();
             if(ccp_obj->ccp1_priority == INTERRUPT_LOW_PRIORITY)
            {
                INTERRUPT_GlobalInterruptEnableLOW();
                CCP1_INTERRUPT_LOW_PRIORITY();
            }
            else if(ccp_obj->ccp1_priority == INTERRUPT_HIGH_PRIORITY)
            {
                INTERRUPT_GlobalInterruptEnableHigh();
                CCP1_INTERRUPT_HIGH_PRIORITY();
            }
            else{ /* Nothing */ }
        #else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
    
        #endif
        #endif   
        }
        else if(CCP2_INST == ccp_obj->ccp_inst)
		{
        #if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
            CCP2_INTERRUPT_Clear_FLAG();
            CCP2_INTERRUPT_ENABLE(); 
            /* Initialize CallBack */
            CCP2_InterruptHandler = ccp_obj->ccp2_intrrupt_handler;
	
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
            Interrupt_Priority_Level_Enable();
             if(ccp_obj->ccp2_priority == INTERRUPT_LOW_PRIORITY)
            {
                INTERRUPT_GlobalInterruptEnableLOW();
                CCP2_INTERRUPT_LOW_PRIORITY();
            }
            else if(ccp_obj->ccp2_priority == INTERRUPT_HIGH_PRIORITY)
            {
                INTERRUPT_GlobalInterruptEnableHigh();
                CCP2_INTERRUPT_HIGH_PRIORITY();
            }
            else{ /* Nothing */ }
        #else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
    
        #endif
        #endif   
        }

		
		ret = E_OK;
	}
	
	return ret;
}


static Std_ReturnType CCP_Capture_Mode_Timer_Select(const ccp_t * ccp_obj)
{
    if(CCP1_CCP2_TIMER1 == (ccp_obj->ccp_cap_comp_timer))
    {
        /* Timer1 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP2 = 0;
        T3CONbits.T3CCP1 = 0;
        
    }
    else if(CCP1_TIMER1_CCP2_TIMER3 == (ccp_obj->ccp_cap_comp_timer))
    {
        /*  Timer3 is the capture/compare clock source for CCP2;
            Timer1 is the capture/compare clock source for CCP1 */
        T3CONbits.T3CCP2 = 0;
        T3CONbits.T3CCP1 = 1;
    }
    else if(CCP1_CCP2_TIMER3 == (ccp_obj->ccp_cap_comp_timer))
    {
        /*  Timer3 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP2 = 1;
        T3CONbits.T3CCP1 = 0;
    }
    else 
    { /* Nothing */ }
}
