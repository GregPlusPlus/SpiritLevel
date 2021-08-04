#ifndef API_BMX_H
#define API_BMX_H

#include <stdint.h>
#include <stdbool.h>

#define API_BMX_ACC_ADDR    0x18
#define API_BMX_GYR_ADDR    0x68
#define API_BMX_MAG_ADDR    0x10

extern void        (*API_BMX_ACC_Reset)(void);
extern void        (*API_BMX_ACC_SetRange)(uint8_t range);
extern uint8_t     (*API_BMX_ACC_GetRange)(void);
extern float       (*API_BMX_ACC_GetQuantum)(void);
extern int16_t     (*API_BMX_ACC_Axis)(bool *avail, uint8_t startReg);
extern int16_t     (*API_BMX_ACC_X)(bool *avail);
extern int16_t     (*API_BMX_ACC_Y)(bool *avail);
extern int16_t     (*API_BMX_ACC_Z)(bool *avail);
extern float       (*API_BMX_GetTilt)(bool *avail);

extern void        (*API_BMX_MAG_Reset)(void);
extern uint8_t     (*API_BMX_MAG_ReadReg)(uint8_t reg);
extern void        (*API_BMX_MAG_WriteReg)(uint8_t reg, uint8_t bits);
extern uint8_t     (*API_BMX_MAG_ReadCTRLBits)(void);
extern void        (*API_BMX_MAG_WriteCTRLBits)(uint8_t bits);
extern uint8_t     (*API_BMX_MAG_getChipID)(void);
extern uint8_t     (*API_BMX_MAG_GetRate)(void);
extern void        (*API_BMX_MAG_SetRate)(uint8_t rate);
extern uint8_t     (*API_BMX_MAG_GetRepXY)(void);
extern void        (*API_BMX_MAG_SetRepXY)(uint8_t rep);
extern uint16_t    (*API_BMX_MAG_GetVal)(uint8_t startReg);
extern uint8_t     (*API_BMX_MAG_GetMode)(void);
extern void        (*API_BMX_MAG_SetMode)(uint8_t mode);
extern void        (*API_BMX_MAG_ToggleSelfTest)(bool selfTest);
extern uint8_t     (*API_BMX_MAG_SelfTest)(void);
extern int16_t     (*API_BMX_MAG_X)(void);
extern int16_t     (*API_BMX_MAG_Y)(void);
extern int16_t     (*API_BMX_MAG_Z)(void);

#endif // API_BMX_H