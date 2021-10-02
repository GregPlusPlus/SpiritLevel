#include "guiassets.h"

void loadScreen(char *msg) {
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);

    UTILS_drawBMP("sys/hourglass.bmp", 85, 18);

    ssd1306_SetCursor(25, 18);
    ssd1306_WriteString(msg, Font_7x10, White);

    ssd1306_UpdateScreen();
}

void splash(void) {
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);

    UTILS_drawBMP("sys/splash.bmp", 0, 0);

    ssd1306_SetCursor(0, 42);
    ssd1306_WriteString("(c) Gregoire BOST", Font_7x10, White);

    ssd1306_UpdateScreen();

    for(int i = 0; i < 6; i++) {
        API_IO_ToggleLED();

        HAL_Delay(80);
    }

    HAL_Delay(2000);
}
