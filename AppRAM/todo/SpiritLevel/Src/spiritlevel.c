#include "spiritlevel.h"

#define DELTA 1.5f
#define MEAN_SIZE 8

static App_t a = {.name = "Spirit level", .init = SpiritLevel_Init, .loop = SpiritLevel_Loop};

static uint32_t t = 0;
static float quantum = 1;
static bool hold = false;
static BMP_t bmp;

static void initUI(void);
static void drawBubble(float tilt);
static float computeMean(float val);

App_t *SpiritLevel_GetApp(void) {
    return &a;
}

void SpiritLevel_Init(void) {
    hold = false;
    t = HAL_GetTick();
    API_BMX_ACC_Reset();
    API_BMX_ACC_SetRange(4);
    quantum = API_BMX_ACC_GetQuantum();

    f_mount(&SDFatFS, "/", 1);

    initUI();
}

void SpiritLevel_Loop(void) {
    if(API_getLastEvents() & EV_PB_MID) {
        API_IO_SetLED(false);

        BMP_release(&bmp);

        API_Quit();

        return;
    }

    if(API_getLastEvents() & EV_PB_RIGHT) {
        hold = !hold;
    }

    if((HAL_GetTick() - t) >= 50) {
        t = HAL_GetTick();

        bool avail = false;

        float accZ = API_BMX_ACC_Z(&avail) * quantum / 1000.f;

        if(!avail) {
            return;
        }

        if(!hold) {
            if(fabs(accZ) < .2f) {
                float currTilt = API_BMX_GetTilt(&avail);

                if(!avail) {
                    return;
                }

                float meanTilt = computeMean(currTilt);

                API_IO_SetLED(fabs(meanTilt) < DELTA);

                static char buffer[50];
                snprintf(buffer, sizeof(buffer), "%0.2f deg", meanTilt);

                int textX = (SSD1306_WIDTH / 2) - (ssd1306_GetTextWidth(Font_11x18, buffer) / 2);

                ssd1306_Fill(Black);
                ssd1306_SetCursor(textX, 15);
                ssd1306_WriteString(buffer, Font_11x18, White);
                drawBubble(meanTilt);
                ssd1306_UpdateScreen();
            } else {
                ssd1306_Fill(Black);
                /*ssd1306_SetCursor(0, 0);
                ssd1306_WriteString("Hold the\ncard\nstraight.", Font_11x18, White);*/
                BMP_blit(&bmp, 0, 0);
                ssd1306_UpdateScreen();
            }
        } else {
            ssd1306_SetCursor(46, 0);
            ssd1306_WriteString("HOLD", Font_7x10, White);
            ssd1306_UpdateScreen();
        }
    }
}

void initUI(void) {
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);

    FIL fil;

    BMP_zeroBMP(&bmp);

    if(f_open(&fil, "apps/spiritlevel/card_up.bmp", FA_READ) != FR_OK) {
        return;
    }

    BMP_setFile(&fil);

    BMP_Err_t err;
    err = BMP_parseFile(&bmp);

    if(err) {
        return;
    }
    
    BMP_readData(&bmp);
    
    f_close(&fil);
}

float computeMean(float val) {
    static float mean[MEAN_SIZE];
    memset(mean, 0, MEAN_SIZE);

    for(size_t i = 0; i < (MEAN_SIZE - 1); i ++) {
        mean[i] = mean[i + 1];
    }
    mean[MEAN_SIZE - 1] = val;

    float meanTilt = 0;

    for(size_t i = 0; i < MEAN_SIZE; i ++) {
        meanTilt += mean[i];
    }

    meanTilt = meanTilt / (float)MEAN_SIZE;

    return meanTilt;
}

void drawBubble(float tilt) {
    static float x = 0;
    static const int y = 44;
    static const int w = 90;
    static const int startx = (SSD1306_WIDTH / 2) - (w / 2);

    float force = cosf((tilt / 360.f)* 2 * M_PI) * 5;
    int dir = 0;
    if(tilt > 0) {
        dir = -1;
    } else if(tilt < 0) {
        dir = 1;
    }

    if(fabs(tilt) < DELTA) {
        if(x < (w  / 2)) {
            if((x + 3) < (w / 2)) {
                x += 3;
            } else {
                x = (w / 2);
            }
        } else if(x > (w / 2)) {
            if((x - 3) > (w / 2)) {
                x -= 3;
            } else {
                x = (w / 2);
            }
        }
    } else {
        x += (force * dir);
    }

    if(x > w) {
        x = w;
    }
    if(x < 0) {
        x = 0;
    }

    ssd1306_DrawCircle( x + startx,         y,      3,  White);
    ssd1306_DrawPixel(  x + startx + 1,     y - 1,      White);

    //ssd1306_DrawRectangle(startx - 3, y - 4, startx + w + 3, y + 4, White);
    ssd1306_Line(startx, y - 4, startx + w,  y - 4, White);
    ssd1306_Line(startx, y + 4, startx + w,  y + 4, White);
    ssd1306_DrawArc(startx, y, 4, 180, 180, White);
    ssd1306_DrawArc(startx + w, y, 4, 0, 180, White);

    ssd1306_Line(SSD1306_WIDTH / 2, y - 4, SSD1306_WIDTH / 2, y - 3, White);
    ssd1306_Line(SSD1306_WIDTH / 2, y + 4, SSD1306_WIDTH / 2, y + 3, White);
}
