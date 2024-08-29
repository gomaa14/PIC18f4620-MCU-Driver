/* 
* File:   ecu_chr_lcd.c
* Author: Gomaa Ayman Gomaa 
*
* Created on May 28, 2024, 1:38 AM
*/


#include "ecu_chr_lcd.h"



static Std_ReturnType lcd_send_4bit(const chr_lcd_4bit_t* lcd, uint8 value);
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t* lcd);
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t* lcd, uint8 row, uint8 coulmn);


static Std_ReturnType lcd_send_8bit(const chr_lcd_8bit_t* lcd, uint8 value);
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t* lcd);
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t* lcd, uint8 row, uint8 coulmn);


#if LCD_CHR_4BIT_CONFIGURATION == CHR_LCD_ENABLE

/**
 * 
 * @param lcd
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType lcd_4bit_initialze(const chr_lcd_4bit_t* lcd)
{
	Std_ReturnType Ret = E_OK;
    uint8 l_counter = ZERO_INIT;
    
    if( NULL == lcd )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		
        Ret = gpio_pin_initialize(&(lcd->lcd_rs));
        Ret = gpio_pin_initialize(&(lcd->lcd_en));
        
        for(l_counter = ZERO_INIT; l_counter< _LCD_4BIT_PINS; l_counter++)
        {
            Ret = gpio_pin_initialize(&(lcd->lcd_data[l_counter]));  
        }
        
		__delay_ms(15);
        
        Ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        
        __delay_ms(5);
        
        Ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        
        __delay_us(100);
        
        Ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        
        Ret = lcd_4bit_send_command(lcd, _LCD_CLEAR_DISPLAY);
        
        Ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        
        Ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE_INCREMENT_SHIFT_OFF);
        
        Ret = lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERCURSOR_OFF_BLINKING_OFF);
        
        Ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2LINE);
        
        Ret = lcd_4bit_send_command(lcd, _LCD_DDRAM_START);
	}
	
	return Ret;	
		
}

/**
 * 
 * @param lcd
 * @param command
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */

Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t* lcd, uint8 command)
{
	
	Std_ReturnType Ret = E_OK;
    
    if( NULL == lcd )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
        
        /* Write On Read/Write Pin LOW -> It Connect To ground*/
        
        /* Write on Register Select LOW To Send Instruction */
        
		Ret = gpio_pin_write_logic(&(lcd->lcd_rs), LOW);
        
        /* Send Most SignIfcant Bit */
		Ret = lcd_send_4bit(lcd, command>>4);
		
        /* Write on Enable HIGH To Active LCD */
		Ret = lcd_4bit_send_enable_signal(lcd);
		
		/* Send lest SignIfcant Bit */
		Ret = lcd_send_4bit(lcd, command);
		
        /* Write on Enable HIGH To Active LCD */
		Ret = lcd_4bit_send_enable_signal(lcd);
		
	}
	
	return Ret;
	
	
	
	
}

/**
 * 
 * @param lcd
 * @param data
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */

Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t* lcd, uint8 data)
{
	
	Std_ReturnType Ret = E_OK;
    
    if( NULL == lcd )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		/* Write On Read/Write Pin LOW -> It Connect To ground*/
        
        /* Write on Register Select LOW To Send Data */
        
		Ret = gpio_pin_write_logic(&(lcd->lcd_rs), HIGH);
        
        /* Send Most SignIfcant Bit */
		Ret = lcd_send_4bit(lcd, data>>4);
		
        /* Write on Enable HIGH To Active LCD */
		Ret = lcd_4bit_send_enable_signal(lcd);
		
		/* Send lest SignIfcant Bit */
		Ret = lcd_send_4bit(lcd, data);
		
        /* Write on Enable HIGH To Active LCD */
		Ret = lcd_4bit_send_enable_signal(lcd);
		
	}
	
	return Ret;
	
	
	
	
}

/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @param data
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t* lcd, uint8 row, uint8 coulmn, uint8 data)
{
	
	Std_ReturnType Ret = E_OK;
    
    if( NULL == lcd )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		Ret = lcd_4bit_set_cursor(lcd, row, coulmn);
		
		Ret = lcd_4bit_send_char_data(lcd, data);
		
		
	}
	
	return Ret;
	
	
	
	
}

/**
 * 
 * @param lcd
 * @param str_data
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_string_data(const chr_lcd_4bit_t* lcd, uint8* str_data)
{
	
	Std_ReturnType Ret = E_OK;
    
    if( (NULL == lcd)  || (NULL == str_data) )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		uint8 l_counter = ZERO_INIT;
		for(l_counter =ZERO_INIT; str_data[l_counter] != '\0'; l_counter++)
		{
			Ret &= lcd_4bit_send_char_data(lcd, str_data[l_counter]);
		}
		
	}
	
	return Ret;
	
	
	
	
}

/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @param str_data
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_string_data_pos(const chr_lcd_4bit_t* lcd, uint8 row, uint8 coulmn, uint8* str_data)
{
	
	Std_ReturnType Ret = E_OK;
    
    if( (NULL == lcd)  || (NULL == str_data) )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		Ret = lcd_4bit_set_cursor(lcd, row, coulmn);
		
		Ret = lcd_4bit_send_string_data(lcd, str_data);
		
		
	}
	
	return Ret;
	
	
	
	
}

/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @param _chr
 * @param mem_pos
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
 
Std_ReturnType lcd_4bit_send_custome_char(const chr_lcd_4bit_t* lcd, uint8 row, uint8 coulmn,
                                         const uint8 _chr[], uint8 mem_pos)
{
	
	Std_ReturnType Ret = E_OK;
    uint8 l_counter = ZERO_INIT;
    
    if( NULL == lcd )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		/* Store Data in CGRAM */
		Ret = lcd_4bit_send_command(lcd, _LCD_CGRAM_START+(8*mem_pos));
		
		for(l_counter = ZERO_INIT; l_counter<8; l_counter++)
		{
			Ret = lcd_4bit_send_char_data(lcd, _chr[l_counter]);
			
		}
		
		/* Write Data in DDRAM */
		Ret = lcd_4bit_send_char_data_pos(lcd, row, coulmn, mem_pos);
        
        
	}
	
	return Ret;
	
}

#endif




#if LCD_CHR_8BIT_CONFIGURATION == CHR_LCD_ENABLE

/**
 * 
 * @param lcd
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType lcd_8bit_initialze(const chr_lcd_8bit_t* lcd)
{
	
	Std_ReturnType Ret = E_OK;
    uint8 l_counter = ZERO_INIT;
    
    if( NULL == lcd )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		
        Ret = gpio_pin_initialize(&(lcd->lcd_rs));
        Ret = gpio_pin_initialize(&(lcd->lcd_en));
        
        for(l_counter = ZERO_INIT; l_counter< _LCD_8BIT_PINS; l_counter++)
        {
            Ret = gpio_pin_initialize(&(lcd->lcd_data[l_counter]));  
        }
		
		
		__delay_ms(20);
        
        Ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        
        __delay_ms(5);
        
        Ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        
        __delay_us(120);
        
        Ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        
		
        Ret = lcd_8bit_send_command(lcd, _LCD_CLEAR_DISPLAY);
        
        Ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
        
        Ret = lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE_INCREMENT_SHIFT_OFF);
        
        Ret = lcd_8bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERCURSOR_OFF_BLINKING_OFF);
        
        Ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        
        Ret = lcd_8bit_send_command(lcd, _LCD_DDRAM_START);
	}
	
	return Ret;
	
	
	
	
}

/**
 * 
 * @param lcd
 * @param command
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t* lcd, uint8 command)
{
	
	Std_ReturnType Ret = E_OK;
    
    if( NULL == lcd )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		
        /* Write On Read/Write Pin LOW -> It Connect To ground*/
        
        /* Write on Register Select LOW To Send Instruction */
        
		Ret = gpio_pin_write_logic(&(lcd->lcd_rs), LOW);
        
        /* Send Command */
		Ret = lcd_send_8bit(lcd, command);
		
        /* Write on Enable HIGH To Active LCD */
		Ret = lcd_8bit_send_enable_signal(lcd);
		
	}
	
	return Ret;
	
	
	
	
}

/**
 * 
 * @param lcd
 * @param data
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t* lcd, uint8 data)
{
	
	Std_ReturnType Ret = E_OK;
    
    if( NULL == lcd )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		
        /* Write On Read/Write Pin LOW -> It Connect To ground*/
        
        /* Write on Register Select HIGH To Send DATA */
        
		Ret = gpio_pin_write_logic(&(lcd->lcd_rs), HIGH);
        
        /* Send Command */
		Ret = lcd_send_8bit(lcd, data);
		
        /* Write on Enable HIGH To Active LCD */
		Ret = lcd_8bit_send_enable_signal(lcd);
        
	}
	
	return Ret;
	
	
	
	
}


/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @param data
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t* lcd, uint8 row, uint8 coulmn, uint8 data)
{
	
	Std_ReturnType Ret = E_OK;
    
    if( NULL == lcd )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		
        Ret = lcd_8bit_set_cursor(lcd, row, coulmn);
        
        Ret = lcd_8bit_send_char_data(lcd, data);
		
        
	}
	
	return Ret;
	
	
	
	
}

/**
 * 
 * @param lcd
 * @param str_data
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_string_data(const chr_lcd_8bit_t* lcd, uint8* str_data)
{
	
	Std_ReturnType Ret = E_OK;
    
    if( (NULL == lcd)  || (NULL == str_data) )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		
		uint8 l_counter = ZERO_INIT;
		for(l_counter =ZERO_INIT; str_data[l_counter] != '\0'; l_counter++)
		{
			Ret &= lcd_8bit_send_char_data(lcd, str_data[l_counter]);
		}
		
	}
	
	return Ret;
	
	
	
	
	
}

/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @param str_data
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_string_data_pos(const chr_lcd_8bit_t* lcd, uint8 row, uint8 coulmn, uint8* str_data)
{
	
	
	Std_ReturnType Ret = E_OK;
    
    if( (NULL == lcd)  || (NULL == str_data) )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		Ret = lcd_8bit_set_cursor(lcd, row, coulmn);
        Ret = lcd_8bit_send_string_data(lcd, str_data);
        
		
	}
	
	return Ret;
	
	
	
	
}

/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @param _chr
 * @param mem_pos
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */

Std_ReturnType lcd_8bit_send_custome_char(const chr_lcd_8bit_t* lcd, uint8 row, uint8 coulmn,
                                         const uint8 _chr[], uint8 mem_pos)
{
	
	Std_ReturnType Ret = E_OK;
    uint8 l_counter = ZERO_INIT;
	
    if( NULL == lcd )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		/* Store Data in CGRAM */
		Ret = lcd_8bit_send_command(lcd, _LCD_CGRAM_START+(8*mem_pos));
		
		for(l_counter = ZERO_INIT; l_counter<8; l_counter++)
		{
			Ret = lcd_8bit_send_char_data(lcd, _chr[l_counter]);
			
		}
		
		/* Write Data in DDRAM */
		Ret = lcd_8bit_send_char_data_pos(lcd, row, coulmn, mem_pos);
		
	}
	
	return Ret;
	
	
	
	
}

#endif

/**
 * @brief         ::  convert date from type uint8 to type string 
 * @param value   ::  uint8 value 
 * @param str     ::  pointer to string vlaue 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
 
Std_ReturnType convert_uint8_to_string(uint8 value, uint8* str)
{
	
	Std_ReturnType Ret = E_OK;
    
    if( NULL == str )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		
		memset(str, '\0', 4);
		
        
		sprintf(str, "%i", value);
		
		
	}
	
	return Ret;
	
	
	
	
}

/**
 * @brief         ::  convert date from type uint16 to type string 
 * @param value   ::  uint16 value 
 * @param str     ::  pointer to string vlaue 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */

Std_ReturnType convert_uint16_to_string(uint16 value, uint8* str)
{
	
	Std_ReturnType Ret = E_OK;
    
    if( NULL == str )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		uint8 temp_str[6] = {0};
		uint8 Data_Counter =0;
		
		memset(str, ' ', 5);
		str[5] = '\0';
		
		sprintf(temp_str, "%i", value);
		
		while(temp_str[Data_Counter] != '\0')
		{
			str[Data_Counter] = temp_str[Data_Counter];
			
			Data_Counter++;	
		}
		
	}
	
	return Ret;
	
	
	
	
}

/**
 * @brief         ::  convert date from type uint32 to type string 
 * @param value   ::  uint32 value 
 * @param str     ::  pointer to string vlaue 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */

Std_ReturnType convert_uint32_to_string(uint32 value, uint8* str)
{
	
	Std_ReturnType Ret = E_OK;
    
    if( NULL == str )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		
		memset(str, '\0', 11);
		
		sprintf(str, "%i", value);
		
		
	}
	
	return Ret;
	
	
	
	
}


/**
 * @brief         ::  convert date from type float32 to type string 
 * @param value   ::  float32 value 
 * @param str     ::  pointer to string vlaue 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
 
Std_ReturnType convert_float32_to_string(float32 value, uint8* str)
{
	
	Std_ReturnType Ret = E_OK;
    
    if( NULL == str )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		
		memset(str, '\0', 11);
		
		sprintf(str, "%.1f", value);
		
		
	}
	
	return Ret;
	
	
	
}

/**
 * @brief         ::  convert date from type float64 to type string 
 * @param value   ::  float64 value 
 * @param str     ::  pointer to string vlaue 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
Std_ReturnType convert_float64_to_string(float64 value, uint8* str)
{
	
	
	Std_ReturnType Ret = E_OK;
    
    if( NULL == str )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		
		memset(str, '\0', 21);
		
		sprintf(str, "%.6f", value);
		
		
	}
	
	return Ret;
	
	
	
}


/**
 * @brief         :: Send Data or Command to LCD
 * @param lcd     :: Pointer to LCD you want to send data or command
 * @param value   :: The vlaue you wnt to send it  " Take First 4 bit "
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
 
static Std_ReturnType lcd_send_4bit(const chr_lcd_4bit_t* lcd, uint8 value)
{
	
	Std_ReturnType Ret = E_OK;
    uint8 l_counter = ZERO_INIT;
    
    if( NULL == lcd )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
        for(l_counter = ZERO_INIT; l_counter< _LCD_4BIT_PINS; l_counter++)
        {
            Ret &= gpio_pin_write_logic( &(lcd->lcd_data[l_counter]), (uint8)(value >> l_counter) & 0x01);
        }
		
        
	}
	
	return Ret;
	
	
}

/**
 * @brief         :: Enable LCD 
 * @param lcd     :: Pointer to LCD you want to Enable it 
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
 
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t* lcd)
{
    
	Std_ReturnType Ret = E_OK;
    
    
    if( NULL == lcd )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
        Ret = gpio_pin_write_logic( &(lcd->lcd_en), HIGH);
        
        __delay_us(5);
        
        Ret = gpio_pin_write_logic( &(lcd->lcd_en), LOW);
        
        
	}
	
	return Ret;
}


/**
 * @brief         ::
 * @param lcd
 * @param value
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
static Std_ReturnType lcd_send_8bit(const chr_lcd_8bit_t* lcd, uint8 value)
{
	
	Std_ReturnType Ret = E_OK;
    uint8 l_counter = ZERO_INIT;
    
    if( NULL == lcd )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
        for(l_counter = ZERO_INIT; l_counter< _LCD_8BIT_PINS; l_counter++)
        {
            Ret &= gpio_pin_write_logic( &(lcd->lcd_data[l_counter]), (uint8)(value >> l_counter) & 0x01);
        }
		
        
	}
	
	return Ret;
}

/**
 * @brief         ::
 * @param lcd
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t* lcd)
{
    
	Std_ReturnType Ret = E_OK;
    
    if( NULL == lcd )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
        Ret = gpio_pin_write_logic( &(lcd->lcd_en), HIGH);
        
        __delay_us(5);
        
        Ret = gpio_pin_write_logic( &(lcd->lcd_en), LOW);
        
        
	}
	
	return Ret;

}

/**
 * @brief         ::
 * @param lcd
 * @param row
 * @param coulmn
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t* lcd, uint8 row, uint8 coulmn)
{
	
	Std_ReturnType Ret = E_OK;
    
    if( NULL == lcd )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		coulmn--;
        
		switch(row)
        {
            case ROW1 :  Ret = lcd_8bit_send_command(lcd, 0X80+coulmn);          break;
			
            case ROW2 :  Ret = lcd_8bit_send_command(lcd, 0XC0+coulmn);          break;
			
            case ROW3 :  Ret = lcd_8bit_send_command(lcd, 0X94+coulmn);          break;
			
            case ROW4 :  Ret = lcd_8bit_send_command(lcd, 0XD4+coulmn);          break;
            
			default  : break;
            
            
        }
		
	}
	
	return Ret;
	
}

/**
 * @brief         ::
 * @param lcd
 * @param row
 * @param coulmn
 * @return :: Status of Function
 *      E_OK     :: The Function Done successfully
 *      E_NOT_OK :: The Function has issue to perform this action
 */
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t* lcd, uint8 row, uint8 coulmn)
{
	
	Std_ReturnType Ret = E_OK;
    
    if( NULL == lcd )
    {
        Ret = E_NOT_OK;
    }
    
    else
    {
		coulmn--;
        
		switch(row)
        {
            case ROW1:  Ret = lcd_4bit_send_command(lcd, 0X80+coulmn);          break;
			
            case ROW2:  Ret = lcd_4bit_send_command(lcd, 0XC0+coulmn);          break;
			
            case ROW3:  Ret = lcd_4bit_send_command(lcd, 0X94+coulmn);          break;
			
            case ROW4:  Ret = lcd_4bit_send_command(lcd, 0XD4+coulmn);          break;
            
			default  : break;
            
            
        }
		
	}
	
	return Ret;
	
}





