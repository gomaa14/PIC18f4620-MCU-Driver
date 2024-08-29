/* 
 * File:   hal_adc.h
 * Author: Gomaa Ayman Gomaa
 *
 * Created on July 1, 2024, 12:02 AM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H




/*******************Section :: Includes***********************************/

#include "hal_adc_cfg.h"

#include "pic18f4620.h"

#include "../mcal_std_types.h"

#include "../GPIO/hal_gpio.h"

#include "../INTERRUPT/mcal_internal_interrupt.h"




/************Section :: Macro Declaration *************************/


#define ADC_AN0_ANALOG_FUNCTIONALITY		0x0E  
#define ADC_AN1_ANALOG_FUNCTIONALITY		0x0D    
#define ADC_AN2_ANALOG_FUNCTIONALITY		0x0C    
#define ADC_AN3_ANALOG_FUNCTIONALITY		0x0B    
#define ADC_AN4_ANALOG_FUNCTIONALITY		0x0A    
#define ADC_AN5_ANALOG_FUNCTIONALITY		0x09    
#define ADC_AN6_ANALOG_FUNCTIONALITY		0x08    
#define ADC_AN7_ANALOG_FUNCTIONALITY		0x07    
#define ADC_AN8_ANALOG_FUNCTIONALITY		0x06    
#define ADC_AN9_ANALOG_FUNCTIONALITY		0x05   
#define ADC_AN10_ANALOG_FUNCTIONALITY		0x04    
#define ADC_AN11_ANALOG_FUNCTIONALITY		0x03   
#define ADC_AN12_ANALOG_FUNCTIONALITY		0x02    
#define ADC_ALL_ANALOG_FUNCTIONALITY		0x00  
#define ADC_ALL_DIGITAL_FUNCTIONALITY		0x0F  


#define ADC_RESULT_RIGHT                    1
#define ADC_RESULT_LEFT                     0

#define ADC_VOLTAGE_REFRENCE_ENABLED        1
#define ADC_VOLTAGE_REFRENCE_DISABLED		0

#define ADC_CONVERSION_COMPLETED            1
#define ADC_CONVERSION_IN_PROGRESS          0

/************Section :: Macro Function Declaration ****************/


/*  Read A/D Conversion Status bit  :: A/D conversion in progress / A/D Idle */
#define ADC_CONVERSION_STATUS()      (ADCON0bits.GO_DONE)

/* Start A/D Conversion */
#define ADC_CONVERSION_START()      (ADCON0bits.GO_DONE = 1)  

/* Enable ADC Conversion  */

#define ADC_CONVERTER_ENABLE()       (ADCON0bits.ADON = 1)  


/* Disable ADC Conversion  */
#define ADC_CONVERTER_DISABLE()      (ADCON0bits.ADON = 0)

/*
* @brief  :: Voltage Reference Configuration bit
* @note   ::
* 		ADC_ENABLE_VOLATAGE_REFRENCE    :: Voltage Reference is Vref+ & Vref-
*       ADC_DISABLE_VOLATAGE_REFRENCE   :: Voltage Reference is VDD   & VSS
*/

#define ADC_ENABLE_VOLATAGE_REFRENCE()  do{ ADCON1bits.VCFG0 = 1 ;\
											ADCON1bits.VCFG1 = 1 ;\
                                            }while(0)

//#define ADC_ENABLE_VOLATAGE_REFRENCE()    (ADCON1bits.VCFG = 11)

#define ADC_DISABLE_VOLATAGE_REFRENCE()  do{ ADCON1bits.VCFG0 = 0 ;\
											 ADCON1bits.VCFG1 = 0 ;\
                                            }while(0)  

//#define ADC_DISABLE_VOLATAGE_REFRENCE()   (ADCON1bits.VCFG = 00)



/*
 * @brief ::    A/D Port Configuration Control bits  
 * @note  ::    When you configuration  AN04 Analog functionality
 *              That mean you configure AN4, AN3, AN2, AN1 and AN0 as Analog functionality also 
 * 
 */

#define  ADC_ANALOG_DIGITAL_PORT_CONFIG(__CONFIG)   (ADCON1bits.PCFG = __CONFIG)



/* ADC Result Format Select bit*/

#define ADC_RESULT_RIGHT_FORMAT()		(ADCON2bits.ADFM = 1)  
#define ADC_RESULT_LEFT_FORMAT()		(ADCON2bits.ADFM = 0)




/************Section :: User Define Data Type *********************/

typedef uint16 adc_result_t;


/*
 * @brief ::  Analog Channel Select  
 */
typedef enum 
{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12
	
}adc_channel_select_t;


/*
 * @brief ::  ADC Acquisition Time Select bits
 */


typedef enum
{
	ADC_0_TAD = 0,
	ADC_2_TAD  ,
	ADC_4_TAD  ,
	ADC_6_TAD  ,
	ADC_8_TAD  ,
	ADC_12_TAD ,
	ADC_16_TAD ,
	ADC_20_TAD 
	
}adc_acquisition_time_t;

/*
 * @brief ::  ADC Conversion Clock Select bits
 */


typedef enum
{
	ADC_CONVERSION_CLOCK_FOSC_DIV_2  = 0,
	ADC_CONVERSION_CLOCK_FOSC_DIV_8,
	ADC_CONVERSION_CLOCK_FOSC_DIV_32,
	ADC_CONVERSION_CLOCK_FRC,
	ADC_CONVERSION_CLOCK_FOSC_DIV_4 ,
	ADC_CONVERSION_CLOCK_FOSC_DIV_16,
	ADC_CONVERSION_CLOCK_FOSC_DIV_64
	
}adc_conversion_clock_t;



typedef struct 
{
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
	void (*ADC_InterruptHandler)(void);       /*  POinter  to CallBack Function    */
	interrupt_priority_t priority;	          /*  Priority Level                   */
#endif
	adc_acquisition_time_t  acquisition_time; /*  @ref :: adc_acquisition_time_t   */
	adc_conversion_clock_t  conversion_clock; /*  @ref :: adc_conversion_clock_t   */
	adc_channel_select_t  channel_select;     /*  @ref :: adc_channel_select_t     */
	uint8 voltage_reference : 1;              /*  Voltage Reference Configuration  */                   
	uint8 result_formate    : 1;              /*  ADC Result Format Select         */              
	uint8 ADC_Reeserved     : 6;                               
}adc_confg_t;


/************Section :: Function Prototype  *********************/



Std_ReturnType ADC_Init(const adc_confg_t* _adc);
Std_ReturnType ADC_DeInit(const adc_confg_t* _adc);

Std_ReturnType ADC_SelectChannel(const adc_confg_t* _adc, adc_channel_select_t channel);

Std_ReturnType ADC_StartConversion(const adc_confg_t* _adc);

Std_ReturnType ADC_IsConversionDone(const adc_confg_t* _adc, uint8* conversion_Status);

Std_ReturnType ADC_GetConversionResult(const adc_confg_t* _adc, adc_result_t* result);



Std_ReturnType ADC_GetConversion_Blocking(const adc_confg_t* _adc, adc_channel_select_t channel,
								 adc_result_t* result);


Std_ReturnType ADC_StartConversion_Interrupt(const adc_confg_t* _adc, adc_channel_select_t channel);


#endif	/* HAL_ADC_H */

