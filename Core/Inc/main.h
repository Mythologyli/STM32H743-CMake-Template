/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

#include "stm32h7xx_ll_rcc.h"
#include "stm32h7xx_ll_spi.h"
#include "stm32h7xx_ll_tim.h"
#include "stm32h7xx_ll_usart.h"
#include "stm32h7xx_ll_bus.h"
#include "stm32h7xx_ll_cortex.h"
#include "stm32h7xx_ll_system.h"
#include "stm32h7xx_ll_utils.h"
#include "stm32h7xx_ll_pwr.h"
#include "stm32h7xx_ll_gpio.h"
#include "stm32h7xx_ll_dma.h"

#include "stm32h7xx_ll_exti.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>

#include "cmsis_os2.h"
#include "FreeRTOS.h"

#include "lvgl.h"

#include "console_conf.h"
#include "ili9341.h"

#include "run_time.h"
#include "main_task.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern void Usart2Callback(void);
extern void UsbCallback(uint8_t *data_buffer, uint32_t length);

extern void lv_port_disp_init(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Led2_Pin GPIO_PIN_1
#define Led2_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */
#define Led2_Pin GPIO_PIN_1
#define Led2_GPIO_Port GPIOA

#define Led2_On HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, GPIO_PIN_RESET)
#define Led2_Off HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, GPIO_PIN_SET)
#define Led2_Toggle HAL_GPIO_TogglePin(Led2_GPIO_Port, Led2_Pin)

#define ENABLE_FREERTOS_CLI 0
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
