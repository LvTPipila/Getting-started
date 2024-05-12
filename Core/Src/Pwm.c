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
    Pwm_ChannelType maxChannels;
    const Pwm_ChannelConfigType* localPwmChannelPtr;

    /* DON'T DOs
     * Call Init during running operation. */

    /* DOs
     * Set default values for the DT.
     * Disable all notifications
     * Run DeInit before Init for re-initialization.
     */

    if(ConfigPtr != NULL)
    {
        Pwm_kConfigPtr = ConfigPtr;
    } else
    {
        return;
    }

    maxChannels = ConfigPtr->PwmMaxChannels;
    localPwmChannelPtr = ConfigPtr->ChannelConfigPtr;

    for(uint8 channel = 0; channel < maxChannels; channel++)
    {
        /* Register only contains information of 2 channels per register */
        uint32 channelOffset;
        channelOffset = ((localPwmChannelPtr->HwChannel << 3U) - 8U);

        tempReg = localPwmChannelPtr->ModReg->CCMR1;
        temp = 0U;
        /* Set PWM mode */
        temp = (localPwmChannelPtr->Mode << CCMR1_OC1M_POS);
        /* Enable preload register. */
        temp &= ~(CCMR1_OC1PE);
        temp |= (localPwmChannelPtr->PreloadEnable << CCMR1_OC1PE_POS);
        /* CCMR1 has 8 config bits per channel */
        tempReg &= ~(0xFFU << channelOffset);
        tempReg |= (temp << channelOffset);
        localPwmChannelPtr->ModReg->CCMR1 = tempReg;

        localPwmChannelPtr->ModReg->ARR = localPwmChannelPtr->Period;
        
        Pwm_SetDutyCycle(channel, localPwmChannelPtr->DutyCycle);

        channelOffset = ((localPwmChannelPtr->HwChannel << 2U) - 4U);
        /* Set necessary config in CCER register */
        tempReg = localPwmChannelPtr->ModReg->CCER;
        temp = 0U;
        temp = (localPwmChannelPtr->Polarity << TIM_CCER_CC1P_Pos);           
        /* Enable channel 1 */
        temp |= (TIM_CCER_CC1E);
        /* CCER has 4 config bits per channel */
        tempReg &= ~(0xFU << channelOffset);
        tempReg |= (temp << channelOffset);
        localPwmChannelPtr->ModReg->CCER = tempReg;

        if(IS_TIM_BREAK_INSTANCE(localPwmChannelPtr->ModReg))
        {
            /* Main output enable */
            localPwmChannelPtr->ModReg->BDTR |= TIM_BDTR_MOE;
        }
        /* Start PWM */
        localPwmChannelPtr->ModReg->CR1 |= TIM_CR1_CEN;

        localPwmChannelPtr++;
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
    const Pwm_ChannelConfigType* localChannelPtr;
    uint32 AbsDutyCycle;

    localChannelPtr = ((Pwm_kConfigPtr->ChannelConfigPtr) + ChannelNumber);
    
    /* SWS_Pwm_00014 */
    if((DutyCycle == PWM_ZERO_PERCENT && localChannelPtr->Polarity == PWM_CC_ACTIVE_HIGH) ||
    (DutyCycle >= PWM_HUNDRED_PERCENT && localChannelPtr->Polarity == PWM_CC_ACTIVE_LOW))
    {
        /* Set the duty cycle to 100% */
        DutyCycle = PWM_ZERO_PERCENT;
    }
    else if((DutyCycle == PWM_ZERO_PERCENT && localChannelPtr->Polarity == PWM_CC_ACTIVE_LOW) ||
    (DutyCycle >= PWM_HUNDRED_PERCENT && localChannelPtr->Polarity == PWM_CC_ACTIVE_HIGH))
    {
        DutyCycle = PWM_HUNDRED_PERCENT;
    }
    else
    {
        /* Do nothing */
    }

    /* SWS_Pwm_00059 */
    AbsDutyCycle = ((uint32)localChannelPtr->ModReg->ARR * DutyCycle) >> 15u;
    
    /* SWS_Pwm_00013 */
    switch(localChannelPtr->HwChannel)
    {
        case 1:
            {
                localChannelPtr->ModReg->CCR1 = AbsDutyCycle;
                break;
            }
        case 2:
            {
                localChannelPtr->ModReg->CCR2 = AbsDutyCycle;
                break;
            }
        case 3:
            {
                localChannelPtr->ModReg->CCR3 = AbsDutyCycle;
                break;
            }
        case 4:
            {
                localChannelPtr->ModReg->CCR4 = AbsDutyCycle;
                break;
            }
        default:
            break;
    }
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
