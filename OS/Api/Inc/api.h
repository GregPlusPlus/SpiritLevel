#ifndef API_H
#define API_H

#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"
#include "ssd1306.h"
#include "swo.h"

#include "api_bmx.h"
#include "api_sht.h"
#include "api_lps.h"
#include "apps.h"

#include "event.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

Event_t API_getLastEvents(void);
void API_updateEvents(void);

void API_Quit(void);

void API_DispERROR(const char *format, ...);

void API_setPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period, uint16_t pulse);
void API_I2C_Scan(I2C_HandleTypeDef *hi2c, bool addrList[128]);

void API_IO_SetFlashlight(uint8_t value);
void API_IO_SetLED(bool state);
void API_IO_ToggleLED(void);
bool API_IO_ReadPB1(void);
bool API_IO_ReadPB2(void);
bool API_IO_ReadPB3(void);

uint16_t API_ADC_ReadA0(void);

uint32_t API_RNG_GetEntropy(void);
void API_RNG_Init(void);
int32_t API_RNG_randRange(int32_t min, int32_t max);

#endif