#include "dice.h"

static App_t a = {.name = "Dice", .init = Dice_Init, .loop = Dice_Loop};
static uint32_t t = 0;

#define ACCEL_TRIG 600

static void DrawDice(uint8_t number, uint8_t x, uint8_t y);

App_t *Dice_GetApp(void) {
    return &a;
}

void Dice_Init(void) {
    t = HAL_GetTick();

    API_RNG_Init();

    API_BMX_ACC_Reset();
    API_BMX_ACC_SetRange(4);

    ssd1306_SetCursor(20, 5);
    ssd1306_WriteString("Shake\n Me !", Font_16x26, White);
    ssd1306_UpdateScreen();
}

void Dice_Loop(void) {
    if(API_getLastEvents() & EV_PB_MID) {
        API_Quit();
    }

    if((HAL_GetTick() - t) >= 200) {
        t = HAL_GetTick();

        uint16_t accel = abs(API_BMX_ACC_X(NULL));

        if(accel > ACCEL_TRIG) {
            uint8_t minRoll = (((float)accel / (float)ACCEL_TRIG) * 10);
            uint8_t rollNumber = minRoll + (rand() % 16);
            uint8_t numberPicked = 0;

            for(uint8_t i = 0; i < rollNumber; i ++) {
                numberPicked = 1 + (rand() % 6);

                ssd1306_Fill(Black);
                DrawDice(numberPicked, 50, 18);
                ssd1306_UpdateScreen();

                HAL_Delay(25 + (i * 2));
            }

            char buff[50];

            snprintf(buff, sizeof(buff), "%hu", numberPicked);

            ssd1306_Fill(Black);
            DrawDice(numberPicked, 35, 18);
            ssd1306_SetCursor(70, 20);
            ssd1306_WriteString(buff, Font_16x26, White);
            ssd1306_UpdateScreen();
        }
    }
}

inline void DrawDot(uint8_t x, uint8_t y) {
    ssd1306_DrawRectangle(x, y, x + 5, y + 5, White);
}

inline void DrawDot_Left_Top(uint8_t x, uint8_t y) {
    DrawDot(3 + x, 3 + y);
}

inline void DrawDot_Left_Middle(uint8_t x, uint8_t y) {
    DrawDot(3 + x, 11 + y);
}

inline void DrawDot_Left_Bottom(uint8_t x, uint8_t y) {
    DrawDot(3 + x, 19 + y);
}

inline void DrawDot_Middle(uint8_t x, uint8_t y) {
    DrawDot(11 + x, 11 + y);
}

inline void DrawDot_Right_Top(uint8_t x, uint8_t y) {
    DrawDot(19 + x, 3 + y);
}

inline void DrawDot_Right_Middle(uint8_t x, uint8_t y) {
    DrawDot(19 + x, 11 + y);
}

inline void DrawDot_Right_Bottom(uint8_t x, uint8_t y) {
    DrawDot(19 + x, 19 + y);
}

void DrawDice(uint8_t number, uint8_t x, uint8_t y) {
    ssd1306_DrawRectangle(0 + x, 0 + y, 27 + x, 27 + y, White);

    switch(number) {
        case 1:
            DrawDot_Middle(x, y);
            break;
        case 2:
            DrawDot_Left_Bottom(x, y);
            DrawDot_Right_Top(x, y);
            break;
        case 3:
            DrawDot_Left_Bottom(x, y);
            DrawDot_Middle(x, y);
            DrawDot_Right_Top(x, y);
            break;
        case 4:
            DrawDot_Left_Top(x, y);
            DrawDot_Left_Bottom(x, y);
            DrawDot_Right_Top(x, y);
            DrawDot_Right_Bottom(x, y);
            break;
        case 5:
            DrawDot_Left_Top(x, y);
            DrawDot_Left_Bottom(x, y);
            DrawDot_Middle(x, y);
            DrawDot_Right_Top(x, y);
            DrawDot_Right_Bottom(x, y);
            break;
        case 6:
            DrawDot_Left_Top(x, y);
            DrawDot_Left_Middle(x, y);
            DrawDot_Left_Bottom(x, y);
            DrawDot_Right_Top(x, y);
            DrawDot_Right_Middle(x, y);
            DrawDot_Right_Bottom(x, y);
            break;
    }
}
