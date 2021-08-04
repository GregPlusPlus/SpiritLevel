#ifndef ALTIMETER_H
#define ALTIMETER_H

#include "app.h"

#include <math.h>

App_t *Altimeter_GetApp(void);

void Altimeter_Init(void);
void Altimeter_Loop(void);

#endif // ALTIMETER_H