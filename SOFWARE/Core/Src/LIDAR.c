#include "LIDAR.h"
#include <stdio.h>
#include "usart.h"
#include <math.h>

static int LIDAR_UART_transmit(uint8_t *p_data, uint16_t size){
	HAL_UART_Transmit(&huart3, p_data, size, HAL_MAX_DELAY);
	return 0;
}
static int LIDAR_UART_poll_receive(uint8_t *p_data, uint16_t size){
	HAL_UART_Receive(&huart3, p_data, size, HAL_MAX_DELAY);
	return 0;
}

static int LIDAR_UART_DMA_receive(uint8_t *p_data, uint16_t size){
	HAL_UART_Receive_DMA(&huart3, p_data, size);
	return 0 ;
}


//Start scanning and export point cloud data
//Sustained response
int LIDAR_start(h_LIDAR_t * h_LIDAR){
	uint8_t cmd_buff[CMD_BUFF_SIZE]={CMD_BEGIN,CMD_START};
	LIDAR_UART_DMA_receive(h_LIDAR->data_buff,DATA_BUFF_SIZE);
	LIDAR_UART_transmit(cmd_buff,CMD_BUFF_SIZE);
	return 0;
}

//Stop and stop scanning
//No answer
int LIDAR_stop(){
	uint8_t cmd_buff[CMD_BUFF_SIZE]={CMD_BEGIN,CMD_STOP};
	LIDAR_UART_transmit(cmd_buff,CMD_BUFF_SIZE);
	return 0;
}

//Get device information
//Single response
int LIDAR_get_info(h_LIDAR_t * h_LIDAR) {
    uint8_t cmd_buff[CMD_BUFF_SIZE] = {CMD_BEGIN, CMD_INFO};  // Command buffer
    LIDAR_UART_transmit(cmd_buff, CMD_BUFF_SIZE);
    LIDAR_UART_poll_receive(h_LIDAR->info_buff, INFO_BUFF_SIZE);

    h_LIDAR->device_info.start_sign = (h_LIDAR->info_buff[0] << 8) | h_LIDAR->info_buff[1];
    h_LIDAR->device_info.lenght = (h_LIDAR->info_buff[2]) | (h_LIDAR->info_buff[3] << 8) | (h_LIDAR->info_buff[4] << 16);
    h_LIDAR->device_info.mode = h_LIDAR->info_buff[5];
    h_LIDAR->device_info.type_code = h_LIDAR->info_buff[6];
    h_LIDAR->device_info.model = h_LIDAR->info_buff[7];
    h_LIDAR->device_info.firmware =  h_LIDAR->info_buff[8]|(h_LIDAR->info_buff[9]<<1);
    h_LIDAR->device_info.hardware = h_LIDAR->info_buff[10];
    
    snprintf(h_LIDAR->device_info.serial, sizeof(h_LIDAR->device_info.serial),"%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u" ,
             h_LIDAR->info_buff[11], h_LIDAR->info_buff[12], h_LIDAR->info_buff[13], h_LIDAR->info_buff[14],
             h_LIDAR->info_buff[15], h_LIDAR->info_buff[16], h_LIDAR->info_buff[17], h_LIDAR->info_buff[18],
             h_LIDAR->info_buff[19], h_LIDAR->info_buff[20], h_LIDAR->info_buff[21], h_LIDAR->info_buff[22],
             h_LIDAR->info_buff[23], h_LIDAR->info_buff[24], h_LIDAR->info_buff[25], h_LIDAR->info_buff[26]);

    // Output for debugging
    printf("Start sign : %x\r\n", h_LIDAR->device_info.start_sign);
    printf("Length : %ld\r\n", h_LIDAR->device_info.lenght);
    printf("Mode : %x\r\n", h_LIDAR->device_info.mode);
    printf("Type code : %x\r\n", h_LIDAR->device_info.type_code);
    printf("Model %x\r\n", h_LIDAR->device_info.model);
    printf("Firmware version : %u\r\n", h_LIDAR->device_info.firmware);
    printf("Hardware version : %d\r\n", h_LIDAR->device_info.hardware);
    printf("Serial number : %s\r\n", h_LIDAR->device_info.serial);

    return 0;
}


//Get device health status
//Single response
int LIDAR_get_health_stat(h_LIDAR_t * h_LIDAR){
	uint8_t cmd_buff[CMD_BUFF_SIZE]={CMD_BEGIN,CMD_HEALTH}; //Buffer de commande
	LIDAR_UART_transmit(cmd_buff,2);
	LIDAR_UART_poll_receive(h_LIDAR->health_buff,HEALTH_BUFF_SIZE);

	h_LIDAR->health_stat.start_sign=(h_LIDAR->health_buff[0]<<8)|h_LIDAR->health_buff[1];
	h_LIDAR->health_stat.lenght=(h_LIDAR->health_buff[2])|(h_LIDAR->health_buff[3]<<8)|(h_LIDAR->health_buff[4]<<16);
	h_LIDAR->health_stat.mode=h_LIDAR->health_buff[5];
	h_LIDAR->health_stat.type_code=h_LIDAR->health_buff[6];
	h_LIDAR->health_stat.status_code=h_LIDAR->health_buff[7];
	h_LIDAR->health_stat.error_code=h_LIDAR->health_buff[8]|(h_LIDAR->health_buff[9]<<8);

	printf("Start sign : %x\r\n",h_LIDAR->health_stat.start_sign);
	printf("Length : %ld\r\n",h_LIDAR->health_stat.lenght);
	printf("Mode : %x\r\n",h_LIDAR->health_stat.mode);
	printf("Type code : %x\r\n",h_LIDAR->health_stat.type_code);
	printf("Status code : %x\r\n",h_LIDAR->health_stat.status_code);
	printf("Error code : %x\r\n",h_LIDAR->health_stat.error_code);

	return 0;
}

//Soft restart
//No response
int LIDAR_restart(){
	uint8_t cmd_buff[CMD_BUFF_SIZE]={CMD_BEGIN,CMD_RESTART};
	LIDAR_UART_transmit(cmd_buff,CMD_BUFF_SIZE);
	return 0;
}

void LIDAR_process_frame(h_LIDAR_t * LIDAR){
	uint16_t Si;
	int Di;
	int Ai;
	int AngleFSA=(LIDAR->processing.FSA>>1); //64
	int AngleLSA=(LIDAR->processing.LSA>>1);
	int index;
	for(int i=0;i<LIDAR->processing.idx/2;i++){
		Si=LIDAR->processing.frame_buff[2*i]|(LIDAR->processing.frame_buff[2*i+1]<<8);
		Di=Si/4; //Distance du point i
		Ai=AngleFSA/64+i*(AngleLSA-AngleFSA)/64/(LIDAR->processing.LSN-1);
		index = round(Ai);

		if(Di>2000){ //On affiche pas les points trop loin
			LIDAR->processing.point_buff[index]=0;
		}
		else if(Di<40){
			LIDAR->processing.point_buff[index]=0;
		}
		else{
			LIDAR->processing.point_buff[index]=Di;
		}
	}
}
