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
#include "stm32g4xx_hal.h"

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
#define LED1_Pin GPIO_PIN_13
#define LED1_GPIO_Port GPIOC
#define DEV_EN_Pin GPIO_PIN_0
#define DEV_EN_GPIO_Port GPIOA
#define M_EN_Pin GPIO_PIN_1
#define M_EN_GPIO_Port GPIOA
#define TX_LIDAR_Pin GPIO_PIN_2
#define TX_LIDAR_GPIO_Port GPIOA
#define RX_LIDAR_Pin GPIO_PIN_3
#define RX_LIDAR_GPIO_Port GPIOA
#define CB_IN_Pin GPIO_PIN_5
#define CB_IN_GPIO_Port GPIOA
#define CB_OUT1_Pin GPIO_PIN_6
#define CB_OUT1_GPIO_Port GPIOA
#define CB_OUT2_Pin GPIO_PIN_7
#define CB_OUT2_GPIO_Port GPIOA
#define CB_OUT3_Pin GPIO_PIN_4
#define CB_OUT3_GPIO_Port GPIOC
#define CB_OUT4_Pin GPIO_PIN_0
#define CB_OUT4_GPIO_Port GPIOB
#define CHAT_SOURIS_Pin GPIO_PIN_1
#define CHAT_SOURIS_GPIO_Port GPIOB
#define REV2_Pin GPIO_PIN_13
#define REV2_GPIO_Port GPIOB
#define REV1_Pin GPIO_PIN_14
#define REV1_GPIO_Port GPIOB
#define ENCODER_A1_Pin GPIO_PIN_6
#define ENCODER_A1_GPIO_Port GPIOC
#define FWD2_Pin GPIO_PIN_8
#define FWD2_GPIO_Port GPIOA
#define FWD1_Pin GPIO_PIN_9
#define FWD1_GPIO_Port GPIOA
#define M_SCTR_LIDAR_Pin GPIO_PIN_10
#define M_SCTR_LIDAR_GPIO_Port GPIOA
#define ENCODER_A2_Pin GPIO_PIN_11
#define ENCODER_A2_GPIO_Port GPIOA
#define ENCODER_B2_Pin GPIO_PIN_12
#define ENCODER_B2_GPIO_Port GPIOA
#define SWD_TX_Pin GPIO_PIN_10
#define SWD_TX_GPIO_Port GPIOC
#define SWD_RX_Pin GPIO_PIN_11
#define SWD_RX_GPIO_Port GPIOC
#define ENCODER_B1_Pin GPIO_PIN_5
#define ENCODER_B1_GPIO_Port GPIOB
#define INT_ACCELERO_Pin GPIO_PIN_6
#define INT_ACCELERO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
