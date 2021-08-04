#include "api_bmx.h"

void API_BMX_ACC_Reset(void) {
    uint8_t b = 0xB6;
    HAL_I2C_Mem_Write(&hi2c1, API_BMX_ACC_ADDR << 1, 0x14, 1, &b, 1, 100);

    HAL_Delay(100);
}

void API_BMX_ACC_SetRange(uint8_t range) {
    uint8_t code = 0x00;

    switch(range) {
        case 2:
        code = 0x03;
        break;
        case 4:
        code = 0x05;
        break;
        case 8:
        code = 0x08;
        break;
        case 16:
        code = 0x0C;
        break;
        default:
        code = 0x03;
        break;
    }

    HAL_I2C_Mem_Write(&hi2c1, API_BMX_ACC_ADDR << 1, 0x0F, 1, &code, 1, 100);

    HAL_Delay(100);
}

uint8_t API_BMX_ACC_GetRange(void) {
    uint8_t range = 0;
    uint8_t res;

    HAL_I2C_Mem_Read(&hi2c1, API_BMX_ACC_ADDR << 1, 0x0F, 1, &range, 1, 100);

    switch(range & 0x0F) {
        case 3:
        res = 2;
        break;
        case 5:
        res = 4;
        break;
        case 8:
        res = 8;
        break;
        case 12:
        res = 16;
        break;
        default:
        res = 1;
        break;
    }

    return res;
}

float API_BMX_ACC_GetQuantum(void) {
    uint8_t range = 0;
    float res;

    HAL_I2C_Mem_Read(&hi2c1, API_BMX_ACC_ADDR << 1, 0x0F, 1, &range, 1, 100);

    switch(range & 0x0F) {
        case 3:
        res = 0.98f;
            break;
        case 5:
        res = 1.95f;
            break;
        case 8:
        res = 3.91f;
            break;
        case 12:
        res = 7.81;
            break;
        default:
        res = 1;
            break;
    }

    return res;
}

int16_t API_BMX_ACC_Axis(bool *avail, uint8_t startReg) {
    int16_t acc = 0;

    if(avail) {
        *avail = true;
    }

    HAL_I2C_Mem_Read(&hi2c1, API_BMX_ACC_ADDR << 1, startReg, 1, &((uint8_t*)(&acc))[0], 1, 100);

    if((acc & 0x01) == 0) {
        if(avail) {
        *avail = false;

        return 0;
        }
    }

    HAL_I2C_Mem_Read(&hi2c1, API_BMX_ACC_ADDR << 1, startReg + 1, 1, &((uint8_t*)(&acc))[1], 1, 100);

    acc >>= 4;

    return acc;
}

int16_t API_BMX_ACC_X(bool *avail) {
  return API_BMX_ACC_Axis(avail, 0x02);
}

int16_t API_BMX_ACC_Y(bool *avail) {
  return API_BMX_ACC_Axis(avail, 0x04);
}

int16_t API_BMX_ACC_Z(bool *avail) {
  return API_BMX_ACC_Axis(avail, 0x06);
}

float API_BMX_GetTilt(bool *avail) {
    int16_t accX = API_BMX_ACC_X(avail);
    if(avail) {
        if(!*avail) {
        return 0;
        }
    }

    int16_t accY = API_BMX_ACC_Y(avail);
    if(avail) {
        if(!*avail) {
        return 0;
        }
    }

    float tilt = (accX != 0)?atan((float)accY / (float)accX) / (2*M_PI) * 360:(accY > 0)?90:(accY < 0)?-90:0;

    return tilt;
}

void API_BMX_MAG_Reset(void) {
    API_BMX_MAG_WriteReg(0x4B, 0x83);

    API_BMX_MAG_WriteCTRLBits(0x00);

    HAL_Delay(100);
}

uint8_t API_BMX_MAG_ReadReg(uint8_t reg) {
    uint8_t bits;

    HAL_I2C_Mem_Read(&hi2c1, API_BMX_MAG_ADDR << 1, reg, 1, &bits, 1, 100);

    return bits;
}

void API_BMX_MAG_WriteReg(uint8_t reg, uint8_t bits) {
    HAL_I2C_Mem_Write(&hi2c1, API_BMX_MAG_ADDR << 1, reg, 1, &bits, 1, 100);
}

uint8_t API_BMX_MAG_ReadCTRLBits(void) {
    return API_BMX_MAG_ReadReg(0x4C);
}

void API_BMX_MAG_WriteCTRLBits(uint8_t bits) {
    API_BMX_MAG_WriteReg(0x4C, bits);
}

uint8_t API_BMX_MAG_getChipID(void) {
    return API_BMX_MAG_ReadReg(0x40);
}

uint8_t API_BMX_MAG_GetRate(void) {
    uint8_t bits = API_BMX_MAG_ReadCTRLBits();
    uint8_t rate;

    bits >>= 3;

    switch(bits & 0x07) {
        case 0:
        rate = 10;
            break;
        case 1:
        rate = 2;
            break;
        case 2:
        rate = 6;
            break;
        case 3:
        rate = 8;
            break;
        case 4:
        rate = 15;
            break;
        case 5:
        rate = 20;
            break;
        case 6:
        rate = 25;
            break;
        case 7:
        rate = 30;
            break;
        default:
        rate = 0;
            break;
    }

    return rate;
}

void API_BMX_MAG_SetRate(uint8_t rate) {
    uint8_t code;
    uint8_t bits = API_BMX_MAG_ReadCTRLBits();

    switch(rate) {
        case 10:
        code = 0x00;
            break;
        case 2:
        code = 0x01;
            break;
        case 6:
        code = 0x02;
            break;
        case 8:
        code = 0x03;
            break;
        case 15:
        code = 0x04;
            break;
        case 20:
        code = 0x05;
            break;
        case 25:
        code = 0x06;
            break;
        case 30:
        code = 0x07;
            break;
        default:
        code = 0x00;
            break;
    }

    bits &= 0xC7;
    bits |= (code << 3);

    API_BMX_MAG_WriteCTRLBits(bits);
}

uint8_t API_BMX_MAG_GetRepXY(void) {
    return API_BMX_MAG_ReadReg(0x51);
}

void API_BMX_MAG_SetRepXY(uint8_t rep) {
    API_BMX_MAG_WriteReg(0x51, rep);
}

uint16_t API_BMX_MAG_GetVal(uint8_t startReg) {
    uint16_t val = 0;

    HAL_I2C_Mem_Read(&hi2c1, API_BMX_MAG_ADDR << 1, startReg, 1, &((uint8_t*)(&val))[0], 1, 100);

    HAL_I2C_Mem_Read(&hi2c1, API_BMX_MAG_ADDR << 1, startReg + 1, 1, &((uint8_t*)(&val))[1], 1, 100);

    return val;
}

uint8_t API_BMX_MAG_GetMode(void) {
    uint8_t b = API_BMX_MAG_ReadReg(0x4C);

    b >>= 1;
    b &= 0x03;

    return b;
}

void API_BMX_MAG_SetMode(uint8_t mode) {
    uint8_t bits = API_BMX_MAG_ReadCTRLBits();

    bits &= 0xF9;
    bits |= ((mode & 0x03) << 1);

    API_BMX_MAG_WriteCTRLBits(bits);
}

void API_BMX_MAG_ToggleSelfTest(bool selfTest) {
    uint8_t bits = API_BMX_MAG_ReadCTRLBits();

    bits &= 0xFE;
    bits |= selfTest;

    API_BMX_MAG_WriteCTRLBits(bits);
}

uint8_t API_BMX_MAG_SelfTest(void) {
    uint8_t res = 0;

    uint8_t lastMode = API_BMX_MAG_GetMode();
    
    API_BMX_MAG_SetMode(0x03);
    API_BMX_MAG_ToggleSelfTest(1);

    HAL_Delay(200);

    res |= (API_BMX_MAG_ReadReg(0x42) & 0x01);
    res |= ((API_BMX_MAG_ReadReg(0x44) & 0x01) << 1);
    res |= ((API_BMX_MAG_ReadReg(0x46) & 0x01) << 2);

    API_BMX_MAG_SetMode(lastMode);

    return res;
}

int16_t API_BMX_MAG_X(void) {
    int16_t mag = API_BMX_MAG_GetVal(0x42);

    mag >>= 3;

    return mag;
}

int16_t API_BMX_MAG_Y(void) {
    int16_t mag = API_BMX_MAG_GetVal(0x44);

    mag >>= 3;

    return mag;
}

int16_t API_BMX_MAG_Z(void) {
    int16_t mag = API_BMX_MAG_GetVal(0x46);

    mag >>= 1;

    return mag;
}
