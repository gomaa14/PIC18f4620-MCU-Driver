/* 
 * File:   hal_usart.h
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on August 4, 2024, 5:45 AM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H




/************Section :: Includes***********************************/

#include "hal_usart_cfg.h"
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"



/************Section :: Macro Declaration *************************/


/* Selection EUSART Working Mode */
#define EUSART_SYNCHRONOUS_MODE_CFG								1
#define EUSART_ASYNCHRONOUS_MODE_CFG							0

/* Selection EUSART Baud Rate */
#define EUSART_ASYNCHRONOUS_HIGH_BAUD_RAT_CFG					1
#define EUSART_ASYNCHRONOUS_LOW_BAUD_RATE_CFG					0

/* Baud Rate Generator Register Size */
#define EUSART_16_BIT_BAUD_RATE_GENERATOR_CFG					1
#define EUSART_08_BIT_BAUD_RATE_GENERATOR_CFG					0


/* -------------------------------------------------------- */

/* Selection EUSART Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLED_CFG						1
#define EUSART_ASYNCHRONOUS_TX_DISABLEd_CFG						0

/* Selection EUSART 9-Bit Transmit Enable */
#define EUSART_SELECTS_9_BIT_TX_CFG								1
#define EUSART_SELECTS_8_BIT_TX_CFG								0


/* Selection EUSART Transmit Interrupt Enable */
#define EUSART_TX_INTERRUPT_ENABLED_CFG							1
#define EUSART_TX_INTERRUPT_DISABLEd_CFG						0

/* -------------------------------------------------------- */

/* Selection EUSART Receive Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLED_CFG						1
#define EUSART_ASYNCHRONOUS_RX_DISABLEd_CFG						0

/* Selection EUSART 9-Bit Receive Enable */
#define EUSART_SELECTS_9_BIT_RX_CFG								1
#define EUSART_SELECTS_8_BIT_RX_CFG								0

/* Selection EUSART Receive Interrupt Enable */
#define EUSART_RX_INTERRUPT_ENABLED_CFG							1
#define EUSART_RX_INTERRUPT_DISABLEd_CFG						0

/* -------------------------------------------------------- */
/*  EUSART Overrun Error */
#define EUSART_OVERRUN_ERROR_DETECTED							1
#define EUSART_OVERRUN_ERROR_CLEARED							0
/*  EUSART Framing Error */
#define EUSART_FRAMING_ERROR_DETECTED							1
#define EUSART_FRAMING_ERROR_CLEARED							0


/************Section :: Macro Function Declaration ****************/

/*  TXSTA: transmit status and control register */


#define EUSART_TRANSMIT_SHIFT_REGISTER_STATUS()			 	 (TXSTAbits.TRMT)

#define EUSART_ASYNCHRONOUS_HIGH_BAUD_RATE()			 	 (TXSTAbits.BRGH = 1)
#define EUSART_ASYNCHRONOUS_LOW_BAUD_RATE()			 	 	 (TXSTAbits.BRGH = 0)

#define EUSART_SYNCHRONOUS_MODE() 							 (TXSTAbits.SYNC = 1)
#define EUSART_ASYNCHRONOUS_MODE() 							 (TXSTAbits.SYNC = 0)

#define EUSART_TRANSMIT_ENABLED()							 (TXSTAbits.TXEN = 1)
#define EUSART_TRANSMIT_DISABLED()							 (TXSTAbits.TXEN = 0)

#define EUSART_SELECTS_9_BIT_TRANSMISSION()					 (TXSTAbits.TX9 = 1)
#define EUSART_SELECTS_8_BIT_TRANSMISSION()					 (TXSTAbits.TX9 = 0)



/* RCSTA: receive status and control register */


#define EUSART_OVERRUN_ERROR_STATUS()						 (RCSTAbits.OERR)

#define EUSART_FRAMING_ERROR_STATUS()						 (RCSTAbits.FERR)

#define EUSART_ASYNCHRONOUS_ENABLE_RECEIVER()				 (RCSTAbits.CREN = 1)
#define EUSART_ASYNCHRONOUS_DISABLE_RECEIVER()				 (RCSTAbits.CREN = 0)

#define EUSART_SELECTS_9_BIT_RECEPTION()					 (RCSTAbits.RX9 = 1)
#define EUSART_SELECTS_8_BIT_RECEPTION()					 (RCSTAbits.RX9 = 0)

#define EUSART_SERIAL_PORT_ENABLED()						 (RCSTAbits.SPEN = 1)
#define EUSART_SERIAL_PORT_DISABLED()						 (RCSTAbits.SPEN = 0)


/* BAUDCON: baud rate control register */


#define EUSART_16_BIT_BAUD_RATE_GENERATOR()					 (BAUDCONbits.BRG16 = 1)
#define EUSART_08_BIT_BAUD_RATE_GENERATOR()					 (BAUDCONbits.BRG16 = 0)




/************Section :: User Define Data Type *********************/

typedef enum {
    BAUDRAT_ASYN_8_BIT_LOW_SPEED =0,
    BAUDRAT_ASYN_8_BIT_HIGH_SPEED,
    BAUDRAT_ASYN_16_BIT_LOW_SPEED,
    BAUDRAT_ASYN_16_BIT_HIGH_SPEED,
    BAUDRAT_SYN_8_BIT = 4,
    BAUDRAT_SYN_16_BIT = 7       
            
}baud_rate_gen_t;



typedef struct
{
	uint8 usart_tx_reserved         : 5;
	uint8 usart_tx_enable           : 1;
	uint8 usart_tx_9_bit_enable     : 1;
	uint8 usart_tx_interrupt_enable : 1;
}usart_tx_cfg_t;

typedef struct
{
	uint8 usart_rx_reserved         : 5;
	uint8 usart_rx_enable           : 1;
	uint8 usart_rx_9_bit_enable     : 1;
	uint8 usart_rx_interrupt_enable : 1;
}usart_rx_cfg_t;

typedef union
{
	struct
	{
		uint8 usart_tx_reserved   : 6;
		uint8 usart_ferr          : 1;
		uint8 usart_oerr          : 1;
	};
	
	uint8 status;
	
}usart_error_status_t;


typedef struct {
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE  
	void (*EUSART_TX_Default_Interrupt_Handler)(void);
    interrupt_priority_t EUSART_TX_priority; 
#endif  
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE  
	void (*EUSART_RX_Default_Interrupt_Handler)(void);
    void (*EUSART_FramingError_Handler)(void);
	void (*EUSART_overrunError_Handler)(void);
    interrupt_priority_t EUSART_RX_priority; 
#endif
	uint32 BaudRate;
	baud_rate_gen_t baud_rate_gen_config;
	usart_tx_cfg_t usart_tx_cfg;
	usart_rx_cfg_t usart_rx_cfg;
	usart_error_status_t usart_error_status;
}usart_t;


 
/************Section :: Function Prototype  *********************/

Std_ReturnType EUSART_ASYNC_Init(const usart_t* eusart_obj);
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t* eusart_obj);
Std_ReturnType EUSART_ASYNC_Read_Byte_Blocking(const usart_t* eusart_obj, uint8* _data );
Std_ReturnType EUSART_ASYNC_Read_Byte_NON_Blocking(const usart_t* eusart_obj, uint8* _data );
Std_ReturnType EUSART_ASYNC_Write_Byte_Blocking(const usart_t* eusart_obj, uint8 _data );
Std_ReturnType EUSART_ASYNC_Write_String_Blocking(const usart_t* eusart_obj, uint8* _data );
Std_ReturnType EUSART_ASYNC_Write_Byte_NON_Blocking(const usart_t* eusart_obj, uint8 _data );
Std_ReturnType EUSART_ASYNC_Write_String_NON_Blocking(const usart_t* eusart_obj, uint8* _data );

#endif	/* HAL_USART_H */

