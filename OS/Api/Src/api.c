#include "api.h"

Event_t event = EV_NONE;

Event_t API_getLastEvents(void) {
    return event;
}

void API_updateEvents(void) {
    event = Events_computeEvents();
}

void API_DispERROR(char *str) {
    SWO_PrintString(str);

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_SetWordWrap(true);
    ssd1306_WriteString(str, Font_7x10, White);
    ssd1306_UpdateScreen();

    while(1);
}

void API_setPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period, uint16_t pulse) {
    HAL_TIM_PWM_Stop(&timer, channel); // stop generation of pwm
    TIM_OC_InitTypeDef sConfigOC;
    timer.Init.Period = period; // set the period duration
    HAL_TIM_PWM_Init(&timer); // reinititialise with new period value
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = pulse; // set the pulse duration
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&timer, &sConfigOC, channel);
    HAL_TIM_PWM_Start(&timer, channel); // start pwm generation
} 

void API_I2C_Scan(I2C_HandleTypeDef *hi2c, bool addrList[128]) {
    //API_printVCP("Scanning I2C bus...\r\n");

    memset(addrList, 0, 128);

    HAL_StatusTypeDef res;
    for(uint16_t i = 0; i < 128; i++) {
        res = HAL_I2C_IsDeviceReady(hi2c, i << 1, 1, 10);
        if(res == HAL_OK) {
            char msg[64];
            snprintf(msg, sizeof(msg), "0x%02X\r\n", i);
            //API_printVCP(msg);

            if(addrList) {
                addrList[i] = true;
            }
        }
    }

    //API_printVCP("\r\nDone !\r\n");
}

void API_IO_SetFlashlight(uint8_t value) {
    API_setPWM(htim2, TIM_CHANNEL_3, 100, value);
}

void API_IO_SetLED(bool state) {
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, state);
}

void API_IO_ToggleLED(void) {
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

bool API_IO_ReadPB1(void)  {
    return !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12);
}

bool API_IO_ReadPB2(void)  {
    return !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
}

bool API_IO_ReadPB3(void)  {
    return !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
}

uint16_t API_ADC_ReadA0(void) {
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

    return HAL_ADC_GetValue(&hadc1);
}

uint32_t API_RNG_GetEntropy(void) {
    return (HAL_GetTick() << 4) | (API_ADC_ReadA0() & 0x000F);
}

void API_RNG_Init(void) {
    uint32_t seed = API_RNG_GetEntropy();

    srand(seed);
}

int32_t API_RNG_randRange(int32_t min, int32_t max) {
    return (rand() % ((max - min) + 1)) + min;
}
