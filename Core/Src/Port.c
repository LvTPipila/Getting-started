/******************************* [general info] *******************************/
/*
 * File:    Port.c
 */

/********************************* [includes] *********************************/
#include "Port.h"
#include "stm32f302x8.h"
/********************************** [macros] **********************************/

/********************************* [typedefs] *********************************/

/************************** [variable declaration] ****************************/
const Port_ConfigType *Port_kConfigPtr = NULL;

/********************** [external function declarations] **********************/
/**
 * @brief Add a brief description of this function/interface.
 *
 * param  Add description of parameter value.
 *
 * retval Add name description of return value.
 */
void Port_Init(const Port_ConfigType *ConfigPtr)
{
    // TODO
    // It should initialize:
    // Pin usage (ADC, PWM, SPI, ...)
    // Pin direction (in, out)
    // Pin level init value
    // Pin direction changeable at runtime (yes/no)
    // Activaiton of internal pull-up/pull-down
    // Pin drive mode (push-pull/open-drain)
    // Other micro specific properties

    uint32 temp;
    uint32 tempReg;

    /* Copy pointer to local variable */
    if(ConfigPtr != NULL)
    {
        Port_kConfigPtr = ConfigPtr;
    } else
    {
        return;
    }

}

/**
 * @brief Add a brief description of this function/interface.
 *
 * param  Add description of parameter value.
 *
 * retval Add name description of return value.
 */
// void template_fcn(void);
/****************************** [end of file] *********************************/
