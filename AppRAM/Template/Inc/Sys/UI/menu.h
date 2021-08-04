#ifndef MENU_H
#define MENU_H

#include "api.h"

typedef struct {
  char *name;
  size_t index;
} MenuEntry_t;

typedef struct {
  char *name;
  size_t count;
  MenuEntry_t **entries;
  MenuEntry_t *current;
} Menu_t;

extern void (*UI_Menu_Init)(Menu_t *menu);
extern void (*UI_Menu_Draw)(Menu_t *menu);
extern void (*UI_Menu_Next)(Menu_t *menu);
extern void (*UI_Menu_Prev)(Menu_t *menu);

#endif // MENU_H