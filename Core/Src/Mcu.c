/******************************* [general info] *******************************/
/*
 * File:    Mcu.c
 */

/********************************* [includes] *********************************/
#include "Mcu.h"
/********************************** [macros] **********************************/

/********************************* [typedefs] *********************************/

/************************** [variable declaration] ****************************/

/********************** [internal function declarations] **********************/

/*********************** [external function definition] ***********************/
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
void Mcu_Init(const Mcu_ConfigType* ConfigPtr)
{
    // Configure the clock settings and the PLL
    // Also, need to investigate how to generate reference point for the 
    // pwm driver.
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
