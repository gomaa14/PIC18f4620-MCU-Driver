/* 
 * File:   ecu_dc_motor.c
 * Author: User
 *
 * Created on May 18, 2024, 1:52 AM
 */

#include "ecu_dc_motor.h"



#if DC_MOTOR_CONFIGURATION == DC_MOTOR_ENABLE

/**
 * @brief     :: initialize the DC motor pins  
 * @param obj :: pointer to two pin of DC motor  
 * @return       :: status of function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType dc_motor_initialize(const dc_motor_t* obj)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == obj)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        pin_config_t pin_1;
        pin_1.Pin = obj->dc_motor[DC_MOTOR_PIN_1].dc_motor_pin;
        pin_1.Port = obj->dc_motor[DC_MOTOR_PIN_1].dc_motor_port;
        pin_1.Direction = OUTPUT;
        pin_1.Logic = obj->dc_motor[DC_MOTOR_PIN_1].motor_status;
        
        
        ret = gpio_pin_initialize(&pin_1);
        
        pin_config_t pin_2;
        pin_2.Pin = obj->dc_motor[DC_MOTOR_PIN_2].dc_motor_pin;
        pin_2.Port = obj->dc_motor[DC_MOTOR_PIN_2].dc_motor_port;
        pin_2.Direction = OUTPUT;
        pin_2.Logic = obj->dc_motor[DC_MOTOR_PIN_2].motor_status;
        
        ret = gpio_pin_initialize(&pin_2);
        
    }
    
    return ret;
    
}


/**
 * @brief     :: moving  DC motor  right
 * @param obj :: pointer to two pin of DC motor  
 * @return       :: status of function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t* obj)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == obj)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        pin_config_t pin_1;
        pin_1.Pin = obj->dc_motor[DC_MOTOR_PIN_1].dc_motor_pin;
        pin_1.Port = obj->dc_motor[DC_MOTOR_PIN_1].dc_motor_port;
        pin_1.Direction = OUTPUT;
        pin_1.Logic = obj->dc_motor[DC_MOTOR_PIN_1].motor_status;
		
        pin_config_t pin_2;
        pin_2.Pin = obj->dc_motor[DC_MOTOR_PIN_2].dc_motor_pin;
        pin_2.Port = obj->dc_motor[DC_MOTOR_PIN_2].dc_motor_port;
        pin_2.Direction = OUTPUT;
        pin_2.Logic = obj->dc_motor[DC_MOTOR_PIN_2].motor_status;
        
        ret = gpio_pin_write_logic(&pin_1, HIGH);
        ret = gpio_pin_write_logic(&pin_2, LOW);
    }
    
    return ret;
    
}

/**
 * @brief     :: moving  DC motor  left
 * @param obj :: pointer to two pin of DC motor  
 * @return       :: status of function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t* obj)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == obj)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        pin_config_t pin_1;
        pin_1.Pin = obj->dc_motor[DC_MOTOR_PIN_1].dc_motor_pin;
        pin_1.Port = obj->dc_motor[DC_MOTOR_PIN_1].dc_motor_port;
        pin_1.Direction = OUTPUT;
        pin_1.Logic = obj->dc_motor[DC_MOTOR_PIN_1].motor_status;
		
        pin_config_t pin_2;
        pin_2.Pin = obj->dc_motor[DC_MOTOR_PIN_2].dc_motor_pin;
        pin_2.Port = obj->dc_motor[DC_MOTOR_PIN_2].dc_motor_port;
        pin_2.Direction = OUTPUT;
        pin_2.Logic = obj->dc_motor[DC_MOTOR_PIN_2].motor_status;
        
        ret = gpio_pin_write_logic(&pin_1, LOW);
        ret = gpio_pin_write_logic(&pin_2, HIGH);
    }
    
    return ret;
    
}

/**
 * @brief     :: stopping the DC motor 
 * @param obj :: pointer to two pin of DC motor  
 * @return       :: status of function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType dc_motor_stop(const dc_motor_t* obj)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == obj)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        pin_config_t pin_1;
        pin_1.Pin = obj->dc_motor[DC_MOTOR_PIN_1].dc_motor_pin;
        pin_1.Port = obj->dc_motor[DC_MOTOR_PIN_1].dc_motor_port;
        pin_1.Direction = OUTPUT;
        pin_1.Logic = obj->dc_motor[DC_MOTOR_PIN_1].motor_status;
		
        pin_config_t pin_2;
        pin_2.Pin = obj->dc_motor[DC_MOTOR_PIN_2].dc_motor_pin;
        pin_2.Port = obj->dc_motor[DC_MOTOR_PIN_2].dc_motor_port;
        pin_2.Direction = OUTPUT;
        pin_2.Logic = obj->dc_motor[DC_MOTOR_PIN_2].motor_status;
        
       ret = gpio_pin_write_logic(&pin_1,  LOW);
        ret = gpio_pin_write_logic(&pin_2, LOW);
    }
    
    return ret;
    
}


#endif

