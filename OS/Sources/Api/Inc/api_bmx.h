#ifndef API_BMX_H
#define API_BMX_H

#include "i2c.h"

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define API_BMX_ACC_ADDR    0x18
#define API_BMX_GYR_ADDR    0x68
#define API_BMX_MAG_ADDR    0x10

void        API_BMX_ACC_Reset(void);
void        API_BMX_ACC_SetRange(uint8_t range);
uint8_t     API_BMX_ACC_GetRange(void);
float       API_BMX_ACC_GetQuantum(void);
int16_t     API_BMX_ACC_Axis(bool *avail, uint8_t startReg);
int16_t     API_BMX_ACC_X(bool *avail);
int16_t     API_BMX_ACC_Y(bool *avail);
int16_t     API_BMX_ACC_Z(bool *avail);
float       API_BMX_GetTilt(bool *avail);

void        API_BMX_MAG_Reset(void);
uint8_t     API_BMX_MAG_ReadReg(uint8_t reg);
void        API_BMX_MAG_WriteReg(uint8_t reg, uint8_t bits);
uint8_t     API_BMX_MAG_ReadCTRLBits(void);
void        API_BMX_MAG_WriteCTRLBits(uint8_t bits);
uint8_t     API_BMX_MAG_getChipID(void);
uint8_t     API_BMX_MAG_GetRate(void);
void        API_BMX_MAG_SetRate(uint8_t rate);
uint8_t     API_BMX_MAG_GetRepXY(void);
void        API_BMX_MAG_SetRepXY(uint8_t rep);
uint16_t    API_BMX_MAG_GetVal(uint8_t startReg);
uint8_t     API_BMX_MAG_GetMode(void);
void        API_BMX_MAG_SetMode(uint8_t mode);
void        API_BMX_MAG_ToggleSelfTest(bool selfTest);
uint8_t     API_BMX_MAG_SelfTest(void);
int16_t     API_BMX_MAG_X(void);
int16_t     API_BMX_MAG_Y(void);
int16_t     API_BMX_MAG_Z(void);

#endif // API_BMX_H