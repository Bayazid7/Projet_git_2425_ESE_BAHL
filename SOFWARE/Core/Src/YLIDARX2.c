/**
 * @file YLIDARX2.c
 * @author Aliou LY (aliou.ly@ensea.fr)
 * @brief
 * @version 0.1
 * @date 2024-11-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "YLIDARX2.h"
#include <math.h>
#include  "usart.h"

uint8_t flagDMA=0;
uint8_t flagStart = 0 ;

void LIDAR_Init(h_LIDAR_t *h_LIDAR, UART_HandleTypeDef *huart)
{
	h_LIDAR->huart = huart;
	h_LIDAR->info.start_sign=0xA55A ;
	h_LIDAR->processing.PH =0x55AA;
	h_LIDAR->point[250].Angle=25;
	h_LIDAR->point[250].Distance=25;
	h_LIDAR->processing.idx = 0;

}

static float calculAngle(h_LIDAR_t *h_LIDAR,float Distance )
{
	float Angle_FSA = ((h_LIDAR->processing.FSA) >> 1) / 64.0;
	float Angle_LSA = ((h_LIDAR->processing.LSA) >> 1) / 64.0;
	float Angle = (Angle_LSA - Angle_FSA) * (h_LIDAR->processing.idx - 1)/(float)(h_LIDAR->processing.LSN-1) + Angle_FSA;
	float Angle_Correc = 0;
	if (Distance != 0)
	{
		float numerator = 21.8 * (155.3 - Distance);
		float denominator = 155.3 * Distance;
		Angle_Correc = atan(numerator / denominator);
	}
	return Angle + Angle_Correc ;
}

HAL_StatusTypeDef LIDAR_start(h_LIDAR_t *h_LIDAR)
{
	printf("hello \n");
	return HAL_UART_Receive_DMA(h_LIDAR->huart, h_LIDAR->data_buff, DATA_BUFF_SIZE);
}

void process(h_LIDAR_t *h_LIDAR, uint16_t start, uint16_t end)
{
    for (uint16_t i = start; i < end;)
    {
        // Lecture de l'en-tête (header)
        uint16_t header = (h_LIDAR->data_buff[i] << 8) | h_LIDAR->data_buff[i + 1];

        if (header == h_LIDAR->info.start_sign)
        {
            i += 25; // Ignorer 27 octets pour ce type de header
        }
        else if (header == h_LIDAR->processing.PH)
        {
            // Début du traitement
            h_LIDAR->processing.CT = h_LIDAR->data_buff[i + 2];
            h_LIDAR->processing.LSN = h_LIDAR->data_buff[i + 3];
            h_LIDAR->processing.FSA = (h_LIDAR->data_buff[i + 5] << 8) | h_LIDAR->data_buff[i + 4];
            h_LIDAR->processing.LSA = (h_LIDAR->data_buff[i + 7] << 8) | h_LIDAR->data_buff[i + 6];
            h_LIDAR->processing.CS = (h_LIDAR->data_buff[i + 9] << 8) | h_LIDAR->data_buff[i + 8];
            i += 10;

            // Initialisation de l'indice
            h_LIDAR->processing.idx = 1;

            // Traitement des points
            uint16_t index;
            float Distance, Angle;

            for (uint16_t j = 0; j < h_LIDAR->processing.LSN; ++j)
            {
                // Lecture des distances
                Distance = ((h_LIDAR->data_buff[i + 1] << 8) | h_LIDAR->data_buff[i]) / 4.0f;

                // Calcul des angles avec `idx`
                Angle = calculAngle(h_LIDAR, Distance);
                index = (uint16_t)(Angle);

                // Mise à jour des données des points
                h_LIDAR->point[index].Distance = Distance;
                h_LIDAR->point[index].Angle = Angle;

                // Avancer dans le buffer
                i += 2;

                // Mise à jour de l'indice
                h_LIDAR->processing.idx++;
            }
        }
        else
        {
            i++; // Si aucun des cas ne correspond, passer au prochain octet
        }
    }
}


void LIDAR_process_frame(h_LIDAR_t *LIDAR)
{
	if(flagDMA==1)
	{
		process(LIDAR, 0, DATA_BUFF_SIZE/2) ;
	}
	if (flagDMA==2)
	{
		process(LIDAR, DATA_BUFF_SIZE/2,DATA_BUFF_SIZE) ;
		flagDMA = 0 ;
	}
}
