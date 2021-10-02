#include "api_sht.h"

void API_SHT_Reset(void) {
    API_SHT_Write(0xFE);

    HAL_Delay(100);
}

void API_SHT_Write(uint8_t bits) {
    HAL_I2C_Master_Transmit(&hi2c1, API_SHT_ADDR << 1, &bits, 1, 100);
}

uint8_t API_SHT_Read(void) {
    uint8_t bits = 0x00;

    HAL_I2C_Master_Receive(&hi2c1, API_SHT_ADDR << 1, &bits, 1, 100);

    return bits;
}

uint8_t API_SHT_ReadUsrReg(void) {
    API_SHT_Write(0xE7);
    return API_SHT_Read();
}

uint32_t API_SHT_ReadVal(uint8_t command) {
    uint32_t val;

    API_SHT_Write(command);

    HAL_Delay(100);

    HAL_I2C_Master_Receive(&hi2c1, API_SHT_ADDR << 1, ((uint8_t*)(&val)), 3, 100);

    return val;
}

uint32_t API_SHT_ReadTemp(void) {
    return API_SHT_ReadVal(0xE3);
}

float API_SHT_GetTemp(void) {
    uint8_t raw[3];
    *(uint32_t*)(raw) = API_SHT_ReadTemp();

    uint16_t temp_16 = ((uint16_t)raw[0] << 8) | raw[1];
    temp_16 &= ~0x0003;
    return -46.85f + (175.72f * ((float)temp_16 / 65536.f));
}

uint32_t API_SHT_ReadRH(void) {
    return API_SHT_ReadVal(0xE5);
}

float API_SHT_GetRH(void) {
    uint8_t raw[3];
    *(uint32_t*)(raw) = API_SHT_ReadRH();

    uint16_t RH_16 = ((uint16_t)raw[0] << 8) | raw[1];
    RH_16 &= ~0x0003;
    return -6.f + (125.f * ((float)RH_16 / 65536.f));
}
