#ifndef DICE_H
#define DICE_H

#include "app.h"

#include <stdlib.h>
#include <math.h>

App_t *Dice_GetApp(void);

void Dice_Init(void);
void Dice_Loop(void);

#endif // DICE_H