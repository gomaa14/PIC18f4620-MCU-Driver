/* 
 * File:   ecu_button.c
 * Author: Gomaa Ayman Gomaa
 *
 * Created on May 15, 2024, 12:36 AM
 */


#include "ecu_button.h"



/****************************Section :: Function Defination ****************************/


#if BUTTON_COFIGURATION == BUTTON_ENABLE

/**
 * @brief      :: Initialize the pin on button  
 * @param btn  :: pointer to button configuration 
 * @return     :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType button_initialize(const button_t* btn)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == btn)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_initialize(&(btn->button_pin));
        
    }
    
    return ret;
    
}


/**
 * @brief             :: Read the state of button 
 * @param btn         :: pointer to button configuration 
 * @param btn_state   :: pointer to state of button 
 * @return            :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType button_read(const button_t* btn, button_state_t* btn_state)
{
    Std_ReturnType ret = E_OK;
    
    logic_t logic = LOW;
    
    if((NULL == btn) || (NULL == btn_state))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_read_logic(&(btn->button_pin), &logic);
        
        if(btn->button_active == ACTIVE_HIGH )
        {
            
            if(logic == HIGH)
            {
                *btn_state = BUTTON_PRESSED;
            }
            else
            {
                *btn_state = BUTTON_RELEASED;
            }
            
            
        }
        else if(btn->button_active == ACTIVE_LOW )
        {
            
            
            if(logic == LOW)
            {
                *btn_state = BUTTON_PRESSED;
            }
            else
            {
                *btn_state = BUTTON_RELEASED;
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

