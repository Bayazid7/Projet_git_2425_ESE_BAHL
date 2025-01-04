#include "MoteurPWM.h"
#include <stdlib.h>

#define PI 3.14159

void Moteur_init(Moteur_HandleTypeDef* moteur, TIM_HandleTypeDef* timer, uint32_t channel)
{
    moteur->pwm_timer = timer;
    moteur->channel = channel;
    moteur->direction = MOTEUR_STOP;
    moteur->vitesse = 0;
}

void Moteur_setSpeed(Moteur_HandleTypeDef* moteur, int speed)
{
    int vitesse = (int)(speed * 4250 / 290);
    moteur->vitesse = speed;

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
void Moteur_recule(Moteur_HandleTypeDef* moteur)
{
    Moteur_setDirection(moteur,MOTEUR_RECULER);
}
void Robot_Start(h_Robot* robot)
{
	Moteur_start(robot->moteur_droite) ;
	Moteur_start(robot->moteur_droite) ;
	robot->direction = 'A' ;
}
void Robot_Stop(h_Robot* robot)
{
	Moteur_stop(robot->moteur_droite) ;
	Moteur_stop(robot->moteur_droite) ;
	robot->direction = 'S' ;
}
void Robot_Recule(h_Robot* robot)
{
	Moteur_recule(robot->moteur_droite) ;
	Moteur_recule(robot->moteur_droite) ;
	robot->direction = 'R' ;
}

void Robot_Init(h_Robot* robot ,Moteur_HandleTypeDef* moteurD,Moteur_HandleTypeDef* moteurG )
{
	robot->moteur_droite = moteurD ;
	robot->moteur_gauche = moteurG ;
	robot->omega = 0 ;
	robot->theta =0 ;
	robot->vitesse = 0 ;
	robot->mode = 0 ; // 0 : mode chat et 1 : mode souris
	robot->direction = 'S' ;

}

void Robot_setAngle(h_Robot* robot, float angle)
{
    //  Rotation pour atteindre l'angle spécifié
	angle = angle*(2*PI/360) ;
    robot->omega = (2.0 / Ts) * (angle - robot->theta) + robot->omega;
    robot->moteur_droite->vitesse =robot->vitesse + robot->omega * L / 2.0;
    robot->moteur_gauche->vitesse = robot->vitesse - robot->omega * L / 2.0;

    // Limiter les vitesses des moteurs pendant la rotation
    if (robot->moteur_droite->vitesse > 290) robot->moteur_droite->vitesse = 290;
    if (robot->moteur_droite->vitesse < -290) robot->moteur_droite->vitesse = -290;
    if (robot->moteur_gauche->vitesse > 290) robot->moteur_gauche->vitesse = 290;
    if (robot->moteur_gauche->vitesse < -290) robot->moteur_gauche->vitesse = -290;

    // Appliquer les vitesses des moteurs pour la rotation
    Moteur_setSpeed(robot->moteur_droite, (int)robot->moteur_droite->vitesse);
    Moteur_setSpeed(robot->moteur_gauche, (int)robot->moteur_gauche->vitesse);

    // Attendre que l'angle soit atteint
    HAL_Delay(1);

    // Mettre à jour l'angle courant
    robot->theta = angle;

    //  Avancer en ligne droite
    // Appliquer les vitesses des moteurs pour avancer
    Moteur_setSpeed(robot->moteur_droite, 120);
    Moteur_setSpeed(robot->moteur_gauche, 80);
    robot->omega = 0;
    robot->vitesse = (robot->moteur_gauche->vitesse + robot->moteur_droite->vitesse )*0.5 ;
}

/*void Robot_setAngle(h_Robot* robot, float target_angle) {
    // Conversion de l'angle cible en radians
    target_angle = target_angle * (2 * PI / 360);

    // Constantes de contrôle pour ajustement progressif
    float Kp = 0.5;
    float Ki = 0.0;
    float Kd = 0.0;

    static float error_sum = 0;
    static float previous_error = 0;
    float error = target_angle - robot->theta;
    error_sum += error * Ts;
    float d_error = (error - previous_error) / Ts;

    // Calcul de la commande de rotation (omega) avec un PID simplifié
    robot->omega = Kp * error + Ki * error_sum + Kd * d_error;

    // Calcul des vitesses des moteurs pour atteindre l'angle cible
    robot->moteur_droite->vitesse = robot->vitesse + robot->omega * L / 2.0;
    robot->moteur_gauche->vitesse = robot->vitesse - robot->omega * L / 2.0;

    // Limiter les vitesses des moteurs
    if (robot->moteur_droite->vitesse > 290) robot->moteur_droite->vitesse = 290;
    if (robot->moteur_droite->vitesse < -290) robot->moteur_droite->vitesse = -290;
    if (robot->moteur_gauche->vitesse > 290) robot->moteur_gauche->vitesse = 290;
    if (robot->moteur_gauche->vitesse < -290) robot->moteur_gauche->vitesse = -290;

    // Appliquer les vitesses aux moteurs
    Moteur_setSpeed(robot->moteur_droite, (int)robot->moteur_droite->vitesse);
    Moteur_setSpeed(robot->moteur_gauche, (int)robot->moteur_gauche->vitesse);

    // Petite pause pour donner le temps au système de s'ajuster
    HAL_Delay(1);

    // Mettre à jour l'angle courant en fonction de l'omega
    robot->theta += robot->omega * Ts;

    // Stocker l'erreur précédente pour le calcul dérivé
    previous_error = error;
}*/


