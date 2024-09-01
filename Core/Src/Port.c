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

/********************** [internal function declarations] **********************/
static void Port_SetOutputConfig(const Port_PinConfigType* PinConfigPtr, uint32 regOffset);

/*********************** [external function definition] ***********************/
/**
 * @brief Add a brief description of this function/interface.
 *
 * param  Add description of parameter value.
 *
 * retval Add name description of return value.
 */
void Port_Init(const Port_ConfigType *ConfigPtr)
{
    // It should initialize:
    // Pin level init value
    // Pin direction changeable at runtime (yes/no)
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

        if(localPortConfigPtr->PinMode == DIO)
        {
            if(localPortConfigPtr->Direction == PORT_PIN_OUT)
            {
                Port_SetOutputConfig(localPortConfigPtr, offset);
            }

            tempReg = localPortConfigPtr->ModReg->PUPDR;
            tempReg &= (~(GPIO_PUPDR_PUPDR0 << (offset * 2U)));
            tempReg |= (localPortConfigPtr->PullMode << (offset * 2U));
            localPortConfigPtr->ModReg->PUPDR = tempReg;

            /* Use GPIO_MODER_MODER0 as base to move the offset */
            tempReg = localPortConfigPtr->ModReg->MODER;
            tempReg &= (~(GPIO_MODER_MODER0 << (offset * 2U)));
            tempReg |= (localPortConfigPtr->PinMode << (offset * 2U));
            localPortConfigPtr->ModReg->MODER = tempReg;

        }else if(localPortConfigPtr->PinMode == PWM)
        {
            tempReg = localPortConfigPtr->ModReg->AFR[offset >> 3U];
            /* 4 is the number of bits in the register to config alternate fcn */
            tempReg &= (~(0xFU << ((offset & 7U) * 4U)));
            tempReg |= ((localPortConfigPtr->Alternate) << ((offset & 7U) * 4U));
            localPortConfigPtr->ModReg->AFR[offset >> 3U] = tempReg;

            if(localPortConfigPtr->Direction == PORT_PIN_OUT)
            {
                Port_SetOutputConfig(localPortConfigPtr, offset);
            }

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

static void Port_SetOutputConfig(const Port_PinConfigType* PinConfigPtr, uint32 regOffset)
{
    uint32 temp;
    /* Configure open drain / push-pull register */
    temp = PinConfigPtr->ModReg->OTYPER;
    temp &= (~(1U << regOffset));
    temp |= (PinConfigPtr->OutputMode << regOffset);
    PinConfigPtr->ModReg->OTYPER = temp;

    /* Configure output speed register. ONLY LOW SPEED for the moment. */
    temp = PinConfigPtr->ModReg->OSPEEDR;
    temp &= (~(GPIO_OSPEEDER_OSPEEDR0 << (regOffset * 2U)));
    temp |= (SPEED_FREQ_LOW << (regOffset * 2U));
    PinConfigPtr->ModReg->OSPEEDR = temp;
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
