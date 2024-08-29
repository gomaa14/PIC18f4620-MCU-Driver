/* 
 * File:   ecu_led.h
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on May 7, 2024, 11:01 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H




/************Section :: Includes***********************************/

#include "../../MCAL_Layer/GPIO/hal_gpio.h"

#include "ecu_led_cfg.h"


/************Section :: Macro Declaration *************************/


/************Section :: Macro Function Declaration ****************/




/************Section :: User Define Data Type *********************/

typedef enum 
{
    LED_OFF =0,
    LED_ON        
}led_status_t;

typedef struct
{
    uint8 port_name :4; // @ref port_index_t
    uint8 pin_name  :3; // @ref pin_index_t
    uint8 led_state :1; // @ref led_status_t
    
}led_t;


/************Section :: Function Prototype  *********************/


Std_ReturnType led_initialize(const led_t *led);

Std_ReturnType led_on(const led_t *led);

Std_ReturnType led_off(const led_t *led);

Std_ReturnType led_toggle(const led_t *led);


#endif	/* ECU_LED_H */

