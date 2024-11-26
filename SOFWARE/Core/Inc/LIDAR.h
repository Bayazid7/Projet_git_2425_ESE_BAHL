/**
 * @file LIDAR.h
 * @author Aliou LY(aliou.ly@ensea.fr)
 * @brief 
 * @version 0.1
 * @date 2024-11-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __LIDAR__
#define __LIDAR__

#include "stm32g4xx_hal.h"

#define INFO_BUFF_SIZE 27	// 7reply  + 20 infos
#define HEALTH_BUFF_SIZE 10 // 7 + 3
#define CMD_BUFF_SIZE 2		// start + commande
#define DATA_BUFF_SIZE 4000 // Prut etre plus
#define FRAME_BUFF_SIZE 90	// mas 40points + 10 header
#define POINT_BUFF_SIZE 360 //  les 360°
#define NB_DEGRES 360

typedef enum LIDAR_command_enum
{
	CMD_BEGIN = 0xA5,  // Premier octet de la commande
	CMD_START = 0x60,  // Start scanning and export point cloud data
	CMD_STOP = 0x65,   // Stop and stop scanning
	CMD_INFO = 0x90,   // Get device information
	CMD_HEALTH = 0x91, // Get device health status
	CMD_RESTART = 0x80 // Soft restart
} LIDAR_command_t;

typedef struct LIDAR_health_stat_struct
{
	uint16_t start_sign;
	uint32_t lenght;
	uint8_t mode;
	uint8_t type_code;
	uint8_t status_code;
	uint16_t error_code;
} LIDAR_health_stat_t;

typedef struct LIDAR_device_info_struct
{
	uint16_t start_sign;
	uint32_t lenght;
	uint8_t mode;
	uint8_t type_code;
	uint8_t model;
	uint16_t firmware;
	uint8_t hardware;
	char serial[16];
} LIDAR_device_info_t;

typedef struct LIDAR_processing_struct
{
	// Header
	uint16_t PH;

	// CT Package Type / fréquence
	uint8_t CT;

	// LSN nombre de points de la trame
	uint8_t LSN;

	// FSA Start Angle
	uint16_t FSA;

	// LSA End Angle
	uint16_t LSA;

	// CS Check Code
	uint16_t CS;

	// Frame index
	uint8_t idx;

	// Buffer contenant les trames reçu en DMA
	uint8_t receive_buff[DATA_BUFF_SIZE];

	// Buffer contenant une frame
	uint8_t frame_buff[FRAME_BUFF_SIZE];

	// Buffer contenant les points
	int point_buff[POINT_BUFF_SIZE];

} LIDAR_processing_t;

typedef struct h_LIDAR_struct
{

	// health status
	LIDAR_health_stat_t health_stat;

	// device info
	LIDAR_device_info_t device_info;

	// variables propres au lidar
	uint8_t info_buff[INFO_BUFF_SIZE];
	uint8_t health_buff[HEALTH_BUFF_SIZE];
	uint8_t data_buff[DATA_BUFF_SIZE];

	// Traitement des trames
	LIDAR_processing_t processing;

} h_LIDAR_t;

int LIDAR_start(h_LIDAR_t *h_LIDAR);
int LIDAR_stop();
int LIDAR_get_info(h_LIDAR_t *h_LIDAR);
int LIDAR_get_health_stat(h_LIDAR_t *h_LIDAR);
int LIDAR_restart();
void LIDAR_process_frame(h_LIDAR_t *LIDAR);
int calculer_distance_moyenne(int distances[], int debut, int fin);

#endif