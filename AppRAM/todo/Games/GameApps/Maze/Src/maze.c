#include "maze.h"

static App_t a = {.name = "Maze", .init = Maze_Init, .loop = Maze_Loop};

#define MAZE_SIZE_W     14
#define MAZE_SIZE_H     6
#define TILE_SIZE       8

static void genMaze(void);
static void createMaze(void);
static bool isMazeComplete(void);
static void showMaze(void);
static void loadSprite(void);

static uint8_t maze[MAZE_SIZE_W + 1][MAZE_SIZE_H + 1];
static BMP_t sprite;

App_t *Maze_GetApp(void) {
    return &a;
}

void Maze_Init(void) {
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen();

    loadSprite();

    genMaze();
    showMaze();
}

void Maze_Loop(void) {
    if(API_getLastEvents() & EV_PB_MID) {
        BMP_release(&sprite);

        Game_Quit();
    }

    if(API_getLastEvents() & EV_PB_LEFT) {
        genMaze();
        showMaze();
    }
}

static void genMaze(void) {
    for(uint8_t x = 0; x < (MAZE_SIZE_W + 1); x ++) {
        for(uint8_t y = 0; y < (MAZE_SIZE_H + 1); y ++) {
            maze[x][y] = 0;
        }
    }

    uint16_t i = 1;

    for(uint8_t x = 0; x < (MAZE_SIZE_W + 1); x ++) {
        for(uint8_t y = 0; y < (MAZE_SIZE_H + 1); y ++) {
            if((x % 2) && (y % 2)) {
                maze[x][y] = i;
                i ++;
            }
        }
    }

    maze[0][1] = 1;
    maze[MAZE_SIZE_W][MAZE_SIZE_H - 1] = i - 1;

    createMaze();
}

void createMaze(void) {
    while (!isMazeComplete()) {
        uint8_t x = rand() % (MAZE_SIZE_W - 1) + 1;
        uint8_t y;

        if((x % 2) == 0) {
            y = ((rand() % ((MAZE_SIZE_H) / 2))) * 2 + 1;
        } else {
            y = ((rand() % ((MAZE_SIZE_H - 1) / 2))) * 2 + 2;
        }

        uint16_t cell_1;
        uint16_t cell_2;

        if(maze[x - 1][y] == 0) {
            cell_1 = maze[x][y - 1];
            cell_2 = maze[x][y + 1];
        } else {
            cell_1 = maze[x - 1][y];
            cell_2 = maze[x + 1][y];
        }

        if(cell_1 != cell_2) {
            maze[x][y] = 1;

            for (uint8_t i = 1; i < MAZE_SIZE_W ; i += 2) {
                for (uint8_t j = 1; j < MAZE_SIZE_H; j += 2) {
                    if (maze[i][j] == cell_2) {
                        maze[i][j] = cell_1;
                    }
                }
            }
        }
    }

    for (uint8_t i = 0; i < MAZE_SIZE_W; i ++) {
        uint8_t x = rand() % (MAZE_SIZE_W - 1) + 1;
        uint8_t y;

        if (x % 2 == 0) {
            y = ((rand() % ((MAZE_SIZE_H) / 2))) * 2 + 1;

        } else {
            y = ((rand() % ((MAZE_SIZE_H - 1) / 2))) * 2 + 2;
        }

        maze[x][y] = 1;
    }
}

bool isMazeComplete(void) {
    for (int i = 1; i < MAZE_SIZE_W - 1; i += 2) {
        for (int j = 1; j < MAZE_SIZE_H - 1; j += 2) {
            if (maze[i][j] != maze[1][1]) {
                return false;
            }
        }
    }

    return true;
}

void showMaze(void) {
    ssd1306_Fill(Black);
    
    for(uint8_t x = 0; x < (MAZE_SIZE_W + 1); x ++) {
        for(uint8_t y = 0; y < (MAZE_SIZE_H + 1); y ++) {
            if(maze[x][y] == 0) {
                //ssd1306_DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, (x * TILE_SIZE) + TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE, White);
                if(sprite.data) {
                    BMP_blit(&sprite, x * TILE_SIZE, y * TILE_SIZE);
                }
            }
        }
    }

    ssd1306_UpdateScreen();
}

void loadSprite(void) {
  FIL fil;

  BMP_zeroBMP(&sprite);

  if(f_open(&fil, "apps/games/maze/wall.bmp", FA_READ) != FR_OK) {
    return;
  }

  BMP_setFile(&fil);

  BMP_Err_t err;
  err = BMP_parseFile(&sprite);

  if(err) {
    return;
  }
  
  err = BMP_readData(&sprite);

  if(err) {
    return;
  }

  f_close(&fil);
}
