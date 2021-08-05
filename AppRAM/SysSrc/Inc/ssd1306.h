/**
 * This Library was originally written by Olivier Van den Eede (4ilo) in 2016.
 * Some refactoring was done and SPI support was added by Aleksander Alekseev (afiskon) in 2018.
 *
 * https://github.com/afiskon/stm32-ssd1306
 */

#ifndef SSD1306_H__
#define SSD1306_H__

#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "ssd1306_fonts.h"

// SSD1306 OLED height in pixels
#ifndef SSD1306_HEIGHT
#define SSD1306_HEIGHT          64
#endif

// SSD1306 width in pixels
#ifndef SSD1306_WIDTH
#define SSD1306_WIDTH           128
#endif

// some LEDs don't display anything in first two columns
// #define SSD1306_WIDTH           130

// Enumeration for screen colors
typedef enum {
    Black = 0x00, // Black color, no pixel
    White = 0x01  // Pixel is set. Color depends on OLED
} SSD1306_COLOR;

// Struct to store transformations
typedef struct {
    int32_t StartX;
    int32_t CurrentX;
    int32_t CurrentY;
    uint8_t Inverted;
    uint8_t Initialized;
    bool wordWrap;
} SSD1306_t;
typedef struct {
    uint8_t x;
    uint8_t y;
} SSD1306_VERTEX;

extern void (*ssd1306_Init)(void);
extern void (*ssd1306_Fill)(SSD1306_COLOR color);
extern void (*ssd1306_UpdateScreen)(void);
extern void (*ssd1306_DrawPixel)(int32_t x, int32_t y, SSD1306_COLOR color);
extern char (*ssd1306_WriteChar)(char ch, FontDef Font, SSD1306_COLOR color);
extern char (*ssd1306_WriteString)(char* str, FontDef Font, SSD1306_COLOR color);
extern void (*ssd1306_SetCursor)(int32_t x, int32_t y);
extern void (*ssd1306_SetWordWrap)(bool enabled);
extern void (*ssd1306_Line)(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
extern void (*ssd1306_DrawArc)(uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, SSD1306_COLOR color);
extern void (*ssd1306_DrawCircle)(uint8_t par_x, uint8_t par_y, uint8_t par_r, SSD1306_COLOR color);
extern void (*ssd1306_Polyline)(const SSD1306_VERTEX *par_vertex, uint16_t par_size, SSD1306_COLOR color);
extern void (*ssd1306_DrawRectangle)(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
extern void (*ssd1306_DrawPlainRectangle)(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
extern int (*ssd1306_GetTextWidth)(FontDef Font, const char *str);
extern void (*ssd1306_Reset)(void);
extern void (*ssd1306_WriteCommand)(uint8_t byte);
extern void (*ssd1306_WriteData)(uint8_t* buffer, size_t buff_size);

#endif // SSD1306_H
