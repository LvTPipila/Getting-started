/******************************** [general info] ******************************/
/*
 * File:    Adc.h
 */

#ifndef ADC_H
#define ADC_H
/********************************* [includes] *********************************/
#include "Std_Types.h"
#include "stm32f302x8.h"

/******************************* [global macros] ******************************/

/****************************** [global typedefs] *****************************/
/* Structure with config parameters to initialize ADC driver and ADC HW unit. */
typedef struct
{
    /* Structure params ADC config. */
}Adc_ConfigType;

/* Numeric ID of an ADC channel. */
typedef uint32  Adc_ChannelType;

/* Numeric ID of an ADC channel group. */
typedef uint32  Adc_GroupType;

/* Type for reading converted values of a channel group
 * (raw, without scaling, alignment according to configuration).
 * Read section 8.2.4 for implementation requirements.
 */
typedef int16   Adc_ValueGroupType;

/* Type of clock prescaler factor. */
typedef uint8   Adc_PrescaleType;

/* SKIPPED SWS_ADC_00510 Adc_ConversionTimeType. Didn't understand it. */

/* SKIPPED SWS_ADC_00511 Adc_SamplingTimeType. Didn't understand it. */

/* Type of channel resolution in number of bits. */
typedef uint8   Adc_ResolutionType;

/* Current status of convertion of requested ADC Channel group. */
typedef enum
{
    ADC_IDLE = 0x00,
    ADC_BUSY = 0x01,
    ADC_COMPLETED = 0x02,
    ADC_STREAM_COMPLETED = 0x03
}Adc_StatusType;

/* Type for configuring the trigger source of a channel group. */
typedef enum
{
    ADC_TRIGG_SRC_SW = 0x00,
    ADC_TRIGG_SRC_HW = 0x01
}Adc_TriggerSourceType;

/* Type for configuring the conversion mode of a channel group. */
typedef enum
{
    ADC_CONV_MODE_ONESHOT = 0x00,
    ADC_CONV_MODE_CONTINUOUS = 0x01
}Adc_TriggerSourceType;

/* Priority level of the channel. Lowest priority is 0. */
typedef uint8   Adc_GroupPriorityType;

/* SKIPPED SWS_Adc_00517 Adc_GroupDefType. Didn't understand. */

/* SKIPPED SWS_Adc_00518 Adc_SteamNumSampleType. Didn't understand. */

/* Type for configuring the streaming access mode buffer type. */
typedef enum
{
    ADC_STREAM_BUFFER_LINEAR = 0x00,
    ADC_STREAM_BUFFER_CIRCULAR = 0x01
}Adc_StreamBufferModeType;

/* Type for configuring access mode to group conversion results. */
typedef enum
{
    ADC_ACCESS_MODE_SINGLE = 0x00,
    ADC_ACCESS_MODE_STREAMING = 0x01
}Adc_GroupAccessModeType;

/* SKIPPED SWS_Adc_00520 Adc_HwSignalTriggerType. Not implementing HW trigger.*/

/* SKIPPED SWS_Adc_00521 Adc_HwTriggerTimeType. Didn't understand it. */

/* SKIPPED SWS_Adc_00522 Adc_PriorityImplementatioType. Not implementing priority
 * yet.
 */

/* SKIPPED SWS_Adc_00523 Adc_GroupReplacementType. Not implementing priority yet.
 */

/* SKIPPED SWS_Adc_00524 Adc_ChannelRangeSelectType. Didn't understad it. */

/* Type of alignment of ADC result in buffet (left/right alignment). */
typedef enum
{
    ADC_ALIGN_LEFT = 0x00,
    ADC_ALIGN_RIGHT = 0x01
}Adc_ResultAlignmentType;

/* SKIPPED SWS_Adc_00526 Adc_PowerStateType. Not implementing power states yet.
 */

/* SKIPPED SWS_Adc_00527 Adc_PowerStateRequestResultType. Not implementing power 
 * states yet.
 */

/************************** [variable declaration] ****************************/

/********************** [external function declarations] **********************/
/**
 * @brief   This service initializes the ADC hardware unit and driver.
 *
 * service ID   0x00
 *
 * param (in)   ConfigPtr is a pointer to a structure of MCU configuration.
 *
 * param (out)  None.
 *
 * retval   None.
 */
void Adc_Init(const Adc_ConfigType* ConfigPtr);

/**
 * @brief   Initializes ADC driver with the group specific result buffer start address where
 *          the conversion result will be stored.
 *
 * service ID   0x0c
 *
 * param (in)   Group is the numeric ID of the ADC channel group.
 *
 * param (in)   DataBufferPtr is a pointer to the starting address for the result buffer.
 *
 * param (out)  None.
 *
 * retval   Std_ReturnType.
 */
Std_ReturnType Adc_SetupResultBuffer(Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr);

/**
 * @brief   Starts the conversion of all channels of the requested channel group.
 *
 * service ID   0x02
 *
 * param (in)   Group is the numeric ID of the ADC channel group.
 *
 * param (out)  None.
 *
 * retval   None.
 */
void Adc_StartGroupConversion(Adc_GroupType Group);

/**
 * @brief   Stops the conversion of all channels of the requested channel group.
 *
 * service ID   0x03
 *
 * param (in)   Group is the numeric ID of the ADC channel group.
 *
 * param (out)  None.
 *
 * retval   None.
 */
void Adc_StopGroupConversion(Adc_GroupType Group);

/**
 * @brief   Reads the group conversion result of the last completed conversion round of the
 *          selected channel group. The group channel values are stored in ascending channel
 *          number order (in contrast to the storage layout of the result buffer if streaming
 *          access is configured.
 *
 * service ID   0x04
 *
 * param (in)   Group is the numeric ID of the ADC channel group.
 *
 * param (out)  DataBufferPtr is a pointer to the ADC results of all channels of selected
 *              group.
 *
 * retval   Std_ReturnType.
 */
Std_ReturnType Adc_ReadGroup(Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr);

/**
 * @brief   Add a brief description of this function/interface.
 *
 * service ID   0x09
 *
 * param (in)   Group is the numeric ID of the ADC channel group.
 *
 * param (out)  None.
 *
 * retval   Conversion status for the requested group.
 */
Adc_StatusType Adc_GetGroupStatus(Adc_GroupType Group);
#endif /* if !define(ADC_H) */
/****************************** [end of file] *********************************/
