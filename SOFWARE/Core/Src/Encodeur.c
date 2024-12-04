#include <Encodeur.h>
#include <stdio.h>
#include "tim.h"
#include "usart.h"

volatile int32_t current_position1 = 0;
volatile float speed1 = 0.0f;
uint32_t time_interval1 = 1000; // Intervalle en ms
volatile int32_t last_position1 = 0;
float motor_speed_rpm1 = 0.0;    // Vitesse du moteur en RPM

volatile int32_t current_position2 = 0;
volatile float speed2 = 0.0f;
uint32_t time_interval2 = 1000; // Intervalle en ms
volatile int32_t last_position2 = 0;
float motor_speed_rpm2 = 0.0;    // Vitesse du moteur en RPM

void Transmit_Speed1(void)
{
    char buffer[50];  // Buffer pour stocker la chaîne à envoyer
    // Formater la chaîne avec la vitesse en RPM
    sprintf(buffer, "Vitesse: %.2f RPM\r\n", motor_speed_rpm1);

    // Transmettre la chaîne via UART (ici on utilise huart2, à ajuster selon votre configuration)
    HAL_UART_Transmit(&huart4, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
}

void calculate_speed1() {
    current_position1 = __HAL_TIM_GET_COUNTER(&htim3);
    speed1 = (current_position1 - last_position1) * (1000.0 / time_interval1); // Vitesse en impulsions par seconde
    last_position1 = current_position1;
    printf("la valeur de vitesse egale %.2f \r\n ",speed1);
    Transmit_Speed1();
}

void StartEncodeur1(){

	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);  // Démarrer le Timer en mode encodeur
	calculate_speed1();

}


void Transmit_Speed2(void)
{
    char buffer[50];  // Buffer pour stocker la chaîne à envoyer
    // Formater la chaîne avec la vitesse en RPM
    sprintf(buffer, "Vitesse: %.2f RPM\r\n", motor_speed_rpm2);

    // Transmettre la chaîne via UART (ici on utilise huart2, à ajuster selon votre configuration)
    HAL_UART_Transmit(&huart4, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
}

void calculate_speed2() {
    current_position2 = __HAL_TIM_GET_COUNTER(&htim4);;
    speed2 = (current_position2 - last_position2) * (1000.0 / time_interval2); // Vitesse en impulsions par seconde
    last_position2 = current_position2;
    printf("la valeur de vitesse egale %.2f \r\n ",speed2);
    Transmit_Speed2();
}

void StartEncodeur2(){

	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);  // Démarrer le Timer en mode encodeur
	calculate_speed2();

}
