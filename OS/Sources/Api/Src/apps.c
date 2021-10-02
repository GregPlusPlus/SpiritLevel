#include "apps.h"

#include "ssd1306.h"

#define APPS_PATH "apps"

static bool folderContainsApp(char *fn);
static char *getFileName(char *fn);
static void parseApp(App_t *app);
static void parseHeader(FIL *f, App_t *app);

size_t API_Apps_countApps(void) {
    DIR dir;
    FILINFO fno;
    fno.fname[0] = 0x00;
    size_t i = 0;

    if(f_opendir(&dir, APPS_PATH) != FR_OK) {
        f_closedir(&dir);
        return 0;
    }

    while(1) {
        if(f_readdir(&dir, &fno) != FR_OK) {
            f_closedir(&dir);
            return 0;
        }

        if(fno.fname[0] == 0) {
            break;
        }

        if(fno.fattrib & AM_DIR) {
            if(folderContainsApp(fno.fname)) {
                i ++;
            }
        }
    }

    return i;
}

bool folderContainsApp(char *fn) {
    DIR dir;
    FILINFO fno;
    fno.fname[0] = 0x00;

    char path[50];
    snprintf(path, sizeof(path), "%s/%s", APPS_PATH, fn);

    if(f_opendir(&dir, path) != FR_OK) {
        f_closedir(&dir);

        return false;
    }

    while(1) {
        if(f_readdir(&dir, &fno) != FR_OK) {
            f_closedir(&dir);
            return false;
        }

        if(fno.fname[0] == 0) {
            break;
        }

        if(!(fno.fattrib & AM_DIR)) {
            if(UTILS_checkExtension(fno.fname, ".app")) {
                f_closedir(&dir);

                return true;
            }
        }
    }

    f_closedir(&dir);

    return false;
}

void API_apps_getFiles(App_t *apps, size_t count) {
    DIR dir;
    FILINFO fno;
    fno.fname[0] = 0x00;
    size_t i = 0;

    if(f_opendir(&dir, "apps") != FR_OK) {
        f_closedir(&dir);
        return;
    }

    while(1) {
        if(f_readdir(&dir, &fno) != FR_OK) {
            f_closedir(&dir);
            return;
        }

        if(fno.fname[0] == 0 || (i >= count)) {
            break;
        }

        if(fno.fattrib & AM_DIR) {
            if(folderContainsApp(fno.fname)) {
                apps[i].fileName = getFileName(fno.fname);
                i ++;
            }
        }
    }
}

char *getFileName(char *fn) {
    DIR dir;
    FILINFO fno;
    fno.fname[0] = 0x00;

    char path[50];
    snprintf(path, sizeof(path), "%s/%s", "apps", fn);

    if(f_opendir(&dir, path) != FR_OK) {
        f_closedir(&dir);

        return NULL;
    }

    while(1) {
        if(f_readdir(&dir, &fno) != FR_OK) {
            f_closedir(&dir);
            return NULL;
        }

        if(fno.fname[0] == 0) {
            break;
        }

        if(!(fno.fattrib & AM_DIR)) {
            if(UTILS_checkExtension(fno.fname, ".app")) {
                snprintf(path, sizeof(path), "%s/%s/%s", APPS_PATH, fn, fno.fname);

                char *str = malloc(strlen(path) + 1);
                strcpy(str, path);

                f_closedir(&dir);

                return str;
            }
        }
    }

    f_closedir(&dir);

    return NULL;
}

void API_apps_parseApps(App_t *apps, size_t count) {
    for(size_t i = 0; i < count; i ++) {
        parseApp(&apps[i]);
    }
}

void parseApp(App_t *app) {
    FIL fil;

    if(f_open(&fil, app->fileName, FA_READ) != FR_OK) {
        return;
    }

    app->formatVersion = UTILS_readFile8(&fil);
    app->codeOffset = UTILS_readFile32(&fil);
    app->codeSize = UTILS_readFile32(&fil);
    app->headerLength = UTILS_readFile16(&fil);

    parseHeader(&fil, app);

    f_close(&fil);
}

void parseHeader(FIL *f, App_t *app) {
    char *headerStr = malloc(app->headerLength);
    
    for(size_t i = 0; i < app->headerLength; i ++) {
        headerStr[i] = UTILS_readFile8(f);
    }

    char *tok = strtok(headerStr, "\n");

    if(!tok) {
        return;
    }

    app->name = tok;

    tok = strtok(NULL, "\n");

    if(!tok) {
        return;
    }

    app->version = tok;

    tok = strtok(NULL, "\n");

    if(!tok) {
        return;
    }

    app->author = tok;

    tok = strtok(NULL, "\n");

    if(!tok) {
        return;
    }

    app->description = tok;
    
}
