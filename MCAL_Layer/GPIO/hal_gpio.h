/* 
* File:   hal_gpio.h
* Author: Gomaa Ayman Gomaa
*
* Created on May 7, 2024, 10:31 PM
*/

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/*******************Section :: Includes***********************************/
#include "pic18f4620.h"

#include "../mcal_std_types.h"

#include "../device_config.h"

#include "hal_gpio_cfg.h"

/************Section :: Macro Declaration *************************/

#define BIT_MASK     (uint8)     1
#define PORT_MASK               0XFF

#define PORT_PIN_MAX_NUMBER      8
#define PORT_MAX_NUMBER          5


/************Section :: Macro Function Declaration ****************/

// Accsess register by address  
#define HWREG8(_x)       (*((volatile uint8 *)(_x)))

//Set bit in register  
#define SET_BIT(REG, BIT_BOSN)          (REG |= ( BIT_MASK << BIT_BOSN))

//clear bit in register 
#define CLEAR_BIT(REG, BIT_BOSN)        (REG &= ~( BIT_MASK << BIT_BOSN))

//toggle bit in register 
#define TOGGLE_BIT(REG, BIT_BOSN)       (REG ^= ( BIT_MASK << BIT_BOSN))


#define READ_BIT(REG, BIT_BOSN)         ((REG >>BIT_BOSN) & BIT_MASK)

/************Section :: User Define Data Type *********************/

typedef enum
{
    LOW=0,
    HIGH
}logic_t;

typedef enum
{
    OUTPUT =0,
    INPUT
}direction_t;

typedef enum
{
    PIN0 =0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7

}pin_index_t;

typedef enum
{
    PORTA_INDEX =0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX

}port_index_t;




typedef struct
{ 
    uint8 Pin       :3;     /* @ref port_index_t */
    uint8 Port      :3;     /* @ref pin_index_t  */
    uint8 Logic     :1;     /* @ref logic_t      */
    uint8 Direction :1;     /* @ref direction_t  */

}pin_config_t;



/************Section :: Function Prototype  *********************/




Std_ReturnType gpio_pin_direction_initialize(const pin_config_t* pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t* pin_config, direction_t* direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t* pin_config, logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t* pin_config, logic_t* logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t* pin_config);
Std_ReturnType gpio_pin_initialize(const pin_config_t* pin_config);





Std_ReturnType gpio_port_direction_initialize(port_index_t port, uint8 direction);
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8* direction_status);
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic);
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8* logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);
Std_ReturnType gpio_port_initialize(port_index_t port, uint8 direction, uint8 logic);




#endif	/* HAL_GPIO_H */

