/**************************** [general information] ***************************/
/*
 * File:    Std_Types.h
 */

#ifndef STD_TYPES_H
#define STD_TYPES_H

/********************************* [includes] *********************************/
#include <stddef.h>
#include "Platform_Types.h"
//#include "Compiler.h"
/******************************* [global macros] ******************************/

#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
#define E_OK                    0x00u

typedef unsigned char StatusType;
#endif

#define E_NOT_OK                0x01u

#define STD_HIGH                0x01u        /* Physical state 5V or 3.3V */
#define STD_LOW                 0x00u        /* Physical state 0V */
#define STD_ACTIVE              0x01u        /* Logical state active */
#define STD_IDLE                0x00u        /* Logical state idle */
#define STD_ON                  0x01u
#define STD_OFF                 0x00u
/****************************** [global typedefs] *****************************/
typedef uint8   Std_ReturnType;

/************************** [variable declaration] ****************************/

/********************** [external function declarations] **********************/

#endif /* if !define(STD_TYPES_H) */
/****************************** [end of file] *********************************/
