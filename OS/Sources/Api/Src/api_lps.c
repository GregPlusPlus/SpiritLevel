#include "api_lps.h"

void API_LPS_Reset(void) {
    API_LPS_Write(0x11, 0x04);      // Reset
    API_LPS_Write(0x11, 0x80);      // Reboot reg
    API_LPS_Write(0x10, 0x00);      // Set one shot mode
}

void API_LPS_Write(uint8_t addr, uint8_t bits) {
    HAL_I2C_Mem_Write(&hi2c1, API_LPS_ADDR << 1, addr, 1, &bits, 1, 100);
}

uint8_t API_LPS_Read(uint8_t addr) {
    uint8_t bits = 0x00;

    HAL_I2C_Mem_Read(&hi2c1, API_LPS_ADDR << 1, addr, 1, &bits, 1, 100);

    return bits;
}
void API_LPS_OneShot(void) {
    API_LPS_Write(0x11, 0x80);      // Reboot reg
    API_LPS_Write(0x11, 0x01);      // Trigger read
}

int32_t API_LPS_GetPressure(void) {
    uint32_t data = 0;

    while(!(API_LPS_Read(0x27) & 0x01));            // Wait for pressure data

    // Reading pressure
    data |= API_LPS_Read(0x28);
    data |= ((uint32_t)API_LPS_Read(0x29) << 8);
    data |= ((uint32_t)API_LPS_Read(0x2A) << 16);

    if(data & 0x00800000) {
        data |= 0xFF000000;
    }

    return (int32_t)data;
}

int16_t API_LPS_GetOffsetPressure(void) {
    uint16_t data = 0;

    // Reading referrence pressure
    data |= API_LPS_Read(0x18);
    data |= ((uint16_t)API_LPS_Read(0x19) << 8);

    return (int16_t)data;
}

int16_t API_LPS_GetTemp(void) {
    uint16_t temp = 0;

    while(!(API_LPS_Read(0x27) & 0x02));            // Wait for pressure data

    // Reading temperature
    temp |= API_LPS_Read(0x2B);
    temp |= ((uint16_t)API_LPS_Read(0x2C) << 8);

    return (int16_t)temp;
}
