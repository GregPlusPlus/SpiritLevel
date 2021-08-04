#ifndef SLIDESHOW_H
#define SLIDESHOW_H

#include "app.h"
#include "api.h"
#include "ui.h"

#include "fatfs.h"

#include <ctype.h>

App_t *Slideshow_GetApp(void);

void Slideshow_Init(void);
void Slideshow_Loop(void);

#endif // SLIDESHOW_H