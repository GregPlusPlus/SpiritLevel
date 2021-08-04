#ifndef API_SHT_H
#define API_SHT_H

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define API_SHT_ADDR        0x40

extern void        (*API_SHT_Reset)(void);
extern void        (*API_SHT_Write)(uint8_t bits);
extern uint8_t     (*API_SHT_Read)(void);
extern uint8_t     (*API_SHT_ReadUsrReg)(void);
extern uint32_t    (*API_SHT_ReadVal)(uint8_t command);
extern uint32_t    (*API_SHT_ReadTemp)(void);
extern float       (*API_SHT_GetTemp)(void);
extern uint32_t    (*API_SHT_ReadRH)(void);
extern float       (*API_SHT_GetRH)(void);

#endif // API_SHT_H