#include "apps.h"

#include "api_hook.h"

#define POOL_SIZE       32768
static uint8_t pool[POOL_SIZE] __attribute__((section(".pool_section"))) = {0};

static void initPool(void);
static bool loadFile(char *fn, uint32_t offset);
static void runRam(void);

void API_apps_runApp(App_t *app) {
    initPool();

    if(loadFile(app->fileName, app->codeOffset)) {
        runRam();
    }
}

void initPool(void) {
    memset(pool, 0x00, POOL_SIZE);
}

bool loadFile(char *fn, uint32_t offset) {
    FIL fil;

    int err = f_open(&fil, fn, FA_READ);
    if(err != FR_OK) {
        char buff[50];
        snprintf(buff, sizeof(buff), "Unable to open app file !\nError code %hu", err);
        API_DispERROR(buff);
        
        return false;
    }

    f_lseek(&fil, offset);

    for(size_t i = 0; i < POOL_SIZE && !f_eof(&fil); i ++) {
        pool[i] = UTILS_readFile8(&fil);
    }

    return true;
}

void runRam(void) {
    asm("mov r2, %0" : : "r"(API_hook));    // Pass hook function

    // Save SP & LR
    asm("mov r0, sp");
    asm("mov r1, lr");

    // Jump to code !
    asm("mov r7, %0" : : "r"(pool));
    asm("mov pc, r7");
}
