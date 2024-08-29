/* 
 * File:   ecu_keypad.h
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on May 23, 2024, 1:00 AM
 */

#ifndef ECU_KEYPSD_H
#define	ECU_KEYPSD_H




/*******************Section :: Includes***********************************/


#include "../../MCAL_Layer/GPIO/hal_gpio.h"

#include "ecu_keypad_cfg.h"


/************Section :: Macro Declaration *************************/

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4


/************Section :: Macro Function Declaration ****************/




/************Section :: User Define Data Type *********************/


typedef struct
{
    pin_config_t keypad_row_pins[KEYPAD_ROWS];
    pin_config_t keypad_col_pins[KEYPAD_COLS];
    
}keypad_t;

/************Section :: Function Prototype  *********************/


Std_ReturnType keypad_initialize(const keypad_t* obj);

Std_ReturnType keypad_get_value(const keypad_t* obj, uint8* value);

#endif	/* ECU_KEYPSD_H */

