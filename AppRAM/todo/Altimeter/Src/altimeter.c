#include "altimeter.h"

static App_t a = {.name = "Altimeter", .init = Altimeter_Init, .loop = Altimeter_Loop};

//static uint32_t t = 0;

App_t *Altimeter_GetApp(void) {
    return &a;
}

void Altimeter_Init(void) {
    printf("Reset LPS... ");
    //API_LPS_Reset();
    printf("OK\n");
}

void Altimeter_Loop(void) {
    if(API_getLastEvents() & EV_PB_MID) {
        API_Quit();
    }

    API_LPS_OneShot();

    int32_t rawpres = API_LPS_GetPressure();
    float pres = ((float)(rawpres/4096.f));

    printf("%ld %.2f %.2f\n", rawpres, pres, ((float)API_LPS_GetTemp()/100.f));

    char buff[50];

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);

    float alt = (1.f - powf(pres / 1013.25f, 0.190284)) * 145366.45f *  0.3048f;
    
    snprintf(buff, sizeof(buff), "%.2f m", alt);

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(buff, Font_7x10, White);

    ssd1306_UpdateScreen();

    HAL_Delay(100);
}
