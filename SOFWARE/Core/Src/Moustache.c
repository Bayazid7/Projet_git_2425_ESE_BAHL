#include "Moustache.h"
#include "cmsis_os.h"
#include "stdio.h"
#include "MoteurPWM.h"

// Déclaration des handles des tâches
static TaskHandle_t cb_out1_task_handle = NULL;
static TaskHandle_t cb_out2_task_handle = NULL;
extern h_Robot robot;
// Variable pour enregistrer l'interruption active
static volatile uint8_t exclusive_task = 0; // 0: aucune, 1: CB_OUT1, 2: CB_OUT2

// Prototypes des tâches
static void CB_OUT1_Task(void *pvParameters);
static void CB_OUT2_Task(void *pvParameters);

// Initialisation
void Moustache_Init(void) {
    // Création des tâches
    xTaskCreate(CB_OUT1_Task, "CB_OUT1_Task", 128, NULL, 5, &cb_out1_task_handle);
    xTaskCreate(CB_OUT2_Task, "CB_OUT2_Task", 128, NULL, 5, &cb_out2_task_handle);
}

// Gestion des interruptions GPIO
void Moustache_HandleInterrupt(uint16_t GPIO_Pin){
    BaseType_t higherPriorityTaskWoken = pdFALSE;

    if (GPIO_Pin == CB_OUT1_Pin) {
        if (exclusive_task == 0 || exclusive_task == 1) {
            // Activer CB_OUT1
            exclusive_task = 1; // Marquer CB_OUT1 comme exclusif
            xTaskNotifyFromISR(cb_out1_task_handle, 0x01, eSetBits, &higherPriorityTaskWoken);
        }
    } else if (GPIO_Pin == CB_OUT2_Pin) {
        if (exclusive_task == 0 || exclusive_task == 2) {
            // Activer CB_OUT2
            exclusive_task = 2; // Marquer CB_OUT2 comme exclusif
            xTaskNotifyFromISR(cb_out2_task_handle, 0x01, eSetBits, &higherPriorityTaskWoken);
        }
    }

    // Passer à une tâche de priorité plus élevée si nécessaire
    portYIELD_FROM_ISR(higherPriorityTaskWoken);
}

static void Bord(void ) {
	if (robot.direction == 'A') {
		Robot_Recule(&robot);
	} else if (robot.direction == 'R') {
		Robot_Start(&robot);
	}
	//Robot_Stop(&robot);
}
// Tâches pour traiter les interruptions
static void CB_OUT1_Task(void *pvParameters)
{
    uint32_t notificationValue = 0;
    for (;;) {
        // Attend une notification
        if (xTaskNotifyWait(0, 0xFFFFFFFF, &notificationValue, portMAX_DELAY) == pdTRUE) {
            // Action pour CB_OUT1
            //printf("CB_OUT1 Detected\r\n");
            //HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0); // Exemple d'action
        	Bord();
            // Simule une tâche longue
            //vTaskDelay(pdMS_TO_TICKS(1000));

            // Réinitialiser l'état pour permettre de détecter CB_OUT1 ou CB_OUT2 à nouveau
            exclusive_task = 0;
        }
    }
}

static void CB_OUT2_Task(void *pvParameters) {
    uint32_t notificationValue = 0;
    for (;;) {
        // Attend une notification
        if (xTaskNotifyWait(0, 0xFFFFFFFF, &notificationValue, portMAX_DELAY) == pdTRUE) {
            // Action pour CB_OUT2
            //printf("CB_OUT2 Detected\r\n");
           // HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1); // Exemple d'action
        	Bord();
            // Simule une tâche longue
            //vTaskDelay(pdMS_TO_TICKS(1000));

            // Réinitialiser l'état pour permettre de détecter CB_OUT1 ou CB_OUT2 à nouveau
            exclusive_task = 0;
        }
    }
}
