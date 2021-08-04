#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "fatfs.h"
#include "sdio.h"
#include "stm32f4xx_hal_sd.h"

void UTILS_getStorageUsage(uint32_t *free, uint32_t *total);
bool UTILS_checkExtension(char *fn, char *ext);
uint8_t UTILS_readFile8(FIL *f);
uint16_t UTILS_readFile16(FIL *f);
uint32_t UTILS_readFile32(FIL *f);

#endif // UTILS_H