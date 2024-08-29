/* 
 * File:   ecu_led.c
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on May 7, 2024, 11:01 PM
 */


#include "ecu_led.h"

#if LED_CONFIGURATION == LED_ENABLE

/**
 * @brief        :: initialize led to be output 
 * @param led    :: pointer to led module configuration 
 * @return       :: status of function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType led_initialize(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj;
        pin_obj.Port = led->port_name;
        pin_obj.Pin = led->pin_name;
        pin_obj.Logic = led->led_state;
        pin_obj.Direction = OUTPUT;
        
        ret = gpio_pin_initialize(&pin_obj);
    }
    
    return ret;
    
            
}

/**
 * @brief        :: turn on led 
 * @param led    :: pointer to led module configuration 
 * @return       :: status of function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType led_on(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    
    
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj;
        pin_obj.Port = led->port_name;
        pin_obj.Pin = led->pin_name;
        pin_obj.Logic = led->led_state;
        pin_obj.Direction = OUTPUT;
        
        ret = gpio_pin_write_logic(&pin_obj, HIGH);
        
        
    }
    
    return ret;
    
}

/**
 * @brief        :: turn off led 
 * @param led    :: pointer to led module configuration 
 * @return       :: status of function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType led_off(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj;
        pin_obj.Port = led->port_name;
        pin_obj.Pin = led->pin_name;
        pin_obj.Logic = led->led_state;
        pin_obj.Direction = OUTPUT;
        
        ret = gpio_pin_write_logic(&pin_obj, LOW);
    }
    
    return ret;
}

/**
 * @brief        :: toggle status of led  
 * @param led    :: pointer to led module configuration 
 * @return       :: status of function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType led_toggle(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj;
        pin_obj.Port = led->port_name;
        pin_obj.Pin = led->pin_name;
        pin_obj.Logic = led->led_state;
        pin_obj.Direction = OUTPUT;
        
        ret = gpio_pin_toggle_logic(&pin_obj);
    }
    
    return ret;
}

#endif

