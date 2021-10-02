#include "progressbar.h"

static uint8_t UI_Priv_Progressbar_GetProgressWidth(uint8_t w, uint32_t max, uint32_t value);

void UI_Progressbar_Init(Progressbar_t *pb, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint32_t max) {
    pb->x = x;
    pb->y = y;

    if(w < 10) {
        w = 10;
    }

    pb->w = w;

    if(h < 5) {
        h = 5;
    }

    pb->h = h;
    pb->max = max;
    pb->value = 0;
}

void UI_Progressbar_Setvalue(Progressbar_t *pb, uint32_t value) {
    pb->value = value;
}

void UI_Progressbar_Draw(Progressbar_t *pb) {
    uint8_t pw = UI_Priv_Progressbar_GetProgressWidth(pb->w, pb->max, pb->value);

    for(uint8_t i = 0; i <= pb->h; i ++) {
        ssd1306_Line(pb->x, pb->y + i, pb->x + pb->w, pb->y + i, Black);
    }

    ssd1306_DrawRectangle(pb->x, pb->y, pb->x + pb->w, pb->y + pb->h, White);

    for(uint8_t i = 2; i < (pb->h - 1); i ++) {
        ssd1306_Line(pb->x + 2, pb->y + i, pb->x + pw, pb->y + i, White);
    }
}

static uint8_t UI_Priv_Progressbar_GetProgressWidth(uint8_t w, uint32_t max, uint32_t value) {
    return (w - 2) * (float)((float)value / (float)max);
}
