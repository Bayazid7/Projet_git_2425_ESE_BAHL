#include "Moteur.h"

// Fonction d'initialisation de l'instance de moteur
void Moteur_Init(Moteur_InstanceDef_t* moteur, TIM_HandleTypeDef* pwm_timer, uint32_t ch_fwd, TIM_HandleTypeDef* encoder_timer) {
    moteur->pwm_timer = pwm_timer;
    moteur->channel = ch_fwd;
    moteur->encoder_timer = encoder_timer;
    moteur->position = 0;
    moteur->distance = 0.0;

    // Démarrer le timer en mode encodeur
    HAL_TIM_Encoder_Start(moteur->encoder_timer, TIM_CHANNEL_ALL);
}

// Fonction pour régler la vitesse du moteur
void Moteur_SetSpeed(Moteur_InstanceDef_t* moteur, int speed) {
    if (speed >= 0) {
        __HAL_TIM_SET_COMPARE(moteur->pwm_timer, moteur->channel, speed);
    }

}

// Fonction pour régler la direction du moteur
void Moteur_SetDirection(Moteur_InstanceDef_t* moteur, Moteur_Direction_t direction) {
    switch (direction) {
        case MOTEUR_AVANCER:
            HAL_TIM_PWM_Start(moteur->pwm_timer, moteur->channel);
            HAL_TIMEx_PWMN_Stop(moteur->pwm_timer, moteur->channel);
            break;

        case MOTEUR_RECULER:
            HAL_TIMEx_PWMN_Start(moteur->pwm_timer, moteur->channel);
            HAL_TIM_PWM_Stop(moteur->pwm_timer, moteur->channel);
            break;

        case MOTEUR_ARRET:
        default:
            HAL_TIM_PWM_Stop(moteur->pwm_timer, moteur->channel);
            HAL_TIMEx_PWMN_Stop(moteur->pwm_timer, moteur->channel);
            break;
    }
}

// Fonction pour démarrer le moteur
void Moteur_Start(Moteur_InstanceDef_t* moteur) {
    Moteur_SetDirection(moteur, MOTEUR_AVANCER); // Direction par défaut
}

// Fonction pour arrêter le moteur
void Moteur_Stop(Moteur_InstanceDef_t* moteur) {
    Moteur_SetDirection(moteur, MOTEUR_ARRET);
}

// Mise à jour de la position de l'encodeur
void Moteur_UpdatePosition(Moteur_InstanceDef_t* moteur) {
    moteur->position = __HAL_TIM_GET_COUNTER(moteur->encoder_timer);
}

