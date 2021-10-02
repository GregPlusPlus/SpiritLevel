#ifndef API_LPS_H
#define API_LPS_H

#include "i2c.h"

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define API_LPS_ADDR    0x5C

void API_LPS_Reset(void);

void API_LPS_Write(uint8_t addr, uint8_t bits);
uint8_t API_LPS_Read(uint8_t addr);

void API_LPS_OneShot(void);
int32_t API_LPS_GetPressure(void);
int16_t API_LPS_GetOffsetPressure(void);
int16_t API_LPS_GetTemp(void);

#endif // API_LPS_H