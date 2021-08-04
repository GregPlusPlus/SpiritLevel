#include "pb.h"

uint32_t tPB1, tPB2, tPB3;

volatile PB_Flags_t flags = {0};
PB_Flags_t waitFlags = {0};
PB_Flags_t debFlags = {0};

int delay = 0;

void PB_Init(int _delay) {
  tPB1 = tPB2 = tPB3 = HAL_GetTick();

  delay = _delay;
}

void PB_Scan() {
  debFlags.PB1 = false;
  debFlags.PB2 = false;
  debFlags.PB3 = false;

  // PB1
  
  if(flags.PB1 && !waitFlags.PB1) {
    flags.PB1 = false;

    waitFlags.PB1 = true;
    tPB1 = HAL_GetTick();
  }

  if(waitFlags.PB1 && ((HAL_GetTick() - tPB1) >= delay)) {
    waitFlags.PB1 = false;

    debFlags.PB1 = !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12);
  }

  // PB2

  if(flags.PB2 && !waitFlags.PB2) {
    flags.PB2 = false;

    waitFlags.PB2 = true;
    tPB2 = HAL_GetTick();
  }

  if(waitFlags.PB2 && ((HAL_GetTick() - tPB2) >= delay)) {
    waitFlags.PB2 = false;

    debFlags.PB2 = !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
  }

  // PB3

  if(flags.PB3 && !waitFlags.PB3) {
    flags.PB3 = false;

    waitFlags.PB3 = true;
    tPB3 = HAL_GetTick();
  }

  if(waitFlags.PB3 && ((HAL_GetTick() - tPB3) >= delay)) {
    waitFlags.PB3 = false;

    debFlags.PB3 = !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
  }
}

PB_Flags_t *PB_getFlags() {
  return &debFlags;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  flags.PB1 = (GPIO_Pin == GPIO_PIN_12);
  flags.PB2 = (GPIO_Pin == GPIO_PIN_13);
  flags.PB3 = (GPIO_Pin == GPIO_PIN_14);
}
