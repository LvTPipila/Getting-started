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
    uint32 tempReg;
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
    tempReg &= ~(MCU_CR_HSITRIM_MASK);
    tempReg |= (localMcuConfigPtr->CalibrationValue << MCU_CR_HSITRIM_POS);
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
    uint32 tempReg;
    const Mcu_ConfigType* localMcuConfigPtr;

    /* Disable PLL and wait until PLLRDY is cleared. */
    tempReg = Mcu_kConfigPtr->ModReg->CFGR;
    tempReg &= (~(MCU_CFGR_PLLSRC_MASK));
    /* CONFIG OF THE PLL
     * Select PLL src and multiplication factor.
     * Enable PLL.
     */

    /* Init clocks PCLK2 (APB2) for TIM16 */
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
