#include "stm32g4xx.h"
#include "tim.h"
static int encoder_now = 5000;       // Position actuelle de l'encodeur (en impulsions)
static int encoder_old = 4900;       // Position précédente de l'encodeur (en impulsions)
static float dt = 0.1f;              // Intervalle de temps entre les deux mesures (en secondes)
static int encoder_resolution = 1000; // Nombre d'impulsions par tour
void EncoderStart(void);
uint16_t GetEncodeur(void);
float GetMotorSpeed(void);
void DirMoteur(void);
float calculateInstantaneousSpeed(int encoder_now, int encoder_old, float dt, int encoder_resolution);
