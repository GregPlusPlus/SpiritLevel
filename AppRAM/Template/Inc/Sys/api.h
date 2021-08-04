#ifndef API_H
#define API_H

#include <stdint.h>
#include <stdbool.h>

#include "ff.h"

typedef enum {
    EV_NONE         = 0x00,
    EV_PB_LEFT      = 0x01,
    EV_PB_MID       = 0x02,
    EV_PB_RIGHT     = 0x04
} Event_t;

extern uint32_t (*API_hook)(uint32_t id);
extern uint32_t (*sysTick)(void);
extern Event_t (*API_getLastEvents)(void);
extern void (*API_updateEvents)(void);
extern void (*API_Quit)(void);

extern void (*API_DispERROR)(char *str);

extern void (*API_IO_SetFlashlight)(uint8_t value);
extern void (*API_IO_SetLED)(bool state);
extern void (*API_IO_ToggleLED)(void);
extern bool (*API_IO_ReadPB1)(void);
extern bool (*API_IO_ReadPB2)(void);
extern bool (*API_IO_ReadPB3)(void);

extern uint16_t (*API_ADC_ReadA0)(void);

extern uint32_t (*API_RNG_GetEntropy)(void);
extern void (*API_RNG_Init)(void);
extern int32_t (*API_RNG_randRange)(int32_t min, int32_t max);

extern FATFS *SDFatFS;

extern void (*Delay)(uint32_t ms);

extern int (*core_snprintf)(char *s, size_t n, const char * format, ...);

#endif