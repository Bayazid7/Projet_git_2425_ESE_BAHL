#ifndef MOTEUR_H
#define MOTEUR_H

#include "stm32g4xx.h"
#include "tim.h"

// Définitions
#define MOTEUR_AVANCER 'A'
#define MOTEUR_RECULER 'R'
#define MOTEUR_STOP 'S'

#define Ts 0.01  // Période d'échantillonnage
#define L 0.2    // Distance entre les roues

// Structure pour le moteur
typedef struct Moteur_HandleTypeDef {
    TIM_HandleTypeDef* pwm_timer;    // Timer pour le PWM
    uint32_t channel;                // Canal du timer
    char direction;                  // Direction actuelle
    int speed;                       // Vitesse actuelle
    float theta;                     // Angle
    float vitesse;                   // Vitesse
    float omega;                     // Vitesse angulaire
    struct Moteur_HandleTypeDef* moteur_droite;
    struct Moteur_HandleTypeDef* moteur_gauche;
} Moteur_HandleTypeDef;

// Prototypes des fonctions
void Moteur_init(Moteur_HandleTypeDef* moteur, TIM_HandleTypeDef* timer, uint32_t channel);
void Moteur_setSpeed(Moteur_HandleTypeDef* moteur, int speed);
void Moteur_setDirection(Moteur_HandleTypeDef* moteur, char direction);
void Moteur_start(Moteur_HandleTypeDef* moteur);
void Moteur_stop(Moteur_HandleTypeDef* moteur);
void Robot_setAngle(Moteur_HandleTypeDef* robot, float angle);

#endif /* MOTEUR_H */
