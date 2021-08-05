#include "appmenugeneration.h"

App_t *loadApps(size_t *count) {
    size_t appCount = API_Apps_countApps();
    App_t *apps = (App_t*)malloc(appCount * sizeof(App_t));
    memset(apps, 0x00, appCount * sizeof(App_t));

    API_apps_getFiles(apps, appCount);
    API_apps_parseApps(apps, appCount);

    *count = appCount;

    return apps;
}

void buildAppsMenu(Menu_t *menu, App_t *apps, size_t count) {
    menu->name = "Applications";
    menu->count = count;
    menu->entries = (MenuEntry_t**)malloc(count * sizeof(MenuEntry_t*));

    if(!menu->entries) {
        API_DispERROR("ERROR :\nUnable to allocate\nmenu list.");

        while(1);
    }

    for(size_t i = 0; i < count; i++) {
        if(!apps[i].name) {
        continue;
        }

        menu->entries[i] = (MenuEntry_t*)malloc(sizeof(MenuEntry_t));

        if(!menu->entries[i]) {
        API_DispERROR("ERROR :\nUnable to allocate\nmenu entry.");

        while(1);
        }

        menu->entries[i]->name = apps[i].name;
        menu->entries[i]->index = i;
    }
}

void refreshAppMenu(App_t **apps, Menu_t *mainMenu, size_t *appCount) {
    loadScreen("Loading\napps... ");

    if(*apps) {
        free(*apps);
        *apps = NULL;
    }

    for(int i = 0; i < mainMenu->count; i ++) {
        free(mainMenu->entries[i]);
    }

    if(mainMenu->entries) {
        free(mainMenu->entries);
    }

    mainMenu->entries = NULL;
    mainMenu->current = NULL;
    mainMenu->count = 0;

    f_mount(&SDFatFS, "/", 1);

    *apps = loadApps(appCount);
    buildAppsMenu(mainMenu, *apps, *appCount);

    UI_Menu_Init(mainMenu);
}
