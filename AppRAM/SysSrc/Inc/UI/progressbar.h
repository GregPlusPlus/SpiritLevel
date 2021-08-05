#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "ssd1306.h"

#include <stdint.h>

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t w;
    uint8_t h;
    uint32_t max;
    uint32_t value;
} Progressbar_t;

extern void (*UI_Progressbar_Init)(Progressbar_t *pb, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint32_t max);
extern void (*UI_Progressbar_Setvalue)(Progressbar_t *pb, uint32_t value);
extern void (*UI_Progressbar_Draw)(Progressbar_t *pb);

#endif // PROGRESSBAR_H