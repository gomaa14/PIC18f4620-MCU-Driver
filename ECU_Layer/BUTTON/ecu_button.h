/* 
 * File:   ecu_button.h
 * Author: Gomaa Ayman Gomaa
 *
 * Created on May 15, 2024, 12:36 AM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H


/************Section :: Includes***********************************/

#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_button_cfg.h"



/************Section :: Macro Declaration *************************/



/************Section :: Macro Function Declaration ****************/



/************Section :: User Define Data Type *********************/

typedef enum
{
    
    BUTTON_RELEASED =0,
    BUTTON_PRESSED
    
}button_state_t;

typedef enum
{
    ACTIVE_LOW  =0,
    ACTIVE_HIGH   
    
}button_active_t;


typedef struct 
{
    pin_config_t   button_pin;        /* @ref pin_config_t      */
    button_state_t button_state;      /* @ref button_state_t    */
    button_active_t button_active;    /* @ref button_active_t   */
    
}button_t;



/************Section :: Function Prototype  *********************/


Std_ReturnType button_initialize(const button_t* btn);

Std_ReturnType button_read(const button_t* btn, button_state_t* btn_state);




#endif	/* ECU_BUTTON_H */

