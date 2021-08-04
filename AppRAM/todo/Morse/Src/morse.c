#include "morse.h"

#define BUFF_LEN 23
#define TIME_UNIT 100
#define BEEP_ON() do{API_IO_SetFlashlight(100);}while(0)
#define BEEP_OFF() do{API_IO_SetFlashlight(0);}while(0)

static char *alpha[] = {
    ".-",   //A
    "-...", //B
    "-.-.", //C
    "-..",  //D
    ".",    //E
    "..-.", //F
    "--.",  //G
    "....", //H
    "..",   //I
    ".---", //J
    "-.-",  //K
    ".-..", //L
    "--",   //M
    "-.",   //N
    "---",  //O
    ".--.", //P
    "--.-", //Q
    ".-.",  //R
    "...",  //S
    "-",    //T
    "..-",  //U
    "...-", //V
    ".--",  //W
    "-..-", //X
    "-.--", //Y
    "--..", //Z
};
static char *num[] = {
    "-----", //0
    ".----", //1
    "..---", //2
    "...--", //3
    "....-", //4
    ".....", //5
    "-....", //6
    "--...", //7
    "---..", //8
    "----.", //9
};

static App_t a = {.name = "Morse", .init = Morse_Init, .loop = Morse_Loop};

static FIL fil;
static Progressbar_t pb;

static void dispInitStateMessage(int res);
static void sendCharMorse(char c);
static void sendCode(char *code);

App_t *Morse_GetApp(void) {
    return &a;
}

void Morse_Init(void) {
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);

    ssd1306_WriteString("Mounting File system... ", Font_6x8, White);
    dispInitStateMessage(f_mount(&SDFatFS, "/", 1));

    ssd1306_WriteString("Opening file... ", Font_6x8, White);
    dispInitStateMessage(f_open(&fil, "apps/morse/morse.txt", FA_READ));

    HAL_Delay(250);
}

void dispInitStateMessage(int res) {
    if(res == FR_OK) {
        ssd1306_WriteString("OK\n", Font_6x8, White);
        ssd1306_UpdateScreen();
    } else {
        ssd1306_WriteString("Failed !", Font_6x8, White);
        ssd1306_UpdateScreen();
        
        HAL_Delay(1000);
        API_Quit();
    }
}

void Morse_Loop(void) {
    char c = 0;
    uint32_t fileSize = f_size(&fil);
    uint32_t current = 0;

    UI_Progressbar_Init(&pb, 14, 40, 100, 10, fileSize);

    while(!f_eof(&fil)) {
        UINT br;
        f_read(&fil, &c, 1, &br);

        if(isalnum(c) || c == ' ') {
            ssd1306_Fill(Black);
            ssd1306_SetCursor(60, 10);
            ssd1306_WriteChar(c, Font_16x26, White);
            UI_Progressbar_Setvalue(&pb, ++ current);
            UI_Progressbar_Draw(&pb);
            ssd1306_UpdateScreen();

            sendCharMorse(toupper(c));
        }
    }

    f_close(&fil);

    API_Quit();
}

void sendCharMorse(char c) {
    char *code = NULL;

    if(isalpha(c)) {
        code = alpha[c - 'A'];
    } else if(isdigit(c)) {
        code = num[c - '0'];
    } else if(c == ' ') {
        code = "s";
    }

    if(code) {
        sendCode(code);
    }
}

 void sendCode(char *code) {
    for(size_t i = 0; i < strlen(code); i ++) {
        if(code[i] == '.') {
            BEEP_ON();
            HAL_Delay(TIME_UNIT);
            BEEP_OFF();
        } else if (code[i] == '-') {
            BEEP_ON();
            HAL_Delay(3 * TIME_UNIT);
            BEEP_OFF();
        } else if(code[i] == 's') {
            HAL_Delay(7 * TIME_UNIT);
        }

        HAL_Delay(TIME_UNIT);
    }

    HAL_Delay(3 * TIME_UNIT);
}
