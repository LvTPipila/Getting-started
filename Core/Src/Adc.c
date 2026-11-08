/******************************* [general info] *******************************/
/*
 * File:    Adc.c
 */

/********************************* [includes] *********************************/
#include "Adc.h"
/********************************** [macros] **********************************/

/********************************* [typedefs] *********************************/

/************************** [variable declaration] ****************************/
const Adc_ConfigType* Adc_kConfigPtr = NULL;

/********************** [internal function declarations] **********************/

/*********************** [external function definition] ***********************/
/**
 * @brief   This service initializes the ADC hardware unit and driver.
 *          SWS_Adc_00077 Adc_init shall disable notifications and hardware
 *          trigger capabilities.
 *
 *          SWS_Adc_00307 Adc_Init shall set all groups to IDLE state.
 *
 * service ID   0x00
 *
 * param (in)   ConfigPtr is a pointer to a structure of MCU configuration.
 *
 * param (out)  None.
 *
 * retval   None.
 */
void Adc_Init(const Adc_ConfigType* ConfigPtr)
{
    uint32  tempReg;
    const Adc_ConfigType* localAdcConfigPtr;

    /* Also, need to investigate how to generate reference point for the pwm driver. */
    if(ConfigPtr != NULL)
    {
        Adc_kConfigPtr = ConfigPtr;
        localAdcConfigPtr = ConfigPtr;
    } else
    {
        return;
    }

    /* Step 1 is to configure the clock source. */
    tempReg = localMcuConfigPtr->ModReg->CR;
    CLEAR_BITS(tempReg, MCU_CR_HSITRIM_MASK);
    WRITE_BITS(tempReg, (localMcuConfigPtr->CalibrationValue << MCU_CR_HSITRIM_POS));
    localMcuConfigPtr->ModReg->CR = tempReg;

    /* Step 2 make routine for voltage regulation.
     * Does it need a static function?
     */
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
void template_fcn(void);
/****************************** [end of file] *********************************/
