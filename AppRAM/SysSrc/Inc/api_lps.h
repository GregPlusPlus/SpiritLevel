#ifndef API_LPS_H
#define API_LPS_H

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define API_LPS_ADDR    0x5C

extern void (*API_LPS_Reset)(void);
extern void (*API_LPS_Write)(uint8_t addr, uint8_t bits);
extern uint8_t (*API_LPS_Read)(uint8_t addr);
extern void (*API_LPS_OneShot)(void);
extern int32_t (*API_LPS_GetPressure)(void);
extern int16_t (*API_LPS_GetOffsetPressure)(void);
extern int16_t (*API_LPS_GetTemp)(void);

#endif // API_LPS_H