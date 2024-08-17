/******************************* [general info] *******************************/
/*
 * File:    Port.c
 */

/********************************* [includes] *********************************/
#include "Port.h"
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

    uint8 portMaxPins;
    uint16 currentPin;
    uint32 position;
    uint32 offset;
    uint32 tempReg;
    const Port_PinConfigType* localPortConfigPtr;

    /* Copy pointer to local variable */
    if(ConfigPtr != NULL)
    {
        Port_kConfigPtr = ConfigPtr;
    } else
    {
        return;
    }

    localPortConfigPtr = ConfigPtr->PinConfigPtr;
    portMaxPins = ConfigPtr->PortMaxConfigPins;

    for(uint8 configPin = 0; configPin < portMaxPins; configPin++)
    {
        position = localPortConfigPtr->Pin;

        if((position == 0x00U) || (position > PORT_PIN_ALL))
        {
            return;
        }

        currentPin = 0U;
        while((position >> currentPin) != 0x00U)
        {
            currentPin++;
        }

        /* GOT POSITION OF PIN STARTING FROM 1 */
        offset = (currentPin - 1U);

        if(localPortConfigPtr->Direction == PORT_PIN_IN)
        {
            /* Set alternate function */
            /* Set PUPDR */
            /* Set Mode in MODER register */
            tempReg = localPortConfigPtr->ModReg->PUPDR;
            tempReg &= (~(GPIO_PUPDR_PUPDR0 << (offset * 2U)));
            tempReg |= (localPortConfigPtr->PullMode << (offset * 2U));
            localPortConfigPtr->ModReg->PUPDR = tempReg;

            /* Use GPIO_MODER_MODER0 as base to move the offset */
            tempReg = localPortConfigPtr->ModReg->MODER;
            tempReg &= (~(GPIO_MODER_MODER0 << (offset * 2U)));
            localPortConfigPtr->ModReg->MODER = tempReg;

        }else if(localPortConfigPtr->Direction == PORT_PIN_OUT)
        {
            /* Configure output */
            if(localPortConfigPtr->PinMode == PIN_MODE_ALTERNATE)
            {
                tempReg = localPortConfigPtr->ModReg->AFR[offset >> 3U];
                /* 4 is the number of bits in the register to config alternate fcn */
                tempReg &= (~(0xFU << ((offset & 7U) * 4U)));
                tempReg |= ((localPortConfigPtr->Alternate) << ((offset & 7U) * 4U));
                localPortConfigPtr->ModReg->AFR[offset >> 3U] = tempReg;
            }
            /* Configure open drain / push-pull register */
            tempReg = localPortConfigPtr->ModReg->OTYPER;
            tempReg &= (~(1U << offset));
            tempReg |= (localPortConfigPtr->OutputMode << offset);
            localPortConfigPtr->ModReg->OTYPER = tempReg;

            /* Configure output speed register. ONLY LOW SPEED for the moment. */
            tempReg = localPortConfigPtr->ModReg->OSPEEDR;
            tempReg &= (~(GPIO_OSPEEDER_OSPEEDR0 << (offset * 2U)));
            tempReg |= (SPEED_FREQ_LOW << (offset * 2U));
            localPortConfigPtr->ModReg->OSPEEDR = tempReg;

            /* Configure pull-up / pull-down register */
            tempReg = localPortConfigPtr->ModReg->PUPDR;
            tempReg &= (~(GPIO_PUPDR_PUPDR0 << (offset * 2U)));
            tempReg |= (localPortConfigPtr->PullMode << (offset * 2U));
            localPortConfigPtr->ModReg->PUPDR = tempReg;

            tempReg = localPortConfigPtr->ModReg->MODER;
            tempReg &= (~(GPIO_MODER_MODER0 << (offset * 2U)));
            tempReg |= (localPortConfigPtr->PinMode << (offset * 2U));
            localPortConfigPtr->ModReg->MODER = tempReg;
        }else
        {
            return;
        }

        localPortConfigPtr++;
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
