#include "MoteurPWM.h"
#include <stdlib.h>

void Moteur_init(Moteur_HandleTypeDef* moteur, TIM_HandleTypeDef* timer, uint32_t channel)
{
    moteur->pwm_timer = timer;
    moteur->channel = channel;
    moteur->direction = MOTEUR_STOP;
    moteur->speed = 0;
    moteur->theta = 0;
    moteur->vitesse = 0;
    moteur->omega = 0;
    moteur->moteur_droite = NULL;
    moteur->moteur_gauche = NULL;
}

void Moteur_setSpeed(Moteur_HandleTypeDef* moteur, int speed)
{
    int vitesse = (int)(speed * 4250 / 290);
    moteur->speed = speed;

    if (speed >= 0)
    {
        Moteur_setDirection(moteur, MOTEUR_AVANCER);
        __HAL_TIM_SET_COMPARE(moteur->pwm_timer, moteur->channel, vitesse);
    }
    else
    {
        Moteur_setDirection(moteur, MOTEUR_RECULER);
        __HAL_TIM_SET_COMPARE(moteur->pwm_timer, moteur->channel, 8500-abs(vitesse));
    }
}

void Moteur_setDirection(Moteur_HandleTypeDef* moteur, char direction)
{
    moteur->direction = direction;

    switch (direction)
    {
        case MOTEUR_AVANCER:
            HAL_TIM_PWM_Start(moteur->pwm_timer, moteur->channel);
            HAL_TIMEx_PWMN_Stop(moteur->pwm_timer, moteur->channel);
            break;

        case MOTEUR_RECULER:
            HAL_TIMEx_PWMN_Start(moteur->pwm_timer, moteur->channel);
            HAL_TIM_PWM_Stop(moteur->pwm_timer, moteur->channel);
            break;

        case MOTEUR_STOP:
        default:
            HAL_TIM_PWM_Stop(moteur->pwm_timer, moteur->channel);
            HAL_TIMEx_PWMN_Stop(moteur->pwm_timer, moteur->channel);
            break;
    }
}

void Moteur_start(Moteur_HandleTypeDef* moteur)
{
    Moteur_setDirection(moteur, MOTEUR_AVANCER);
}

void Moteur_stop(Moteur_HandleTypeDef* moteur)
{
    Moteur_setDirection(moteur, MOTEUR_STOP);
}

void Robot_setAngle(Moteur_HandleTypeDef* robot, float angle)
{
    //  Rotation pour atteindre l'angle spécifié
    robot->omega = (2.0 / Ts) * (angle - robot->theta) + robot->omega;
    robot->moteur_droite->vitesse = robot->omega * L / 2.0;
    robot->moteur_gauche->vitesse = -robot->omega * L / 2.0;

    // Limiter les vitesses des moteurs pendant la rotation
    if (robot->moteur_droite->vitesse > 290) robot->moteur_droite->vitesse = 290;
    if (robot->moteur_droite->vitesse < -290) robot->moteur_droite->vitesse = -290;
    if (robot->moteur_gauche->vitesse > 290) robot->moteur_gauche->vitesse = 290;
    if (robot->moteur_gauche->vitesse < -290) robot->moteur_gauche->vitesse = -290;

    // Appliquer les vitesses des moteurs pour la rotation
    Moteur_setSpeed(robot->moteur_droite, (int)robot->moteur_droite->vitesse);
    Moteur_setSpeed(robot->moteur_gauche, (int)robot->moteur_gauche->vitesse);

    // Attendre que l'angle soit atteint
    HAL_Delay(500);

    // Mettre à jour l'angle courant
    robot->theta = angle;

    //  Avancer en ligne droite
    robot->omega = 0;

    // Appliquer les vitesses des moteurs pour avancer
    Moteur_setSpeed(robot->moteur_droite, 120);
    Moteur_setSpeed(robot->moteur_gauche, 80);
}
