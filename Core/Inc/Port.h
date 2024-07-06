/**************************** [general information] ***************************/
/*
 * File:    Port.h
 */

#ifndef PORT_H
#define PORT_H
/********************************* [includes] *********************************/
#include "Std_Types.h"

/******************************* [global macros] ******************************/

/****************************** [global typedefs] *****************************/
/* Data type for the symbolic name of port pin. */
typedef uint32  Port_PinType;

/* Possible direction of a port pin. */
typedef enum
{
    PORT_PIN_IN = 0x00,
    PORT_PIN_OUT = 0x01
}Port_PinDirectionType;

/* Different port pin modes. */
typedef uint32  Port_PinModeType;

/* Structure with necessary infor to configure port channel. */
typedef struct
{
}Port_ChannelConfigType;
/* Type of external data structure containing the initialization data. */
typedef struct 
{
    // Copy structure from pwm
}Port_ConfigType;
/************************** [variable declaration] ****************************/

/********************** [external function declarations] **********************/
/**
 * @brief   Initializes the Port Driver module.
 *
 * service ID   0x00
 *
 * param (in)   ConfigPtr is a pointer to configuration for Port.
 *
 * param (out)  none.
 *
 * retval   none.
 */
void Port_Init(const Port_ConfigType *ConfigPtr);

/**
 * @brief   This service sets the port pin direction.
 *
 * service ID   0x01
 *
 * param (in)   Port pin ID number.
 *
 * param (in)   Port pin direction.
 *
 * param (out)  none.
 *
 * retval   none.
 */
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType);

/**
 * @brief   This service sets the port pin mode.
 *
 * service ID   0x04
 *
 * param (in)   Port pin ID number.
 *
 * param (in)   New port pin mode to be set on port pin.
 *
 * param (out)  none.
 *
 * retval   none.
 */
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
#endif /* if !define(PORT_H) */
/****************************** [end of file] *********************************/
