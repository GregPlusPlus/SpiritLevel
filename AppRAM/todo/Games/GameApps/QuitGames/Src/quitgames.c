#include "quitgames.h"

static App_t a = {.name = "Quit games", .init = QuitGames_Init, .loop = QuitGames_Loop};

App_t *QuitGames_GetApp(void) {
    return &a;
}

void QuitGames_Init(void) {

}

void QuitGames_Loop(void) {

}
