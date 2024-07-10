/**************************** [general information] ***************************/
/*
 * File:    Port.h
 */

#ifndef PORT_H
#define PORT_H
/********************************* [includes] *********************************/
#include "Std_Types.h"

/******************************* [global macros] ******************************/
/* Port pins */
#define PORT_PIN_0      ((Port_PinType)0x0001U)
#define PORT_PIN_1      ((Port_PinType)0x0002U)
#define PORT_PIN_2      ((Port_PinType)0x0004U)
#define PORT_PIN_3      ((Port_PinType)0x0008U)
#define PORT_PIN_4      ((Port_PinType)0x0010U)
#define PORT_PIN_5      ((Port_PinType)0x0020U)
#define PORT_PIN_6      ((Port_PinType)0x0040U)
#define PORT_PIN_7      ((Port_PinType)0x0080U)
#define PORT_PIN_8      ((Port_PinType)0x0100U)
#define PORT_PIN_9      ((Port_PinType)0x0200U)
#define PORT_PIN_10     ((Port_PinType)0x0400U)
#define PORT_PIN_11     ((Port_PinType)0x0800U)
#define PORT_PIN_12     ((Port_PinType)0x1000U)
#define PORT_PIN_13     ((Port_PinType)0x2000U)
#define PORT_PIN_14     ((Port_PinType)0x4000U)
#define PORT_PIN_15     ((Port_PinType)0x8000U)
#define PORT_PIN_ALL    ((Port_PinType)0xFFFFU)

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
    // Copy structure from pwm
    GPIO_TypeDef* ModReg;
}Port_ChannelConfigType;
/* Type of external data structure containing the initialization data. */
typedef struct 
{
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
 * @brief   This service refresh port direction.
 *
 * service ID   0x02
 *
 * param (in)   none.
 *
 * param (out)  none.
 *
 * retval   none.
 */
void Port_RefreshPortDirection(void);

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
