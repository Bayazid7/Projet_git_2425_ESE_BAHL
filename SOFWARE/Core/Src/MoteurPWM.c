#include <MoteurPWM.h>
#include <stdio.h>
#include "tim.h"
#include "usart.h"
#include "stdio.h"

void Moteur_Direction(const char* Direction) {
    if (strcmp(Direction, "avance") == 0) {
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    } else if (strcmp(Direction, "recule") == 0) {
        HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
    } else if (strcmp(Direction, "Droit") == 0) {
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
    } else if (strcmp(Direction, "Gauche") == 0) {
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    } else if (strcmp(Direction, "stop") == 0) {
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
    }
}

void stop() {
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
}

void avance() {
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}

void recule() {
    Moteur_Direction("recule");
}

void Droit() {
    Moteur_Direction("Droit");
}

void Gauche() {
    Moteur_Direction("Gauche");
}
