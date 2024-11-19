#ifndef __MOTEUR__
#define  __MOTEUR__

#include "stm32g4xx_hal.h"

// Définition de la structure pour une instance de moteur
typedef struct {
    TIM_HandleTypeDef* pwm_timer;    // Pointeur vers le timer pour le PWM
    uint32_t channel;             // Canal PWM pour l'avant 
    TIM_HandleTypeDef* encoder_timer; // Timer pour l'encodeur
    int32_t position;                 // Position actuelle
    float distance;                   // Distance estimée parcourue
} Moteur_InstanceDef_t;

// Enumération pour les directions du moteur
typedef enum {
    MOTEUR_ARRET = 0,
    MOTEUR_AVANCER,
    MOTEUR_RECULER,
} Moteur_Direction_t;


// Fonctions du driver
void Moteur_Init(Moteur_InstanceDef_t* moteur, TIM_HandleTypeDef* pwm_timer, uint32_t ch_fwd,TIM_HandleTypeDef* encoder_timer);
void Moteur_SetSpeed(Moteur_InstanceDef_t* moteur, int speed);
void Moteur_SetDirection(Moteur_InstanceDef_t* moteur, Moteur_Direction_t direction);
void Moteur_Start(Moteur_InstanceDef_t* moteur);
void Moteur_Stop(Moteur_InstanceDef_t* moteur);
void Moteur_UpdatePosition(Moteur_InstanceDef_t* moteur);

#endif // MOTEUR_H
