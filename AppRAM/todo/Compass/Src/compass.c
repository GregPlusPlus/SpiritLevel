#include "compass.h"

static App_t a = {.name = "Compass", .init = Compass_Init, .loop = Compass_Loop};

static uint32_t t = 0;

App_t *Compass_GetApp(void) {
    return &a;
}

void Compass_Init(void) {
    API_BMX_MAG_Reset();
    HAL_Delay(200);

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    if(API_BMX_MAG_SelfTest() == 0x07) {
        ssd1306_WriteString("Self test OK", Font_7x10, White);
        ssd1306_UpdateScreen();
    } else {
        ssd1306_WriteString("Self test FAILED", Font_7x10, White);
        ssd1306_UpdateScreen();
        
        while(1);
    }

    API_BMX_MAG_Reset();
    API_BMX_MAG_SetRate(20);
    API_BMX_MAG_SetRepXY(0x00);
    HAL_Delay(200);
}

void Compass_Loop(void) {
    if(API_getLastEvents() & EV_PB_MID) {
        API_Quit();
    }

    if((HAL_GetTick() - t) >= 100) {
        t = HAL_GetTick();

        char buff[100];

        int16_t X = API_BMX_MAG_X();
        int16_t Y = API_BMX_MAG_Y();
        int16_t Z = API_BMX_MAG_Z() ;

        float angle = (float)atan2(Y, X);
        float angleD = (angle / (2.f * M_PI)) * 360;

        snprintf(buff, sizeof(buff), "X: %d\nY: %d\nZ: %d\nangle: %f\nrep: %hu", X, Y, Z, angleD, API_BMX_MAG_GetRepXY());

        ssd1306_Fill(Black);
        ssd1306_SetCursor(0, 0);
        ssd1306_WriteString(buff, Font_7x10, White);

        float x = 20 * sinf(angle);
        float y = 20 * cosf(angle);

        ssd1306_Line(64, 32, x + 64, y + 32, White);

        ssd1306_UpdateScreen();
    }
}
