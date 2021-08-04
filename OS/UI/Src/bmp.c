#include "bmp.h"

static size_t readBuff(uint8_t *v, size_t s);
static void readNext(uint8_t *v);
static void jumpTo(size_t pos);
static void putpixel(uint32_t x, uint32_t y, bool color);

static uint16_t read16(void);
static uint32_t read32(void);
static void buildPalette(BMP_t *bmp);
static uint8_t getBit(uint8_t i, uint8_t N);

static FIL *fp = NULL;
void BMP_setFile(FIL *_fp) {
    fp = _fp;
}


size_t readBuff(uint8_t *v, size_t s) {
    size_t br;

    f_read (fp, (char*)v, s, &br);

    return br;
}

void readNext(uint8_t *v) {
    readBuff(v, 1);
}

void jumpTo(size_t pos) {
    f_lseek(fp, pos);
}

void putpixel(uint32_t x, uint32_t y, bool color) {
    ssd1306_DrawPixel(x, y, color);
}

void BMP_zeroBMP(BMP_t *bmp) {
    memset(bmp, 0x00, sizeof(BMP_t));
}

BMP_Err_t BMP_parseFile(BMP_t *bmp) {
    BMP_Err_t err = 0;

    bmp->ID                  = read16();
    bmp->fileSize            = read32();
    bmp->appID               = read32();
    bmp->dataOffset          = read32();
    bmp->DIBHeaderSize       = read32();
    bmp->w                   = read32();
    bmp->h                   = read32();
    bmp->planeNumber         = read16();
    bmp->bitsPerPixel        = read16();
    bmp->compression         = read32();
    bmp->rawBMPDataSize      = read32();
    bmp->PPMH                = read32();
    bmp->PPMV                = read32();
    bmp->colorsInPalette     = read32();
    bmp->importantColors     = read32();

    if(bmp->rawBMPDataSize == 0) {
        bmp->rawBMPDataSize = bmp->fileSize - bmp->dataOffset;
    }

    err = BMP_check(bmp);

    if(err) {
        return err;
    }

    buildPalette(bmp);

    bmp->data = (uint8_t*)malloc(bmp->rawBMPDataSize);

    return err;
}

void buildPalette(BMP_t *bmp) {
    bmp->BWPalette[0] = 0;
    bmp->BWPalette[1] = 1;

    if(bmp->colorsInPalette == 0) {
        return;
    }

    jumpTo(0x36);
    bmp->BWPalette[0] = (read32() & 0x00FFFFFF)?1:0;
    jumpTo(0x3A);
    bmp->BWPalette[1] = (read32() & 0x00FFFFFF)?1:0;
}

BMP_Err_t BMP_check(BMP_t *bmp) {
    int res = 0;

    if(bmp->ID != 0x4D42) {
        res = BMP_Err_Bad_Signature;
    }

    if(bmp->bitsPerPixel > 1 || bmp->compression != 0) {
        res = BMP_Err_Not_BW;
    }

    if(bmp->colorsInPalette != 0 && bmp->colorsInPalette != 2) {
        res = BMP_Err_Invalid_Palette;
    }

    return res;
}

BMP_Err_t BMP_readData(BMP_t *bmp) {
    BMP_Err_t err = BMP_Err_OK;

    jumpTo(bmp->dataOffset);

    if(readBuff(bmp->data, bmp->rawBMPDataSize) != bmp->rawBMPDataSize) {
        err = BMP_Err_Data_Read;
    }

    return err;
}

void BMP_release(BMP_t *bmp) {
    free(bmp->data);
}

BMP_Err_t BMP_blit(BMP_t *bmp, uint32_t _x, uint32_t _y) {
    if(!bmp->data) {
        return BMP_Err_Empty_Data;
    }

    uint32_t lineWidth = bmp->w / 8;
    if(bmp->w % 8) {
        lineWidth += 1;
    }

    uint32_t BMPLineWidth;
    BMPLineWidth = ((lineWidth / 4) * 4);
    if(lineWidth % 4) {
        BMPLineWidth += 4;
    }

    for(uint32_t y = 0; y < bmp->h; y ++) {
        uint32_t BMPLine = bmp->h - (y + 1);
        uint32_t lineByteOffset = BMPLine * BMPLineWidth;

        for(uint32_t x = 0; x < bmp->w; x ++) {
            uint32_t offsetInLine = x / 8;
            uint32_t i = lineByteOffset + offsetInLine;
            uint8_t bitIndex = 7 - (x % 8);

            uint8_t byte = bmp->data[i];

            putpixel(_x + x, _y + y, bmp->BWPalette[getBit(bitIndex, byte)]);
        }
    }

    return 0;
}


uint8_t getBit(uint8_t i, uint8_t N) {
    return (N >> i) & 0x01;
}

uint16_t read16(void) {
    uint16_t v = 0;

    for(uint8_t i = 0; i < 2; i ++) {
        readNext((uint8_t*)(&v) + i);
    }

    return v;
}

uint32_t read32(void) {
    uint32_t v = 0;

    for(uint8_t i = 0; i < 4; i ++) {
        readNext((uint8_t*)(&v) + i);
    }

    return v;
}
