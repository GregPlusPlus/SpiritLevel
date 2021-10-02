#ifndef PB_H
#define PH_H

#include "gpio.h"

#include <stdbool.h>

typedef struct {
  bool PB1;
  bool PB2;
  bool PB3;
} PB_Flags_t;

void PB_Init(int _delay);

void PB_Scan();

PB_Flags_t *PB_getFlags();

#endif