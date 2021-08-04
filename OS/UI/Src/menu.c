#include "menu.h"

void UI_Priv_Menu_DrawDots(Menu_t *menu);
void UI_Priv_Menu_ScrollText(char *str);

void UI_Menu_Init(Menu_t *menu) {
    if(menu->count > 0) {
        menu->current = menu->entries[0];
    } else {
        menu->current = NULL;
    }
}

void UI_Menu_Draw(Menu_t *menu) {
    ssd1306_Fill(Black);
    ssd1306_SetCursor(2, 2);
    ssd1306_WriteString(menu->name, Font_7x10, White);
    ssd1306_Line(0, 14, SSD1306_WIDTH, 14, White);

    if(menu->count) {
        UI_Priv_Menu_DrawDots(menu);
        UI_Priv_Menu_ScrollText(menu->current->name);
    }

    ssd1306_UpdateScreen();
}

void UI_Priv_Menu_ScrollText(char *str) {
    static uint32_t t = 0;
    static int offset = 0;
    static uint8_t spacing = 20;
    static char *lastStr = NULL;
    static bool lock = true;
    size_t textWidth = 0;

    if(strcmp(str, lastStr)) {
        offset = 0;
        lock = true;
        t = HAL_GetTick();
    }

    lastStr = str;
    textWidth = ssd1306_GetTextWidth(Font_11x18, str);

    if(lock) {
        if((HAL_GetTick() - t) >= 1000) {
            t = HAL_GetTick();
            lock = false;
        }
    } else {
        if((HAL_GetTick() - t) >= 20) {
            t = HAL_GetTick();

            offset --;
        }
    }

    if((int)offset < (int)(-(int)textWidth - spacing)) {
        offset = 0;
    }
    
    ssd1306_SetWordWrap(false);

    if((textWidth + 2) < SSD1306_WIDTH) {
        ssd1306_SetCursor(2, 25);
        ssd1306_WriteString(str, Font_11x18, White);
    } else {
        ssd1306_SetCursor(offset + 2, 25);
        ssd1306_WriteString(str, Font_11x18, White);
        ssd1306_SetCursor(offset + textWidth + spacing + 2, 25);
        ssd1306_WriteString(str, Font_11x18, White);
    }
    
    ssd1306_SetWordWrap(true);
}

void UI_Priv_Menu_DrawDots(Menu_t *menu) {
    uint8_t spacing = 9;
    uint8_t length = spacing * menu->count;
    uint8_t startX = (SSD1306_WIDTH / 2) - (length / 2);

    for(int i = 0; i < menu->count; i++) {
        uint8_t rad = 2;
        uint8_t x = i * spacing + startX;
        uint8_t y = 60;

        if(i == menu->current->index) {
            rad = 3;

            ssd1306_DrawPixel(x, y, White);
        }

        ssd1306_DrawCircle(x, y, rad, White);
    }
}

void UI_Menu_Next(Menu_t *menu) {
    if(!menu->current) {
        return;
    }

    size_t i = menu->current->index;

    if(i < (menu->count - 1)) {
        i ++;
    } else {
        i = 0;
    }

    menu->current = menu->entries[i];
}

void UI_Menu_Prev(Menu_t *menu) {
    if(!menu->current) {
        return;
    }

    size_t i = menu->current->index;

    if(i > 0) {
        i --;
    } else {
        i = (menu->count - 1);
    }

    menu->current = menu->entries[i];
}
