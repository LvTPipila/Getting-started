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

    /* RIGHT NOW, ONLY DONE FOR CHANNEL 1 OF TIM1 */
    /* Set PWM Capture/Compare. */
    temp = TIM1->CCMR1;
    temp &= ~(CCMR1_CC1S);  /* Clearing CC1S bits sets channel as output. */
    /* Set PWM mode */
    temp &= ~(CCMR1_OC1M);
    temp |= (Pwm_kConfigPtr->Mode << CCMR1_OC1M_POS);
    /* Enable preload register. */
    temp &= ~(CCMR1_OC1PE);
    temp |= (PWM_PRELOAD_ENABLE << CCMR1_OC1PE_POS);
    /* Write config in CCMR1 */
    TIM1->CCMR1 = temp;

    /* Set necessary config in CCER register */
    /* First, clear the bits */
    temp = TIM1->CCER;
    temp &= ~(TIM_CCER_CC1E + TIM_CCER_CC1P);   // Change polarity parameter for kCondifPtr
    /* Set defaut DT of 50% */
    TIM1->CCR1 = Pwm_kConfigPtr->DutyCycle;
    /* Enable channel 1 */
    temp |= (TIM_CCER_CC1E);
    TIM1->CCER = temp;

    /* Main output enable */
    TIM1->BDTR |= TIM_BDTR_MOE;
    /* Start PWM */
    TIM1->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief Service to set PWM duty cycle.      
 *
 * param  Channel number to set the duty cycle.
 *
 * param  DutyCycle is the duty cycle to be set.
 *
 * retval None
 */
void Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle)
{
    // TODO
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
