#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "api.h"
#include "ssd1306.h"
#include "bmp.h"
#include "api_bmx.h"

 uint32_t t = 0;
 float quantum = 1;
 uint8_t axis = 0;

 float accX[SSD1306_WIDTH];
 float accY[SSD1306_WIDTH];
 float accZ[SSD1306_WIDTH];

 void initArrays(void);
 void rollData(float *array, size_t s, float data);
 float *currentBuffer(uint8_t axis);
 void readAxis(uint8_t axis);
 float getMax(uint8_t axis);
 float getMin(uint8_t axis);
 void plot(uint8_t axis);
 void drawAxisName(uint8_t axis);
 void drawValue(uint8_t axis);
 void drawAxis(void);

void app_main(void) {
    axis = 0;
    t = sysTick();
    initArrays();
    API_BMX_ACC_Reset();
    API_BMX_ACC_SetRange(4);
    quantum = API_BMX_ACC_GetQuantum();

    while(1) {
        API_updateEvents();
        
        if(API_getLastEvents() & EV_PB_LEFT) {
            if(axis == 0) {
                axis = 2;
            } else {
                axis --;
            }
        }

        if(API_getLastEvents() & EV_PB_MID) {
            return;
        }

        if(API_getLastEvents() & EV_PB_RIGHT) {
            if(axis == 2) {
                axis = 0;
            } else {
                axis ++;
            }
        }

        if((sysTick() - t) >= 1) {
            t = sysTick();
            
            readAxis(axis);

            ssd1306_Fill(Black);
            drawAxis();
            plot(axis);
            drawAxisName(axis);
            drawValue(axis);
            ssd1306_UpdateScreen();
        }
    }
}


void initArrays(void) {
    for(size_t i = 0; i < SSD1306_WIDTH; i ++) {
        accX[i] = NAN;
        accY[i] = NAN;
        accZ[i] = NAN;
    }
}

float *currentBuffer(uint8_t axis) {
    switch(axis) {
        case 0:
        return accX;
            break;
        case 1:
        return accY;
            break;
        case 2:
        return accZ;
            break;
        default :
        return NULL;
            break;
    }
}

void rollData(float *array, size_t s, float data) {
    for(size_t i = 0; i < (s - 1); i ++) {
        array[i] = array[i + 1];
    }

    array[s - 1] = data;
}

void readAxis(uint8_t axis) {
    switch(axis) {
        case 0:
        rollData(accX, SSD1306_WIDTH, API_BMX_ACC_X(NULL) * quantum / 9.81f);
            break;
        case 1:
        rollData(accY, SSD1306_WIDTH, API_BMX_ACC_Y(NULL) * quantum / 9.81f);
            break;
        case 2:
        rollData(accZ, SSD1306_WIDTH, API_BMX_ACC_Z(NULL) * quantum / 9.81f);
            break;
        default :
            break;
    }
}

 float getMax(uint8_t axis) {
    float *buff = currentBuffer(axis);

    float max = NAN;

    for(size_t i = 0; isnan(max) && i < SSD1306_WIDTH; i ++) {
        max = buff[i];
    }

    for(size_t i = 1; i < SSD1306_WIDTH; i ++) {
        if(!isnan(buff[i])) {
            if(buff[i] > max) {
                max = buff[i];
            }
        }
    }

    return max;
}

 float getMin(uint8_t axis) {
    float *buff = currentBuffer(axis);

    float min = NAN;

    for(size_t i = 0; isnan(min) && i < SSD1306_WIDTH; i ++) {
        min = buff[i];
    }

    for(size_t i = 1; i < SSD1306_WIDTH; i ++) {
        if(!isnan(buff[i])) {
            if(buff[i] < min) {
                min = buff[i];
            }
        }
    }

    return min;
}

void plot(uint8_t axis) {
    float *buff = currentBuffer(axis);
    float max = 0;
    float min = 0;
    float range = 0;

    if(!buff) {
        return;
    }

    max = getMax(axis);
    min = getMin(axis);
    range = max - min;

    for(size_t i = 0; i < (SSD1306_WIDTH - 1); i ++) {
        float currVal = buff[i];
        float nextVal = buff[i + 1];

        if(range != 0 && !isnan(currVal) && !isnan(nextVal)) {
            currVal = (float)((float)((float)currVal - (float)min) / (float)range) * (float)SSD1306_HEIGHT;
            nextVal = (float)((float)((float)nextVal - (float)min) / (float)range) * (float)SSD1306_HEIGHT;
        } else {
            currVal = 0;
            nextVal = 0;
        }

        if(!isnan(currVal) && !isnan(nextVal)) {
            ssd1306_Line(i, SSD1306_HEIGHT - currVal, i + 1, SSD1306_HEIGHT - nextVal, White);
        }
    }
}

 void drawAxisName(uint8_t axis) {
    ssd1306_SetCursor(0, 0);

    switch(axis) {
        case 0:
        ssd1306_WriteString("X", *Font_7x10, White);
            break;
        case 1:
        ssd1306_WriteString("Y", *Font_7x10, White);
            break;
        case 2:
        ssd1306_WriteString("Z", *Font_7x10, White);
            break;
        default :
            break;
    }
}

 void drawValue(uint8_t axis) {
    char buff[20];
    float acc = currentBuffer(axis)[SSD1306_WIDTH - 1];

    if(acc == NAN) {
        return;
    }

    core_snprintf(buff, sizeof(buff), "%.2f m.s-2", acc);

    ssd1306_SetCursor(10, 0);
    ssd1306_WriteString(buff, *Font_6x8, White);
}

void drawAxis(void) {
    bool state = true;

    for(uint8_t i = 4; i < SSD1306_WIDTH; i += 4) {
        ssd1306_Line(i - 4, SSD1306_HEIGHT / 2, i, SSD1306_HEIGHT / 2, state);

        state = !state;
    }
}
