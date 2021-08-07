#ifndef APP_H
#define APP_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "api.h"
#include "UI.h"

#define TUBE_W 12
#define OPENING_H 32
#define SPACING 80
#define NTUBES 3
#define FALL_ACC .023f
#define RISE_ACC 1.55f
#define HITBOX_MARGIN 2

typedef struct {
    uint8_t openingTop;
    int32_t x;
} Tube_t;

typedef struct {
    float v;
    float x;
    float y;
    uint8_t w;
    uint8_t h;
} Chick_t;

typedef struct {
    int32_t x;
    int32_t y;
} Point_t;

bool loadSprites(void);
BMP_Err_t loadSprite(const char *fn, BMP_t *bmp);
void initTubes(Tube_t *tubes, size_t nTubes);
uint8_t generateOpening(void);
void dispPoints(uint32_t x);
void dispGameOver(Tube_t *tubes, size_t nTubes, Chick_t *chick, int32_t xBG,uint32_t x);
void update(Tube_t *tubes, size_t nTubes, Chick_t *chick, int32_t xBG);
void drawTubes(Tube_t *tubes, size_t nTubes);
void drawTube(Tube_t tube);
void updateTubes(Tube_t *tubes, size_t nTubes);
void rollTubes(Tube_t *tubes, size_t nTubes);
void fly(Event_t ev, Chick_t *chick);
bool hasCrashed(Tube_t *tubes, size_t nTubes, Chick_t *chick);
bool rectOverlap(Point_t l1, Point_t r1, Point_t l2, Point_t r2);

#endif // APP_H