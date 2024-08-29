/* 
 * File:   ecu_relay.h
 * Author: User
 *
 * Created on May 16, 2024, 9:24 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H



/*******************Section :: Includes***********************************/

#include "ecu_relay_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"



/************Section :: Macro Declaration *************************/



/************Section :: Macro Function Declaration ****************/


/************Section :: User Define Data Type *********************/


typedef enum
{
    RELAY_OFF =0,
    RELAY_ON
    
}relay_status_t;

typedef struct
{
    uint8 relay_port            :4; 
    uint8 relay_pin             :3; 
    relay_status_t relay_status   ; /* @ref :: relay_status_t*/
    
}relay_t;


/************Section :: Function Prototype  *********************/

Std_ReturnType relay_initialize (const relay_t* relay);


Std_ReturnType relay_turn_on (const relay_t* relay);


Std_ReturnType relay_turn_off (const relay_t* relay);


#endif	/* ECU_RELAY_H */

