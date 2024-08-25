/******************************* [general info] *******************************/
/*
 * File:    IoHwAb.c
 */

/********************************* [includes] *********************************/
#include "IoHwAb.h"
/********************************** [macros] **********************************/

/********************************* [typedefs] *********************************/

/************************** [variable declaration] ****************************/

/********************** [external function declarations] **********************/
/**
 * @brief Add a brief description of this function/interface.
 *
 * param (in)   Add description of parameter value.
 *
 * param (out)  Add description of parameter value.
 *
 * retval   Add name description of return value.
 */
void IoHwAb_Init(void)
{
    /* Initialize port driver. */
    const Port_PinConfigType Port_kChannelConfig0 [] =
        {
            {
                LED_Pin,
                PORT_PIN_OUT,
                PIN_MODE_DIGITAL_OUTPUT,
                0U,
                MODE_NO_PULL,
                MODE_PUSH_PULL,
                0U,
                GPIOB,
            },
            {
                /* Configure GPIO pin for PWM on TIM16_CH1, PB4 */
                PORT_PIN_4,
                PORT_PIN_OUT,
                PIN_MODE_ALTERNATE,
                AF_1,
                MODE_NO_PULL,
                MODE_PUSH_PULL,
                SPEED_FREQ_LOW,
                GPIOB,
            },
            {
                /*Configure GPIO pin for PWM on TIM2_CH2, PA1 */
                PORT_PIN_1,
                PORT_PIN_OUT,
                PIN_MODE_ALTERNATE,
                AF_1,
                MODE_NO_PULL,
                MODE_PUSH_PULL,
                SPEED_FREQ_LOW,
                GPIOA,
            },
        };

    const Port_ConfigType Port_ConfigPorts =
        {
            Port_kChannelConfig0,
            3U
        };
    Port_Init(&Port_ConfigPorts);

    /* Initialize pwm driver. */
    const Pwm_ChannelConfigType Pwm_kChannelConfig0[ ] =
        {
            {
                2u,
                PWM_CC_SELECT_OUTPUT,
                PWM_MODE_1,
                PWM_PRELOAD_ENABLE,
                (0xFFFFu), // Period
                PWM_CC_ACTIVE_HIGH,
                (0x8000u >> 3),
                TIM2
            },
            {
                1u,
                PWM_CC_SELECT_OUTPUT,
                PWM_MODE_1,
                PWM_PRELOAD_ENABLE,
                (0xFFFFu), // Period
                PWM_CC_ACTIVE_HIGH,
                (0x8000u >> 2),
                TIM16
            },
        };

    const Pwm_ConfigType Pwm_Channels =
        {
            Pwm_kChannelConfig0,
            2u,
        };
    Pwm_Init(&Pwm_Channels);
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
// void template_fcn(void);
/****************************** [end of file] *********************************/
