#ifndef APP_H
#define APP_H

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

#include "api.h"
#include "menu.h"

typedef struct {
    char *name;
    void (*init)(void);
    void (*loop)(void);
} App_t;

typedef struct {
    App_t **apps;
    size_t count;
} Apps_t;

void registerApps(Apps_t *apps, ...);
void initAppMenu(Menu_t *menu, Apps_t *apps, char *name);

#endif // APP_H