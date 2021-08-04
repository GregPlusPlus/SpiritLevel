#ifndef MORSE_H
#define MORSE_H

#include "app.h"
#include "api.h"
#include "ui.h"

#include "fatfs.h"

#include <ctype.h>

App_t *Morse_GetApp(void);

void Morse_Init(void);
void Morse_Loop(void);

#endif