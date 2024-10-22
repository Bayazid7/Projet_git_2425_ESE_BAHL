#include "Encoder.h"


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
