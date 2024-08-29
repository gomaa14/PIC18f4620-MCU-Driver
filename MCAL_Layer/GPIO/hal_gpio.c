/* 
* File:   hai_gpio.c
* Author: Gomaa Ayman Gomaa 
*
* Created on May 7, 2024, 10:07 PM
*/

#include "hal_gpio.h"



/*Reference to Data Direction Register */
volatile uint8* tris_register [] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};


/*Reference to Port Status Register */
volatile uint8* port_register [] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};


/*Reference to Data Latch Register  */
volatile uint8* lat_register  [] = {&LATA, &LATB, &LATC, &LATD, &LATE};





/****************************Section :: Function Defination ****************************/


#if PORT_PIN_CONFIGURATION == CONFIG_ENABLE


/**
 * @brief  :: Initialize specific pin
 * @param  :: pin_config :: Pointer to The Pin pin_configuration @ref pin_config_t
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */

Std_ReturnType gpio_pin_direction_initialize(const pin_config_t* pin_config)
{
    Std_ReturnType Ret = E_OK;
    
    if( (NULL == pin_config) || (pin_config->Pin >= PORT_PIN_MAX_NUMBER)  || (pin_config->Port >= PORT_MAX_NUMBER))
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
        switch( pin_config->Direction)
        {
            case OUTPUT :                

                CLEAR_BIT(*tris_register[pin_config->Port], pin_config->Pin);
                
                break;
            
            case INPUT :
                
                SET_BIT(*tris_register[pin_config->Port], pin_config->Pin);
                
                break;
            
            default:
                
                Ret = E_NOT_OK;
            
            
            
        }
    }
    
    return Ret;
    
}



/**
 * @brief  :: Get the direction of specific pin
 * @param  :: direction_status
 * @param  :: pin_config :: Pointer to The Pin pin_configuration @ref pin_config_t
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t* pin_config, direction_t* direction_status)
{
    
    Std_ReturnType Ret = E_OK;
    
    if((NULL == pin_config) || (NULL == direction_status) || (pin_config->Pin >= PORT_PIN_MAX_NUMBER)  || (pin_config->Port >= PORT_MAX_NUMBER))
    {
        Ret = E_NOT_OK;
    }
    else
    {
        
        *direction_status = READ_BIT(*tris_register[pin_config->Port], pin_config->Pin);
        
    }
    
    return Ret;
    
}


/**
 * @brief             :: Write on specific pin 
 * @param logic       :: Logic you write it on pin 
 * @param pin_config  :: Pointer to The Pin pin_configuration @ref pin_config_t
 * @return  Status of Function
 *      E_OK      :: The Function Done successfully
 *      E_NOT_OK  :: The Function has issue to perform this action
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t* pin_config, logic_t logic)
{
    Std_ReturnType Ret = E_OK;
    
    if(NULL == pin_config || (pin_config->Pin >= PORT_PIN_MAX_NUMBER)  || (pin_config->Port >= PORT_MAX_NUMBER))
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
        if(logic == HIGH)
        {
            
            SET_BIT(*lat_register[pin_config->Port], pin_config->Pin);
            
        }
        
        else if(logic == LOW)
        {
            
            CLEAR_BIT(*lat_register[pin_config->Port], pin_config->Pin);
        }
        else
        {
            Ret = E_NOT_OK;
        }
        
    }
    
    
    return Ret;
    
    
}

/**
 * @brief            :: Read specific pin 
 * @param pin_config :: Pointer to The Pin pin_configuration @ref pin_config_t
 * @param logic      :: pointer to variable you store logic in it 
 * @return 
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t* pin_config, logic_t* logic)
{
    Std_ReturnType Ret = E_OK;
    
    if((NULL == pin_config) || (NULL == logic) || (pin_config->Pin >= PORT_PIN_MAX_NUMBER)  || (pin_config->Port >= PORT_MAX_NUMBER))
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
        *logic = READ_BIT(*port_register[pin_config->Port], pin_config->Pin);
        
    }
    
    
    return Ret;
    
    
}

/**
 * @brief  :: Toggle specific pin 
 * @param  :: Pointer to The Pin pin_configuration @ref pin_config_t
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t* pin_config)
{
    
    Std_ReturnType Ret = E_OK;
    
    if(NULL == pin_config || (pin_config->Pin >= PORT_PIN_MAX_NUMBER)  || (pin_config->Port >= PORT_MAX_NUMBER))
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
        TOGGLE_BIT(*lat_register[pin_config->Port], pin_config->Pin);
                    
    }
    
    
    return Ret;
    
}


/**
 * @brief            :: initialize pin with direction and initial value 
 * @param pin_config :: Pointer to The Pin pin_configuration @ref pin_config_t
 * @return           :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType gpio_pin_initialize(const pin_config_t* pin_config)
{
    Std_ReturnType Ret = E_OK;
    
    if(NULL == pin_config || (pin_config->Pin >= PORT_PIN_MAX_NUMBER)  || (pin_config->Port >= PORT_MAX_NUMBER))
    {
        Ret = E_NOT_OK;
    }
    else
    {
        
        Ret = gpio_pin_direction_initialize(pin_config);
        Ret = gpio_pin_write_logic(pin_config, pin_config->Logic);
        
    }
    
    return Ret;
    
}


#endif




#if PORT_CONFIGURATION == CONFIG_ENABLE

/**
 * @brief            ::
 * @param port       ::
 * @param direction  ::
 * @return 
 *      E_OK      :: The Function Done successfully
 *      E_NOT_OK  :: The Function has issue to perform this action
 */
Std_ReturnType gpio_port_direction_initialize(port_index_t port, uint8 direction)
{
    Std_ReturnType Ret = E_OK;
    
    if(port >= PORT_MAX_NUMBER)
    {
        Ret = E_NOT_OK;
    }
    else
    {
        *tris_register[port] = direction;
    }
    
    return Ret;
    
    
}
/**
 * @brief                   :: 
 * @param port              :: 
 * @param direction_status  :: 
 * @return 
 *      E_OK      :: The Function Done successfully
 *      E_NOT_OK  :: The Function has issue to perform this action
 */
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8* direction_status)
{
    Std_ReturnType Ret = E_OK;
    
    if((NULL == direction_status) || (port >= PORT_MAX_NUMBER))
    {
        Ret = E_NOT_OK;
    }
    else
    {
        
        *direction_status = *tris_register[port];
        
    }
    return Ret;
    
}
/**
 * @brief        ::
 * @param port   :: 
 * @param logic  ::
 * @return 
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic)
{
    Std_ReturnType Ret = E_OK;
    
    if(port >= PORT_MAX_NUMBER)
    {
        Ret = E_NOT_OK;
    }
    else
    {
        *lat_register[port] = logic;
        
    }

    
    return Ret;
    
    
    
}

/**
 * @brief       :: 
 * @param port  ::
 * @param logic ::
 * @return 
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8* logic)
{
    Std_ReturnType Ret = E_OK;
    
    if((NULL == logic) || ((port >= PORT_MAX_NUMBER)))
    {
        Ret = E_NOT_OK;
    }
    else
    {
        *logic = *port_register[port];
    }
    
    return Ret;
    
    
    
}

/**
 * @brief       ::
 * @param port  ::
 * @return 
 *      E_OK :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType gpio_port_toggle_logic(port_index_t port)
{
    Std_ReturnType Ret = E_OK;
    
    if(((port >= PORT_MAX_NUMBER)))
    {
        Ret = E_NOT_OK;
    }
    else
    {
        *lat_register[port] ^= PORT_MASK;
        
    }
    
    return Ret;
    
    
}


/**
 * @brief       ::
 * @param port  :: 
 * @return 
 *      E_OK :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */

Std_ReturnType gpio_port_initialize(port_index_t port, uint8 direction, uint8 logic)
{
    Std_ReturnType Ret = E_OK;
    
    if(port >= PORT_MAX_NUMBER)
    {
        Ret = E_NOT_OK;
    }
    else
    {
        Ret = gpio_port_direction_initialize(port, direction);
        Ret = gpio_port_write_logic(port, logic);
        
    }
    
    return Ret;
    
    
}

#endif


