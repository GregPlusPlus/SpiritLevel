#ifndef API_SHT_H
#define API_SHT_H

#include "i2c.h"

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define API_SHT_ADDR        0x40

void        API_SHT_Reset(void);
void        API_SHT_Write(uint8_t bits);
uint8_t     API_SHT_Read(void);
uint8_t     API_SHT_ReadUsrReg(void);
uint32_t    API_SHT_ReadVal(uint8_t command);
uint32_t    API_SHT_ReadTemp(void);
float       API_SHT_GetTemp(void);
uint32_t    API_SHT_ReadRH(void);
float       API_SHT_GetRH(void);

#endif // API_SHT_H