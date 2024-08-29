/* 
 * File:   hal_eeprom.h
 * Author: User
 *
 * Created on June 28, 2024, 1:50 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H


/*******************Section :: Includes***********************************/

#include "pic18f4620.h"

#include "../mcal_std_types.h"

#include "../INTERRUPT/mcal_internal_interrupt.h"



/************Section :: Macro Declaration *************************/

/* Flash Program or Data EEPROM Memory Select bit */
#define ACCESS_FLASH_PROGRAM_MEMORY   1 
#define ACCESS_DATA_EEPROM_MEMORY     0

/* Flash Program/Data EEPROM or Configuration Select bit */
#define ACCESS_CONFIGURATION_REGISTERS               1     
#define ACCESS_FLASH_PROGRAM_OR_DATA_EEPROM_MEMORY   0   

/* Flash Program/Data EEPROM Write Enable bit */
#define  ENABLE_WRITE_CYCLES            1
#define  INHIBITS_WRITE_CYCLES          0

/* Write Control bit */
#define  INITIATES_ADATA_EEPROM_WRITE            1
#define  WRITE_CYCLE_TO_THE_EEPROM_IS_COMPLETE   0

/* Read Control bit */

#define  INITIATES_AN_EEPROM_READ            1
#define  DOES_NOT_INITIATE_AN_EEPROM_READ    0




/************Section :: Macro Function Declaration ****************/




/************Section :: User Define Data Type *********************/



/************Section :: Function Prototype  *********************/

Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData);
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8* bData);


#endif	/* HAL_EEPROM_H */

