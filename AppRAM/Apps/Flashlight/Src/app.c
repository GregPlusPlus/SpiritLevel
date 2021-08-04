#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "api.h"
#include "ssd1306.h"

void dispLevel(uint8_t level);

void app_main(void) {
    uint8_t targetLevel = 10;
    uint8_t level = 10;
    uint32_t t = 0;

    API_IO_SetFlashlight(level);

    dispLevel(level);

    while(1) {
        API_updateEvents();

        Event_t ev = API_getLastEvents();

        if((ev & EV_PB_MID) != 0) {
            API_IO_SetFlashlight(0);
            API_Quit();

            return;
        }

        if((ev & EV_PB_LEFT) != 0) {
            if(targetLevel >= 20) {
                targetLevel -= 10;

                /*API_IO_SetFlashlight(level);
                dispLevel();*/
            }
        }
        if((ev & EV_PB_RIGHT) != 0) {
            if(targetLevel <= 90) {
                targetLevel += 10;

                /*API_IO_SetFlashlight(level);
                dispLevel();*/
            }
        }

        if((sysTick() - t) >= 1) {
            t = sysTick();

            if(level < targetLevel) {
                level += 2;

                API_IO_SetFlashlight(level);
                dispLevel(level);
            } else if(level > targetLevel) {
                level -= 2;

                API_IO_SetFlashlight(level);
                dispLevel(level);
            }
        }
    }
}

void dispLevel(uint8_t level) {
    ssd1306_Fill(Black);
    char buff[5];

    snprintf(buff, sizeof(buff), "%hu%%", level);

    if(level < 100) {
        ssd1306_SetCursor(48, 24);
    } else {
        ssd1306_SetCursor(42, 24);
    }

    ssd1306_WriteString(buff, *Font_11x18, White);

    float angle = (level / 100.f) * 360;

    ssd1306_DrawArc(64, 32, 28, 360 - angle, angle, White);

    ssd1306_UpdateScreen();
}
