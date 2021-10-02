#ifndef BMP_H
#define BMP_H

#include "ssd1306.h"
#include "fatfs.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
	uint16_t ID;
	uint32_t fileSize;
	uint32_t appID;
	uint32_t dataOffset;
	uint32_t DIBHeaderSize;
	uint32_t w;
	uint32_t h;
	uint16_t planeNumber;
	uint16_t bitsPerPixel;
	uint32_t compression;
	uint32_t rawBMPDataSize;
	uint32_t PPMH;
	uint32_t PPMV;
	uint32_t colorsInPalette;
	uint32_t importantColors;

	bool BWPalette[2];

	uint8_t *data;
} BMP_t;

typedef enum {
	BMP_Err_OK				= 0,
	BMP_Err_Bad_Signature	= -1,
	BMP_Err_Not_BW			= -2,
	BMP_Err_Invalid_Palette	= -3,
	BMP_Err_Empty_Data		= -4,
	BMP_Err_Data_Read		= -5,
	BMP_Err_IO				= -6
} BMP_Err_t;

typedef enum {
	BMP_Alpha_Color_Black = 0,
	BMP_Alpha_Color_White = 1,
	BMP_Alpha_Color_None = 2
} BMP_Alpha_Color_t;

void BMP_setFile(FIL *_fp);

void BMP_zeroBMP(BMP_t *bmp);
BMP_Err_t BMP_parseFile(BMP_t *bmp);
BMP_Err_t BMP_check(BMP_t *bmp);
BMP_Err_t BMP_readData(BMP_t *bmp);
BMP_Err_t BMP_blit(BMP_t *bmp, uint32_t _x, uint32_t _y);
void BMP_setAlphaColor(BMP_Alpha_Color_t color);
void BMP_release(BMP_t *bmp);

#endif // BMP_H