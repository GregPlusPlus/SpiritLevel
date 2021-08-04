#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "swo.h"
#include "api.h"
#include "ssd1306.h"
#include "bmp.h"

uint32_t i = 0;
uint32_t t;
uint32_t start_t;
bool ledState = true;

void displayRAMLogo(void);
void dispTime(void);

void app_main(void) {
    t = sysTick();
    start_t = t;

    f_mount(SDFatFS, "/", 1);

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString("Hello from RAM !\n", *Font_7x10, White);

    displayRAMLogo();

    ssd1306_UpdateScreen();

    while(1) {
        API_updateEvents();
    
        if(API_getLastEvents() & EV_PB_MID) {
            API_IO_SetLED(false);

            return;
        }
    
        if(i == 11) {
            API_IO_SetLED(false);
    
            ssd1306_SetCursor(10, 50);
            ssd1306_WriteString("Push to exit :)", *Font_7x10, White);
            ssd1306_UpdateScreen();
        } else if(((sysTick() - t) >= 200)) {
            t = sysTick();
            i ++;
    
            API_IO_SetLED(ledState);
    
            ledState = !ledState;
        }
    
        dispTime();
    }
}

void displayRAMLogo(void) {
    FIL fil;
    BMP_t bmp;

    BMP_zeroBMP(&bmp);

    if(f_open(&fil, "ram.bmp", FA_READ) != FR_OK) {
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

    BMP_blit(&bmp, 50, 20);
    BMP_release(&bmp);
    f_close(&fil);
}

void dispTime(void) {
    char str[100];

    snprintf(str, sizeof(str), "T+ %lums", (sysTick() - start_t));

    for(uint8_t i = 0; i < 10; i ++) {
        ssd1306_Line(0, 35 + i, 128, 35 + i, Black);
    }

    int w = ssd1306_GetTextWidth(*Font_7x10, str);

    ssd1306_SetCursor((SSD1306_WIDTH / 2) - (w / 2), 35);
    ssd1306_WriteString(str, *Font_7x10, White);
    ssd1306_UpdateScreen();
}