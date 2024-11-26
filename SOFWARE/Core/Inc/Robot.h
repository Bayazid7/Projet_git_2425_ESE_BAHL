/**
 * @file Robot.h
 * @author Aliou LY(aliou.ly@ensea.fr)
 * @brief 
 * @version 0.1
 * @date 2024-11-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __ROBOT__
#define __ROBOT__

#include "stm32g4xx_hal.h"
#include "Moteur.h"

// Définition de la structure pour le robot
typedef struct
{
    Moteur_InstanceDef_t *moteur_gauche; // Instance du moteur gauche
    Moteur_InstanceDef_t *moteur_droite; // Instance du moteur droit
} Robot_InstanceDef_t;

typedef enum
{
    Robot_AVANCER = 0,
    Robot_RECULER,
    Robo_TOURNER_GAUCHE,
    Robot_TOURNER_DROITE,
    Robot_ARRET

} Robot_Direction_t;

// Fonctions du robot
void Robot_Init(Robot_InstanceDef_t *robot, Moteur_InstanceDef_t *moteur_gauche, Moteur_InstanceDef_t *moteur_droite);
void Robot_SetDirection(Robot_InstanceDef_t *robot, Robot_Direction_t direction);
void Robot_Start(Robot_InstanceDef_t *robot);
void Robot_Stop(Robot_InstanceDef_t *robot);
void Robot_UpdatePosition(Robot_InstanceDef_t *robot);

#endif // ROBOT_H
