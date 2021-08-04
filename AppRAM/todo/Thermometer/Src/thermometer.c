#include "thermometer.h"

static App_t a = {.name = "Thermometer", .init = Thermometer_Init, .loop = Thermometer_Loop};

static uint32_t t = 0;
static int ranges[4][2] =   {{-40, 0},
                            {   0, 15 },
                            {  15, 50 },
                            {  50, 125}};
static BMP_t bmp;

#define RANGES_N (sizeof(ranges) / sizeof(int) / 2)

static void initUI(void);
static void drawThermometer(float temp);
static int *getRange(float temp);
static void drawRHBar(float RH);

App_t *Thermometer_GetApp(void) {
    return &a;
}

void Thermometer_Init(void) {
    API_SHT_Reset();

    f_mount(&SDFatFS, "/", 1);

    initUI();
}

void Thermometer_Loop(void) {
    if(API_getLastEvents() & EV_PB_MID) {
        API_Quit();
    }

    if((HAL_GetTick() - t) >= 500) {
        t = HAL_GetTick();

        char buff[50];
        float temp = API_SHT_GetTemp();
        float RH = API_SHT_GetRH();

        snprintf(buff, sizeof(buff), "%.3f'C", temp);

        uint8_t x = (SSD1306_WIDTH / 2) - (ssd1306_GetTextWidth(Font_11x18, buff) / 2);

        ssd1306_Fill(Black);
        ssd1306_SetCursor(x - 15, 20);
        ssd1306_WriteString(buff, Font_11x18, White);
        drawThermometer(temp);
        ssd1306_SetCursor(x - 15, 40);
        snprintf(buff, sizeof(buff), "RH: %.3f%%", RH);
        ssd1306_WriteString(buff, Font_6x8, White);
        drawRHBar(RH);
        ssd1306_UpdateScreen();
    }
}

void initUI(void) {
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);

    FIL fil;

    BMP_zeroBMP(&bmp);

    if(f_open(&fil, "apps/thermometer/ther.bmp", FA_READ) != FR_OK) {
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

void drawThermometer(float temp) {
    int *range;
    char buff[10];

    range = getRange(temp);

    if(!range) {
        return;
    }

    snprintf(buff, sizeof(buff), "%d", range[1]);
    ssd1306_SetCursor(90, 7);
    ssd1306_WriteString(buff, Font_6x8, White);
    snprintf(buff, sizeof(buff), "%d", range[0]);
    ssd1306_SetCursor(90, 50);
    ssd1306_WriteString(buff, Font_6x8, White);

    BMP_blit(&bmp, 105, 6);

    int h = (float)(temp - range[0]) / (float)(range[1] - range[0]) * 38.f;

    for(int i = 0; i < 3; i++) {
        ssd1306_Line(109 + i, 46, 109 + i, 46 - h, White);
    }
}

int *getRange(float temp) {
    for(size_t i = 0; i < RANGES_N; i++) {
        if(temp >= ranges[i][0] && temp < ranges[i][1]) {
            return ranges[i];
        }
    }

    return NULL;
}

static void drawRHBar(float RH) {
    int h = RH / 100.f * 46;

    ssd1306_Line(121, 54, 121, 54 - h, White);
    ssd1306_Line(122, 54, 122, 54 - h, White);
}
