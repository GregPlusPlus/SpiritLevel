#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "UI.h"
#include "utils.h"

void About_Init(void);

void initMenu(void);

void dispAbout(void);
void dispTextFile(void);
void dispQRCode(void);
void manageStorage(void);
void setBrightness(void);

#define NUMBER_OF_ENTRIES   6
#define PRJ_NAME            "SpiritLevel"
#define PRJ_VERSION         "V3.0"

Menu_t menu;
MenuEntry_t *entries[NUMBER_OF_ENTRIES];
MenuEntry_t entry_1;
MenuEntry_t entry_2;
MenuEntry_t entry_3;
MenuEntry_t entry_4;
MenuEntry_t entry_5;
MenuEntry_t entry_6;

uint8_t page;
bool showPage;
bool updatePage;

void app_main(void) {
    About_Init();

    while(1) {
        API_updateEvents();
        
        if(!showPage) {
            if(API_getLastEvents() & EV_PB_LEFT) {
                UI_Menu_Prev(&menu);
            }

            if(API_getLastEvents() & EV_PB_RIGHT) {
                UI_Menu_Next(&menu);
            }

            if(API_getLastEvents() & EV_PB_MID) {
                showPage = true;
                updatePage = true;
                page = menu.current->index;
            }

            UI_Menu_Draw(&menu);
            ssd1306_UpdateScreen();
        } else {

            if(updatePage) {
                switch(page) {
                case 0:
                dispAbout();
                updatePage = false;
                    break;
                case 1:
                dispTextFile();
                updatePage = false;
                    break;
                case 2:
                dispQRCode();
                updatePage = false;
                    break;
                case 3:
                manageStorage();
                updatePage = false;
                    break;
                case 4:
                setBrightness();
                updatePage = false;
                    break;
                case 5:
                return;
                    break;
                default:
                    break;
                }
            }

            if(API_getLastEvents() & EV_PB_MID) {
                showPage = false;
            }

        }
    }
}

void About_Init(void) {
    page = 0;
    showPage = false;
    updatePage = false;

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);

    ssd1306_UpdateScreen();

    f_mount(SDFatFS, "/", 1);

    //Delay(250);

    initMenu();
}


void initMenu(void) {
    menu.name = "About...";
    menu.count = NUMBER_OF_ENTRIES;
    menu.entries = (MenuEntry_t**)&entries;

    menu.entries[0] = &entry_1;
    menu.entries[1] = &entry_2;
    menu.entries[2] = &entry_3;
    menu.entries[3] = &entry_4;
    menu.entries[4] = &entry_5;
    menu.entries[5] = &entry_6;

    entry_1.name = "Information";
    entry_1.index = 0;

    entry_2.name = "Show \"about\" file";
    entry_2.index = 1;

    entry_3.name = "Show QR code";
    entry_3.index = 2;

    entry_4.name = "Storage management";
    entry_4.index = 3;

    entry_5.name = "Set brightness";
    entry_5.index = 4;

    entry_6.name = "Quit";
    entry_6.index = 5;

    UI_Menu_Init(&menu);
}

void dispAbout(void) {
    char buff[50];

    snprintf(buff, sizeof(buff), "%s %s", PRJ_NAME, PRJ_VERSION);

    ssd1306_Fill(Black);
    ssd1306_SetCursor(5, 5);
    ssd1306_WriteString(buff, *Font_7x10, White);

    ssd1306_Line(0, 17, SSD1306_WIDTH, 17, White);

    snprintf(buff, sizeof(buff), "Build on %s\n" \
                                    "GCC %s", __DATE__, __VERSION__);

    ssd1306_SetCursor(5, 22);
    ssd1306_WriteString(buff, *Font_6x8, White);
    ssd1306_UpdateScreen();

    ssd1306_UpdateScreen();
}

void dispTextFile(void) {
    FIL fil;

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);

    if(f_open(&fil, "apps/About/about.txt", FA_READ) != FR_OK) {
        ssd1306_WriteString("Failed to open file !", *Font_6x8, White);
        ssd1306_UpdateScreen();

        return;
    }

    uint32_t fileSize = (f_size(&fil) + 1) * sizeof(char);
    char *buff = NULL;
    char c = 0;

    buff = (char*)malloc(fileSize);
    memset(buff, 0x00, fileSize);

    for(uint8_t i = 0; !f_eof(&fil); i ++) {
        UINT br;
        f_read(&fil, &c, 1, &br);

        buff[i] = (c != '\r')? c : '\n';
        buff[i + 1] = 0;
    }

    ssd1306_WriteString(buff, *Font_6x8, White);
    ssd1306_UpdateScreen();

    f_close(&fil);
    free(buff);
}

void dispQRCode(void) {
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    
    FIL fil;
    BMP_t bmp;

    BMP_zeroBMP(&bmp);

    if(f_open(&fil, "apps/About/qr.bmp", FA_READ) != FR_OK) {
        ssd1306_WriteString("Failed to open file !", *Font_6x8, White);
        ssd1306_UpdateScreen();

        return;
    }

    BMP_setFile(&fil);

    BMP_Err_t err;
    err = BMP_parseFile(&bmp);

    if(err) {
        ssd1306_WriteString("INVALID FILE !", *Font_6x8, White);
        ssd1306_UpdateScreen();

        return;
    }
    
    BMP_readData(&bmp);
    BMP_blit(&bmp, 34, 0);
    BMP_release(&bmp);
    
    f_close(&fil);

    ssd1306_UpdateScreen();
}

void manageStorage(void) {
    Progressbar_t pb;
    char buff[100];
    uint32_t free;
    uint32_t total;

    UTILS_getStorageUsage(&free, &total);

    UI_Progressbar_Init(&pb, 14, 40, 100, 10, total);

    ssd1306_Fill(Black);

    core_snprintf(buff, sizeof(buff), "Total: %lu KiB\n" \
                                 "Free : %lu KiB\n" \
                                 "Used : %.2f%%",
                                 total / 1024, free / 1024, (float)(total - free) * 100 / (float)total);

    ssd1306_SetCursor(5, 5);
    ssd1306_WriteString(buff, *Font_6x8, White);

    UI_Progressbar_Setvalue(&pb, (total - free));

    UI_Progressbar_Draw(&pb);

    ssd1306_UpdateScreen();
}

void setBrightness(void) {
    Progressbar_t pb;

    uint8_t b = 0x7F;

    ssd1306_Fill(Black);

    ssd1306_WriteCommand(0x81); //--set contrast control register - CHECK
    ssd1306_WriteCommand(b);

    UI_Progressbar_Init(&pb, 14, 30, 101, 10, 255);

    UTILS_drawBMP("apps/About/brightness.bmp", 0, 0);

    while(1) {
        API_updateEvents();

        if(API_getLastEvents() & EV_PB_LEFT) {
            b -= 0x10;

            ssd1306_WriteCommand(0x81); //--set contrast control register - CHECK
            ssd1306_WriteCommand(b);
        }

        if(API_getLastEvents() & EV_PB_RIGHT) {
            b += 0x10;

            ssd1306_WriteCommand(0x81); //--set contrast control register - CHECK
            ssd1306_WriteCommand(b);
        }

        if(API_getLastEvents() & EV_PB_MID) {
            return;
        }
        
        UI_Progressbar_Setvalue(&pb, b);
        UI_Progressbar_Draw(&pb);

        ssd1306_UpdateScreen();
    }
}
