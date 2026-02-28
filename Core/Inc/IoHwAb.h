/******************************** [general info] ******************************/
/*
 * File:    IoHwAb.h
 */

#ifndef IO_HW_AB_H
#define IO_HW_AB_H
/********************************* [includes] *********************************/
#include "stm32f302x8.h"
#include "Port.h"
#include "Pwm.h"
/******************************* [global macros] ******************************/
#define LED_Pin     PORT_PIN_13
/****************************** [global typedefs] *****************************/

/************************** [variable declaration] ****************************/

/********************** [external function declarations] **********************/
/**
 * @brief   Add a brief description of this function/interface.
 *
 * param (in)   Add description of parameter value.
 *
 * param (out)  Add description of parameter value.
 *
 * retval   Add name description of return value.
 */
void IoHwAb_Init(void);
#endif /* if !define(IO_HW_AB_H) */
/****************************** [end of file] *********************************/
