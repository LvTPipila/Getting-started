/**************************** [general information] ****************************/
/*
 * File:    Pwm.h
 */

#ifndef PWM_H
#define PWM_H
/********************************* [includes] *********************************/
#include "Std_Types.h"
#include "Pwm_MemMap.h"
//#include "Pwm_cfg.h"
/******************************* [global macros] ******************************/

/* Mask PWM Capture / Compare modes */
#define PWM_CC_SELECT_OUTPUT    (0x0U)
/* Polarity of the output channel */
#define PWM_CC_ACTIVE_HIGH      (0x0U)
#define PWM_CC_ACTIVE_LOW       (0x1U)

/* PWM modes */
#define PWM_MODE_1              (0x6U)
#define PWM_MODE_2              (0x7U)
#define PWM_PRELOAD_ENABLE      (0x1U)
#define PWM_PRELOAD_DISABLE     (0x0U)

/* PWM Duty Cycle percentage */
#define PWM_HUNDRED_PERCENT     (0xFFFFU)
#define PWM_ZERO_PERCENT        (0U)

/* Create some masks for CCER register */

/* Create some masks for the CCMRx registers */
#define CCMR1_CC1S_POS          (0U)
#define CCMR1_CC1S_MASK         (0x3U)        // 2 bits for this option.
#define CCMR1_CC1S              (CCMR1_CC1S_MASK << CCMR1_CC1S_POS)

#define CCMR1_OC1FE_POS         (2U)
#define CCMR1_OC1FE_MASK        (0x1U)
#define CCMR1_OC1FE             (CCMR1_OC1FE_MASK << CCMR1_OC1FE_POS)

#define CCMR1_OC1PE_POS         (3U)
#define CCMR1_OC1PE_MASK        (0x1U)
#define CCMR1_OC1PE             (CCMR1_OC1PE_MASK << CCMR1_OC1PE_POS)

#define CCMR1_OC1M_POS          (4U)
#define CCMR1_OC1M_MASK         (0x7U)
#define CCMR1_OC1M              (CCMR1_OC1M_MASK << CCMR1_OC1M_POS)

#define CCMR1_OC1CE_POS         (7U)
#define CCMR1_OC1CE_MASK        (0x1U)
#define CCMR1_OC1CE             (CCMR1_OC1CE_MASK << CCMR1_OC1CE_POS)

#define CCMR1_CC2S_POS          (8U)
#define CCMR1_CC2S_MASK         (0x3U)        // 2 bits for this option.
#define CCMR1_CC2S              (CCMR1_CC2S_MASK << CCMR1_CC2S_POS)

/****************************** [global typedefs] *****************************/
/* Numeric identification of a PWM chanel. */
typedef uint32  Pwm_ChannelType;

/* Definition of the period of a PWM channel. */
typedef uint32  Pwm_PeriodType;

/* Output state of a PWM channel. */
typedef enum
{
    PWM_HIGH  = 0x00u,      // The PWM channel is high state.
    PWM_LOW = 0x01u        // The PWM channel is low state.
}Pwm_OutputStateType;

/* Defines the class of a PWM channel. */
typedef enum
{
    PWM_VARIABLE_PERIOD = 0x00,
    PWM_FIXED_PERIOD = 0x01,
    PWM_FIXED_PERIOD_SHIFTED = 0x02
}Pwm_ChannelClassType;

/* Result of the requests related to power state transitions. */
typedef enum
{
    PWM_SERVICE_ACCEPTED = 0x00,    // Power state change exectuted.
    PWM_NOT_INIT = 0x01,
    PWM_SEQUENCE_ERROR = 0X02,
    PWM_HW_FAILURE = 0x03,
    PWM_POWER_STATE_NOT_SUPP = 0x04,
    PWM_TRANS_NOT_POSSIBLE = 0x05
}Pwm_PowerStateRequestResultType;

/* Power state currently active or set as target power state. */
typedef enum
{
    PWM_FULL_POWER = 0x00
}Pwm_PowerStateType;

/* Struct containing initialization data for the PWM driver. */
typedef struct
{
    /* HW specific */
    Pwm_ChannelType HwChannel;  /* Channel to configure */
    uint32  CompareMode;   /* Set PWM channel as input capture or output. */

    /* PWM mode as Input and Output PWM, consider both scenarios. For 
     * Output mode, value is 3-bit and for Input is 4-bit value.
     */
    uint32  Mode;
    uint32  PreloadEnable;       /* Preload register enable/disable */

    /* Polarity of the channel */
    uint32  Polarity;
    uint16  DutyCycle;

    /* Structure of TIM registers */
    TIM_TypeDef *ModReg;

}Pwm_ConfigType;

/************************** [variable declaration] ****************************/

/********************** [external function declarations] **********************/
/**
 * @brief Service for PWM initialization.
 *
 * param  ConfigPtr is a pointer to configureation for PWM channels.
 *
 * retval none.
 */
void Pwm_Init(const Pwm_ConfigType* ConfigPtr);

/**
 * @brief Service sets the duty cycle of the PWM channel.
 *
 * param  ChannelNumber is the channel to be set.
 *
 * param  DutyCycle is the DT to be set.
 *
 * retval none.
 */
void Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle);

/**
 * @brief Add a brief description of this function/interface.
 *
 * param  Add description of parameter value.
 *
 * retval Add name description of return value.
 */
// void template_fcn(void);

#endif /* if !define(PWM_H) */
/****************************** [end of file] *********************************/
