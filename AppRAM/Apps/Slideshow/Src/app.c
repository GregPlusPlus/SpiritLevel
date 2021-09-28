#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "api.h"
#include "ui.h"

#define SLDSHW_PATH "apps/slideshow"

size_t findex = 0;
size_t cnt = 0;

size_t countFiles(void);
FIL goToFile(size_t index);
void showImg(FIL fil);
bool isBMP(const char *str);

void Slideshow_Init(void);

void app_main(void) {
    Slideshow_Init();

    while(1) {
        API_updateEvents();

        if(API_getLastEvents() & EV_PB_MID) {
            return;
        }

        if(API_getLastEvents() & EV_PB_LEFT) {
            size_t fcount = countFiles();

            if(!fcount) {
                return;
            }

            if(findex >= fcount) {
                findex = fcount - 1;
            } else {
                if(findex == 0) {
                    findex = fcount - 1;
                } else {
                    findex --;
                }
            }

            showImg(goToFile(findex));
        }

        if(API_getLastEvents() & EV_PB_RIGHT) {
            size_t fcount = countFiles();

            if(!fcount) {
                return;
            }

            if(findex >= fcount) {
                findex = fcount - 1;
            } else {
                if(findex == (fcount - 1)) {
                    findex = 0;
                } else {
                    findex ++;
                }
            }

            showImg(goToFile(findex));
        }
    }
    
}

void Slideshow_Init(void) {
    findex = 0;
    
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_UpdateScreen();

    f_mount(SDFatFS, "/", 1);

    if(countFiles()) {
        showImg(goToFile(findex));
    } else {
        ssd1306_Fill(Black);
        ssd1306_SetCursor(20, 30);
        ssd1306_WriteString("Empty folder", *Font_7x10, White);
        ssd1306_UpdateScreen();
    }
}


FIL goToFile(size_t index) {
    DIR dir;
    FILINFO fno;
    fno.fname[0] = 0x00;
    FIL fil;

    size_t i = 0;

    if (f_opendir(&dir, SLDSHW_PATH) != FR_OK) {
        f_closedir(&dir);
        return fil;
    }

    while(1) {
        if(f_readdir(&dir, &fno) != FR_OK) {
            f_closedir(&dir);
            return fil;
        }

        if(fno.fname[0] == 0) {
            break;
        }

        if ((fno.fattrib & AM_DIR) == 0) {
            if(isBMP(fno.fname)) {
                if(i == findex) {
                    break;
                }

                i ++;
            }
        }
    }

    char path[50];

    snprintf(path, sizeof(path), "%s/%s", SLDSHW_PATH, fno.fname);
    
    int err = f_open(&fil, path, FA_READ);

    if(err != FR_OK) {
        return fil;
    }

    f_closedir(&dir);

    return fil;
}

size_t countFiles(void) {
    DIR dir;
    FILINFO fno;
    fno.fname[0] = 0x00;
    size_t i = 0;

    if (f_opendir(&dir, SLDSHW_PATH) != FR_OK) {
        f_closedir(&dir);
        return 0;
    }

    while(1) {
        if(f_readdir(&dir, &fno) != FR_OK) {
            f_closedir(&dir);
            return 0;
        }

        if(fno.fname[0] == 0) {
            break;
        }

        if ((fno.fattrib & AM_DIR) == 0) {
            if(isBMP(fno.fname)) {
                i ++;
            }
        }
    }

    cnt = i;

    return i;
}

void showImg(FIL fil) {
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);

    BMP_t bmp;

    BMP_zeroBMP(&bmp);

    BMP_setFile(&fil);

    BMP_Err_t err;
    err = BMP_parseFile(&bmp);

    if(err) {
        ssd1306_SetCursor(20, 30);
        ssd1306_WriteString("Invalid file", *Font_7x10, White);
        ssd1306_UpdateScreen();

        f_close(&fil);
        return;
    }
    
    err = BMP_readData(&bmp);
    
    f_close(&fil);

    if(err) {
        ssd1306_SetCursor(20, 30);
        ssd1306_WriteString("Cannot read data", *Font_7x10, White);
        ssd1306_UpdateScreen();
        return;
    }
    
    BMP_blit(&bmp,
                    (SSD1306_WIDTH / 2) - (bmp.w / 2),
                    (SSD1306_HEIGHT / 2) - (bmp.h / 2));
    BMP_release(&bmp);

    ssd1306_UpdateScreen();
}

bool isBMP(const char *str) {
    const char *dot = strrchr(str, '.');

    return strcmp(dot, ".bmp") == 0;
}
