/**************************** [general information] ***************************/
/*
 * File:    Platform_Types.h
 *
 * Should define the width of the CPU registers. CPU_TYPE_8, CPU_TYPE_16 and so.
 *
 */

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/********************************* [includes] *********************************/

/******************************* [global macros] ******************************/
/* Width of CPU registers */
#define CPU_TYPE_8      8U
#define CPU_TYPE_16     16U
#define CPU_TYPE_32     32U

/* Bit ordering (register) */
#define MSB_FIRST       0U      /* Big endian */
#define LSB_FIRST       1U      /* Little endian */

/* Byte ordering (memory) */
#define HIGH_BYTE_FIRST 0U      /* Big endian */
#define LOW_BYTE_FIRST  1U      /* Little endian */

/* Platform type and endianess for STM32F302R8 */
#define CPU_TYPE            CPU_TYPE_32
#define CPU_BIT_ORDER       LSB_FIRST /* little endianess */
#define CPU_BYTE_ORDER      LOW_BYTE_FIRST

#ifndef TRUE
#define TRUE            1U
#endif

#ifndef FALSE
#define FALSE           0U
#endif
/****************************** [global typedefs] *****************************/
typedef unsigned char   boolean;

typedef unsigned char   uint8;
typedef signed char     sint8;
typedef unsigned short  uint16;
typedef signed short    sint16;
typedef unsigned long   uint32;
typedef signed long     sint32;

typedef float           float32;
typedef double          float64;
/************************** [variable declaration] ****************************/

/********************** [external function declarations] **********************/

#endif /* if !define(PLATFORM_TYPES_H) */
/****************************** [end of file] *********************************/
