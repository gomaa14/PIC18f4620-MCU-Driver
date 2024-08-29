/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: Gomaa Ayman Gomaa
 *
 * Created on June 19, 2024, 1:28 PM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

/*******************Section :: Includes***********************************/



/************Section :: Macro Declaration *************************/

#define INTERRUPT_FEATURE_ENABLE    1
#define INTERRUPT_FEATURE_DISABLE   0




//#define INTERRUPT_PRIORITY_LEVELS_ENABLE             INTERRUPT_FEATURE_ENABLE

#define EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE       INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE   INTERRUPT_FEATURE_ENABLE

#define ADC_INTERRUPT_FEATURE_ENABLE                 INTERRUPT_FEATURE_ENABLE

#define TIMER0_INTERRUPT_FEATURE_ENABLE              INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_FEATURE_ENABLE              INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_FEATURE_ENABLE              INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_FEATURE_ENABLE              INTERRUPT_FEATURE_ENABLE

#define CCP1_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE


#define EUSART_RX_INTERRUPT_FEATURE_ENABLE           INTERRUPT_FEATURE_ENABLE
#define EUSART_TX_INTERRUPT_FEATURE_ENABLE           INTERRUPT_FEATURE_ENABLE

#define MSSP_I2C_INTERRUPT_FEATURE_ENABLE                 INTERRUPT_FEATURE_ENABLE



/************Section :: Macro Function Declaration ****************/


/************Section :: User Define Data Type *********************/



/************Section :: Function Prototype  *********************/



#endif	/* MCAL_INTERRUPT_GEN_CFG_H */

