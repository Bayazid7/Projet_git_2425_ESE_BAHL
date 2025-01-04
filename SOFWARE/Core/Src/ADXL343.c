/**
 * @file ADXL343.c
 * @author Aliou LY(aliou.ly@ensea.fr)
 * @brief
 * @version 0.1
 * @date 2024-11-21
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "ADXL343.h"
#include <stdio.h>
#include "cmsis_os.h"

TaskHandle_t TapDetected_task = NULL;

static uint8_t ADXL343_I2C_Read(ADXL343_InstanceDef_t *Instance, uint8_t reg, uint8_t *buf, uint16_t size)
{
	if (Instance == NULL || buf == NULL || size == 0)
	{
		return 1;
	}
	if (HAL_I2C_Mem_Read(Instance->hi2c, ADXL343_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, buf, size, HAL_MAX_DELAY) != HAL_OK)
	{
		return 1;
	}
	return 0;
}

static uint8_t ADXL343_I2C_Write(ADXL343_InstanceDef_t *Instance, uint8_t reg, uint8_t *buf, uint16_t size)
{
	if (Instance == NULL || buf == NULL || size == 0)
	{
		return 1;
	}
	if (HAL_I2C_Mem_Write(Instance->hi2c, ADXL343_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, buf, size, HAL_MAX_DELAY) != HAL_OK)
	{
		return 1;
	}
	return 0;
}


uint8_t ADXL343_Init(ADXL343_InstanceDef_t *Instance,I2C_HandleTypeDef *hi2c)
{
	if (Instance == NULL )
	{
		printf("Erreur : Instance ou handle I2C est NULL.\r\n");
		return 1;
	}
	Instance->hi2c = hi2c;
	Instance->accX = 0;
	Instance->accY = 0;
	Instance->accZ = 0;
	uint8_t configData;
	uint8_t deviceID = 0;
	if (ADXL343_I2C_Read(Instance, ADXL343_REG_DEVID, &deviceID, 1) != 0)
	{
		printf("Erreur : Échec de la lecture de l'identifiant de l'appareil.\r\n");
		return 1;
	}

	if (deviceID != ADXL343_DEVID)
	{
		printf("Erreur : ID de l'appareil incorrect (attendu : 0x%X, lu : 0x%X).\r\n", ADXL343_DEVID, deviceID);
		return 1;
	}

	configData = 0x08;
	if (ADXL343_I2C_Write(Instance, ADXL343_REG_POWER_CTL, &configData, 1) != 0)
	{
		printf("Erreur : Échec de la configuration de POWER_CTL.\r\n");
		return 1;
	}
	// Configuration du format des données
	configData = 0x0B; // Exemple de format : Full resolution, ±16g
	if (ADXL343_I2C_Write(Instance, ADXL343_REG_DATA_FORMAT, &configData, 1) != 0)
	{
		printf("Erreur : Échec de la configuration de DATA_FORMAT.\r\n");
		return 1;
	}

	ADXL343_SetOffset(Instance, 0,0, 0)	;


	// Désactivation des interruptions
	configData = 0x00;
	if (ADXL343_I2C_Write(Instance, ADXL343_REG_INT_ENABLE, &configData, 1) != 0)
	{
		printf("Erreur : Échec de la désactivation des interruptions.\r\n");
		return 1;
	}
	// Configuration des seuils de tap
	if (ADXL343_SetTapThreshold(Instance,70) != 0)
	{
		printf("Erreur : Échec de la configuration de THRESH_TAP.\r\n");
		return 1;
	}
	// Configuration de la durée
	if (ADXL343_SetTapDuration(Instance, 90)!= 0)
	{
		printf("Erreur : Échec de la configuration de DUR.\r\n");
		return 1;
	}

	// Configuration des axes de tap
	configData = 0x06; // Activer les axes X, Y
	if (ADXL343_I2C_Write(Instance, ADXL343_REG_TAP_AXES, &configData, 1) != 0)
	{
		printf("Erreur : Échec de la configuration de TAP_AXES.\r\n");
		return 1;
	}

	// Configuration de la fréquence d'échantillonnage
	configData = RATE_200_HZ;
	if (ADXL343_I2C_Write(Instance, ADXL343_REG_BW_RATE, &configData, 1) != 0)
	{
		printf("Erreur : Échec de la configuration de BW_RATE.\r\n");
		return 1;
	}

	// Configuration de la carte d'interruption
	configData = 0x40; // Exemple de configuration
	if (ADXL343_I2C_Write(Instance, ADXL343_REG_INT_MAP, &configData, 1) != 0)
	{
		printf("Erreur : Échec de la configuration de INT_MAP.\r\n");
		return 1;
	}

	// Activation des interruptions
	configData = 0x40; // Exemple pour activer les interruptions
	if (ADXL343_I2C_Write(Instance, ADXL343_REG_INT_ENABLE, &configData, 1) != 0)
	{
		printf("Erreur : Échec de l'activation des interruptions.\r\n");
		return 1;
	}

	printf("Initialisation de l'ADXL343 réussie.\r\n");
	return 0;
}

uint8_t ADXL343_SetOffset(ADXL343_InstanceDef_t *Instance, uint8_t ofsX, uint8_t ofsY, uint8_t ofsZ)
{
	uint8_t offsetData[3];
	offsetData[0] = ofsX;
	offsetData[1] = ofsY;

	if (ADXL343_I2C_Write(Instance, ADXL343_REG_OFSX, offsetData, 3) != 0)
	{
		return 1;
	}
	return 0;
}

uint8_t ADXL343_GetOffset(ADXL343_InstanceDef_t *Instance, uint8_t *ofsX, uint8_t *ofsY, uint8_t *ofsZ)
{

	uint8_t offsetData[3];

	if (ADXL343_I2C_Read(Instance, ADXL343_REG_OFSX, offsetData, 3) != 0)
	{
		return 1;
	}

	*ofsX = offsetData[0];
	*ofsY = offsetData[1];
	*ofsZ = offsetData[2];

	return 0;
}

uint8_t ADXL343_ClearInterrupt(void)
{
	uint8_t interruptSource = 0;
	if (HAL_I2C_Mem_Read(&ADXL343I2C, ADXL343_ADDRESS, ADXL343_REG_INT_SOURCE, I2C_MEMADD_SIZE_8BIT, &interruptSource, 1, HAL_MAX_DELAY) != 0)
	{
		return 1;
	}
	return 0;
}

uint8_t ADXL343_ReadAcceleration(ADXL343_InstanceDef_t *Instance)
{
	uint8_t data[6];

	if (Instance == NULL)
	{
		return 1;
	}

	if (ADXL343_I2C_Read(Instance, ADXL343_REG_DATAX0, data, 6) != 0)
	{
		return 2;
	}

	// Lire les données brutes pour chaque axe
	int16_t rawX = (int16_t)((data[1] << 8) | data[0]);
	int16_t rawY = (int16_t)((data[3] << 8) | data[2]);
	int16_t rawZ = (int16_t)((data[5] << 8) | data[4]);

	// Convertir en mg (float)
	Instance->accX = (rawX)/32.0;
	Instance->accY = (rawY)/32.0;
	Instance->accZ = (rawZ)/32.0;

	return 0;
}

uint8_t ADXL343_SetTapThreshold(ADXL343_InstanceDef_t *Instance, uint8_t threshold)
{
	if (ADXL343_I2C_Write(Instance, ADXL343_REG_THRESH_TAP, &threshold, 1) != 0)
	{
		return 1;
	}
	return 0;
}

uint8_t ADXL343_SetTapDuration(ADXL343_InstanceDef_t *Instance, uint8_t duration)
{
	if (ADXL343_I2C_Write(Instance, ADXL343_REG_DUR, &duration, 1) != 0)
	{
		return 1;
	}
	return 0;
}
