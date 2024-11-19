#include "ADXL343.h"

static uint8_t ADXL343_I2C_Read(ADXL343_InstanceDef_t *Instance, uint8_t reg, uint8_t *buf, uint16_t size)
{
    if (Instance == NULL || buf == NULL || size == 0)
    {
        return 1;
    }
    if (HAL_I2C_Mem_Read(Instance->hi2c, ADXL343_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, buf, size, HAL_MAX_DELAY) != HAL_OK)
    {
        return 2;
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
        return 2;
    }
    return 0;
}

uint8_t ADXL343_Init(ADXL343_InstanceDef_t *Instance,I2C_HandleTypeDef *hi2c)
{
    if (Instance == NULL)
    {
        return 1;
    }

    Instance->hi2c = hi2c ;
    Instance->accX = 0 ;
    Instance->accY = 0 ;
    Instance->accZ = 0 ;

    uint8_t deviceID;
    uint8_t configData[1] = {0x08} ;
    if (ADXL343_I2C_Write(Instance, ADXL343_REG_POWER_CTL, configData, 1) != 0)
    {
        return 2;
    }
    HAL_Delay(10);

    if (ADXL343_I2C_Read(Instance, ADXL343_REG_DEVID, &deviceID, 1) != 0)
    {
        return 3;
    }
    if (deviceID != 0xE5)
    {
        return 4;
    }

    return 0;
}
uint8_t ADXL343_SetOffset(ADXL343_InstanceDef_t *Instance, int8_t ofsX, int8_t ofsY, int8_t ofsZ)
{
    uint8_t offsetData[3];
    offsetData[0] = ofsX;
    offsetData[1] = ofsY;
    offsetData[2] = ofsZ;

    if (ADXL343_I2C_Write(Instance, ADXL343_REG_OFSX, offsetData, 3) != 0)
    {
        return 1; 
    }
    return 0; 
}

uint8_t ADXL343_GetOffset(ADXL343_InstanceDef_t *Instance, int8_t *ofsX, int8_t *ofsY, int8_t *ofsZ)
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

uint8_t ADXL343_SetFIFO(ADXL343_InstanceDef_t *Instance, uint8_t mode)
{
    uint8_t configData[1] = {mode};
    if (ADXL343_I2C_Write(Instance, ADXL343_REG_FIFO_CTL, configData, 1) != 0)
    {
        return 1;
    }
    return 0;
}

uint8_t ADXL343_SetInterrupt(ADXL343_InstanceDef_t *Instance)
{
    uint8_t interruptMap = 0x80;
    if (ADXL343_I2C_Write(Instance, ADXL343_REG_INT_MAP, &interruptMap, 1) != 0)
    {
        return 2;
    }
    uint8_t interruptEnable = 0xC0;
    if (ADXL343_I2C_Write(Instance, ADXL343_REG_INT_ENABLE, &interruptEnable, 1) != 0)
    {
        return 1;
    }

    return 0;
}

uint8_t ADXL343_ClearInterrupt(ADXL343_InstanceDef_t *Instance)
{
    uint8_t interruptSource = 0;
    if (ADXL343_I2C_Read(Instance, ADXL343_REG_INT_SOURCE, &interruptSource, 1) != 0)
    {
        return 1;
    }
    return 0;
}

uint8_t ADXL343_ReadInterruptSource(ADXL343_InstanceDef_t *Instance)
{
    uint8_t interruptSource;
    if (ADXL343_I2C_Read(Instance, ADXL343_REG_INT_SOURCE, &interruptSource, 1) != 0)
    {
        return 1;
    }
    return interruptSource;
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

    Instance->accX = (int16_t)((data[1] << 8) | data[0]);
    Instance->accX = (int16_t)((data[3] << 8) | data[2]);
    Instance->accX = (int16_t)((data[5] << 8) | data[4]);

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
