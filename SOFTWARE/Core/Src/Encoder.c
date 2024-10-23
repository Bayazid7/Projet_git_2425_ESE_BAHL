#include "Encoder.h"
#include <stdio.h>

void EncoderStart(void)
{
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL); //l'activation de l'encodeur
}

uint16_t GetEncodeur(void)
{
	uint16_t valueEnc = __HAL_TIM_GET_COUNTER(&htim3); //valeur de l'encodeur

	    return valueEnc;
}

float GetMotorSpeed(void)
{
  uint16_t valueSpeed = GetEncodeur()*65535;

  return valueSpeed;

}

void DirMoteur(void)
{
if (__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3))
{
    printf("Le moteur recule\r\n");	// le bit DIR=0 le moteur tourne dans le sens antihoraire
}
else
{
	printf("Le moteur avance\r\n");//le bit DIR=1 le moteur tourne dans le sens horaire
}
}

