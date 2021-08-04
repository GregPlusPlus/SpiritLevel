#include "sand.h"

static App_t a = {.name = "Sand", .init = Sand_Init, .loop = Sand_Loop};

#define NUM_PART        800
#define ACCEL_MAX       100
#define IMU_ACCEL       12
#define BOUNCE_ACCEL    20

#define POOL_W          128
#define POOL_H          64
#define SCALE_FTOR      100

static uint32_t t = 0;

static int axis_max[2] = {POOL_W * SCALE_FTOR, POOL_H * SCALE_FTOR};
static int particle_pos[NUM_PART][2];
static int particle_vel[NUM_PART][2];

static bool started = false;
static bool paused = false;

static void initPart(void);
static void update_pos_vel(int particle_num, int acc_x, int acc_y);
static void draw_particles(int particle_num);

App_t *Sand_GetApp(void) {
    return &a;
}

void Sand_Init(void) {
    t = HAL_GetTick();
    started = false;
    paused = false;

    API_RNG_Init();
    
    API_BMX_ACC_Reset();
    API_BMX_ACC_SetRange(4);

    initPart();

    ssd1306_Fill(Black);

    for (int i = 0; i < NUM_PART; i++) {
        draw_particles(i);
    }

    ssd1306_SetCursor(10, 35);
    ssd1306_WriteString("Press to start !", Font_7x10, White);

    ssd1306_UpdateScreen();
}

void Sand_Loop(void) {
    if(API_getLastEvents() & EV_PB_MID) {
        if(started) {
            Game_Quit();
        } else {
            started = true;
        }
    }

    if(API_getLastEvents() & EV_PB_RIGHT) {
        if(started) {
            paused = !paused;
        }
    }

    if(!started || paused) {
        return;
    }

    if((HAL_GetTick() - t) >= 1) {
        t = HAL_GetTick();

        int16_t x = -API_BMX_ACC_X(NULL) / IMU_ACCEL;
        int16_t y = -API_BMX_ACC_Y(NULL) / IMU_ACCEL;

        ssd1306_Fill(Black);

        for (int i = 0; i < NUM_PART; i++) {
            update_pos_vel(i, y, x);
            draw_particles(i);
        }

        ssd1306_UpdateScreen();
    }
}

void initPart(void) {
    for(int i = 0; i < NUM_PART; i ++) {

        int x_vel = API_RNG_randRange(-ACCEL_MAX, ACCEL_MAX);
        int y_vel = API_RNG_randRange(-ACCEL_MAX, ACCEL_MAX);
        particle_vel[i][0] = x_vel;
        particle_vel[i][1] = y_vel;

        int x_pos = API_RNG_randRange(0, axis_max[0]);
        int y_pos = API_RNG_randRange(0, axis_max[1] / 2);
        particle_pos[i][0] = x_pos;
        particle_pos[i][1] = y_pos;
    }
}

void update_pos_vel(int particle_num, int acc_x, int acc_y) {
    int acc[3] = {0, 0};
    acc[0] = acc_x;
    acc[1] = acc_y;

    /*for(int i = 0; i < NUM_PART; i++) {
        if(particle_pos[particle_num][0] == particle_pos[i][0] &&
            particle_pos[particle_num][1] == particle_pos[i][1] &&
            particle_pos[particle_num] != particle_pos[i]) {
                particle_vel[particle_num][0] *= -2;
                particle_vel[particle_num][1] *= -2;

                break;
        }
    }*/

    for(int axis = 0; axis < 2; axis ++) {

        particle_vel[particle_num][axis] += acc[axis];

        particle_pos[particle_num][axis] += particle_vel[particle_num][axis];

        if(particle_pos[particle_num][axis] > (axis_max[axis]) || particle_pos[particle_num][axis] < 0) {

            if(particle_pos[particle_num][axis] > axis_max[axis]) {
                particle_pos[particle_num][axis] = axis_max[axis] - ACCEL_MAX;
            }
            if(particle_pos[particle_num][axis] < 0) {
                particle_pos[particle_num][axis] = ACCEL_MAX;
            }

            if(particle_vel[particle_num][axis] < 0) {
                particle_vel[particle_num][axis] += 1;
            } else {
                particle_vel[particle_num][axis] -= 1;
            }


            particle_vel[particle_num][axis] *= 10;
            particle_vel[particle_num][axis] /= -BOUNCE_ACCEL;
            particle_vel[particle_num][axis] += API_RNG_randRange(-50, 50);
        }
    }
}

void draw_particles(int particle_num) {
    int pixel[2] = {0, 0};

    for(int axis = 0; axis < 2; axis ++) {
        pixel[axis] = particle_pos[particle_num][axis] / SCALE_FTOR;

        /*if(pixel[axis] > axis_max[axis]) {
        pixel[axis] = axis_max[axis];
        }

        if(pixel[axis] < 0) {
        pixel[axis] = 0;
        }*/
    }

    ssd1306_DrawPixel(pixel[0], pixel[1], White);
}
