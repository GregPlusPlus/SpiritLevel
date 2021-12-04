#ifndef SPRITE_H
#define SPRITE_H

#include "bmp.h"
#include "ssd1306.h"

typedef struct {
    BMP_t *BMP_B;
    BMP_t *BMP_W;
} Sprite_t;

int SPRITE_load(Sprite_t *s, const char *fn_b, const char *fn_w);
int SPRITE_blit(Sprite_t *s, uint8_t x, uint8_t y);
void SPRITE_free(Sprite_t *s);

#endif // SPRITE_H