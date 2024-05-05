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
     * Set default values for the DT.
     * Disable all notifications
     * Run DeInit before Init for re-initialization.
     */

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
     */
    for(uint8 k = 0; k < 2; k++)
    {
        /* Register only contains information of 2 channels per register */
        uint32 channelOffset;

        channelOffset = ((Pwm_kConfigPtr[k].HwChannel << 3U) - 8U);

        tempReg = Pwm_kConfigPtr[k].ModReg->CCMR1;
        temp = 0U;
        /* Set PWM mode */
        temp = (Pwm_kConfigPtr[k].Mode << CCMR1_OC1M_POS);
        /* Enable preload register. */
        temp &= ~(CCMR1_OC1PE);
        temp |= (Pwm_kConfigPtr[k].PreloadEnable << CCMR1_OC1PE_POS);
        /* CCMR1 has 8 config bits per channel */
        tempReg &= ~(0xFFU << channelOffset);
        tempReg |= (temp << channelOffset);
        Pwm_kConfigPtr[k].ModReg->CCMR1 = tempReg;

        Pwm_SetDutyCycle(k, Pwm_kConfigPtr[k].DutyCycle);

        channelOffset = ((Pwm_kConfigPtr[k].HwChannel << 2U) - 4U);
        /* Set necessary config in CCER register */
        tempReg = Pwm_kConfigPtr[k].ModReg->CCER;
        temp = 0U;
        temp = (Pwm_kConfigPtr[k].Polarity << TIM_CCER_CC1P_Pos);           
        /* Enable channel 1 */
        temp |= (TIM_CCER_CC1E);
        /* CCER has 4 config bits per channel */
        tempReg &= ~(0xFU << channelOffset);
        tempReg |= (temp << channelOffset);
        Pwm_kConfigPtr[k].ModReg->CCER = tempReg;

        if(IS_TIM_BREAK_INSTANCE(Pwm_kConfigPtr[k].ModReg))
        {
            /* Main output enable */
            Pwm_kConfigPtr[k].ModReg->BDTR |= TIM_BDTR_MOE;
        }
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
    uint32 AbsDutyCycle;

    /* SWS_Pwm_00014 */
    if((DutyCycle == PWM_ZERO_PERCENT && Pwm_kConfigPtr[ChannelNumber].Polarity == PWM_CC_ACTIVE_HIGH) ||
    (DutyCycle >= PWM_HUNDRED_PERCENT && Pwm_kConfigPtr[ChannelNumber].Polarity == PWM_CC_ACTIVE_LOW))
    {
        /* Set the duty cycle to 100% */
        DutyCycle = PWM_ZERO_PERCENT;
    }
    else if((DutyCycle == PWM_ZERO_PERCENT && Pwm_kConfigPtr[ChannelNumber].Polarity == PWM_CC_ACTIVE_LOW) ||
    (DutyCycle >= PWM_HUNDRED_PERCENT && Pwm_kConfigPtr[ChannelNumber].Polarity == PWM_CC_ACTIVE_HIGH))
    {
        DutyCycle = PWM_HUNDRED_PERCENT;
    }
    else
    {
        /* Do nothing */
    }

    /* SWS_Pwm_00059 */
    AbsDutyCycle = ((uint32)Pwm_kConfigPtr[ChannelNumber].ModReg->ARR * DutyCycle) >> 15;
    
    /* SWS_Pwm_00013 */
    switch(Pwm_kConfigPtr[ChannelNumber].HwChannel)
    {
        case 1:
            {
                Pwm_kConfigPtr[ChannelNumber].ModReg->CCR1 = AbsDutyCycle;
                break;
            }
        case 2:
            {
                Pwm_kConfigPtr[ChannelNumber].ModReg->CCR2 = AbsDutyCycle;
                break;
            }
        case 3:
            {
                Pwm_kConfigPtr[ChannelNumber].ModReg->CCR3 = AbsDutyCycle;
                break;
            }
        case 4:
            {
                Pwm_kConfigPtr[ChannelNumber].ModReg->CCR4 = AbsDutyCycle;
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
