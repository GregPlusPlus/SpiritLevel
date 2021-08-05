/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "fatfs.h"
#include "i2c.h"
#include "sdio.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "ssd1306.h"
#include "api.h"
#include "ui.h"

#include "swo.h"

#include <stdbool.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void splash(void);
void showDevices(void);
void loadScreen(char *msg);
App_t *loadApps(size_t *count);
void buildAppsMenu(Menu_t *menu, App_t *apps, size_t count);
void refreshAppMenu(App_t **apps, Menu_t *mainMenu, size_t *appCount);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  SWO_PrintString("System init _ ");

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  //MX_USB_DEVICE_Init();
  MX_ADC1_Init();
  MX_SDIO_SD_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */

  f_mount(&SDFatFS, "/", 1);
  MX_USB_DEVICE_Init();

  SWO_PrintString("OK\n");
  SWO_PrintString("Screen & PB _ ");

  PB_Init(50);

  ssd1306_Init();
  ssd1306_SetWordWrap(true);

  SWO_PrintString("OK\n");

  splash();

  SWO_PrintString("Ready _______ OK\n");

  /*char testBuff[100];
  core_snprintf(testBuff, sizeof(testBuff), "Hello, %s %f !", "World", 12.5);
  SWO_PrintString(testBuff);*/

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  Menu_t mainMenu;
  mainMenu.entries = NULL;
  mainMenu.count = 0;

  App_t *apps = NULL;
  size_t appCount = 0;

  API_setPWM(htim2, 0, 0, 0);

  if(API_IO_ReadPB2()) {
    showDevices();

    while(!(API_getLastEvents() & EV_PB_RIGHT)) API_updateEvents();
  }

  refreshAppMenu(&apps, &mainMenu, &appCount);
  
  while (1) {
    API_updateEvents();

    if(API_getLastEvents() & EV_PB_LEFT) {
      UI_Menu_Prev(&mainMenu);
    }

    if(API_getLastEvents() & EV_PB_RIGHT) {
      UI_Menu_Next(&mainMenu);
    }

    if(API_getLastEvents() & EV_PB_MID) {
      loadScreen("Starting\napp...");
      API_apps_runApp(&apps[mainMenu.current->index]);
      
      refreshAppMenu(&apps, &mainMenu, &appCount);
    }

    UI_Menu_Draw(&mainMenu);
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
  Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
  Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void loadScreen(char *msg) {
  ssd1306_Fill(Black);
  ssd1306_SetCursor(0, 0);

  FIL fil;
  BMP_t bmp;

  BMP_zeroBMP(&bmp);

  if(f_open(&fil, "sys/hourglass.bmp", FA_READ) != FR_OK) {
    return;
  }

  BMP_setFile(&fil);

  BMP_Err_t err;
  err = BMP_parseFile(&bmp);

  if(err) {
    return;
  }
  
  err = BMP_readData(&bmp);

  if(err) {
    return;
  }

  BMP_blit(&bmp, 85, 18);
  BMP_release(&bmp);
  f_close(&fil);

  ssd1306_SetCursor(25, 18);
  ssd1306_WriteString(msg, Font_7x10, White);

  ssd1306_UpdateScreen();
}

App_t *loadApps(size_t *count) {
  size_t appCount = API_Apps_countApps();
  App_t *apps = (App_t*)malloc(appCount * sizeof(App_t));
  memset(apps, 0x00, appCount * sizeof(App_t));

  API_apps_getFiles(apps, appCount);
  API_apps_parseApps(apps, appCount);

  *count = appCount;

  return apps;
}

void buildAppsMenu(Menu_t *menu, App_t *apps, size_t count) {
  menu->name = "Applications";
  menu->count = count;
  menu->entries = (MenuEntry_t**)malloc(count * sizeof(MenuEntry_t*));

  if(!menu->entries) {
    API_DispERROR("ERROR :\nUnable to allocate\nmenu list.");

    while(1);
  }

  for(size_t i = 0; i < count; i++) {
    if(!apps[i].name) {
      continue;
    }

    menu->entries[i] = (MenuEntry_t*)malloc(sizeof(MenuEntry_t));

    if(!menu->entries[i]) {
      API_DispERROR("ERROR :\nUnable to allocate\nmenu entry.");

      while(1);
    }

    menu->entries[i]->name = apps[i].name;
    menu->entries[i]->index = i;
  }
}

void refreshAppMenu(App_t **apps, Menu_t *mainMenu, size_t *appCount) {
    loadScreen("Loading\napps... ");

    if(*apps) {
      free(*apps);
      *apps = NULL;
    }

    for(int i = 0; i < mainMenu->count; i ++) {
      free(mainMenu->entries[i]);
    }
    
    if(mainMenu->entries) {
      free(mainMenu->entries);
    }

    mainMenu->entries = NULL;
    mainMenu->current = NULL;
    mainMenu->count = 0;

    f_mount(&SDFatFS, "/", 1);

    *apps = loadApps(appCount);
    buildAppsMenu(mainMenu, *apps, *appCount);

    UI_Menu_Init(mainMenu);
}

void splash(void) {
  ssd1306_Fill(Black);
  ssd1306_SetCursor(0, 0);

  FIL fil;
  BMP_t bmp;

  BMP_zeroBMP(&bmp);

  if(f_open(&fil, "sys/splash.bmp", FA_READ) != FR_OK) {
    return;
  }

  BMP_setFile(&fil);

  BMP_Err_t err;
  err = BMP_parseFile(&bmp);

  if(err) {
    return;
  }
  
  err = BMP_readData(&bmp);

  if(err) {
    return;
  }

  BMP_blit(&bmp, 0, 0);
  BMP_release(&bmp);
  f_close(&fil);

  ssd1306_SetCursor(0, 42);
  ssd1306_WriteString("(c) Gregoire BOST", Font_7x10, White);

  ssd1306_UpdateScreen();

  for(int i = 0; i < 6; i++) {
    API_IO_ToggleLED();

    HAL_Delay(80);
  }

  HAL_Delay(2000);
}

void API_Quit() {
  /* DUMMY */
}

void showDevices(void) {

  /* *********** I2C *********** */
  bool dev[128];
  char buff[50];

  API_I2C_Scan(&hi2c1, dev);

  ssd1306_Fill(Black);
  ssd1306_SetCursor(0, 0);
  ssd1306_WriteString("Devices on I2C1 :\n", Font_6x8, White);

  uint8_t count = 0;

  for(uint8_t i = 0; i < 128; i++) {
    if(dev[i]) {
      snprintf(buff, sizeof(buff), "0x%02X,", i);

      ssd1306_WriteString(buff, Font_6x8, White);

      count ++;
    }
  }
  /* *************************** */

  /* *********** SD ************ */
  HAL_SD_CardInfoTypeDef info;
  HAL_SD_GetCardInfo(&hsd, &info);

  snprintf(buff, sizeof(buff), "SD Blocks : %lu\nBlock size : %lu", info.LogBlockNbr  - 1, info.LogBlockSize);

  ssd1306_SetCursor(0, 30);
  ssd1306_WriteString(buff, Font_6x8, White);

  ssd1306_UpdateScreen();

  if(count < 5) {
    API_DispERROR("ERROR :\nMissing I2C device");
  }
  /* *************************** */
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
