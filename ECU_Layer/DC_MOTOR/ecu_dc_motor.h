/* 
 * File:   ecu_dc_motor.h
 * Author: User
 *
 * Created on May 18, 2024, 1:52 AM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H



/*******************Section :: Includes***********************************/


#include "ecu_dc_motor_cfg.h"

#include "../../MCAL_Layer/GPIO/hal_gpio.h"


/************Section :: Macro Declaration *************************/

#define DC_MOTOR_OFF 0X00
#define DC_MOTOR_ON  0X01

#define MOTOR_MOVE_RIGHT 0X02
#define MOTOR_MOVE_LEFT  0X03


#define DC_MOTOR_PIN_1 0
#define DC_MOTOR_PIN_2 1



/************Section :: Macro Function Declaration ****************/


/************Section :: User Define Data Type *********************/



typedef struct
{
    uint8 dc_motor_port :4;
    uint8 dc_motor_pin  :3;
    uint8 motor_status  :1;
    
}dc_motor_pin_t;


typedef struct
{
    dc_motor_pin_t dc_motor[2];
    
}dc_motor_t;



/************Section :: Function Prototype  *********************/

Std_ReturnType dc_motor_initialize(const dc_motor_t* obj);

Std_ReturnType dc_motor_move_right(const dc_motor_t* obj);

Std_ReturnType dc_motor_move_left(const dc_motor_t* obj);

Std_ReturnType dc_motor_stop(const dc_motor_t* obj);


#endif	/* ECU_DC_MOTOR_H */

