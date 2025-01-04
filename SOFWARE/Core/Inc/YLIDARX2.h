/**
 * @file YLIDARX2.h
 * @author Aliou LY (aliou.ly@ensea.fr)
 * @brief 
 * @version 0.1
 * @date 2024-11-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __LIDARX2__
#define __LIDARX2__
#include "usart.h"
#include <stdio.h>

#define INFO_BUFF_SIZE 27	
#define DATA_BUFF_SIZE 500
#define POINT_BUFF_SIZE 360	

typedef struct LIDAR_point_struct
{
	float Distance ;
	float Angle ;

}  LIDAR_point_t ;

typedef struct LIDAR_device_info_struct
{
	uint16_t start_sign;
	uint32_t lenght;
	uint8_t mode;
	uint8_t type_code;
	uint8_t model;
	uint16_t firmware;
	uint8_t hardware;
	uint8_t serial[16];
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

} LIDAR_processing_t;

typedef struct h_LIDAR_struct
{
	LIDAR_point_t point[POINT_BUFF_SIZE] ;
	LIDAR_device_info_t info ;
	UART_HandleTypeDef *huart ;
	uint8_t data_buff[DATA_BUFF_SIZE];
	LIDAR_processing_t processing;

} h_LIDAR_t;

void LIDAR_Init(h_LIDAR_t *h_LIDAR ,UART_HandleTypeDef *huart ) ;
HAL_StatusTypeDef  LIDAR_start(h_LIDAR_t *h_LIDAR);
void LIDAR_process_frame(h_LIDAR_t *LIDAR);
void process(h_LIDAR_t *h_LIDAR, uint16_t start, uint16_t end);

#endif
