/******************************* [general info] *******************************/
/*
 * File:    Pwm.c
 */

/********************************* [includes] *********************************/
#include "Pwm.h"
#include "Pwm_MemMap.h"
/********************************** [macros] **********************************/

/********************************* [typedefs] *********************************/

/************************** [variable declaration] ****************************/
const Pwm_ConfigType *Pwm_kConfigPtr = NULL;
/********************** [external function declarations] **********************/
/**
 * @brief Service for PWM initialization. Init shall not be call during running
 *      operation, and shall call DeInit before a re-initialization.
 *      
 *      By initializing the PWM dirver, all PWM-channels shall be started
 *      SRS_Pwm_12380.
 *
 * param  Pointer to a Pwm_ConfigType structure with PWM parameters to 
 *      initialize.
 *
 * retval None
 */
void Pwm_Init(const Pwm_ConfigType* ConfigPtr)
{
    uint32 temp;
    uint32 tempReg;

    /* DON'T DOs
     * Call Init during running operation. */

    /* DOs
     * Init variables of Pwm_ConfigType structure.*/
    /* Set default values for the DT.*/
    /* Set polarity of channels and modes.*/
    /* Disable all notifications.*/
    /* Run DeInit before Init for re-initialization. */

    /* Copy configuration */
    if(ConfigPtr != NULL)
    {
        Pwm_kConfigPtr = ConfigPtr;
    } else
    {
        return;
    }

    /* NEED TO REPLACE 2 FOR A MACRO THAT FOR NUMBER OF PWM
     * CHANNELS THAT NEED TO BE CONFIGURED 
     * */
    for(uint8 k = 0; k < 2; k++)
    {
        /* Register only contains information of 2 channels per register */
        uint32 channelOffSet = ((Pwm_kConfigPtr[k].HwChannel << 3U) - 8U);

        tempReg = Pwm_kConfigPtr[k].ModReg->CCMR1;
        temp = 0U;
        /* Set PWM mode */
        temp = (Pwm_kConfigPtr[k].Mode << CCMR1_OC1M_POS);
        /* Enable preload register. */
        temp &= ~(CCMR1_OC1PE);
        temp |= (PWM_PRELOAD_ENABLE << CCMR1_OC1PE_POS);
        /* Clear 8 bits of config depending on channel number. */
        tempReg &= ~(0xFFU << channelOffSet);
        tempReg |= (temp << channelOffSet);
        /* Write config in CCMR1 */
        Pwm_kConfigPtr[k].ModReg->CCMR1 = tempReg;

        /* Set necessary config in CCER register */
        /* First, clear the bits */
        temp = Pwm_kConfigPtr[k].ModReg->CCER;
        temp &= ~(TIM_CCER_CC1E + TIM_CCER_CC1P);   // Change polarity parameter for kCondifPtr
        /* Set defaut DT of 50% */
        Pwm_kConfigPtr[k].ModReg->CCR1 = Pwm_kConfigPtr[k].DutyCycle;
        /* Enable channel 1 */
        temp |= (TIM_CCER_CC1E);
        Pwm_kConfigPtr[k].ModReg->CCER = temp;

        /* Main output enable */
        Pwm_kConfigPtr[k].ModReg->BDTR |= TIM_BDTR_MOE;
        /* Start PWM */
        Pwm_kConfigPtr[k].ModReg->CR1 |= TIM_CR1_CEN;
    }
}

/**
 * @brief Service sets the duty cycle of a PWM channel.
 *
 * param  ChannelNumber to set the duty cycle.
 *
 * param  DutyCycle is the duty cycle to be set.
 *
 * retval None
 */
void Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle)
{
    /* If duty cycle is 0% or 100%, DT has to be set to PWM_HIGH or
     * PWM_LOW depending on the configured polarity of the channel.
     *
     * AbsDutyCycle = ((uint32)AbsPeriodTime * RelativeDutyCycle) >> 15
     */
    if(DutyCycle >= 0x8000U)
    {
        /* Set the duty cycle to 100% */
        Pwm_kConfigPtr[ChannelNumber].ModReg->CCR1 = 0xFFFF;
    }
    /* Set defaut DT of 50% */
    Pwm_kConfigPtr[ChannelNumber].ModReg->CCR1 = DutyCycle;
}

/**
 * @brief Service sets the PWM output to the configured idle state.
 *
 * param  ChannelNumber to set to idle state.
 *
 * retval None.
 */
void Pwm_SetOutputToIdle(Pwm_ChannelType ChannelNumber)
{
    // TODO:
}

/**
 * @brief Add a brief description of this function/interface.
 *
 * param  Add description of parameter value.
 *
 * retval Add name description of return value.
 */
//void template_fcn(void);

/****************************** [end of file] *********************************/
