#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "app.h"

#include <math.h>

App_t *Accelerometer_GetApp(void);

void Accelerometer_Init(void);
void Accelerometer_Loop(void);

#endif // ACCELEROMETER_H