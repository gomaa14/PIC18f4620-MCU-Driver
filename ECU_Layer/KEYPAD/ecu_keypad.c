/* 
 * File:   ecu_keypad.c
 * Author: Gomaa Ayman Gomaa 
 *
 * Created on May 23, 2024, 1:00 AM
 */



#include "ecu_keypad.h"


static const uint8 btn_values[KEYPAD_ROWS][KEYPAD_COLS]= {
                                                         {'7','8','9','/'},
                                                         {'4','5','6','*'},
                                                         {'1','2','3','-'},
                                                         {'#','0','=','+'}
    
};

#if KEYPAD_CONFIGURATION == KEYPAD_ENABLE

/**
 * @brief      :: initialize the keypad pins "rows and cols "
 * @param obj :: pointer to keypad configuration
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType keypad_initialize(const keypad_t* obj)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        uint8 num_row = ZERO_INIT, num_col = ZERO_INIT;
        
        for(num_row = ZERO_INIT; num_row<KEYPAD_ROWS; num_row++)
        {
            ret = gpio_pin_initialize(&(obj->keypad_row_pins[num_row]));
        }
        
        for(num_col = ZERO_INIT; num_col<KEYPAD_COLS; num_col++)
        {
            ret = gpio_pin_direction_initialize(&(obj->keypad_col_pins[num_col]));
        }
        
        
    }
    
    return ret;
    
    
}

/**
 * @brief       :: get the value you pressed on it 
 * @param obj   :: pointer to keypad configuration
 * @param value :: pointer to value you get it 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType keypad_get_value(const keypad_t* obj, uint8* value)
{
    Std_ReturnType ret = E_OK;
    
    if( ( NULL == obj) || (NULL == value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        uint8 rows_counter = ZERO_INIT , cols_counter =ZERO_INIT;
        uint8 count = ZERO_INIT;
        logic_t column_logic = LOW;
        
                  
        for(rows_counter =ZERO_INIT; rows_counter<KEYPAD_ROWS; rows_counter++)
        {
            for(count =ZERO_INIT; count<KEYPAD_ROWS; count++)
            {
                ret = gpio_pin_write_logic(&(obj->keypad_row_pins[count]), LOW);
            }
            
            ret = gpio_pin_write_logic(&(obj->keypad_row_pins[rows_counter]), HIGH);
            
            __delay_ms(10);
            
            for(cols_counter =ZERO_INIT; cols_counter<KEYPAD_COLS; cols_counter++)
            {
                ret = gpio_pin_read_logic(&(obj->keypad_col_pins[cols_counter]), &column_logic);
                
                if(HIGH == column_logic)
                {
                    *value = btn_values[rows_counter][cols_counter];
                }
            }
            
        }
    }
    
    return ret;
    
    
}

#endif

