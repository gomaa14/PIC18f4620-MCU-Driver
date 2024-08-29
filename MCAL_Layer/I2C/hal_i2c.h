/* 
 * File:   hal_i2c.h
 * Author: User
 *
 * Created on August 21, 2024, 6:16 PM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H


/************Section :: Includes***********************************/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"


/************Section :: Macro Declaration *************************/

#define I2C_MSSP_MASTER_MODE                                     0x01
#define I2C_MSSP_SLAVE_MODE                                      0x00

#define I2C_SLEW_RATE_ENABLED                                    0X00
#define I2C_SLEW_RATE_DISABLED                                   0X01

#define I2C_SMBUS_MODE_ENABLED                                   0X01
#define I2C_SMBUS_MODE_DISABLED                                  0X00

#define I2C_LAST_BYTE_DATA                                       0x01
#define I2C_LAST_BYTE_ADDRESS                                    0x00

#define I2C_STOP_BIT_DETECTED                                    0X01
#define I2C_STOP_BIT_NOT_DETECTED                                0X00

#define I2C_START_BIT_DETECTED                                   0X01
#define I2C_START_BIT_NOT_DETECTED                               0X00


#define I2C_GENERAL_CALL_INTERRUPT_ENABLED                       0X01
#define I2C_GENERAL_CALL_INTERRUPT_DISABLED                      0X00

#define I2C_MASTER_RECEIVE_MODE_ENABLED                          0x01
#define I2C_MASTER_RECEIVE_MODE_DISABLED                         0x00


#define  I2C_SLAVE_MODE_7_BIT_ADDRESS                            0x06
#define  I2C_SLAVE_MODE_10_BIT_ADDRESS                           0x07
#define  I2C_MASTER_MODE                                         0x08
#define  I2C_FIRMWARE_CONTROLLED_MASTER_MODE                     0x0B
#define  I2C_SLAVE_MODE_7_BIT_ADDRESS_WITH_S_P_BIT_INTERRUPTS    0x0E
#define  I2C_SLAVE_MODE_10_BIT_ADDRESS_WITH_S_P_BIT_INTERRUPTS   0x0F

#define  I2C_ACK_WAS_NOT_RECEIVED_FROM_SLAVE			 		 0x01
#define  I2C_ACK_WAS_RECEIVED_FROM_SLAVE			     		 0x00

#define  I2C_MASTER_RECEIVE_NOT_ACK_CFG                         0X01
#define  I2C_MASTER_RECEIVE_ACK_CFG                             0X00



/************Section :: Macro Function Declaration ****************/

/* SSPSTAT: MSSP STATUS REGISTER (I2C? MODE) */

// Slew Rate Control bit
#define I2C_SLEW_RATE_CONTROL_DISABLED()        (SSPSTATbits.SMP = 1)
#define I2C_SLEW_RATE_CONTROL_ENABLED()         (SSPSTATbits.SMP = 0)
//SMBus Select bit
#define I2C_SMBUS_ENABLE()                      (SSPSTATbits.CKE = 1)
#define I2C_SMBUS_DISABLE()                     (SSPSTATbits.CKE = 0)
// Buffer Full Status bit
#define I2C_BUFFER_FULL_STATUS()                (SSPSTATbits.BF)
// Start bit
#define I2C_START_BIT_STATUS()                  (SSPSTATbits.S)
// Stop bit
#define I2C_STOP_BIT_STATUS()                   (SSPSTATbits.P)
// Data/Address bit
#define I2C_SLAVE_DATA_ADDRESS_STATUS()         (SSPSTATbits.D_nA)


/* SSPCON1: MSSP CONTROL REGISTER 1 (I2C? MODE) */

#define I2C_MODE_SELECT_COFIG(__CONFIG)         (SSPCON1bits.SSPM = __CONFIG)
// Master Synchronous Serial Port Enable bit
#define I2C_MODULE_ENABLE()                     (SSPCON1bits.SSPEN = 1)
#define I2C_MODULE_DISABLE()                    (SSPCON1bits.SSPEN = 0)


/*  SSPCON2: MSSP CONTROL REGISTER 2 (I2C? MODE)*/

// General Call Enable bit (Slave mode only) 
#define I2C_ENABLES_INTERRUPT_WHEN_AGENERAL_CALL()     (SSPCON2bits.GCEN = 1)
#define I2C_DISABLES_INTERRUPT_WHEN_AGENERAL_CALL()    (SSPCON2bits.GCEN = 0)
// Receive Enable bit (Master mode only)
#define I2C_ENABLES_RECEIVE_MODE()                     (SSPCON2bits.RCEN = 1)
#define I2C_DISABLES_RECEIVE_MODE()                    (SSPCON2bits.RCEN = 0)
// Acknowledge Sequence Enable bit (Master Receive mode only)
#define I2C_INITIATES_ACK_SEQUENCE()                   (SSPCON2bits.ACKEN = 1)
#define I2C_ACK_SEQUENCE_IDLE()                        (SSPCON2bits.ACKEN = 0)
//Acknowledge Data bit (Master Receive mode only)
#define I2C_MASTER_RECEIVE_NOT_ACK()                   (SSPCON2bits.ACKDT = 1)
#define I2C_MASTER_RECEIVE_ACK()                       (SSPCON2bits.ACKDT = 0)

// Start Condition Enable/Stretch Enable bit
#define I2C_MASTER_INITIATE_START_CONDITION()          (SSPCON2bits.SEN = 1)
#define I2C_MASTER_START_CONDITION_IDLE()              (SSPCON2bits.SEN = 0)
#define I2C_SLAVE_CLOCK_STRETCHING_ENABLE()            (SSPCON2bits.SEN = 1)
#define I2C_SLAVE_CLOCK_STRETCHING_DISABLE()           (SSPCON2bits.SEN = 0)
// Repeated Start Condition Enable bit (Master mode only)
#define I2C_MASTER_INITIATE_REPEATED_START_CONDITION() (SSPCON2bits.RSEN = 1)
#define I2C_MASTER_REPEATED_START_CONDITION_IDLE()     (SSPCON2bits.RSEN = 0)
// Stop Condition Enable bit (Master mode only)
#define I2C_MASTER_INITIATE_STOP_CONDITION()           (SSPCON2bits.PEN = 1)
#define I2C_MASTER_STOP_CONDITION_IDLE()               (SSPCON2bits.PEN = 0)
// Acknowledge Status bit (Master Transmit mode only)
#define I2C_MASTER_ACK_STATUS()				   		   (SSPCON2bits.ACKSTAT)








/************Section :: User Define Data Type *********************/



typedef struct
{
    uint8 i2c_mode_config;             /* Master Synchronous Serial Port Mode Select bits */  
    uint8 i2c_slave_address;           /* Slave Address */
    uint8 i2c_mode            : 1;     /* I2C: Master or Salve */
    uint8 i2c_slew_rate       : 1;     /* Slew Rate Enable or Disable */
    uint8 SMBus_mode          : 1;     /* SMBus Select bit */
    uint8 i2c_general_call    : 1;     /* Enable INtrruptwhen General Call or not */
    uint8 i2c_master_rec_mode : 1;     /* Receive Enable bit */
    uint8 i2c_Reserved        : 3;     /* 3 Bit Reserved */
    
}i2c_config_t;



typedef struct
{
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*I2C_intrrupt_handler)(void);             /* Default Interrupt Handler */
    void (*I2C_Report_Write_Collision)(void);       /* Write Collision Detect  */
    void (*I2C_Report_Receive_OverFlow)(void);      /* Receive Overflow Indicator */
    interrupt_priority_t mssp_i2c_priority;     
    interrupt_priority_t mssp_i2c_BC_priority; 
#endif
   
	uint32 i2c_clock;                               /* Master Clock Frequency  */
    i2c_config_t i2c_cfg;
}mssp_i2c_t;



/************Section :: Function Prototype  *********************/

Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_MASTER_Write_Blocking(const mssp_i2c_t *i2c_obj, uint8 i2c_data, uint8* _ack);
Std_ReturnType MSSP_I2C_MASTER_Read_Blocking(const mssp_i2c_t *i2c_obj, uint8 ack, uint8* i2c_data);

#endif	/* HAL_I2C_H */

