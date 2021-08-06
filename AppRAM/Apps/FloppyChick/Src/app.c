#include "app.h"

BMP_t spriteTube;
BMP_t spriteTubeTop;
BMP_t spriteChick;
BMP_t spriteChickAlpha;
BMP_t spriteChickUp;
BMP_t spriteChickUpAlpha;
BMP_t spriteGameOver;
BMP_t spriteBG;

void app_main(void) {
    uint32_t t = 0;
    Tube_t tubes[NTUBES];
    Chick_t chick;
    uint32_t x = 0;
    int32_t xBG = 0;

    API_RNG_Init();
    f_mount(SDFatFS, "/", 1);

    if(!loadSprites()) {
        return;
    }

    while(1) {
        initTubes(tubes, NTUBES);

        chick.w = spriteChick.w;
        chick.h = spriteChick.h;
        chick.x = SSD1306_WIDTH / 2;
        chick.y = 10;
        chick.v = .1;

        x = 0;
        xBG = 0;

        while(1) {
            API_updateEvents();

            Event_t ev = API_getLastEvents();

            if(ev & EV_PB_LEFT) {
                return;
            }

            if(ev & EV_PB_RIGHT) {
                while(!(API_getLastEvents() & EV_PB_MID)) API_updateEvents();
            }

            if((sysTick() - t) >= 1) {
                t = sysTick();

                update(ev, tubes, NTUBES, &chick, xBG);

                if((chick.y + chick.h) >= 64 || chick.y <= 0) {
                    break;
                }

                if(hasCrashed(tubes, NTUBES, &chick)) {
                    break;
                }

                x ++;
                
                if((x % 2)) {
                    xBG --;

                    if(xBG == -128) {
                        xBG = 0;
                    }
                }

                dispPoints(x);

                ssd1306_UpdateScreen();
            }
        }

        dispGameOver(x);

        while(1) {
            API_updateEvents();

            Event_t ev = API_getLastEvents();

            if(ev & EV_PB_LEFT) {
                return;
            }

            if(ev & EV_PB_MID) {
                break;
            }
        }
    }
}

bool loadSprites(void) {
    if(loadSprite("apps/FloppyChick/rc/tube.bmp", &spriteTube)) {
        return false;
    }

    if(loadSprite("apps/FloppyChick/rc/tubetop.bmp", &spriteTubeTop)) {
        return false;
    }

    if(loadSprite("apps/FloppyChick/rc/chick.bmp", &spriteChick)) {
        return false;
    }

    if(loadSprite("apps/FloppyChick/rc/chick_alpha.bmp", &spriteChickAlpha)) {
        return false;
    }

    if(loadSprite("apps/FloppyChick/rc/chick_up.bmp", &spriteChickUp)) {
        return false;
    }

    if(loadSprite("apps/FloppyChick/rc/chick_up_alpha.bmp", &spriteChickUpAlpha)) {
        return false;
    }

    if(loadSprite("apps/FloppyChick/rc/gameover.bmp", &spriteGameOver)) {
        return false;
    }

    if(loadSprite("apps/FloppyChick/rc/bg.bmp", &spriteBG)) {
        return false;
    }

    return true;
}

BMP_Err_t loadSprite(const char *fn, BMP_t *bmp) {
    FIL fil;

    BMP_zeroBMP(bmp);

    if(f_open(&fil, fn, FA_READ) != FR_OK) {
        return -6;
    }

    BMP_setFile(&fil);

    BMP_Err_t err;
    err = BMP_parseFile(bmp);

    if(err) {
        return err;
    }
    
    err = BMP_readData(bmp);

    if(err) {
        return err;
    }

    f_close(&fil);

    return err;
}

void initTubes(Tube_t *tubes, size_t nTubes) {
    for(size_t i = 0; i < nTubes; i ++) {
        tubes[i].openingTop = generateOpening();
        tubes[i].x = i * SPACING + 200;
    }
}

uint8_t generateOpening(void) {
    return API_RNG_randRange(spriteTubeTop.h, 64 - OPENING_H - spriteTubeTop.h);
}

void dispPoints(uint32_t x) {
    char buff[50];

    snprintf(buff, sizeof(buff), "%lu pts", x);

    ssd1306_SetCursor(5, 5);
    ssd1306_WriteString(buff, *Font_7x10, White);
}

void dispGameOver(uint32_t x) {
    char buff[50];

    snprintf(buff, sizeof(buff), "%lu points", x);

    for(uint8_t i = SSD1306_HEIGHT; i > 0; i --) {
        BMP_blit(&spriteGameOver, 0, i - 1);
        ssd1306_UpdateScreen();
    }

    int tw = ssd1306_GetTextWidth(*Font_7x10, buff);

    ssd1306_SetCursor(SSD1306_WIDTH / 2 - tw / 2, 40);
    ssd1306_WriteString(buff, *Font_7x10, White);

    ssd1306_UpdateScreen();
}

void update(Event_t ev, Tube_t *tubes, size_t nTubes, Chick_t *chick, int32_t xBG) {
    updateTubes(tubes, nTubes);
    fly(ev, chick);
    
    ssd1306_Fill(Black);

    uint8_t yBG = (SSD1306_HEIGHT - spriteBG.h);

    BMP_setAlphaColor(BMP_Alpha_Color_Black);
    BMP_blit(&spriteBG, xBG, yBG);
    BMP_blit(&spriteBG, xBG + 128, yBG);
    BMP_setAlphaColor(BMP_Alpha_Color_None);

    drawTubes(tubes, nTubes);

    
    if(chick->v >= 0) {
        BMP_setAlphaColor(BMP_Alpha_Color_White);
        BMP_blit(&spriteChickAlpha, chick->x, chick->y);
        BMP_setAlphaColor(BMP_Alpha_Color_Black);
        BMP_blit(&spriteChick, chick->x, chick->y);
    } else {
        BMP_setAlphaColor(BMP_Alpha_Color_White);
        BMP_blit(&spriteChickUpAlpha, chick->x, chick->y);
        BMP_setAlphaColor(BMP_Alpha_Color_Black);
        BMP_blit(&spriteChickUp, chick->x, chick->y);
    }
    BMP_setAlphaColor(BMP_Alpha_Color_None);

    ssd1306_Line(0, 0, SSD1306_WIDTH, 0, White);
    ssd1306_Line(0, SSD1306_HEIGHT - 1, SSD1306_WIDTH, SSD1306_HEIGHT - 1, White);
}

void drawTubes(Tube_t *tubes, size_t nTubes) {
    for(size_t i = 0; i < nTubes; i ++) {
        drawTube(tubes[i]);
    }
}

void drawTube(Tube_t tube) {
    for(uint8_t i = 0; i < tube.openingTop - spriteTubeTop.h; i ++) {
        BMP_blit(&spriteTube, tube.x + 2, i);
    }

    BMP_blit(&spriteTubeTop, tube.x, tube.openingTop - spriteTubeTop.h);

    for(uint8_t i = tube.openingTop + OPENING_H + spriteTubeTop.h; i < 64; i ++) {
        BMP_blit(&spriteTube, tube.x + 2, i);
    }

    BMP_blit(&spriteTubeTop, tube.x, tube.openingTop + OPENING_H);
}

void updateTubes(Tube_t *tubes, size_t nTubes) {
    for(size_t i = 0; i < nTubes; i ++) {
        tubes[i].x --;
    }

    rollTubes(tubes, nTubes);
}

void rollTubes(Tube_t *tubes, size_t nTubes) {
    if(tubes[0].x <= -TUBE_W) {
        for(size_t i = 1; i < nTubes; i ++) {
            tubes[i - 1] = tubes[i];
        }

        tubes[nTubes - 1].openingTop = generateOpening();
        tubes[nTubes - 1].x = tubes[nTubes - 2].x + SPACING;
    }
}

void fly(Event_t ev, Chick_t *chick) {
    if(ev & EV_PB_MID) {
        chick->v -= RISE_ACC;
    }

    chick->v += FALL_ACC;
    chick->y += chick->v;
}

bool hasCrashed(Tube_t *tubes, size_t nTubes, Chick_t *chick) {
    Point_t l1;
    Point_t r1;
    Point_t l2;
    Point_t r2;

    l1.x = chick->x + HITBOX_MARGIN;
    l1.y = chick->y + HITBOX_MARGIN;
    r1.x = chick->x + chick->w - (2 * HITBOX_MARGIN);
    r1.y = chick->y + chick->h - (2 * HITBOX_MARGIN);

    for(size_t i = 0; i < nTubes; i ++) {
        l2.x = tubes[i].x;
        l2.y = 0;
        r2.x = tubes[i].x + TUBE_W;
        r2.y = tubes[i].openingTop;

        if(rectOverlap(l1, r1, l2, r2)) {
            return true;
        }

        l2.x = tubes[i].x;
        l2.y = tubes[i].openingTop + OPENING_H;
        r2.x = tubes[i].x + TUBE_W;
        r2.y = 63;

        if(rectOverlap(l1, r1, l2, r2)) {
            return true;
        }
    }

    return false;
}

bool rectOverlap(Point_t l1, Point_t r1, Point_t l2, Point_t r2) {
    if (l1.x >= r2.x || l2.x >= r1.x){
        return false;
    }
 
    if (l1.y >= r2.y || l2.y >= r1.y){
        return false;
    }

    return true;
}
