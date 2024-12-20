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

#define MCU_SYSCLKSRC_HSI   0x0U
#define MCU_SYSCLKSRC_HSE   0x1U
#define MCU_SYSCLKSRC_PLL   0x2U

#define MCU_CLKTYPE_HCLK    0x0U
#define MCU_CLKTYPE_PCLK1   0x1U
#define MCU_CLKTYPE_PCLK2   0x2U

/* Defining the masks for the Control Register. */
#define MCU_CR_HSION_POS        (0U)
#define MCU_CR_HSION_MASK       (0x01U << MCU_CR_HSION_POS)

#define MCU_CR_HSIRDY_POS       (1U)
#define MCU_CR_HSIRDY_MASK      (0x01U << MCU_CR_HSIRDY_POS)

#define MCU_CR_HSITRIM_POS      (3U)
#define MCU_CR_HSITRIM_MASK     (0x1FU << MCU_CR_HSITRIM_POS)

#define MCU_CR_HSEON_POS        (16U)
#define MCU_CR_HSEON_MASK       (0x01U << MCU_CR_HSEON_POS)

#define MCU_CR_HSERDY_POS       (17U)
#define MCU_CR_HSERDY_MASK      (0x01U << MCU_CR_HSERDY_POS)

#define MCU_CR_PLLON_POS        (24U)
#define MCU_CR_PLLON_MASK       (0x01U << MCU_CR_PLLON_POS)

#define MCU_CR_PLLRDY_POS       (25U)
#define MCU_CR_PLLRDY_MASK      (0x01U << MCU_CR_PLLRDY_POS)

/* Defininf the masks for the Clock Config Register. */
#define MCU_CFGR_SW_POS         (0U)
#define MCU_CFGR_SW_MASK        (0x03U << MCU_CFGR_SW_POS)

#define MCU_CFGR_SWS_POS        (2U)
#define MCU_CFGR_SWS_MASK       (0x03U << MCU_CFGR_SWS_POS)

#define MCU_CFGR_HPRE_POS       (4U)
#define MCU_CFGR_HPRE_MASK      (0x0FU << MCU_CFGR_HPRE_POS)

#define MCU_CFGR_PPRE1_POS      (8U)
#define MCU_CFGR_PPRE1_MASK     (0x07U << MCU_CFGR_PPRE1_POS)

#define MCU_CFGR_PPRE2_POS      (11U)
#define MCU_CFGR_PPRE2_MASK     (0x07U << MCU_CFGR_PPRE2_POS)

#define MCU_CFGR_PLLSRC_POS     (16U)
#define MCU_CFGR_PLLSRC_MASK    (0x01U << MCU_CFGR_PLLSRC_POS)

#define MCU_CFGR_PLLXTPRE_POS   (17U)
#define MCU_CFGR_PLLXTPRE_MASK  (0x01U << MCU_CFGR_PLLXTPRE_POS)

#define MCU_CFGR_PLLMUL_POS     (18U)
#define MCU_CFGR_PLLMUL_MASK    (0x0FU << MCU_CFGR_PLLMUL_POS)

/* Defininf the masks for the Peripheral clock enable register. */
#define MCU_AHBENR_DMA1_POS     (0U)
#define MCU_AHBENR_DMA1_MASK    (0x01U << MCU_AHBENR_DMA1_POS)

#define MCU_AHBENR_DMA2_POS     (1U)
#define MCU_AHBENR_DMA2_MASK    (0x01U << MCU_AHBENR_DMA2_POS)

#define MCU_AHBENR_SRAM_POS     (2U)
#define MCU_AHBENR_SRAM_MASK    (0x01U << MCU_AHBENR_SRAM_POS)

#define MCU_AHBENR_FLITF_POS    (4U)
#define MCU_AHBENR_FLITF_MASK   (0x01U << MCU_AHBENR_FLITF_POS)

#define MCU_AHBENR_FMC_POS      (5U)
#define MCU_AHBENR_FMC_MASK     (0x01U << MCU_AHBENR_FMC_POS)

#define MCU_AHBENR_CRC_POS      (6U)
#define MCU_AHBENR_CRC_MASK     (0x01U << MCU_AHBENR_CRC_POS)

#define MCU_AHBENR_IOPA_POS     (17U)
#define MCU_AHBENR_IOPA_MASK    (0x01U << MCU_AHBENR_IOPA_POS)

#define MCU_AHBENR_IOPB_POS     (18U)
#define MCU_AHBENR_IOPB_MASK    (0x01U << MCU_AHBENR_IOPB_POS)

#define MCU_AHBENR_IOPC_POS     (19U)
#define MCU_AHBENR_IOPC_MASK    (0x01U << MCU_AHBENR_IOPC_POS)

#define MCU_AHBENR_IOPD_POS     (20U)
#define MCU_AHBENR_IOPD_MASK    (0x01U << MCU_AHBENR_IOPD_POS)

#define MCU_AHBENR_IOPE_POS     (21U)
#define MCU_AHBENR_IOPE_MASK    (0x01U << MCU_AHBENR_IOPE_POS)

#define MCU_AHBENR_IOPF_POS     (22U)
#define MCU_AHBENR_IOPF_MASK    (0x01U << MCU_AHBENR_IOPF_POS)

#define MCU_AHBENR_IOPG_POS     (23U)
#define MCU_AHBENR_IOPG_MASK    (0x01U << MCU_AHBENR_IOPG_POS)

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
    uint8   ClkType;
    uint32  Prescaler;

}Mcu_HwClockType;

typedef struct
{
    uint8   ClkType;
    uint32  Prescaler;

}Mcu_APB1ClockType;

typedef struct
{
    uint8   ClkType;
    uint32  Prescaler;

}Mcu_APB2ClockType;

/* Structure that contains PLL config settings. */
typedef struct
{
    uint8   PllSource;
    uint8   PllMultiplier;
}Mcu_PllConfigType;

/* Structure to hold the MCU driver configuration. */
typedef struct
{
    const Mcu_PllConfigType*  PllConfigPtr;
    uint32  OscType;
    uint32  CalibrationValue;
    uint32  SysClockSource;
    uint32  HwClkPre;
    uint32  APB1Pre;
    uint32  APB2Pre;
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

/**
 * @brief   This service provides the lock status of the PLL.
 *
 * service ID   0x04
 *
 * param (in)   none.
 *
 * param (out)  none.
 *
 * retval   PLL status.
 */
Mcu_PllStatusType Mcu_GetPllStatus(void);

#endif /* if !define(MCU_H) */
/****************************** [end of file] *********************************/
