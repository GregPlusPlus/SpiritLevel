#include "games.h"

static App_t a = {.name = "Games", .init = Games_Init, .loop = Games_Loop};

static Menu_t gamesMenu;
static Apps_t games;
static bool quitGameRequested = false;
static int32_t currentGame = -1;

static void releaseMenu(void);

App_t *Games_GetApp(void) {
    return &a;
}

void Games_Init(void) {
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_UpdateScreen();

    f_mount(&SDFatFS, "/", 1);

    quitGameRequested = false;
    currentGame = -1;

    registerApps(&games,
                    Sand_GetApp(),
                    Maze_GetApp(),
                    QuitGames_GetApp(),
                    NULL);

    initAppMenu(&gamesMenu, &games, "Games");
    UI_Menu_Init(&gamesMenu);
}

void Games_Loop(void) {
    if(quitGameRequested) {
        quitGameRequested = false;

        ssd1306_Fill(Black);
        ssd1306_UpdateScreen();

        currentGame = -1;
    }

    if(currentGame == -1) {
        if(API_getLastEvents() & EV_PB_LEFT) {
            UI_Menu_Prev(&gamesMenu);
        }

        if(API_getLastEvents() & EV_PB_RIGHT) {
            UI_Menu_Next(&gamesMenu);
        }

        if(API_getLastEvents() & EV_PB_MID) {
            currentGame = gamesMenu.current->index;

            if(games.apps[currentGame] == QuitGames_GetApp()) {
                releaseMenu();
                API_Quit();
                currentGame = -1;

                return;
            }

            ssd1306_Fill(Black);
            ssd1306_UpdateScreen();

            games.apps[currentGame]->init();

            return;
        }

        UI_Menu_Draw(&gamesMenu);
    } else {
        games.apps[currentGame]->loop();
    }
}

void releaseMenu(void) {
    for(size_t i = 0; i < gamesMenu.count; i ++) {
        free(gamesMenu.entries[i]);
    }

    free(gamesMenu.entries);
    gamesMenu.count = 0;

    free(games.apps);
    games.count = 0;
}

void Game_Quit(void) {
    quitGameRequested = true;
}
