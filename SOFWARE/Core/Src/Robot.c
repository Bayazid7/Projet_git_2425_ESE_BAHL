#include "Robot.h"

// Fonction d'initialisation du robot
void Robot_Init(Robot_InstanceDef_t* robot, Moteur_InstanceDef_t* moteur_gauche, Moteur_InstanceDef_t* moteur_droite) {
    robot->moteur_gauche = moteur_gauche;
    robot->moteur_droite = moteur_droite;
}

// Fonction pour régler la direction du robot
void Robot_SetDirection(Robot_InstanceDef_t* robot, Robot_Direction_t direction) {
    switch (direction) {
        case Robot_AVANCER:
            Moteur_SetDirection(robot->moteur_gauche, MOTEUR_AVANCER);
            Moteur_SetDirection(robot->moteur_droite, MOTEUR_AVANCER);
            break;
        case Robot_RECULER:
            Moteur_SetDirection(robot->moteur_gauche, MOTEUR_RECULER);
            Moteur_SetDirection(robot->moteur_droite, MOTEUR_RECULER);
            break;
        case Robo_TOURNER_GAUCHE:
            Moteur_SetDirection(robot->moteur_gauche, MOTEUR_RECULER);
            Moteur_SetDirection(robot->moteur_droite, MOTEUR_AVANCER);
            break;
        case Robot_TOURNER_DROITE:
            Moteur_SetDirection(robot->moteur_gauche, MOTEUR_AVANCER);
            Moteur_SetDirection(robot->moteur_droite, MOTEUR_RECULER);
            break;
        case Robot_ARRET:
        default:
            Robot_Stop(robot);
            break;
    }
}

// Fonction pour démarrer le robot
void Robot_Start(Robot_InstanceDef_t* robot) {
    Robot_SetDirection(robot, MOTEUR_AVANCER); // Démarrer par défaut en avançant
}

// Fonction pour arrêter le robot
void Robot_Stop(Robot_InstanceDef_t* robot) {
    Moteur_Stop(robot->moteur_gauche);
    Moteur_Stop(robot->moteur_droite);
}

void Robot_UpdatePosition(Robot_InstanceDef_t* robot) {
    Moteur_UpdatePosition(robot->moteur_gauche);
    Moteur_UpdatePosition(robot->moteur_droite);
}
