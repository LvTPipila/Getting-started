/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * 
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// TIM_HandleTypeDef htim2;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void SystemClock_Config(void);
static void MX_SYSCLK_Init(void);
static void MX_GPIO_Init(void);
static void MX_TIM_Init(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */

    //SystemClock_Config();
    MX_SYSCLK_Init();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    /* USER CODE BEGIN 2 */
    MX_TIM_Init();
    IoHwAb_Init();
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    
    while (1)
    {
        /* USER CODE END WHILE */
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        HAL_Delay(500);
        
        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
#if (0)
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
        |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }

}
#endif

static void MX_SYSCLK_Init(void)
{
    const Mcu_PllConfigType Mcu_PllConfigStruct =
        {
            0U,
            0xEU,
        };

    const Mcu_ConfigType Mcu_InitStruct = 
        {
            &Mcu_PllConfigStruct,
            RCC_OSCILLATORTYPE_HSI,
            RCC_HSICALIBRATION_DEFAULT,
            MCU_SYSCLKSRC_PLL,
            RCC_SYSCLK_DIV1,
            4U,
            RCC_HCLK_DIV1,
            RCC
        };

    Mcu_Init(&Mcu_InitStruct);

    /* Increasing the number of wait states because of higher CPU frequency */
    if(FLASH_LATENCY_2 > __HAL_FLASH_GET_LATENCY())
    {    
        /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
        __HAL_FLASH_SET_LATENCY(FLASH_LATENCY_2);

        /* Check that the new number of wait states is taken into account to access the Flash
        memory by reading the FLASH_ACR register */
        if(__HAL_FLASH_GET_LATENCY() != FLASH_LATENCY_2)
        {
            Error_Handler();
        }
    }

    Mcu_InitClock((Mcu_ClockType)0);

    /* Increasing the number of wait states because of higher CPU frequency */
    if(FLASH_LATENCY_2 < __HAL_FLASH_GET_LATENCY())
    {    
        /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
        __HAL_FLASH_SET_LATENCY(FLASH_LATENCY_2);

        /* Check that the new number of wait states is taken into account to access the Flash
        memory by reading the FLASH_ACR register */
        if(__HAL_FLASH_GET_LATENCY() != FLASH_LATENCY_2)
        {
            Error_Handler();
        }
    }
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : B1_Pin */
    GPIO_InitStruct.Pin = B1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : USART_TX_Pin USART_RX_Pin 
    GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    */

}

/* USER CODE BEGIN 4 */
static void MX_TIM_Init(void)
{
    /* Start codignt the initialization of the TIM1 module for my PWM. */
    TIM_Base_InitTypeDef TIM2_InitStruct = {0};
    TIM_Base_InitTypeDef TIM16_InitStruct = {0};

    /* TIMER CONFIG WILL BE MOVED TO GPT DRIVER LATER ON */
    /* Enable TIM16 clock */
    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_TIM16_CLK_ENABLE();

    TIM2_InitStruct.Prescaler = 0x1u;                   // Prescale 2.
    TIM2_InitStruct.CounterMode = TIM_COUNTERMODE_UP;
    TIM2_InitStruct.Period = (Pwm_PeriodType) 0xF;
    TIM2_InitStruct.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    TIM2_InitStruct.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    TIM_Base_SetConfig(TIM2, &TIM2_InitStruct);

    /* Configure values for the TIM16 init structure. */
    TIM16_InitStruct.Prescaler = 0x1u;                   // Prescale 2.
    TIM16_InitStruct.CounterMode = TIM_COUNTERMODE_UP;
    TIM16_InitStruct.Period = (Pwm_PeriodType) 0xF;
    TIM16_InitStruct.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    TIM16_InitStruct.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    TIM_Base_SetConfig(TIM16, &TIM16_InitStruct);

}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
