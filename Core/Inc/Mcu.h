/******************************** [general info] ******************************/
/*
 * File:    Mcu.h
 */

#ifndef MCU_H
#define MCU_H
/********************************* [includes] *********************************/
#include "Std_Types.h"
#include "stm32f302x8.h"

/******************************* [global macros] ******************************/
#define MCU_HSI_FREQ    8000000U    // Frequency of internal oscilator for HSI.
#define MCU_HSI_TRIM_VALUE  (0x10U)


#define MCU_OSCSRC_HSE  0x0U
#define MCU_OSCSRC_HSI  0x1U

/* Defininf the masks for the Control Register. */
#define MCU_CR_HSION_POS        (0U)
#define MCU_CR_HSION_MASK       (0x01U << MCU_CR_HSION_POS)

#define MCU_CR_HSIRDY_POS       (1U)
#define MCU_CR_HSIRDY_MASK      (0x01U << MCU_CR_HSIRDY_POS)

#define MCU_CR_HSITRIM_POS      (3U)
#define MCU_CR_HSITRIM_MASK     (0x1FU << MCU_CR_HSITRIM_POS)

/* Defininf the masks for the Clock Config Register. */
#define MCU_CFGR_PLLSRC_POS     (16U)
#define MCU_CFGR_PLLSRC_MASK    (0x01U << MCU_CFGR_PLLSRC_POS)

#define MCU_CFGR_PLLMUL_POS     (18U)
#define MCU_CFGR_PLLMUL_MASK    (0x0FU << MCU_CFGR_PLLSRC_POS)

/****************************** [global typedefs] *****************************/
/* Type to specify reset reason in raw register format */
typedef uint32  Mcu_RawResetType;

/* Type to specify the ID for a MCU mode */
typedef uint32  Mcu_ModeType;

/* Structure with clock settings. */
typedef uint32  Mcu_ClockType;

/* Subset of reset types. Dependent on hardware */
typedef enum
{
    MCU_POWER_ON_RESET = 0x00,
    MCU_WATCHDOG_RESET = 0x01,
    MCU_SW_RESET = 0x02,
    MCU_RESET_UNDEFINED = 0x03
    /* More reset types can be added that are supported by hardware. */
}Mcu_ResetType;

/* Status value return for the PLL status. */
typedef enum
{
    MCU_PLL_LOCKED = 0x00,
    MCU_PLL_UNLOCKED = 0x01,
    MCU_PLL_STATUS_UNDEFINED = 0x02
}Mcu_PllStatusType;

/* Structure that contains the common clock settings. */
typedef struct
{
    uint32  Prescaler;

}Mcu_ClockConfigType;
/* Structure to hold the MCU driver configuration. */
typedef struct
{
    Mcu_ClockType ClockSettingID;
    uint32  ClockSource;
    uint32  CalibrationValue;
    RCC_TypeDef* ModReg;
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
 * @brief   This service initializes the PLL and other MCU clock options.
 *
 * service ID   0x02
 *
 * param (in)   ClockSetting is the ID for the clock settings to be initialize.
 *
 * param (out)  none.
 *
 * retval   Std_ReturnType.
 */
Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting);

/**
 * @brief   This service activates de PLL clock to the MCU.
 *
 * service ID   0x03
 *
 * param (in)   none.
 *
 * param (out)  none.
 *
 * retval   Std_ReturnType.
 */
Std_ReturnType Mcu_DistributePllClock(void);

#endif /* if !define(MCU_H) */
/****************************** [end of file] *********************************/
