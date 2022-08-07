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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LD1_Pin GPIO_PIN_2
#define LD1_GPIO_Port GPIOE
#define LD2_Pin GPIO_PIN_3
#define LD2_GPIO_Port GPIOE
#define LD3_Pin GPIO_PIN_4
#define LD3_GPIO_Port GPIOE
#define testOutput_Pin GPIO_PIN_5
#define testOutput_GPIO_Port GPIOE
#define DI20_Pin GPIO_PIN_6
#define DI20_GPIO_Port GPIOE
#define DI19_Pin GPIO_PIN_13
#define DI19_GPIO_Port GPIOC
#define DI18_Pin GPIO_PIN_14
#define DI18_GPIO_Port GPIOC
#define DI17_Pin GPIO_PIN_15
#define DI17_GPIO_Port GPIOC
#define Bus1_check_Pin GPIO_PIN_4
#define Bus1_check_GPIO_Port GPIOC
#define Bus2_check_Pin GPIO_PIN_5
#define Bus2_check_GPIO_Port GPIOC
#define IPM_HALT_DO_Pin GPIO_PIN_0
#define IPM_HALT_DO_GPIO_Port GPIOB
#define IPM_HALT_DI_Pin GPIO_PIN_1
#define IPM_HALT_DI_GPIO_Port GPIOB
#define mcu2_out_Pin GPIO_PIN_14
#define mcu2_out_GPIO_Port GPIOE
#define mcu2_in_Pin GPIO_PIN_15
#define mcu2_in_GPIO_Port GPIOE
#define DO16_Pin GPIO_PIN_12
#define DO16_GPIO_Port GPIOB
#define DO15_Pin GPIO_PIN_13
#define DO15_GPIO_Port GPIOB
#define DO14_Pin GPIO_PIN_14
#define DO14_GPIO_Port GPIOB
#define DO13_Pin GPIO_PIN_15
#define DO13_GPIO_Port GPIOB
#define DO12_Pin GPIO_PIN_8
#define DO12_GPIO_Port GPIOD
#define DO11_Pin GPIO_PIN_9
#define DO11_GPIO_Port GPIOD
#define DO10_Pin GPIO_PIN_10
#define DO10_GPIO_Port GPIOD
#define DO9_Pin GPIO_PIN_11
#define DO9_GPIO_Port GPIOD
#define DO8_Pin GPIO_PIN_12
#define DO8_GPIO_Port GPIOD
#define DO7_Pin GPIO_PIN_13
#define DO7_GPIO_Port GPIOD
#define DO6_Pin GPIO_PIN_14
#define DO6_GPIO_Port GPIOD
#define DO5_Pin GPIO_PIN_15
#define DO5_GPIO_Port GPIOD
#define DO4_Pin GPIO_PIN_6
#define DO4_GPIO_Port GPIOC
#define DO3_Pin GPIO_PIN_7
#define DO3_GPIO_Port GPIOC
#define DO2_Pin GPIO_PIN_8
#define DO2_GPIO_Port GPIOC
#define DO1_Pin GPIO_PIN_9
#define DO1_GPIO_Port GPIOC
#define DOR4_Pin GPIO_PIN_8
#define DOR4_GPIO_Port GPIOA
#define DOR3_Pin GPIO_PIN_9
#define DOR3_GPIO_Port GPIOA
#define DOR2_Pin GPIO_PIN_10
#define DOR2_GPIO_Port GPIOA
#define DOR1_Pin GPIO_PIN_11
#define DOR1_GPIO_Port GPIOA
#define UART_DE_Pin GPIO_PIN_12
#define UART_DE_GPIO_Port GPIOA
#define DI1_Pin GPIO_PIN_12
#define DI1_GPIO_Port GPIOC
#define DI2_Pin GPIO_PIN_0
#define DI2_GPIO_Port GPIOD
#define DI3_Pin GPIO_PIN_1
#define DI3_GPIO_Port GPIOD
#define DI4_Pin GPIO_PIN_2
#define DI4_GPIO_Port GPIOD
#define DI5_Pin GPIO_PIN_3
#define DI5_GPIO_Port GPIOD
#define DI7_Pin GPIO_PIN_4
#define DI7_GPIO_Port GPIOD
#define DI6_Pin GPIO_PIN_5
#define DI6_GPIO_Port GPIOD
#define DI8_Pin GPIO_PIN_6
#define DI8_GPIO_Port GPIOD
#define DI9_Pin GPIO_PIN_7
#define DI9_GPIO_Port GPIOD
#define DI10_Pin GPIO_PIN_5
#define DI10_GPIO_Port GPIOB
#define DI11_Pin GPIO_PIN_6
#define DI11_GPIO_Port GPIOB
#define DI12_Pin GPIO_PIN_7
#define DI12_GPIO_Port GPIOB
#define DI13_Pin GPIO_PIN_8
#define DI13_GPIO_Port GPIOB
#define DI14_Pin GPIO_PIN_9
#define DI14_GPIO_Port GPIOB
#define DI15_Pin GPIO_PIN_0
#define DI15_GPIO_Port GPIOE
#define DI16_Pin GPIO_PIN_1
#define DI16_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
