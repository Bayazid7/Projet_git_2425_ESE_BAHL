/**
 * @file ADXL343.h
 * @author Aliou LY(aliou.ly@ensea.fr)
 * @brief 
 * @version 0.1
 * @date 2024-11-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __ADXL343__
#define __ADXL343__

#include <stdio.h>
#include "i2c.h"

#define ADXL343_ADDRESS (0x53 << 1)
#define ADXL343_DEVID (0xe5)

#define ADXL343_REG_DEVID (0x00)
#define ADXL343_REG_THRESH_TAP (0x1D)
#define ADXL343_REG_OFSX (0x1E)
#define ADXL343_REG_OFSY (0x1F)
#define ADXL343_REG_OFSZ (0x20)
#define ADXL343_REG_DUR (0x21)
#define ADXL343_REG_ACT_INACT_CTL (0x27)
#define ADXL343_REG_TAP_AXES (0x2A)
#define ADXL343_REG_BW_RATE (0x2C)
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

#define ADXL343I2C hi2c1
typedef struct
{
	I2C_HandleTypeDef *hi2c;
	uint8_t range;
	uint8_t rate;
	uint8_t devID;
	float accX;
	float  accY;
	float  accZ;

} ADXL343_InstanceDef_t;

typedef enum
{
	RATE_3200_HZ = 0x0F,
	RATE_1600_HZ = 0x0E,
	RATE_800_HZ = 0x0D,
	RATE_400_HZ = 0x0C,
	RATE_200_HZ = 0x0B,
	RATE_100_HZ = 0x0A,
	RATE_50_HZ = 0x09,
	RATE_25_HZ = 0x08,
	RATE_12_5_HZ = 0x07,
	RATE_6_25_HZ = 0x06,
	RATE_3_13_HZ = 0x05,
	RATE_1_56_HZ = 0x04,
	RATE_0_78_HZ = 0x03,
	RATE_0_39_HZ = 0x02,
	RATE_0_20_HZ = 0x01,
	RATE_0_10_HZ = 0x00
} ADXL343_rate_t;

typedef enum
{
	RANGE_2G = 0b00,
	RANGE_4G = 0b01,
	RANGE_8G = 0b10,
	RANGE_16G = 0b11
} ADXL343_range_t;

uint8_t ADXL343_Init(ADXL343_InstanceDef_t *Instance,I2C_HandleTypeDef *hi2c);
uint8_t ADXL343_SetOffset(ADXL343_InstanceDef_t *Instance, uint8_t ofsX, uint8_t ofsY, uint8_t ofsZ);
uint8_t ADXL343_GetOffset(ADXL343_InstanceDef_t *Instance, uint8_t *ofsX, uint8_t *ofsY, uint8_t *ofsZ);
uint8_t ADXL343_ReadAcceleration(ADXL343_InstanceDef_t *Instance);
uint8_t ADXL343_SetTapThreshold(ADXL343_InstanceDef_t *Instance, uint8_t threshold);
uint8_t ADXL343_SetTapDuration(ADXL343_InstanceDef_t *Instance, uint8_t duration);
uint8_t ADXL343_ClearInterrupt(void);

#endif
