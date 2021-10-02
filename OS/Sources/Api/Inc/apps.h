#ifndef APPS_H
#define APPS_H


#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "sdio.h"
#include "fatfs.h"

#include "utils.h"

typedef struct {
    uint8_t formatVersion;
    uint32_t codeOffset;
    uint32_t codeSize;
    uint16_t headerLength;
    char *fileName;
    char *name;
    char *version;
    char *author;
    char *description;
} App_t;

size_t API_Apps_countApps(void);
void API_apps_getFiles(App_t *apps, size_t count);
void API_apps_parseApps(App_t *apps, size_t count);
void API_apps_runApp(App_t *app);

#endif // APPS_H