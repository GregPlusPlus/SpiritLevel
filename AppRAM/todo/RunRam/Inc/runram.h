#ifndef RUNRAM_H
#define RUNRAM_H

#include "app.h"
#include "swo.h"
#include "api_hook.h"

#include "fatfs.h"

#include <string.h>

App_t *RunRam_GetApp(void);

void RunRam_Init(void);
void RunRam_Loop(void);

#endif // RUNRAM_H