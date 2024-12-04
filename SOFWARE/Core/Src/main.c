/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ADXL343.h"
#include "Robot.h"
#include "Moteur.h"
#include "LIDAR.h"
#include "Encodeur.h"
#include "MoteurPWM.h"
#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define ADXL343_DEVID_REG    0x00
#define ADXL343_POWER_CTL    0x2D
#define ADXL343_DATAX0       0x32

#define M_PI 3.14159265358979323846

#define ENCODER_CPR 11 // Résolution de l'encodeur (impulsions par tour)
#define TIMER_MAX 65535  // Valeur maximale du compteur (16 bits)

// Variables globales
//int32_t last_counter = 0;  // Dernière valeur du compteur
int32_t delta_counter = 0; // Différence entre les lectures
//float motor_speed = 0;     // Vitesse en rad/s
float SAMPLING_TIME = 0.1; // Intervalle de lecture en secondes (100 ms)
//float sampling_time = 0.1; // Intervalle de lecture en secondes (100 ms)


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
Moteur_InstanceDef_t moteur1;
Moteur_InstanceDef_t moteur2;
Robot_InstanceDef_t robot;
ADXL343_InstanceDef_t ADXL343;
h_LIDAR_t lidar;


uint8_t data[6];
int16_t x, y, z;
float x_g, y_g, z_g;

int32_t last_counter = 0;  // Dernière valeur du compteur
float motor_speed = 0;     // Vitesse calculée (en rad/s)
const float pulses_per_revolution = 1632.67;  // Impulsions par tour après réduction
float delta_t = 0.1;       // Intervalle de temps pour le calcul (en secondes)


#define ENCODER_CPR 1632    // Nombre d'impulsions par tour de l'encodeur (encoder resolution)
#define SAMPLING_TIME 0.1   // Temps d'échantillonnage en secondes (100 ms)

// Déclarations globales
int32_t last_encoder_value = 0;   // Dernière valeur du compteur de l'encodeur
int32_t current_encoder_value = 0;  // Valeur actuelle du compteur de l'encodeur




/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int __io_putchar(int chr)
{
  HAL_UART_Transmit(&huart4, (uint8_t *)&chr, 1, HAL_MAX_DELAY);
  return chr;
}


void ADXL343_Initit(void)
{
    uint8_t configData;

    // Vérifier l'identifiant de l'ADXL343
    HAL_I2C_Mem_Read(&hi2c1, ADXL343_ADDRESS, ADXL343_DEVID_REG, 1, &configData, 1, HAL_MAX_DELAY);
    if (configData != 0xE5)
    {
        printf("Erreur : L'ADXL343 n'est pas détecté !\n");
        while (1);
    }
    printf("ADXL343 détecté avec succès.\n");

    // Configurer le capteur en mode mesure
    configData = 0x08; // Mettre le bit mesure à 1
    HAL_I2C_Mem_Write(&hi2c1, ADXL343_ADDRESS, ADXL343_POWER_CTL, 1, &configData, 1, HAL_MAX_DELAY);
}

void ADXL343_ReadAxes(void)
{
    // Lire les 6 octets (X0-X1, Y0-Y1, Z0-Z1)
    HAL_I2C_Mem_Read(&hi2c1, ADXL343_ADDRESS, ADXL343_DATAX0, 1, data, 6, HAL_MAX_DELAY);

    // Combiner les octets pour obtenir des valeurs 16 bits signées
    x = (int16_t)((data[1] << 8) | data[0]);
    y = (int16_t)((data[3] << 8) | data[2]);
    z = (int16_t)((data[5] << 8) | data[4]);

    // Convertir en unités "g" (1g = 9.8 m/s²)
    x_g = x * 0.004;  // Sensibilité typique = 4mg/LSB
    y_g = y * 0.004;
    z_g = z * 0.004;
}




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
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM16_Init();
  MX_UART4_Init();
  MX_USART3_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  //uint8_t res = ADXL343_Init(&ADXL343, &hi2c1);
  //Moteur_Init(&moteur1, &htim1, TIM_CHANNEL_1, &htim3);
 // Moteur_Init(&moteur2, &htim1, TIM_CHANNEL_2, &htim4);
  //Robot_Init(&robot, &moteur1, &moteur2);
 // LIDAR_start(&lidar);
    //HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);  // Démarrer le Timer en mode encodeur
    //HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
   //HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
 // HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);  // Signal complémentaire (CH1N)
  //nbCounter = __HAL_TIM_GET_COUNTER(&htim1);
    //HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
  void avance();
  ADXL343_Initit();
 // uint32_t last_time = HAL_GetTick();  // Temps de référence (ms)
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    printf("hello \r\n");
      HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
      HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
      HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
      //HAL_Delay(500);

    ADXL343_ReadAxes();
    printf("X: %.2fg, Y: %.2fg, Z: %.2fg\n", x_g, y_g, z_g);
    HAL_Delay(500);

    printf("Moteur Avance\r\n");
    //void avance();
    StartEncodeur1();
    StartEncodeur2();
    HAL_Delay(100);
    printf("Moteur Recule\r\n");
    void recule();
    StartEncodeur1();
    StartEncodeur2();




    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */


/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
