#ifndef APPMENUGENERATION_H
#define APPMENUGENERATION_H

#include "ssd1306.h"
#include "api.h"
#include "ui.h"

#include "guiassets.h"

App_t *loadApps(size_t *count);
void buildAppsMenu(Menu_t *menu, App_t *apps, size_t count);
void refreshAppMenu(App_t **apps, Menu_t *mainMenu, size_t *appCount);

#endif // APPMENUGENERATION_H