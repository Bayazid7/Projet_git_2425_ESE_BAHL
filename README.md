# Projet_git_2425_ESE
Projet_2024/2025
## Membres du groupes
Bayazid BELKHIR
<br>
Hedia WERHENI
<br>
Hugo DEVAUX
<br>
Aliou LY

<span style="color: red; font-weight: bold;">⚠️ ATTENTION : Modifiez à la bonne place les amis !</span>
## Introduction

Ce projet a pour objectif de développer un **robot autonome** utilisant un **microcontrôleur STM32** pour la gestion de son comportement, tout en appliquant des principes de noyaux **temps réel** pour contrôler la communication entre ses composants matériels et logiciels. Ce robot sera capable de fonctionner en deux modes :
- **Mode Chat** :
- **Mode Souris** :

Le robot est alimenté par une batterie de 7.2V et comprend des composants essentiels pour son fonctionnement tels que des moteurs, un accéléromètre, et un LIDAR.

---

## Objectifs du projet

Les principaux objectifs de ce projet sont les suivants :
1. **Conception du système à microcontrôleur STM32** : Intégrer un microcontrôleur  pour gérer le comportement du robot.
2. **Implémentation d'un noyau temps réel** : Utiliser un noyau temps réel pour garantir une gestion efficace des tâches .
3. **Contrôle des moteurs avec PWM** : Piloter deux moteurs à l'aide de drivers PWM pour contrôler la vitesse et la direction.
4. **Détection des chocs avec l'accéléromètre ADXL343** : Détecter les collisions avec d'autres robots pour ajuster les actions du robot.
5. **Détection des autres robots avec LIDAR YDLIDAR X4** : Utiliser un LIDAR pour permettre au robot de connaître la position des autres robots.
![image](https://github.com/user-attachments/assets/2dcd4a35-5686-407a-b2e8-3e63c8a9c359)

---

## Matériel utilisé

### 1. **Microcontrôleur STM32**

Le projet repose sur un **STM32** qui gère l'ensemble du système.La programmation du STM32 se fait par un SW

- **Modèle utilisé** : STM32G431CBU6
- **Fonction principale** : Gestion des moteurs, communication avec l'accéléromètre et le LIDAR, traitement des données en temps réel.
- **Peripherals** : PWM pour le contrôle des moteurs, interfaces I2C pour l'accéléromètre et UARTpour  le LIDAR et la communication avec le PC.
  ![image_stm32](https://github.com/user-attachments/assets/6d9773a8-f08b-49c5-a691-985c06e0decb)

### 2. **Alimentation et régulation de tension**

Le robot est alimenté par une batterie **NIMH 7.2V 1.3Ah**. Cette tension est ensuite convertie en différentes tensions nécessaires au bon fonctionnement des différents composants :
- **Convertisseur 3.3V BU33SD5WG-TR** pour alimenter le STM32, l'accéléromètre, et les capteurs de position des moteurs.
- **Convertisseur 5V  MP1475S** pour alimenter le LIDAR.
![image](https://github.com/user-attachments/assets/5129a2ce-9d91-417d-b867-39c3dd2bb6f5)

---

### 3. **Drivers de moteurs PWM**

Le robot est équipé de **deux moteurs DC**, chacun étant contrôlé par un driver PWM. Chaque driver reçoit des signaux PWM du STM32 pour réguler la vitesse et la direction des moteurs.

- **Modèle des drivers** : ZXBM5210-SP-13
- **Fonction principale** : Piloter les moteurs en avant ou en arrière grâce à des signaux PWM.
- **Commandes PWM** : Les signaux PWM (Forward et Reverse) contrôlent la direction des moteurs. La vitesse est ajustée en modifiant le rapport cyclique du PWM.
![image](https://github.com/user-attachments/assets/0cda02bc-fccc-41bd-a066-0c950e37ea76)

### 4. **Accéléromètre ADXL343**

L'accéléromètre **ADXL343** est utilisé pour détecter les chocs entre les robots. Il mesure l'accélération dans les trois axes et peut détecter des variations rapides, comme celles d'une collision.

- **Communication** : Le module utilise le protocole **I2C** pour envoyer les données d'accélération au STM32.
- **Fonction principale** : Détecter les impacts ou les vibrations et permettre une réaction rapide du robot (comme changer de direction ou ajuster son comportement).
![image](https://github.com/user-attachments/assets/9bfa07b8-3d74-4790-9a44-6277851f2bb4)

### 5. **LIDAR YDLIDAR X4**

Le **LIDAR YDLIDAR X4** est utilisé pour scanner l'environnement autour du robot et déterminer la position des autres robots et des obstacles. 
- **Type de capteur** : **LIDAR à balayage laser**.
- **Portée** : Jusqu'à 12 mètres.
- **Communication** : **UART**  pour transmettre les données de mesure.
  
---
# Schema de cablage
![image](https://github.com/user-attachments/assets/3b9caab8-d71d-4af7-be6f-68d475668fa8)
![image](https://github.com/user-attachments/assets/5d58a721-86af-481f-8afd-4aa44524a779)

## Software

### **Drivers de Moustache**
### **1. Fichier `Moustache.c`**-contient l'implémentation du pilote pour gérer les interruptions et les tâches liées à un système utilisant des capteurs "moustaches" pour détecter des bords.
**Principales fonctions et variables :
1. **Variables principales :**
   - `cb_out1_task_handle` et `cb_out2_task_handle` : Des handles pour les tâches FreeRTOS associées aux deux GPIO.
   - `exclusive_task` : Variable pour enregistrer quelle tâche est en cours d'exécution, afin d'éviter que plusieurs tâches ne soient actives simultanément ( On a remarqué que lorsque l'une des deux moustaches détecte le bord, la deuxième va également interrompre après un petit moment, et cela est dû à la conception du robot ). 
     - `0`: Aucune tâche active.
     - `1`: La tâche `CB_OUT1_Task` est active.
     - `2`: La tâche `CB_OUT2_Task` est active.
   - `robot` : Variable globale externe, représentant l'état d'un robot. Elle est utilisée dans la fonction `Bord`.

2. **Initialisation (`Moustache_Init`):**
   - Création de deux tâches FreeRTOS :
     - `CB_OUT1_Task` pour gérer les événements associés au GPIO `CB_OUT1_Pin`.
     - `CB_OUT2_Task` pour gérer les événements associés au GPIO `CB_OUT2_Pin`.

3. **Gestion des interruptions (`Moustache_HandleInterrupt`):**
   - Cette fonction est appelée lorsqu'une interruption GPIO est détectée.
   - Vérifie si une tâche peut être exécutée (selon la valeur de `exclusive_task`).
   - Envoie une notification à la tâche correspondante (`cb_out1_task_handle` ou `cb_out2_task_handle`) en utilisant `xTaskNotifyFromISR`.

4. **Fonction `Bord` :**
   - Gère le comportement du robot en fonction de sa direction (`robot.direction`).
     - `'A'`: Le robot recule.
     - `'R'`: Le robot avance.
   - Cette fonction est appelée par les tâches pour ajuster le mouvement du robot.

5. **Tâches `CB_OUT1_Task` et `CB_OUT2_Task` :**
   - Chaque tâche attend une notification via `xTaskNotifyWait`.
   - Lorsqu'une notification est reçue :
     - Elle effectue une action définie (appel de `Bord`).
     - Réinitialise `exclusive_task` à 0 pour permettre d'autres interruptions.

#### **2. Fichier `Moustache.h`**

Ce fichier est l'en-tête associé, qui déclare les prototypes des fonctions et les dépendances nécessaires.

#### **Principales fonctionnalités :**

1. **Inclusion de bibliothèques nécessaires :**
   - `stm32g4xx_hal.h` : Bibliothèque HAL pour la famille STM32G4.
   - `gpio.h` : Bibliothèque pour gérer les GPIO.

2. **Prototypes de fonctions :**
   - `Moustache_Init(void)` : Initialisation du pilote et des tâches.
   - `Moustache_HandleInterrupt(uint16_t GPIO_Pin)` : Gestion des interruptions GPIO.

### 1.Fichier 'MoteurPWM.c' 

*La fonction Moteur_init: 

Est responsable de l'initialisation d'un moteur en configurant ses paramètres de base. Elle prend en entrée un pointeur vers la structure du moteur, le timer PWM et le canal associé, initialisant la direction à l'arrêt et la vitesse à zéro.

*Moteur_setSpeed:
gère la vitesse du moteur avec une conversion d'échelle, transformant une vitesse d'entrée (±290) en valeur PWM (0-8500) et configurant la direction appropriée.

*Moteur_setDirection:
contrôle la direction du moteur en gérant les signaux PWM complémentaires elle peut faire avancer, reculer ou arrêter le moteur en activant ou désactivant les canaux PWM appropriés.

*Moteur_start, Moteur_stop et Moteur_recule sont des fonctions d'aide qui simplifient le contrôle du moteur en appelant Moteur_setDirection avec les paramètres appropriés.

Du côté du robot, Robot_Start initialise le mouvement en avant avec des vitesses asymétriques (120 pour la droite, 80 pour la gauche), tandis que Robot_Stop arrête les deux moteurs.Robot_Recule fait reculer le robot avec les mêmes vitesses que l'avance mais en négatif.

## 2.Fichier 'MoteurPWM.h' 
## Datasheets et sourcing des composants
https://1drv.ms/x/s!AjphXEW6glNckYErezblGW1QHlP9SQ

# Infos Lidar

trame du YDLIDAR X4 se compose des éléments suivants :
<br>
- En-tête (2 octets) : Indique le début d'une nouvelle trame
- Longueur des données (1 octet) : Taille des données qui suivent
- Données de points (variable) : Informations sur chaque point mesuré
- Checksum (2 octets) : Pour vérifier l'intégrité des données
<br>
(Pour chaque point)

RQ: Utiliser un struct pour les données reçues


# Rappels git

## Les branches

### Creér une branche
``
git checkout -b <nom de la branche>
``

### Changer de branche
``
git checkout <nom de la branche>
``
 ## Commits et push
!!! ATTENTION À LA BRANCHE OÙ L'ON SE TROVUE !!!
```
git add . 
git commit -m "message de commit"
git push
```

## Merge dans le main
On utilise des PR (pull requests), on ne push jamais rien dans le `main`!
