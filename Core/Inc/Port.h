/**************************** [general information] ***************************/
/*
 * File:    Port.h
 */

#ifndef PORT_H
#define PORT_H
/********************************* [includes] *********************************/
#include "Std_Types.h"
#include "stm32f302x8.h"

/******************************* [global macros] ******************************/
/* Symbolic name of port pins */
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

/* Configuration mode of port pins */
#define PIN_MODE_DIGITAL_INPUT  (0x0U)
#define PIN_MODE_DIGITAL_OUTPUT (0x1U)
#define PIN_MODE_ALTERNATE      (0x2U)
#define PIN_MODE_ANALOG         (0x3U)

/* Configuration of pull-up/pull-down option */
#define MODE_NO_PULL        (0x0U)
#define MODE_PULL_UP        (0x1U)
#define MODE_PULL_DOWN      (0x2U)

/* Configuration of output type options */
#define MODE_PUSH_PULL  (0x0U)
#define MODE_OPEN_DRAIN (0x1U)

/* Configureation of output speed options */
#define SPEED_FREQ_LOW      (0x0U)
#define SPEED_FREQ_MEDIUM   (0x1U)
#define SPEED_FREQ_HIGH     (0x3U)

/* Bit Set Reset Register starting positions */
#define GPIO_BSRR_BS    (0x00U)
#define GPIO_BSRR_BR    (0x10U)

/* Alternate function listing */
#define AF_0    (0x0U)
#define AF_1    (0x1U)
#define AF_2    (0x2U)
#define AF_3    (0x3U)
#define AF_4    (0x4U)
#define AF_5    (0x5U)
#define AF_6    (0x6U)
#define AF_7    (0x7U)
#define AF_8    (0x8U)
#define AF_9    (0x9U)
#define AF_10   (0xAU)
#define AF_11   (0xBU)
#define AF_12   (0xCU)
#define AF_13   (0xDU)
#define AF_14   (0xEU)
#define AF_15   (0xFU)

/****************************** [global typedefs] *****************************/
/* Data type for the symbolic name of port pin. */
typedef uint32  Port_PinType;

/* Possible direction of a port pin. */
typedef enum
{
    PORT_PIN_IN = 0x00U,
    PORT_PIN_OUT = 0x01U
}Port_PinDirectionType;

/* Different port pin modes. */
typedef uint32  Port_PinModeType;

/* Structure with necessary infor to configure port channel. */
typedef struct
{
    Port_PinType Pin;
    Port_PinDirectionType Direction;
    Port_PinModeType PinMode;
    uint32 Alternate;
    uint32 PullMode;
    uint32 OutputMode;
    uint32 Speed;
    GPIO_TypeDef* ModReg;
}Port_PinConfigType;
/* Type of external data structure containing the initialization data. */
typedef struct 
{
    const Port_PinConfigType* PinConfigPtr;
    uint8 PortMaxConfigPins;
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
