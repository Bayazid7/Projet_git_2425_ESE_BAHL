#ifndef __ADXL343__
#define __ADXL343__

#include <stdio.h>
#include "stm32g4xx_hal.h"

#define ADXL343_ADDRESS (0x53 << 1)

#define ADXL343_REG_DEVID (0x00)
#define ADXL343_REG_THRESH_TAP (0x1D)
#define ADXL343_REG_OFSX (0x1E)
#define ADXL343_REG_OFSY (0x1F)
#define ADXL343_REG_OFSZ (0x20)
#define ADXL343_REG_DUR (0x21)
#define ADXL343_REG_ACT_INACT_CTL (0x27)
#define ADXL343_REG_POWER_CTL (0x2D)
#define ADXL343_REG_FIFO_CTL (0x38)
#define ADXL343_REG_INT_ENABLE (0x2E)
#define ADXL343_REG_INT_MAP (0x2F)
#define ADXL343_REG_INT_SOURCE (0x30)
#define ADXL343_REG_DATA_FORMAT (0x31)
#define ADXL343_REG_DATAX0 (0x32)
#define ADXL343_REG_DATAX1 (0x33)
#define ADXL343_REG_DATAY0 (0x34)
#define ADXL343_REG_DATAY1 (0x35)
#define ADXL343_REG_DATAZ0 (0x36)
#define ADXL343_REG_DATAZ1 (0x37)

typedef struct
{
    I2C_HandleTypeDef *hi2c;
    uint8_t range ;
    uint8_t rate ;
    uint8_t devID ;
    uint16_t accX;
    uint16_t accY;
    uint16_t accZ;

} ADXL343_InstanceDef_t;

typedef enum 
{
	RATE_3200_HZ = 0x0F,		// 1111
	RATE_1600_HZ = 0x0E,		// 1110
	RATE_800_HZ  = 0x0D,		// 1101
	RATE_400_HZ  = 0x0C,		// 1100
	RATE_200_HZ  = 0x0B,		// 1011
	RATE_100_HZ  = 0x0A,		// 1010
	RATE_50_HZ   = 0x09,		// 1001
	RATE_25_HZ   = 0x08,		// 1000
	RATE_12_5_HZ = 0x07,		// 0111
	RATE_6_25_HZ = 0x06,		// 0110
	RATE_3_13_HZ = 0x05,		// 0101
	RATE_1_56_HZ = 0x04,		// 0100
	RATE_0_78_HZ = 0x03,		// 0011
	RATE_0_39_HZ = 0x02,		// 0010
	RATE_0_20_HZ = 0x01,		// 0001
	RATE_0_10_HZ = 0x00		    // 0000
} ADXL343_rate_t;

typedef enum 
{
	RANGE_2G  = 0x00,
	RANGE_4G  = 0x01,
	RANGE_8G  = 0x02,
	RANGE_16G = 0x03
} ADXL343_range_t;

uint8_t ADXL343_Init(ADXL343_InstanceDef_t *Instance,I2C_HandleTypeDef *hi2c );
uint8_t ADXL343_SetOffset(ADXL343_InstanceDef_t *Instance, int8_t ofsX, int8_t ofsY, int8_t ofsZ);
uint8_t ADXL343_GetOffset(ADXL343_InstanceDef_t *Instance, int8_t *ofsX, int8_t *ofsY, int8_t *ofsZ);
uint8_t ADXL343_SetFIFO(ADXL343_InstanceDef_t *Instance, uint8_t mode);
uint8_t ADXL343_ReadAcceleration(ADXL343_InstanceDef_t *Instance);
uint8_t ADXL343_SetTapThreshold(ADXL343_InstanceDef_t *Instance, uint8_t threshold);
uint8_t ADXL343_SetTapDuration(ADXL343_InstanceDef_t *Instance, uint8_t duration);
uint8_t ADXL343_SetInterrupt(ADXL343_InstanceDef_t *Instance);
uint8_t ADXL343_ClearInterrupt(ADXL343_InstanceDef_t *Instance);
uint8_t ADXL343_ReadInterruptSource(ADXL343_InstanceDef_t *Instance);
uint8_t ADXL343_HandleTapInterrupt(ADXL343_InstanceDef_t *Instance);

#endif
