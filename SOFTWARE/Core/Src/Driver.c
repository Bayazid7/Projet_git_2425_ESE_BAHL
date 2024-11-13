#include "Driver.h"

void StartMoteursens1(void)
{

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//l'activation de channel 1 Timer 1
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);//l'activation de channel 2 Timer 1
	printf("sens1\r\n");

}

void StartMoteursens2(void)
{

	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);//l'activation de channel 1 Timer 1
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);//l'activation de channel 2 Timer 1
	printf("sens2\r\n");

}

void StopMoteur(void)
{

	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);//l'activation de channel 1 Timer 1
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);//l'activation de channel 2 Timer 1
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);//l'activation de channel 1 Timer 1
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);//l'activation de channel 2 Timer 1
	printf("okStop\r\n");
}



