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
#define LED3_Pin GPIO_PIN_15
#define LED3_GPIO_Port GPIOC
#define PHASE_A1_Pin GPIO_PIN_0
#define PHASE_A1_GPIO_Port GPIOA
#define PHASE_B1_Pin GPIO_PIN_1
#define PHASE_B1_GPIO_Port GPIOA
#define PHASE_B2_Pin GPIO_PIN_4
#define PHASE_B2_GPIO_Port GPIOA
#define CHAT_SOURIS_Pin GPIO_PIN_5
#define CHAT_SOURIS_GPIO_Port GPIOA
#define PHASE_A2_Pin GPIO_PIN_6
#define PHASE_A2_GPIO_Port GPIOA
#define DEV_EN_LIDAR_Pin GPIO_PIN_7
#define DEV_EN_LIDAR_GPIO_Port GPIOA
#define M_EN_LIDAR_Pin GPIO_PIN_4
#define M_EN_LIDAR_GPIO_Port GPIOC
#define LIDAR_TX_Pin GPIO_PIN_10
#define LIDAR_TX_GPIO_Port GPIOB
#define LIDAR_RX_Pin GPIO_PIN_11
#define LIDAR_RX_GPIO_Port GPIOB
#define CB_OUT2_Pin GPIO_PIN_12
#define CB_OUT2_GPIO_Port GPIOB
#define CB_IN_Pin GPIO_PIN_13
#define CB_IN_GPIO_Port GPIOB
#define CB_OUT1_Pin GPIO_PIN_14
#define CB_OUT1_GPIO_Port GPIOB
#define FWD1_Pin GPIO_PIN_8
#define FWD1_GPIO_Port GPIOA
#define FWD2_Pin GPIO_PIN_9
#define FWD2_GPIO_Port GPIOA
#define M_SCTR_LIDAR_Pin GPIO_PIN_10
#define M_SCTR_LIDAR_GPIO_Port GPIOA
#define REV1_Pin GPIO_PIN_11
#define REV1_GPIO_Port GPIOA
#define REV2_Pin GPIO_PIN_12
#define REV2_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define SW_TX_Pin GPIO_PIN_10
#define SW_TX_GPIO_Port GPIOC
#define SW_RX_Pin GPIO_PIN_11
#define SW_RX_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define INT1_ACCELERO_Pin GPIO_PIN_6
#define INT1_ACCELERO_GPIO_Port GPIOB
#define SCL_Pin GPIO_PIN_8
#define SCL_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_9
#define SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
