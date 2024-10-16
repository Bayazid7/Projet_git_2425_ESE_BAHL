/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

void transmission(uint8_t Data_T)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)Data, 1 , HAL_MAX_DELAY);
}

void Reception(uint8_t Data_R)
{
	HAL_UART_Receive_DMA(&huart2, (uint8_t*)Data_R, 1);
}

void
