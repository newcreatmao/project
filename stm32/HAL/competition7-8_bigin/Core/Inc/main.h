/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#define gray1_Pin GPIO_PIN_2
#define gray1_GPIO_Port GPIOE
#define gray5_Pin GPIO_PIN_3
#define gray5_GPIO_Port GPIOE
#define gray2_Pin GPIO_PIN_4
#define gray2_GPIO_Port GPIOE
#define gray6_Pin GPIO_PIN_5
#define gray6_GPIO_Port GPIOE
#define gray3_Pin GPIO_PIN_6
#define gray3_GPIO_Port GPIOE
#define gary7_Pin GPIO_PIN_13
#define gary7_GPIO_Port GPIOC
#define gray4_Pin GPIO_PIN_0
#define gray4_GPIO_Port GPIOC
#define encoder3_Pin GPIO_PIN_0
#define encoder3_GPIO_Port GPIOA
#define encoder4_Pin GPIO_PIN_1
#define encoder4_GPIO_Port GPIOA
#define key3_Pin GPIO_PIN_5
#define key3_GPIO_Port GPIOA
#define key2_Pin GPIO_PIN_7
#define key2_GPIO_Port GPIOA
#define key1_Pin GPIO_PIN_5
#define key1_GPIO_Port GPIOC
#define medcine_Pin GPIO_PIN_1
#define medcine_GPIO_Port GPIOB
#define wheel3_Pin GPIO_PIN_11
#define wheel3_GPIO_Port GPIOE
#define BIN1_Pin GPIO_PIN_13
#define BIN1_GPIO_Port GPIOE
#define BIN2_Pin GPIO_PIN_14
#define BIN2_GPIO_Port GPIOE
#define OLED_SCL_Pin GPIO_PIN_10
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_11
#define OLED_SDA_GPIO_Port GPIOB
#define buzzer_Pin GPIO_PIN_9
#define buzzer_GPIO_Port GPIOD
#define led_R_Pin GPIO_PIN_11
#define led_R_GPIO_Port GPIOD
#define led_G_Pin GPIO_PIN_13
#define led_G_GPIO_Port GPIOD
#define led_Y_Pin GPIO_PIN_15
#define led_Y_GPIO_Port GPIOD
#define AIN1_Pin GPIO_PIN_7
#define AIN1_GPIO_Port GPIOC
#define AIN2_Pin GPIO_PIN_8
#define AIN2_GPIO_Port GPIOC
#define TX_bluetooth_Pin GPIO_PIN_9
#define TX_bluetooth_GPIO_Port GPIOA
#define RX_bluetooth_Pin GPIO_PIN_10
#define RX_bluetooth_GPIO_Port GPIOA
#define encoder2_Pin GPIO_PIN_15
#define encoder2_GPIO_Port GPIOA
#define TX_MAIX_Pin GPIO_PIN_5
#define TX_MAIX_GPIO_Port GPIOD
#define RX_MAIX_Pin GPIO_PIN_6
#define RX_MAIX_GPIO_Port GPIOD
#define encoder1_Pin GPIO_PIN_3
#define encoder1_GPIO_Port GPIOB
#define MPU_SCL_Pin GPIO_PIN_6
#define MPU_SCL_GPIO_Port GPIOB
#define MPU_SDA_Pin GPIO_PIN_7
#define MPU_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
