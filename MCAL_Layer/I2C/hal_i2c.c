/* 
 * File:   hal_i2c.c
 * Author: User
 *
 * Created on August 21, 2024, 6:16 PM
 */

#include "hal_i2c.h"

#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

static void (* MSSP_InterruptHandler) (void) = NULL;
static void (* MSSP_RWC_InterruptHandler) (void) = NULL;
static void (* MSSP_RRO_InterruptHandler) (void) = NULL;
#endif


static Std_ReturnType I2C_Select_Mode_Confg(const mssp_i2c_t *i2c_obj);
static Std_ReturnType I2C_Slew_Rate_Confg(const mssp_i2c_t *i2c_obj);
static Std_ReturnType I2C_SMBus_Confg(const mssp_i2c_t *i2c_obj);
static Std_ReturnType I2C_General_Call_Confg(const mssp_i2c_t *i2c_obj);
static Std_ReturnType I2C_Master_Receive_Confg(const mssp_i2c_t *i2c_obj);
static Std_ReturnType I2C_Interrupt_Confg(const mssp_i2c_t *i2c_obj);

/**
 * 
 * @param i2c_obj
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable Module */
        I2C_MODULE_DISABLE();
        /* I2C Select Mode */
        ret = I2C_Select_Mode_Confg(i2c_obj);
        if( I2C_MSSP_MASTER_MODE == i2c_obj->i2c_cfg.i2c_mode)
        { /* I2C Master Mode Configuration*/
            
            /* I2C Clock Configuration*/
            SSPADD = (uint8)( (_XTAL_FREQ/(4.0*(i2c_obj->i2c_clock))) - 1);
            //SSPADD = (uint8)(((_XTAL_FREQ/4.0)/i2c_obj->i2c_clock)-1 );
            //ret |= I2C_Master_Receive_Confg(i2c_obj);
            
        }
        else if( I2C_MSSP_SLAVE_MODE == i2c_obj->i2c_cfg.i2c_mode)     
        {/* I2C Slave Mode Configuration */
            
            /* I2C General Call Configuration */
            ret |= I2C_General_Call_Confg(i2c_obj);
            /* Clear Write Collision Detect */
            SSPCON1bits.WCOL = 0; /*  No collision "By Default" */
            /* Clear Receive Overflow  Detect */
            SSPCON1bits.SSPOV = 0; /* No overflow */
            /* Release Clock */
            SSPCON1bits.CKP =1; /* Releases clock In Slave mode */
            /* Assign The I2C Slave Address */
            SSPADD = i2c_obj->i2c_cfg.i2c_slave_address;
        }
        else {/* Nothing */}   
        
        /* I2C GPIO Configuration*/
        TRISCbits.RC3 = 1;          //Configuration pin RC3 "SCL" to be INPUT
        TRISCbits.RC4 = 1;          //Configuration pin RC4 "SDA" to be INPUT
        
		/* I2C Slew Rate Control */
        ret |= I2C_Slew_Rate_Confg(i2c_obj); 
        /* I2C SMBus Control */
        ret |= I2C_SMBus_Confg(i2c_obj);
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE        
		/* Interrupt Configuration */
        ret |= I2C_Interrupt_Confg(i2c_obj);
#endif
        /* Enable Module */
        I2C_MODULE_ENABLE();
        
    }
    
    return ret;
     
}

/**
 * 
 * @param i2c_obj
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable Module */
        I2C_MODULE_DISABLE();
        /* Disable Interrupt */
    #if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		MSSP_I2C_INTERRUPT_DISABLE();
        MSSP_I2C_BUS_COL_INTERRUPT_DISABLE();
    #endif
        
        ret = E_OK;
    }
    
    return ret;
     
}

/**
 * 
 * @param i2c_obj
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Initialize Start condition on SDA and SCL pins */
        I2C_MASTER_INITIATE_START_CONDITION();
        /* Wait for the Completion of the start condition */
        while(SSPCON2bits.SEN);
        /* Clear MSSP Interrupt Clear Flag -> SSPIF*/
        PIR1bits.SSPIF = 0;
        /* Report Start Condition Detection */
        if(I2C_START_BIT_STATUS() == I2C_START_BIT_DETECTED)
        {
            ret = E_OK;
        }
        else if(I2C_START_BIT_STATUS() == I2C_START_BIT_NOT_DETECTED)
        {
            ret =E_NOT_OK;
        }
        
    }
    
    return ret;
     
}

/**
 * 
 * @param i2c_obj
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        /* Initialize RepStart condition on SDA and SCL pins */
        I2C_MASTER_INITIATE_REPEATED_START_CONDITION();
        /* Wait for the Completion of the RepStart condition */
        while(SSPCON2bits.RSEN);
        /* Clear MSSP Interrupt Clear Flag -> SSPIF*/
        PIR1bits.SSPIF = 0;
        
        ret =E_NOT_OK;
    }
    
    return ret;
     
}

/**
 * 
 * @param i2c_obj
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Initialize Stop condition on SDA and SCL pins */
        I2C_MASTER_INITIATE_STOP_CONDITION();
        /* Wait for the Completion of the Stop condition */
        while(SSPCON2bits.PEN);
        /* Clear MSSP Interrupt Clear Flag -> SSPIF*/
        PIR1bits.SSPIF = 0;
        /* Report Stop Condition Detection */
        if(I2C_STOP_BIT_STATUS() == I2C_STOP_BIT_DETECTED)
        {
            ret = E_OK;
        }
        else if(I2C_STOP_BIT_STATUS() == I2C_STOP_BIT_NOT_DETECTED)
        {
            ret =E_NOT_OK;
        }
        
    }
    
    return ret;
     
}

/**
 * 
 * @param i2c_obj
 * @param i2c_data
 * @param _ack
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType MSSP_I2C_MASTER_Write_Blocking(const mssp_i2c_t *i2c_obj, uint8 i2c_data, uint8* _ack)
{
    Std_ReturnType ret = E_NOT_OK;
    if( (NULL == i2c_obj) || ( NULL == _ack))
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Write Data in Data Register */
        SSPBUF = i2c_data;
        /* Wait The Transmission to complete */
		while(!PIR1bits.SSPIF);
		/* Clear MSSP Interrupt Clear Flag -> SSPIF*/
		PIR1bits.SSPIF = 0;
		/* Report The Acknowledge received from the slave */
		if(I2C_ACK_WAS_RECEIVED_FROM_SLAVE == I2C_MASTER_ACK_STATUS())
		{
			*_ack = I2C_ACK_WAS_RECEIVED_FROM_SLAVE;
		}
		else
		{
			*_ack = I2C_ACK_WAS_NOT_RECEIVED_FROM_SLAVE;
		}
		
		ret = E_OK;
        
    }
    
    return ret;
     
}

/**
 * 
 * @param i2c_obj
 * @param ack
 * @param i2c_data
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType MSSP_I2C_MASTER_Read_Blocking(const mssp_i2c_t *i2c_obj, uint8 ack, uint8* i2c_data)
{
    Std_ReturnType ret = E_NOT_OK;
    if( (NULL == i2c_obj) || (NULL == i2c_data))
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Enable Receive MOde in Master */
        I2C_ENABLES_RECEIVE_MODE();
        /* Wait for buffer full flag :: complete byte receive */
        while(!I2C_BUFFER_FULL_STATUS());
        /* Copy Data from Buffer to Variable */
        *i2c_data = SSPBUF; 
        /* Send ACK or notACK */
        
        if( I2C_MASTER_RECEIVE_ACK_CFG == ack)
        {
            I2C_MASTER_RECEIVE_ACK();
            I2C_INITIATES_ACK_SEQUENCE();
        }
        else if( I2C_MASTER_RECEIVE_NOT_ACK_CFG == ack)
        {
            I2C_MASTER_RECEIVE_NOT_ACK();
            I2C_INITIATES_ACK_SEQUENCE();
        }
        else {/* Nothing */}
        ret = E_OK;
    }
    
    return ret;
     
}


void MSSP_I2C_ISR(void)
{
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
    /* Clear Flag */
    MSSP_I2C_INTERRUPT_Clear_FLAG();
    
    /*  CallBack  */
    if(MSSP_InterruptHandler)
    {
        MSSP_InterruptHandler();
    }
#endif    
}

void MSSP_I2C_BC_ISR(void)
{
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
    /* Clear Flag */
    MSSP_I2C_BUS_COL_INTERRUPT_Clear_FLAG();
    
    /*  CallBack  */
    if(MSSP_RWC_InterruptHandler)
    {
        MSSP_RWC_InterruptHandler();
    }
#endif    
}

/* ******************static Function*************** */

static Std_ReturnType I2C_Select_Mode_Confg(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        I2C_MODE_SELECT_COFIG(i2c_obj->i2c_cfg.i2c_mode_config);
        
    }
    
    return ret;
    
}



static Std_ReturnType I2C_Slew_Rate_Confg(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if(I2C_SLEW_RATE_ENABLED == i2c_obj->i2c_cfg.i2c_slew_rate)
        {
            I2C_SLEW_RATE_CONTROL_ENABLED();
        }
        else if(I2C_SLEW_RATE_DISABLED == i2c_obj->i2c_cfg.i2c_slew_rate)
        {
            I2C_SLEW_RATE_CONTROL_DISABLED();
        }
        else {/* Nothing */}
        
        ret = E_OK;
    }
    return ret;
}

static Std_ReturnType I2C_SMBus_Confg(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if(I2C_SMBUS_MODE_ENABLED == i2c_obj->i2c_cfg.SMBus_mode)
        {
            I2C_SMBUS_ENABLE();
        }
        else if(I2C_SMBUS_MODE_DISABLED == i2c_obj->i2c_cfg.SMBus_mode)
        {
            I2C_SMBUS_DISABLE();
        }
        else {/* Nothing */}
        
        
        ret = E_OK;
    }   
    
    return ret;
    
}

static Std_ReturnType I2C_General_Call_Confg(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if( I2C_GENERAL_CALL_INTERRUPT_ENABLED == i2c_obj->i2c_cfg.i2c_general_call)
        {
            I2C_ENABLES_INTERRUPT_WHEN_AGENERAL_CALL();
        }
        else if( I2C_GENERAL_CALL_INTERRUPT_DISABLED == i2c_obj->i2c_cfg.i2c_general_call)
        {
            I2C_DISABLES_INTERRUPT_WHEN_AGENERAL_CALL();
        }
        else
        { /* Nothing */ }
        
        ret = E_OK;
    }
    
    return ret;
}


static Std_ReturnType I2C_Master_Receive_Confg(const mssp_i2c_t *i2c_obj)
{
    
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if( I2C_MASTER_RECEIVE_MODE_ENABLED == i2c_obj->i2c_cfg.i2c_master_rec_mode)
        {
            I2C_ENABLES_RECEIVE_MODE();
        }
        else if( I2C_MASTER_RECEIVE_MODE_DISABLED == i2c_obj->i2c_cfg.i2c_master_rec_mode)
        {
            I2C_DISABLES_RECEIVE_MODE();
        }
        else
        { /* Nothing */ }
        
        ret = E_OK;
    }
    
    return ret;
    
    
}



static Std_ReturnType I2C_Interrupt_Confg(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
	#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
        MSSP_I2C_INTERRUPT_Clear_FLAG();
        MSSP_I2C_BUS_COL_INTERRUPT_Clear_FLAG();
        MMSSP_I2C_INTERRUPT_ENABLE(); 
        MMSSP_I2C_BUS_COL_INTERRUPT_ENABLE();
        
        /* Initialize CallBack */
        MSSP_InterruptHandler = i2c_obj->I2C_intrrupt_handler;
        MSSP_RWC_InterruptHandler = i2c_obj->I2C_Report_Write_Collision;
        MSSP_RRO_InterruptHandler = i2c_obj->I2C_Report_Receive_OverFlow;
        
	#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        Interrupt_Priority_Level_Enable();
        if(i2c_obj->mssp_i2c_priority == INTERRUPT_LOW_PRIORITY)
        {
            INTERRUPT_GlobalInterruptEnableLOW();
            MSSP_I2C_INTERRUPT_LOW_PRIORITY();
        }
        else if(i2c_obj->mssp_i2c_priority == INTERRUPT_HIGH_PRIORITY)
        {
            INTERRUPT_GlobalInterruptEnableHigh();
            MSSP_I2C_INTERRUPT_HIGH_PRIORITY();
        }
        else{ /* Nothing */ }
        
        if(i2c_obj->mssp_i2c_BC_priority == INTERRUPT_LOW_PRIORITY)
        {
            INTERRUPT_GlobalInterruptEnableLOW();
            MSSP_I2C_BUS_COL_INTERRUPT_LOW_PRIORITY();
        }
        else if(i2c_obj->mssp_i2c_BC_priority == INTERRUPT_HIGH_PRIORITY)
        {
            INTERRUPT_GlobalInterruptEnableHigh();
            MSSP_I2C_BUS_COL_INTERRUPT_HIGH_PRIORITY();
        }
        else{ /* Nothing */ }
	#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
    
	#endif
	#endif
        
        ret = E_OK;
    }
    
    return ret;
    
}



