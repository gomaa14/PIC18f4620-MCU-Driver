/* 
 * File:   ecu_relay.c
 * Author: User
 *
 * Created on May 16, 2024, 9:24 PM
 */


#include "ecu_relay.h"


#if RELAY_CONFIGURATION == RELAY_ENABLE
/**
 * @brief       : initialize the relay configuration and to be output
 * @param relay : pointer to relay type 
  * @return     : Status of Function
 *      E_OK      :: The Function Done successfully
 *      E_NOT_OK  :: The Function has issue to perform this action
 */
Std_ReturnType relay_initialize (const relay_t* relay)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        pin_config_t pin_config = {.Port = relay->relay_port , 
                                   .Pin = relay->relay_pin, 
                                    .Direction = OUTPUT, 
                                    .Logic = relay->relay_status};
        
        ret = gpio_pin_initialize(&pin_config);
        
        
    }
    
    
    return ret;
    
}

/**
 * @brief       : turn on the relay
 *@param relay : pointer to relay type 
 * @return     : Status of Function
 *      E_OK      :: The Function Done successfully
 *      E_NOT_OK  :: The Function has issue to perform this action
 */
Std_ReturnType relay_turn_on (const relay_t* relay)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t  pin_config = {.Port = relay->relay_port , 
                                   .Pin = relay->relay_pin, 
                                    .Direction = OUTPUT, 
                                    .Logic = HIGH};
        
        ret = gpio_pin_write_logic(&pin_config, pin_config.Logic);
    }
    
    
    return ret;
    
}

/**
 * @brief       : turn off the relay
 *@param relay : pointer to relay type
 * @return     : Status of Function
 *      E_OK      :: The Function Done successfully
 *      E_NOT_OK  :: The Function has issue to perform this action
 */
Std_ReturnType relay_turn_off (const relay_t* relay)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        pin_config_t  pin_config = {.Port = relay->relay_port , 
                                   .Pin = relay->relay_pin, 
                                    .Direction = OUTPUT, 
                                    .Logic = LOW};
        
        ret = gpio_pin_write_logic(&pin_config, pin_config.Logic);
        
        
    }
    
    
    return ret;
    
}

#endif

