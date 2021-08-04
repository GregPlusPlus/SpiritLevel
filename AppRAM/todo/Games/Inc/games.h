#ifndef GAMES_H
#define GAMES_H

#include "app.h"
#include "swo.h"

#include "sand.h"
#include "maze.h"
#include "quitgames.h"

App_t *Games_GetApp(void);

void Games_Init(void);
void Games_Loop(void);

void Game_Quit(void);

#endif // GAMES_H