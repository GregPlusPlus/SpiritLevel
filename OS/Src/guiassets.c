#include "guiassets.h"

void loadScreen(char *msg) {
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);

    FIL fil;
    BMP_t bmp;

    BMP_zeroBMP(&bmp);

    if(f_open(&fil, "sys/hourglass.bmp", FA_READ) != FR_OK) {
        return;
    }

    BMP_setFile(&fil);

    BMP_Err_t err;
    err = BMP_parseFile(&bmp);

    if(err) {
        return;
    }
    
    err = BMP_readData(&bmp);

    if(err) {
        return;
    }

    BMP_blit(&bmp, 85, 18);
    BMP_release(&bmp);
    f_close(&fil);

    ssd1306_SetCursor(25, 18);
    ssd1306_WriteString(msg, Font_7x10, White);

    ssd1306_UpdateScreen();
}

void splash(void) {
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);

    FIL fil;
    BMP_t bmp;

    BMP_zeroBMP(&bmp);

    if(f_open(&fil, "sys/splash.bmp", FA_READ) != FR_OK) {
        return;
    }

    BMP_setFile(&fil);

    BMP_Err_t err;
    err = BMP_parseFile(&bmp);

    if(err) {
        return;
    }
    
    err = BMP_readData(&bmp);

    if(err) {
        return;
    }

    BMP_blit(&bmp, 0, 0);
    BMP_release(&bmp);
    f_close(&fil);

    ssd1306_SetCursor(0, 42);
    ssd1306_WriteString("(c) Gregoire BOST", Font_7x10, White);

    ssd1306_UpdateScreen();

    for(int i = 0; i < 6; i++) {
        API_IO_ToggleLED();

        HAL_Delay(80);
    }

    HAL_Delay(2000);
}
