/* 
 * File:   ecu_7_segment.c
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on May 21, 2024, 3:28 PM
 */


#include "ecu_7_segment.h"


#if SEVEN_SEGMENT_CONFIGURATION == SEVEN_SEGMENT_ENABLE


/**
 * &brief        :: initial the 4 pin of seven segment to be output
 * @param seg    ::  pointer to sevent segment  configuration
 * @return       :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */

Std_ReturnType seven_segment_initialize(const seven_segment_t* seg)
{
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == seg)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        
        //Std_ReturnType gpio_pin_initialize(const pin_config_t* pin_config);
        
        
        ret = gpio_pin_initialize( &(seg->segment_pin[0]) );
        
        ret = gpio_pin_initialize( &(seg->segment_pin[1]) );
        
        ret = gpio_pin_initialize( &(seg->segment_pin[2]) );
        
        ret = gpio_pin_initialize( &(seg->segment_pin[3]) );
        
    }
    
    return ret;
    
    
}

/**
 * 
 * &brief         ::  Write the number on seven segment 
 * @param seg     ::  pointer to sevent segment  configuration
 * @param number  ::  the number you want to write it on seven segment 
 * @return        :: Status of Function
 *      E_OK      :: The Function Done successfully
 *      E_NOT_OK  :: The Function has issue to perform this action
 */

Std_ReturnType seven_segment_write(const seven_segment_t* seg, uint8 number)
{
    
    Std_ReturnType ret =E_OK;
    
    if(NULL == seg || number>9)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        
        //Std_ReturnType gpio_pin_write_logic(const pin_config_t* pin_config, logic_t logic) 
        
        // number = 0b 0011 1001 
        
        ret = gpio_pin_write_logic( &(seg->segment_pin[0]),  number &0x01 );
        
        ret = gpio_pin_write_logic( &(seg->segment_pin[1]),(( number >> 1)&0x01) );
        
        ret = gpio_pin_write_logic( &(seg->segment_pin[2]), (( number >> 2)&0x01));
        
        ret = gpio_pin_write_logic( &(seg->segment_pin[3]), (( number >> 3)&0x01));
        
    }
    
    return ret;
    
    
}

#endif

