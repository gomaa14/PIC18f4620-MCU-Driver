/* 
 * File:   hal_ccp.h
 * Author: Gomaa Ayman Gomaa
 *
 * Created on July 16, 2024, 10:47 AM
 */

#ifndef HAL_CCP_H
#define	HAL_CCP_H

/************Section :: Includes***********************************/

#include "pic18f4620.h"
#include "../mcal_std_types.h"

#include "../GPIO/hal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"

#include "hal_ccp_cfg.h"


/************Section :: Macro Declaration *************************/

#define CCP_MODULE_DISABLE            			 ((uint8)0x00) 

#define CCP_CAPTURE_EVERY_FALLING      		 ((uint8)0x04)
#define CCP_CAPTURE_EVERY_RISING       		 ((uint8)0x05)
#define CCP_CAPTURE_EVERY_4TH_RISING       	 ((uint8)0x06)
#define CCP_CAPTURE_EVERY_16TH_RISING      	 ((uint8)0x07)

#define CCP_COMPARE_MODE_TOGGLE_OUTPUT 		 ((uint8)0x02)
#define CCP_COMPARE_MODE_SET_PIN_HIGH 			 ((uint8)0x08)
#define CCP_COMPARE_MODE_SET_PIN_LOW 			 ((uint8)0x09)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT  	 ((uint8)0x0A)
#define CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT  ((uint8)0x0B)

#define CCP_PWM_MODE_SEL						 ((uint8)0x0C)



/* CCP1 Capture Mode State*/
#define CCP_CAPTURE_NOT_READY      0x00
#define CCP_CAPTURE_READY		   0x01

/* CCP Compare Mode State*/
#define CCP_COMPARE_NOT_READY      0x00
#define CCP_COMPARE_READY		   0x01


/* Pre-scaler */
#define CCP_PRESCALE_DIV_BY_1					1
#define CCP_PRESCALE_DIV_BY_4					4
#define CCP_PRESCALE_DIV_BY_16					16

/* Post-scaler*/
#define CCP_POSTSCALE_DIV_BY_1					1
#define CCP_POSTSCALE_DIV_BY_2					2
#define CCP_POSTSCALE_DIV_BY_3					3
#define CCP_POSTSCALE_DIV_BY_4					4
#define CCP_POSTSCALE_DIV_BY_5					5
#define CCP_POSTSCALE_DIV_BY_6					6
#define CCP_POSTSCALE_DIV_BY_7					7
#define CCP_POSTSCALE_DIV_BY_8					8
#define CCP_POSTSCALE_DIV_BY_9					9
#define CCP_POSTSCALE_DIV_BY_10				10
#define CCP_POSTSCALE_DIV_BY_11				11
#define CCP_POSTSCALE_DIV_BY_12				12
#define CCP_POSTSCALE_DIV_BY_13				13
#define CCP_POSTSCALE_DIV_BY_14				14
#define CCP_POSTSCALE_DIV_BY_15				15
#define CCP_POSTSCALE_DIV_BY_16				16


/************Section :: Macro Function Declaration ****************/


#define CCP1_SELECT_MODE_CONFIGURATION(__CONFIG)            (CCP1CONbits.CCP1M = __CONFIG)
#define CCP2_SELECT_MODE_CONFIGURATION(__CONFIG)            (CCP2CONbits.CCP2M = __CONFIG)


/************Section :: User Define Data Type *********************/

typedef enum
{
    CCP_CAPUTR_MODE = 0,
    CCP_COMPARE_MODE,
    CCP_PWM_MODE 
	
}ccp_mode_t;

typedef enum
{
	CCP1_INST,
	CCP2_INST
}ccp_inst_t;


typedef enum
{
	CCP1_CCP2_TIMER1 = 0,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER3
            
}ccp_capture_timer_t;

typedef union
{
    struct
    {
        uint8 ccpr_low;
        uint8 ccpr_high;
    };
    
    struct
    {
        uint16 ccpr_16Bit;
    };
}CCP_REG_T;

typedef struct 
{
	ccp_inst_t ccp_inst;
    ccp_mode_t ccp_mode;
	uint8 ccp_mode_variant;
    pin_config_t pin_mcu;
    ccp_capture_timer_t ccp_cap_comp_timer;
    
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void (*ccp1_intrrupt_handler) (void);
    interrupt_priority_t ccp1_priority;     
#endif    
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void (*ccp2_intrrupt_handler) (void);
    interrupt_priority_t ccp2_priority;     
#endif  
#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)    || (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)
    uint32 PWM_Frequency;
	uint8 timer2_prescaler  :2;
	uint8 timer2_postscaler :4;	
#endif

    
}ccp_t;

/************Section :: Function Prototype  *********************/



Std_ReturnType CCP_Init(const ccp_t * ccp_obj);
Std_ReturnType CCP_DeInit(const ccp_t * ccp_obj);


#if CCP_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED  

Std_ReturnType CCP_ISCaptureDataReady(uint8* _Capture_Status);

Std_ReturnType CCP_Capture_Mode_Read_Value(uint16* Capture_Value);

#endif



#if CCP_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED  

Std_ReturnType CCP_ISCompareComplete(uint8* _Compare_Status);
Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_t * ccp_obj, uint16 Compare_Value);

#endif


#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)  || (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)

Std_ReturnType CCP_PWM_Set_Duty(const ccp_t * ccp_obj, const uint8 _duty);
Std_ReturnType CCP_PWM_Start(const ccp_t * ccp_obj);
Std_ReturnType CCP_PWM_Stop(const ccp_t * ccp_obj);

#endif

#endif	/* HAL_CCP_H */

