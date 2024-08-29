/* 
* File:   ecu_chr_lcd.h
* Author: Gomaa Ayman Gomaa
*
* Created on May 28, 2024, 1:38 AM
*/

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H


/************Section :: Includes***********************************/

#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_chr_lcd_cfg.h"



/************Section :: Macro Declaration *************************/


#define _LCD_4BIT_PINS 4
#define _LCD_8BIT_PINS 8

#define ROW1           1
#define ROW2           2
#define ROW3           3
#define ROW4           4




#define _LCD_CLEAR_DISPLAY  0X01
#define _LCD_RETURN_HOME    0X02


#define _LCD_ENTRY_MODE_DECREMENT_SHIFT_OFF  0X04  
#define _LCD_ENTRY_MODE_DECREMENT_SHIFT_ON   0X05 
#define _LCD_ENTRY_MODE_INCREMENT_SHIFT_OFF  0X06 
#define _LCD_ENTRY_MODE_INCREMENT_SHIFT_ON   0X07

#define _LCD_DISPLAY_ON_UNDERCURSOR_ON_BLINKING_ON    0X0F
#define _LCD_DISPLAY_ON_UNDERCURSOR_ON_BLINKING_OFF   0X0E 
#define _LCD_DISPLAY_ON_UNDERCURSOR_OFF_BLINKING_ON   0X0D  
#define _LCD_DISPLAY_ON_UNDERCURSOR_OFF_BLINKING_OFF  0X0C  
#define _LCD_DISPLAY_OFF_UNDERCURSOR_OFF_BLINKING_OFF 0X08

#define _LCD_CURSIR_MOVE_SHIFT_RIGHT	0X14	            
#define _LCD_CURSIR_MOVE_SHIFT_LEFT 	0X10	            
#define _LCD_DISPLAY_SHIFT_RIGHT 		0X1C            
#define _LCD_DISPLAY_SHIFT_LEFT 		0X18          

#define _LCD_4BIT_MODE_2LINE     0X28
#define _LCD_8BIT_MODE_2LINE     0X38

#define _LCD_CGRAM_START	0X40
#define _LCD_DDRAM_START	0X80



/************Section :: Macro Function Declaration ****************/



/************Section :: User Define Data Type *********************/

typedef struct 
{
    pin_config_t lcd_data[4];
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    
}chr_lcd_4bit_t;

typedef struct 
{
    pin_config_t lcd_data[8];
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    
}chr_lcd_8bit_t;





/************Section :: Function Prototype  *********************/

Std_ReturnType lcd_4bit_initialze(const chr_lcd_4bit_t* lcd);
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t* lcd, uint8 command);
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t* lcd, uint8 data);
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t* lcd, uint8 row, uint8 coulmn, uint8 data);
Std_ReturnType lcd_4bit_send_string_data(const chr_lcd_4bit_t* lcd, uint8* str_data);
Std_ReturnType lcd_4bit_send_string_data_pos(const chr_lcd_4bit_t* lcd, uint8 row, uint8 coulmn, uint8* str_data);
Std_ReturnType lcd_4bit_send_custome_char(const chr_lcd_4bit_t* lcd, uint8 row, uint8 coulmn,
                                         const uint8 _chr[], uint8 mem_pos);




Std_ReturnType lcd_8bit_initialze(const chr_lcd_8bit_t* lcd);
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t* lcd, uint8 command);
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t* lcd, uint8 data);
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t* lcd, uint8 row, uint8 coulmn, uint8 data);
Std_ReturnType lcd_8bit_send_string_data(const chr_lcd_8bit_t* lcd, uint8* str_data);
Std_ReturnType lcd_8bit_send_string_data_pos(const chr_lcd_8bit_t* lcd, uint8 row, uint8 coulmn, uint8* str_data);
Std_ReturnType lcd_8bit_send_custome_char(const chr_lcd_8bit_t* lcd, uint8 row, uint8 coulmn,
                                         const uint8 _chr[], uint8 mem_pos);




Std_ReturnType convert_uint8_to_string(uint8 value, uint8* str);
Std_ReturnType convert_uint16_to_string(uint16 value, uint8* str);
Std_ReturnType convert_uint32_to_string(uint32 value, uint8* str);

Std_ReturnType convert_float32_to_string(float32 value, uint8* str);
Std_ReturnType convert_float64_to_string(float64 value, uint8* str);

#endif	/* ECU_CHR_LCD_H */

