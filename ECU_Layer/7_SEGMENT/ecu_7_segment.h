/* 
 * File:   ecu_7_segment.h
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on May 21, 2024, 3:28 PM
 */

#ifndef ECU_7_SEGMENT_H
#define	ECU_7_SEGMENT_H




/*******************Section :: Includes***********************************/

#include "../../MCAL_Layer/GPIO/hal_gpio.h"

#include "ecu_7_segment_cfg.h"

/************Section :: Macro Declaration *************************/

#define SEVEN_SEGMENT_PIN   4

/************Section :: Macro Function Declaration ****************/


/************Section :: User Define Data Type *********************/

typedef enum 
{
    SEVEN_SEMENT_COMMON_ANODE,
    SEVEN_SEMENT_COMMON_CATODE
}seven_segment_common_t;

typedef struct
{
    
    pin_config_t segment_pin[SEVEN_SEGMENT_PIN];
    
    seven_segment_common_t seven_segment_common;
    
}seven_segment_t;



/************Section :: Function Prototype  *********************/

Std_ReturnType seven_segment_initialize(const seven_segment_t* seg);


Std_ReturnType seven_segment_write(const seven_segment_t* seg, uint8 number);

#endif	/* ECU_7_SEGMENT_H */

