/******************************* [general info] *******************************/
/*
 * File:    Mcu.c
 */

/********************************* [includes] *********************************/
#include "Mcu.h"
/********************************** [macros] **********************************/

/********************************* [typedefs] *********************************/

/************************** [variable declaration] ****************************/
const Mcu_ConfigType* Mcu_kConfigPtr = NULL;

/********************** [internal function declarations] **********************/

/*********************** [external function definition] ***********************/
/**
 * @brief   This service initializes the MCU driver.
 *          SWS_Mcu_00026: Shall make config settings for power down, clock and 
 *          RAM sections visible within the MCU modules.
 *           
 *          SWS_Mcu_00244: If the register affects several hardware modules, and if
 *          it is an I/O reg, then it shall be init by PORT.
 *          SWS_Mcu_00245: If affects several hardware modules and it is not an
 *          I/O reg, then it shall be init by MCU.
 *
 * service ID   0x00
 *
 * param (in)   ConfigPtr is a pointer to a structure of MCU configuration.
 *
 * param (out)  none.
 *
 * retval   none.
 */
void Mcu_Init(const Mcu_ConfigType* ConfigPtr)
{
    volatile uint32 tempReg;
    const Mcu_ConfigType* localMcuConfigPtr;

    /* Also, need to investigate how to generate reference point for the pwm driver. */
    if(ConfigPtr != NULL)
    {
        Mcu_kConfigPtr = ConfigPtr;
        localMcuConfigPtr = ConfigPtr;
    } else
    {
        return;
    }

    localMcuConfigPtr->ModReg->CR |= MCU_CR_HSION_MASK;
    while((localMcuConfigPtr->ModReg->CR & MCU_CR_HSIRDY_MASK) != MCU_CR_HSIRDY_MASK)
    {
        /* Wait until HSI clock is ready. */
    }
    /* Calibrate HSI */
    tempReg = localMcuConfigPtr->ModReg->CR;
    CLEAR_BITS(tempReg, MCU_CR_HSITRIM_MASK);
    WRITE_BITS(tempReg, (localMcuConfigPtr->CalibrationValue << MCU_CR_HSITRIM_POS));
    localMcuConfigPtr->ModReg->CR = tempReg;

}

/**
 * @brief   This service initializes the PLL and other MCU clock options.
 *          SWS_Mcu_00137: Init the PLL and other MCU specific clock settings
 *          provided by the configuration structure.
 *
 *          SWS_Mcu_00138: It shall start the PLL lock procedure, and it shall
 *          return without waiting until the PLL is locked.
 *
 *          SWS_Mcu_00139: Environment shall only call Mcu_ClockInit after the
 *          MCU module has been init with Mcu_Init().
 *
 * service ID   0x02
 *
 * param (in)   Add description of parameter value.
 *
 * param (out)  none.
 *
 * retval   Std_ReturnType.
 */
Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting)
{
    uint32 tickTime = 0U;
    volatile uint32 tempReg;
    // const Mcu_ConfigType* localMcuConfigPtr;
    const Mcu_PllConfigType* localPllConfigPtr;

    localPllConfigPtr = Mcu_kConfigPtr->PllConfigPtr;

    /* I MIGHT NEED TO CONFIGURE THE FLASH MEMORY REGISTERS 
     * I did it outside just before calling MCU_Init.
     */

    /* CONFIG OF THE PLL
     * Turn off and wait to unlock.
     * Select PLL src and multiplication factor.
     * Enable PLL.
     */

    /* Disable PLL. */
    CLEAR_BITS(Mcu_kConfigPtr->ModReg->CR, MCU_CR_PLLON_MASK);

    while(((Mcu_kConfigPtr->ModReg->CR & MCU_CR_PLLRDY_MASK) >> MCU_CR_PLLRDY_POS) != 0)
    {
        /* Wait until PLL is unlocked. */
    }

    tempReg = Mcu_kConfigPtr->ModReg->CFGR;
    CLEAR_BITS(tempReg, (MCU_CFGR_PLLSRC_MASK | MCU_CFGR_PLLMUL_MASK));
    WRITE_BITS(tempReg, (localPllConfigPtr->PllSource << MCU_CFGR_PLLSRC_POS));
    WRITE_BITS(tempReg, (localPllConfigPtr->PllMultiplier << MCU_CFGR_PLLMUL_POS));
    Mcu_kConfigPtr->ModReg->CFGR = tempReg;

    WRITE_BITS(Mcu_kConfigPtr->ModReg->CR, MCU_CR_PLLON_MASK);


    /* Init clocks PCLK2 (APB2) for TIM16.
     * Max Hz for APB1 is 36 MHz.
     * Max Hz for APB2 is 72 MHz.
     */
    tempReg = Mcu_kConfigPtr->ModReg->CFGR;
    CLEAR_BITS(tempReg, MCU_CFGR_SW_MASK);
    WRITE_BITS(tempReg, (Mcu_kConfigPtr->SysClockSource << MCU_CFGR_SW_POS));
    Mcu_kConfigPtr->ModReg->CFGR = tempReg;

    while(((Mcu_kConfigPtr->ModReg->CFGR & MCU_CFGR_SWS_MASK) >> MCU_CFGR_SWS_POS) != \
        Mcu_kConfigPtr->SysClockSource)
    {
        /* Wait until the system clock status is the same as the configured. */
    }
    
    tempReg = Mcu_kConfigPtr->ModReg->CFGR;
    CLEAR_BITS(tempReg, (MCU_CFGR_HPRE_MASK | MCU_CFGR_PPRE1_MASK | MCU_CFGR_PPRE2_MASK));
    WRITE_BITS(tempReg, ((Mcu_kConfigPtr->HwClkPre << MCU_CFGR_HPRE_POS) | \
               (Mcu_kConfigPtr->APB1Pre << MCU_CFGR_PPRE1_POS) | \
               (Mcu_kConfigPtr->APB2Pre << MCU_CFGR_PPRE2_POS)));
    Mcu_kConfigPtr->ModReg->CFGR = tempReg;

    return E_OK;
}

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
Std_ReturnType Mcu_DistributePllClock(void)
{
    while(((Mcu_kConfigPtr->ModReg->CR & MCU_CR_PLLRDY_MASK) >> MCU_CR_PLLRDY_POS) == 0)
    {
        /* Wait until PLL is locked. */
    }

    return E_OK;
}

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
Mcu_PllStatusType Mcu_GetPllStatus(void)
{
    return MCU_PLL_STATUS_UNDEFINED;
}

/**
 * @brief Add a brief description of this function/interface.
 *
 * param (in)   Add description of parameter value.
 *
 * param (out)  Add description of parameter value.
 *
 * retval   Add name description of return value.
 */
//void template_fcn(void);

/****************************** [end of file] *********************************/
