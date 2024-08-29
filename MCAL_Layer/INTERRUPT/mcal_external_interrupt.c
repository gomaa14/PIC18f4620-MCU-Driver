/* 
 * File:   mcal_external_interrupt.c
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on June 19, 2024, 12:03 PM
 */


#include "mcal_external_interrupt.h"


/* Pointer To CallBack Function For External Interrupt INTx*/
static InterruptHandler INT0_InterruptHandler =NULL;
static InterruptHandler INT1_InterruptHandler =NULL;
static InterruptHandler INT2_InterruptHandler =NULL;


/* Pointer To CallBack Function For External Interrupt RBx*/
static InterruptHandler RB4_InterruptHandler_High = NULL;
static InterruptHandler RB4_InterruptHandler_Low  = NULL;
static InterruptHandler RB5_InterruptHandler_High = NULL;
static InterruptHandler RB5_InterruptHandler_Low  = NULL;
static InterruptHandler RB6_InterruptHandler_High = NULL;
static InterruptHandler RB6_InterruptHandler_Low  = NULL;
static InterruptHandler RB7_InterruptHandler_High = NULL;
static InterruptHandler RB7_InterruptHandler_Low  = NULL;






static Std_ReturnType INTx_interrupt_Enable(const INTx_interrupt_t* int_obj);
static Std_ReturnType INTx_interrupt_Disable(const INTx_interrupt_t* int_obj);
static Std_ReturnType INTx_interrupt_Clear_Flag(const INTx_interrupt_t* int_obj);
static Std_ReturnType INTx_interrupt_Priority_Init(const INTx_interrupt_t* int_obj);
static Std_ReturnType INTx_interrupt_Edge_Init(const INTx_interrupt_t* int_obj);
static Std_ReturnType INTx_interrupt_Pin_Init(const INTx_interrupt_t* int_obj);

static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler) (void));
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler) (void));
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler) (void));
static Std_ReturnType INTx_SetInterruptHandler(const INTx_interrupt_t* int_obj);





static Std_ReturnType RBx_interrupt_Enable(const RBx_interrupt_t* int_obj);
static Std_ReturnType RBx_interrupt_Disable(const RBx_interrupt_t* int_obj);
static Std_ReturnType RBx_interrupt_Clear_Flag(const RBx_interrupt_t* int_obj);
static Std_ReturnType RBx_interrupt_Priority_Init(const RBx_interrupt_t* int_obj);
static Std_ReturnType RBx_interrupt_Pin_Init(const RBx_interrupt_t* int_obj);

static Std_ReturnType RB4_SetInterruptHandler(const RBx_interrupt_t* int_obj);
static Std_ReturnType RB5_SetInterruptHandler(const RBx_interrupt_t* int_obj);
static Std_ReturnType RB6_SetInterruptHandler(const RBx_interrupt_t* int_obj);
static Std_ReturnType RB7_SetInterruptHandler(const RBx_interrupt_t* int_obj);
static Std_ReturnType RBx_SetInterruptHandler(const RBx_interrupt_t* int_obj);


/**
 * @brief         ::
 * @param int_obj :: 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType Initialize_INTx_interrupt(const INTx_interrupt_t* int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
		/** Disable External Interrupt */
		
		ret = INTx_interrupt_Disable(int_obj);
		
		/* Clear Interrupt Flag */
		
		ret &= INTx_interrupt_Clear_Flag(int_obj);
		
		/* Configure External Interrupt Edge */
		
		ret &= INTx_interrupt_Edge_Init(int_obj);
		
        
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 

		/* Configure External Interrupt Priority */
		
		ret &= INTx_interrupt_Priority_Init(int_obj);
		
        #endif
        
		/* Configure External Interrupt Pin */
		
		ret &= INTx_interrupt_Pin_Init(int_obj);
		
		/* Configure Default  Interrupt CallBack*/
		
        ret &= INTx_SetInterruptHandler(int_obj);
		
		/* Enable External Interrupt */
		
		ret &= INTx_interrupt_Enable(int_obj);
		
		  
    }
    
    return ret;
    
}


void INT0_ISR(void)
{
	/* Clear Flag For External Interrupt 0*/
	
	INT0_External_Interrupt_Flag_Clear();
	
	/* Code :: Executed From MCAL Interrupt Context   */
	
	
	/* CallBack Function */
	
	if(NULL != INT0_InterruptHandler)
	{
		INT0_InterruptHandler();
	}
	
	else
	{
		/* Nothing */
	}
	
}


void INT1_ISR(void)
{
	/* Clear Flag For External Interrupt 1*/
	
	INT1_External_Interrupt_Flag_Clear();
	
	/* Code */
	
	
	/* CallBack Function */
	
	if(NULL != INT1_InterruptHandler)
	{
		INT1_InterruptHandler();
	}
	
	else
	{
		/* Nothing */
	}
	
	
}


void INT2_ISR(void)
{
	/* Clear Flag For External Interrupt 2 */
	
	INT2_External_Interrupt_Flag_Clear();
	
	/* Code */
	
	
	/* CallBack Function */
	
	if(NULL != INT2_InterruptHandler)
	{
		INT2_InterruptHandler();
	}
	
	else
	{
		/* Nothing */
	}
	
	
}


/**
 * @brief         ::
 * @param int_obj
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType Deinitialize_INTx_interrupt(const INTx_interrupt_t* int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        ret = INTx_interrupt_Disable(int_obj);
		   
    }
    
    return ret;
    
}










/**
 * @brief         ::
 * @param int_obj
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
 
Std_ReturnType Initialize_RBx_interrupt(const RBx_interrupt_t* int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        
        /* Disable RBx External interrupt */
		
		ret = RBx_interrupt_Disable(int_obj);
		
		/* Clear Interrupt Flag */
		
		ret &= RBx_interrupt_Clear_Flag(int_obj);
		
		
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

		/* Configure External Interrupt Priority */
		
		ret &= RBx_interrupt_Priority_Init(int_obj);
		
#endif		
		
		
		/* Configure External Interrupt Pin */
		
		ret &= RBx_interrupt_Pin_Init(int_obj);
		
		/* Configure Default  Interrupt CallBack*/
		
		ret &= RBx_SetInterruptHandler(int_obj);
		
		
        /* Enable RBx External interrupt */
		
		ret &= RBx_interrupt_Enable(int_obj);
		
    }
    
    return ret;
    
}


void RB4_ISR_HIGH(void)
{
    RB_Port_Change_Interrupt_Flag_Clear();
    
    if(NULL == RB4_InterruptHandler_High )  { /* Nothing*/}
    else
    {
        RB4_InterruptHandler_High();
        
    }
}

void RB4_ISR_LOW(void)
{
    RB_Port_Change_Interrupt_Flag_Clear();
    
    if(NULL == RB4_InterruptHandler_Low )  { /* Nothing*/}
    else
    {
        RB4_InterruptHandler_Low();
        
    }
}

void RB5_ISR_HIGH(void)
{
    RB_Port_Change_Interrupt_Flag_Clear();
    
    if(NULL == RB5_InterruptHandler_High )  { /* Nothing*/}
    else
    {
        RB5_InterruptHandler_High();
        
    }
}

void RB5_ISR_LOW(void)
{
    RB_Port_Change_Interrupt_Flag_Clear();
    
    if(NULL == RB5_InterruptHandler_Low )  { /* Nothing*/}
    else
    {
        RB5_InterruptHandler_Low();
        
    }
}

void RB6_ISR_HIGH(void)
{
    RB_Port_Change_Interrupt_Flag_Clear();
    
    if(NULL == RB6_InterruptHandler_High )  { /* Nothing*/}
    else
    {
        RB6_InterruptHandler_High();
        
    }
}

void RB6_ISR_LOW(void)
{
    RB_Port_Change_Interrupt_Flag_Clear();
    
    if(NULL == RB6_InterruptHandler_Low )  { /* Nothing*/}
    else
    {
        RB6_InterruptHandler_Low();
        
    }
}


void RB7_ISR_HIGH(void)
{
    RB_Port_Change_Interrupt_Flag_Clear();
    
    if(NULL == RB7_InterruptHandler_High )  { /* Nothing*/}
    else
    {
        RB7_InterruptHandler_High();
        
    }
}

void RB7_ISR_LOW(void)
{
    RB_Port_Change_Interrupt_Flag_Clear();
    
    if(NULL == RB7_InterruptHandler_Low )  { /* Nothing*/}
    else
    {
        RB7_InterruptHandler_Low();
        
    }
}





/**
 * @brief         ::
 * @param int_obj
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
 
Std_ReturnType Deinitialize_RBx_interrupt(const RBx_interrupt_t* int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        ret = RBx_interrupt_Disable(int_obj);
		
        ret = E_OK;
    }
    
    return ret;
    
}


/**
 * @brief         ::
 * @param int_obj
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
 
static Std_ReturnType INTx_interrupt_Enable(const INTx_interrupt_t* int_obj)
{
	Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
		
        switch((int_obj->source))
        {
            case INTERRUT_INT0:
			
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  == INTERRUPT_FEATURE_ENABLE
                Interrupt_Priority_Level_Enable();
				INTERRUPT_GlobalInterruptEnableHigh();  
#else
            
				INTERRUPT_GlobalInterruptEnable();

#endif
			
				INT0_External_Interrupt_Enable();
			break;
            
            case INTERRUT_INT1:

#if INTERRUPT_PRIORITY_LEVELS_ENABLE  == INTERRUPT_FEATURE_ENABLE
                
            Interrupt_Priority_Level_Enable();
            
            if( (int_obj->priority) == INTERRUPT_HIGH_PRIORITY )
			{
				INTERRUPT_GlobalInterruptEnableHigh();
			}
			else if( (int_obj->priority) == INTERRUPT_LOW_PRIORITY )
			{
				INTERRUPT_GlobalInterruptEnableLOW();
			}
			else
			{
				
			}
            
#else
            
            INTERRUPT_GlobalInterruptEnable();

#endif
				INT1_External_Interrupt_Enable();
			break;
            
            case INTERRUT_INT2:
			
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  == INTERRUPT_FEATURE_ENABLE
                
            Interrupt_Priority_Level_Enable();
            
            if( (int_obj->priority) == INTERRUPT_HIGH_PRIORITY )
			{
				INTERRUPT_GlobalInterruptEnableHigh();
			}
			else if( (int_obj->priority) == INTERRUPT_LOW_PRIORITY )
			{
				INTERRUPT_GlobalInterruptEnableLOW();
			}
			else
			{
				
			}
            
#else
            
            INTERRUPT_GlobalInterruptEnable();

#endif
				INT2_External_Interrupt_Enable();
			break;
            
            default:  ret = E_NOT_OK;
			break;
				
        }
        
    }
    
    return ret;
    
}

/**
 * @brief         ::
 * @param int_obj
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */

static Std_ReturnType INTx_interrupt_Disable(const INTx_interrupt_t* int_obj)
{
	Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        
        switch((int_obj->source))
        {
            case INTERRUT_INT0: INT0_External_Interrupt_Disable();    break;
            
            case INTERRUT_INT1: INT1_External_Interrupt_Disable();    break;
            
            case INTERRUT_INT2: INT2_External_Interrupt_Disable();    break;
            
            default:  ret = E_NOT_OK;                                break;
			
			
        }
        
    }
    
    return ret;
    
}

/**
 * @brief         :: 
 * @param int_obj
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
 
static Std_ReturnType INTx_interrupt_Clear_Flag(const INTx_interrupt_t* int_obj)
{
	Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        
        switch((int_obj->source))
        {
            case INTERRUT_INT0: INT0_External_Interrupt_Flag_Clear();    break;
            
            case INTERRUT_INT1: INT1_External_Interrupt_Flag_Clear();    break;
            
            case INTERRUT_INT2: INT2_External_Interrupt_Flag_Clear();    break;
            
            default:  ret = E_NOT_OK;                                    break;
			
			
        }
        
    }
    
    return ret;
}

/**
 * @brief         :: 
 * @param int_obj
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

static Std_ReturnType INTx_interrupt_Priority_Init(const INTx_interrupt_t* int_obj)
{
	Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
		if((int_obj->source) == INTERRUT_INT1)
        {
            if((int_obj->priority) == INTERRUPT_LOW_PRIORITY)
            {
                INT1_External_Interrupt_Low_Priority();
            }
            else if((int_obj->priority) == INTERRUPT_HIGH_PRIORITY)
            {
                INT1_External_Interrupt_High_Priority();
            }
            else
            {
                ret = E_NOT_OK;
            }
        }
        else if((int_obj->source) == INTERRUT_INT2)
        {
            if((int_obj->priority) == INTERRUPT_LOW_PRIORITY)
            {
                INT2_External_Interrupt_Low_Priority();
            }
            else if((int_obj->priority) == INTERRUPT_HIGH_PRIORITY)
            {
                INT2_External_Interrupt_High_Priority();
            }
            else
            {
                ret = E_NOT_OK;
            }
        }
        else
        {
            ret = E_NOT_OK;
        }
    }
    
    return ret;
    
}

#endif


/**
 * @brief         ::
 * @param int_obj
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */

static Std_ReturnType INTx_interrupt_Edge_Init(const INTx_interrupt_t* int_obj)
{
	Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
		switch((int_obj->source))
        {
            case INTERRUT_INT0:
				
				if(INTERRUT_FALLING_EDGE == (int_obj->edge) )
                {
                    External_Interrupt_0_Falling_Edge_Select();
                }
                else if ( INTERRUT_RISING_EDGE == (int_obj->edge) )
                {
                    External_Interrupt_0_Rising_Edge_Select();
                }
                else
                {
                    ret = E_NOT_OK;
                }
				
			break;
            
            case INTERRUT_INT1:
			
				if(INTERRUT_FALLING_EDGE == (int_obj->edge) )
                {
                    External_Interrupt_1_Falling_Edge_Select();
                }
                else if ( INTERRUT_RISING_EDGE == (int_obj->edge) )
                {
                    External_Interrupt_1_Rising_Edge_Select();
                }
                else
                {
                    ret = E_NOT_OK;
                }
			
			break;
            
            case INTERRUT_INT2:
			
				if(INTERRUT_FALLING_EDGE == (int_obj->edge) )
                {
                    External_Interrupt_2_Falling_Edge_Select();
                }
                else if ( INTERRUT_RISING_EDGE == (int_obj->edge) )
                {
                    External_Interrupt_2_Rising_Edge_Select();
                }
                else
                {
                    ret = E_NOT_OK;
                }
			
			break;
            
            default:
			
				ret = E_NOT_OK;
				
			break;
			
        }
        
    }
    
    return ret;
    
}

/**
 * @brief         ::
 * @param int_obj
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
static Std_ReturnType INTx_interrupt_Pin_Init(const INTx_interrupt_t* int_obj)
{
	Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        ret = gpio_pin_direction_initialize( &(int_obj->mcu_pin) );
        
    }
    
    return ret;
    
}


/**
 * @brief         :: 
 * @param InterruptHandler  :: POinter To Function "ISR Fun"  
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
 
static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler) (void))
{
	Std_ReturnType ret = E_NOT_OK;
	
	if (NULL == InterruptHandler)
	{
		ret = E_NOT_OK;
	}
	else
	{
		INT0_InterruptHandler = InterruptHandler;
		
		ret= E_OK;
	}
	
	return ret;
	
}

/**
 * @brief         :: 
 * @param InterruptHandler  :: POinter To Function "ISR Fun"  
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
 
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler) (void))
{
	Std_ReturnType ret = E_NOT_OK;
	
	if (NULL == InterruptHandler)
	{
		ret = E_NOT_OK;
	}
	else
	{
		INT1_InterruptHandler = InterruptHandler;
		
		ret= E_OK;
	}
	
	return ret;
	
}


/**
 * @brief         ::
 * @param InterruptHandler  :: POinter To Function "ISR Fun"  
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
 
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler) (void))
{
	Std_ReturnType ret = E_NOT_OK;
	
	if (NULL == InterruptHandler)
	{
		ret = E_NOT_OK;
	}
	else
	{
		INT2_InterruptHandler = InterruptHandler;
		
		ret= E_OK;
	}
	
	return ret;
	
}


/**
 * @brief         ::
 * @param int_obj 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
static Std_ReturnType INTx_SetInterruptHandler(const INTx_interrupt_t* int_obj)
{
	Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        
        switch((int_obj->source))
        {
            case INTERRUT_INT0: ret = INT0_SetInterruptHandler(int_obj->Eternal_InterruptHandler);    break;
            
            case INTERRUT_INT1: ret = INT1_SetInterruptHandler(int_obj->Eternal_InterruptHandler);    break;
            
            case INTERRUT_INT2: ret = INT2_SetInterruptHandler(int_obj->Eternal_InterruptHandler);    break;
            
            default:  ret = E_NOT_OK;                                    break;
			
			
        }
        
    }
    
    return ret;
}





/**
 * @brief         ::
 * @param int_obj 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
static Std_ReturnType RBx_interrupt_Enable(const RBx_interrupt_t* int_obj)
{
	Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
		#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
			
			Interrupt_Priority_Level_Enable();
			
			if( INTERRUPT_HIGH_PRIORITY == (int_obj->priority))
			{
				INTERRUPT_GlobalInterruptEnableHigh();
			}
			else if( INTERRUPT_LOW_PRIORITY == (int_obj->priority))
			{
				INTERRUPT_GlobalInterruptEnableLOW();
			}
			else
			{
				/* Nothing*/
			}
		
		#else
			
			INTERRUPT_GlobalInterruptEnable();
			
			
		#endif
		
		RB_Port_Change_Interrupt_Enable();
		
	}
	
	return ret;
	
}

/**
 * @brief         ::
 * @param int_obj 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
 
static Std_ReturnType RBx_interrupt_Disable(const RBx_interrupt_t* int_obj)
{
	Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
		RB_Port_Change_Interrupt_Disable();
		
	}
	
	return ret;
	
}


/**
 * @brief         ::
 * @param int_obj 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
 
static Std_ReturnType RBx_interrupt_Clear_Flag(const RBx_interrupt_t* int_obj)
{
	Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
		RB_Port_Change_Interrupt_Flag_Clear();
		
	}
	
	return ret;
	
}



/**
 * @brief         :: 
 * @param int_obj 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

static Std_ReturnType RBx_interrupt_Priority_Init(const RBx_interrupt_t* int_obj)
{
	Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
		if( INTERRUPT_HIGH_PRIORITY == (int_obj->priority))
		{
			RB_Port_Change_Interrupt_High_Priority();
		}
		else if( INTERRUPT_LOW_PRIORITY == (int_obj->priority))
		{
			RB_Port_Change_Interrupt_LOw_Priority();
		}
		else
		{
			/* Nothing*/
		}
	}
	
	return ret;
	
}

#endif

/**
 * @brief         :: * @brief         ::
 * @param int_obj 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
 
static Std_ReturnType RBx_interrupt_Pin_Init(const RBx_interrupt_t* int_obj)
{
	Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
		
		ret = gpio_pin_direction_initialize(&(int_obj->mcu_pin));
		
	}
	
	return ret;
	
}


/**
 * @brief         :: 
 * @param int_obj 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
static Std_ReturnType RB4_SetInterruptHandler(const RBx_interrupt_t* int_obj)
{
	Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
		RB4_InterruptHandler_High = int_obj->Eternal_InterruptHandler_High;
		RB4_InterruptHandler_Low  = int_obj->Eternal_InterruptHandler_Low;
	}
	
	return ret;
	
}

/**
 * @brief         :: 
 * @param int_obj 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
static Std_ReturnType RB5_SetInterruptHandler(const RBx_interrupt_t* int_obj)
{
	Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
		RB5_InterruptHandler_High = int_obj->Eternal_InterruptHandler_High;
		RB5_InterruptHandler_Low  = int_obj->Eternal_InterruptHandler_Low;
	}
	
	return ret;
	
}


/**
 * @brief         ::
 * @param int_obj 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
static Std_ReturnType RB6_SetInterruptHandler(const RBx_interrupt_t* int_obj)
{
	Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
		RB6_InterruptHandler_High = int_obj->Eternal_InterruptHandler_High;
		RB6_InterruptHandler_Low  = int_obj->Eternal_InterruptHandler_Low;
	}
	
	return ret;
	
}


/**
 * @brief         ::
 * @param int_obj 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
static Std_ReturnType RB7_SetInterruptHandler(const RBx_interrupt_t* int_obj)
{
	Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
		RB7_InterruptHandler_High = int_obj->Eternal_InterruptHandler_High;
		RB7_InterruptHandler_Low  = int_obj->Eternal_InterruptHandler_Low;
		
	}
	
	return ret;
	
}


/**
 * @brief         ::
 * @param int_obj 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
static Std_ReturnType RBx_SetInterruptHandler(const RBx_interrupt_t* int_obj)
{
	Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
		switch (int_obj->mcu_pin.Pin)
		{
            case PIN4:
                
				ret = RB4_SetInterruptHandler(int_obj);
				
            break;
            
            case PIN5:
                
				ret = RB5_SetInterruptHandler(int_obj);
				
            break; 
           
            case PIN6:
                
				ret = RB6_SetInterruptHandler(int_obj);
				
            break;
            
            case PIN7:
                
				ret = RB7_SetInterruptHandler(int_obj);
				
            break;
             
            default :
                ret = E_NOT_OK; 
				
            break;
			
		}
	}
	
	return ret;
	
}


