/*
 * File:   mcal_std_types.h
 * Author: Gomaa Ayman Gomaa
 *
 * Created on May 7, 2024, 10:39 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H






/************Section :: Includes***********************************/

#include "compiler.h"
#include "std_libraries.h"



/************Section :: Macro Declaration *************************/


#define STD_HIGH        0X01
#define STD_LOW         0X00


#define STD_ON          0X01
#define STD_OFF         0X00

#define STD_ACTIVE      0X01
#define STD_IDLE        0X00



#define E_NOT_OK       (Std_ReturnType)0X00 
#define E_OK           (Std_ReturnType)0X01 


#define ZERO_INIT 0
#define ONE_INIT  1




/************Section :: Macro Function Declaration ****************/


/************Section :: User Define Data Type *********************/


typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

typedef signed char    sint8;
typedef signed short   sint16;
typedef signed int     sint32;

typedef float          float32;
typedef double         float64;

typedef uint8          Std_ReturnType;



/************Section :: Function Prototype  *********************/


#endif	/* MCAL_STD_TYPES_H */

