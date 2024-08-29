/* 
 * File:   hal_eeprom.c
 * Author: User
 *
 * Created on June 28, 2024, 1:50 PM
 */


#include "hal_eeprom.h"


/**
 * @brief        :: Write Data from EEPROM  
 * @param bAdd   :: Address you want to Write in EEPROM  
 * @param bData  :: Data you want to write it 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData)
{
    
    Std_ReturnType ret = E_OK;
    
    
    /* Read Interrupt Status  */
    
    uint8 Global_Interrupt_Sataus = INTCONbits.GIE;
    
    /* Update The Address Register  */
    
    EEADR = (uint8)(bAdd & 0xFF);
    
    EEADRH = (uint8) ((bAdd>>8) & 0x03);
    
    /* Update The Data Register  */
    
    EEDATA = bData;
    
    /* Select Access Data EEPROM Memory */
    
    EECON1bits.EEPGD = ACCESS_DATA_EEPROM_MEMORY;
	
    EECON1bits.CFGS =  ACCESS_FLASH_PROGRAM_OR_DATA_EEPROM_MEMORY;
	
	
    /*Allow Write Cycle To Data EEPROM */
    
    EECON1bits.WREN = ENABLE_WRITE_CYCLES;
    
    /* Disable Interrupt  "General Interrupt " */
    
    INTERRUPT_GlobalInterruptDisable();
    
    
    /* Write The Required Sequence : 0x55 -> 0xAA */
    
    
    EECON2 = 0x55;
    EECON2 = 0xAA;
    
    
    /*  Initiates a data EEPROM erase/write cycle*/
    
    EECON1bits.WR = INITIATES_ADATA_EEPROM_WRITE;
    
    
    /* Wait For Write To  Complete */
    
	while(EECON1bits.WR);
	
	
	/* Inhibits write cycles to Flash program/data EEPROM*/
	
	EECON1bits.WREN = INHIBITS_WRITE_CYCLES;
	
	/* Restore INterrupt Status "Enable Or Disable "*/
	
	INTCONbits.GIE = Global_Interrupt_Sataus	;
    
	
    return ret;
    
}


/**
 * @brief        :: Read Data from EEPROM  
 * @param bAdd   :: Address you want to Read it from EEPROM 
 * @param bData  :: Pointer to storage data 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8* bData)
{
    
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == bData)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        /* Update The Address Register  */
    
        EEADR = (uint8)(bAdd & 0xFF);
    
        EEADRH = (uint8) ( (bAdd>>8) &0x03 );
    
        /* Select Access Data EEPROM Memory */
    
        EECON1bits.EEPGD = 0;
        EECON1bits.CFGS  = 0;
     
     
        /*Initiates a data EEPROM Read cycle*/
        
        EECON1bits.RD = INITIATES_AN_EEPROM_READ;
		NOP();
		NOP();
		
        /* Return Data */
        
		*bData = EEDATA;
		
		
        ret= E_OK;
        
    }
    
    
    return ret;
    
    
}
