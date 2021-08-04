#include "runram.h"

#define POOL_SIZE       32768

static App_t a = {.name = "RunRam", .init = RunRam_Init, .loop = RunRam_Loop};

static uint8_t pool[POOL_SIZE] __attribute__((section(".pool_section"))) = {0};

static void initPool(void);
static void loadFile(void);
static void runRam(void);

App_t *RunRam_GetApp(void) {
    return &a;
}

void RunRam_Init(void) {
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);

    initPool();
    loadFile();

    runRam();

    API_Quit();
}

void RunRam_Loop(void) {

}

void initPool(void) {
    memset(pool, 0x00, POOL_SIZE);
}

void loadFile(void) {
    FIL fil;
    if(f_open(&fil, "AppRAM.bin", FA_READ) != FR_OK) {
        API_Quit();
        return;
    }

    for(size_t i = 0; i < POOL_SIZE && !f_eof(&fil); i ++) {
        UINT br;
        char c = 0;
        f_read(&fil, &c, 1, &br);

        pool[i] = c;
    }
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
