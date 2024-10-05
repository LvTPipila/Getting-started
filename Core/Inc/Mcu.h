/******************************** [general info] ******************************/
/*
 * File:    Mcu.h
 */

#ifndef MCU_H
#define MCU_H
/********************************* [includes] *********************************/
#include "Std_Types.h"

/******************************* [global macros] ******************************/

/****************************** [global typedefs] *****************************/
/* Type to specify reset reason in raw register format */
typedef uint32  Mcu_RawResetType;

/* Type to specify the ID for a MCU mode */
typedef uint32  Mcu_ModeType;

/* Subset of reset types. Dependent on hardware */
typedef enum
{
    MCU_POWER_ON_RESET = 0x00,
    MCU_WATCHDOG_RESET = 0x01,
    MCU_SW_RESET = 0x02,
    MCU_RESET_UNDEFINED = 0x03
    /* More reset types can be added that are supported by hardware. */
}Mcu_ResetType;

/* Status value return for the PLL status */
typedef enum
{
    MCU_PLL_LOCKED = 0x00,
    MCU_PLL_UNLOCKED = 0x01,
    MCU_PLL_STATUS_UNDEFINED = 0x02
}Mcu_PllStatusType;
/* Structure to hold the MCU driver configuration */
typedef struct
{
}Mcu_ConfigType;
/************************** [variable declaration] ****************************/

/********************** [external function declarations] **********************/
/**
 * @brief   This service initializes the MCU driver.
 *
 * service ID   0x00
 *
 * param (in)   ConfigPtr is a pointer to a structure of MCU configuration.
 *
 * param (out)  none.
 *
 * retval   none.
 */
void Mcu_Init(const Mcu_ConfigType* ConfigPtr);

/**
 * @brief   Add a brief description of this function/interface.
 *
 * param (in)   Add description of parameter value.
 *
 * param (out)  Add description of parameter value.
 *
 * retval   Add name description of return value.
 */
//void template_fcn(void);
#endif /* if !define(MCU_H) */
/****************************** [end of file] *********************************/
