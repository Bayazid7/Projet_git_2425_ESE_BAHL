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
#include "cmsis_os.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "tab.h"
#include "lidar_X2_driver.h"
#include "MoteurPWM.h"
#include "Moustache.h"
#include "ADXL343.h"
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

extern uint8_t sendTab[TABLE_SIZE];
extern uint8_t flagDMA;
extern uint8_t rxByte;
extern float lidar_point[SIZE_POINT] ;
uint8_t flag = 0;

// FreeRTOS Task Handles
TaskHandle_t initTaskHandle = NULL;
TaskHandle_t lidarTaskHandle = NULL;
TaskHandle_t ledBlinkTaskHandle = NULL;
TaskHandle_t h_task_bord = NULL;
static TaskHandle_t TapDetected_task = NULL;
TaskHandle_t modeTaskHandle = NULL;
TaskHandle_t setangleTaskHandle = NULL;

// Robot and peripheral structures
Moteur_HandleTypeDef moteur_droit;
Moteur_HandleTypeDef moteur_gauche;
h_Robot robot;
float angle;
ADXL343_InstanceDef_t ADXL343;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
int __io_putchar(int chr);
void lidarTask(void *pvParameters);
void ledBlinkTask(void *pvParameters);
void task_angle(void *unused);
void task_Bord(void *unused);
void TapDetected(void *param);
void modeChange(void *param);
void initTask(void *pvParameters);
void robotAngle(void * param);
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
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_TIM1_Init();
	MX_TIM16_Init();
	MX_UART4_Init();
	MX_USART3_UART_Init();
	MX_I2C1_Init();
	MX_TIM2_Init();
	/* USER CODE BEGIN 2 */
	// Peripheral Initialization

	Moteur_init(&moteur_droit, &htim1, TIM_CHANNEL_1);
	Moteur_init(&moteur_gauche, &htim1, TIM_CHANNEL_2);
	Robot_Init(&robot, &moteur_droit, &moteur_gauche);
	Robot_Start(&robot);
	Moustache_Init();
	ADXL343_Init(&ADXL343, &hi2c1);
	HAL_TIM_Base_Start_IT(&htim2) ;
	//Create FreeRTOS tasks
	xTaskCreate(lidarTask, "Lidar Task", 512, NULL, 2, &lidarTaskHandle);
	xTaskCreate(ledBlinkTask, "LED Blink Task", 256, NULL,2, &ledBlinkTaskHandle);
	xTaskCreate(modeChange, "mode", 128, NULL, 5, &modeTaskHandle);
	xTaskCreate(TapDetected, "TapDetected", 128, NULL, 5, &TapDetected_task);
	xTaskCreate(initTask, "Init Task", 256, NULL, 7, &initTaskHandle);
	xTaskCreate(robotAngle, "Init Task", 256, NULL, 2, &setangleTaskHandle) ;

	//
	/* USER CODE END 2 */

	/* Call init function for freertos objects (in cmsis_os2.c) */
	MX_FREERTOS_Init();

	/* Start scheduler */
	osKernelStart();

	/* We should never get here as control is now taken by the scheduler */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	while (1)
	{
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
		HAL_Delay(500);
		//vTaskDelay(pdMS_TO_TICKS(500));
		//lidar_scan_loop();
		/*if(flag == 1){
			for(int i=0 ; i<POINT_BUFF_SIZE ;i++)
			{
				printf("le point %d a angle %f et diastance %f \r\n",i,lidar.point[i].Angle,lidar.point[i].Distance);
				printf("FSA = %d,LSA=%d , LSN=%d , ind=%d \r\n",lidar.processing.LSA,lidar.processing.LSA,lidar.processing.LSN,lidar.processing.idx);
			}
			flag = 0 ;
		}*/

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

//Lidar Task
void initTask (void *pvParameters)
{
	lidar_init();
	vTaskDelete(NULL);
}

void lidarTask(void *pvParameters)
{
	for(;;)
	{
		if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) == pdTRUE)
		{
			lidar_process();
		}
	}
}
// Robot orientation task
void robotAngle(void * param)
{ float angle = 0 ;
for(;;)
{

	if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) == pdTRUE)
	{
		angle = angle +90  ;
		//float distance = lidar_point[0] ;
		//for(int i=1 ; i<SIZE_POINT ; i++)
		//{
		//	if((lidar_point[i]>distance)&&(lidar_point[i]!=0))
		//{
		//	distance = lidar_point[i] ;
		//	angle = i ;
		//}
		//}
		printf("l'angle = %f \n",angle);
		Robot_setAngle(&robot, angle);
	}
}
}
//LED Blink Task
void ledBlinkTask(void *pvParameters) {
	for (;;) {
		if(robot.mode==0)
		{
			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
			//HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		}
		else if(robot.mode==1)
		{
			HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
		}
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

//mode change Task
void modeChange(void *param) {
	uint32_t ulNotificationValue;

	for(;;) {
		ulNotificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		if (ulNotificationValue != 0){
			if(robot.mode == 0)
			{
				robot.mode = 1;
			}
			else
			{
				robot.mode = 0;
			}
		}
	}
}
//Tap Detection Task
void TapDetected(void *param) {
	uint32_t ulNotificationValue;

	for(;;) {
		ulNotificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		if (ulNotificationValue != 0) {
			uint8_t buf;
			HAL_I2C_Mem_Read(&hi2c1, ADXL343_ADDRESS, ADXL343_REG_INT_SOURCE,
					I2C_MEMADD_SIZE_8BIT, &buf, 1, HAL_MAX_DELAY);
			Robot_Stop(&robot);
			if(robot.mode == 0)
			{
				robot.mode = 1;
			}
			else
			{
				robot.mode = 0;
			}
		}
	}
}

//Fonctions CALLBACK

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==CHAT_SOURIS_Pin)
	{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		vTaskNotifyGiveFromISR(modeTaskHandle, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	else if(GPIO_Pin==INT2_Pin)
	{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		vTaskNotifyGiveFromISR(TapDetected_task, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}

	Moustache_HandleInterrupt(GPIO_Pin);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART3)
	{
		if(readTrame(&rxByte))
		{
			BaseType_t xHigherPriorityTaskWoken = pdFALSE;
			vTaskNotifyGiveFromISR(lidarTaskHandle, &xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
		HAL_UART_Receive_IT(&huart3, &rxByte, 1);
	}
}


int __io_putchar(int chr)
{
	HAL_UART_Transmit(&huart4, (uint8_t *)&chr, 1, HAL_MAX_DELAY);
	return chr;
}
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
	if (htim->Instance == TIM2) {
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		vTaskNotifyGiveFromISR(setangleTaskHandle, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
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
