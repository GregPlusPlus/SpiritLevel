#include "hook.h"

#include "ssd1306.h"
#include "ff.h"
#include "bmp.h"
#include "ui.h"

#define _HOOK(label) hookFunction((uint32_t*)&label, #label);

uint32_t    API_hook_addr;

uint32_t    (*API_hook)(const char *label);

uint32_t    (*sysTick)(void);
Event_t     (*API_getLastEvents)(void);
void        (*API_updateEvents)(void);
void        (*API_Quit)(void);

void        (*API_DispERROR)(char *str);

void        (*API_IO_SetFlashlight)(uint8_t value);
void        (*API_IO_SetLED)(bool state);
void        (*API_IO_ToggleLED)(void);
bool        (*API_IO_ReadPB1)(void);
bool        (*API_IO_ReadPB2)(void);
bool        (*API_IO_ReadPB3)(void);

uint16_t    (*API_ADC_ReadA0)(void);

uint32_t    (*API_RNG_GetEntropy)(void);
void        (*API_RNG_Init)(void);
int32_t     (*API_RNG_randRange)(int32_t min, int32_t max);

void        (*API_BMX_ACC_Reset)(void);
void        (*API_BMX_ACC_SetRange)(uint8_t range);
uint8_t     (*API_BMX_ACC_GetRange)(void);
float       (*API_BMX_ACC_GetQuantum)(void);
int16_t     (*API_BMX_ACC_Axis)(bool *avail, uint8_t startReg);
int16_t     (*API_BMX_ACC_X)(bool *avail);
int16_t     (*API_BMX_ACC_Y)(bool *avail);
int16_t     (*API_BMX_ACC_Z)(bool *avail);
float       (*API_BMX_GetTilt)(bool *avail);

void        (*API_BMX_MAG_Reset)(void);
uint8_t     (*API_BMX_MAG_ReadReg)(uint8_t reg);
void        (*API_BMX_MAG_WriteReg)(uint8_t reg, uint8_t bits);
uint8_t     (*API_BMX_MAG_ReadCTRLBits)(void);
void        (*API_BMX_MAG_WriteCTRLBits)(uint8_t bits);
uint8_t     (*API_BMX_MAG_getChipID)(void);
uint8_t     (*API_BMX_MAG_GetRate)(void);
void        (*API_BMX_MAG_SetRate)(uint8_t rate);
uint8_t     (*API_BMX_MAG_GetRepXY)(void);
void        (*API_BMX_MAG_SetRepXY)(uint8_t rep);
uint16_t    (*API_BMX_MAG_GetVal)(uint8_t startReg);
uint8_t     (*API_BMX_MAG_GetMode)(void);
void        (*API_BMX_MAG_SetMode)(uint8_t mode);
void        (*API_BMX_MAG_ToggleSelfTest)(bool selfTest);
uint8_t     (*API_BMX_MAG_SelfTest)(void);
int16_t     (*API_BMX_MAG_X)(void);
int16_t     (*API_BMX_MAG_Y)(void);
int16_t     (*API_BMX_MAG_Z)(void);

void        (*ssd1306_Init)(void);
void        (*ssd1306_Fill)(SSD1306_COLOR color);
void        (*ssd1306_UpdateScreen)(void);
void        (*ssd1306_DrawPixel)(int32_t x, int32_t y, SSD1306_COLOR color);
char        (*ssd1306_WriteChar)(char ch, FontDef Font, SSD1306_COLOR color);
char        (*ssd1306_WriteString)(char* str, FontDef Font, SSD1306_COLOR color);
void        (*ssd1306_SetCursor)(int32_t x, int32_t y);
void        (*ssd1306_SetWordWrap)(bool enabled);
void        (*ssd1306_Line)(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
void        (*ssd1306_DrawArc)(uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, SSD1306_COLOR color);
void        (*ssd1306_DrawCircle)(uint8_t par_x, uint8_t par_y, uint8_t par_r, SSD1306_COLOR color);
void        (*ssd1306_Polyline)(const SSD1306_VERTEX *par_vertex, uint16_t par_size, SSD1306_COLOR color);
void        (*ssd1306_DrawRectangle)(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
void        (*ssd1306_DrawPlainRectangle)(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
int         (*ssd1306_GetTextWidth)(FontDef Font, const char *str);
void        (*ssd1306_Reset)(void);
void        (*ssd1306_WriteCommand)(uint8_t byte);
void        (*ssd1306_WriteData)(uint8_t* buffer, size_t buff_size);

FontDef     *Font_6x8;
FontDef     *Font_7x10;
FontDef     *Font_11x18;
FontDef     *Font_16x26;

void        (*API_SHT_Reset)(void);
void        (*API_SHT_Write)(uint8_t bits);
uint8_t     (*API_SHT_Read)(void);
uint8_t     (*API_SHT_ReadUsrReg)(void);
uint32_t    (*API_SHT_ReadVal)(uint8_t command);
uint32_t    (*API_SHT_ReadTemp)(void);
float       (*API_SHT_GetTemp)(void);
uint32_t    (*API_SHT_ReadRH)(void);
float       (*API_SHT_GetRH)(void);

void        (*API_LPS_Reset)(void);
void        (*API_LPS_Write)(uint8_t addr, uint8_t bits);
uint8_t     (*API_LPS_Read)(uint8_t addr);
void        (*API_LPS_OneShot)(void);
int32_t     (*API_LPS_GetPressure)(void);
int16_t     (*API_LPS_GetOffsetPressure)(void);
int16_t     (*API_LPS_GetTemp)(void);

FRESULT     (*f_open)(FIL* fp, const TCHAR* path, BYTE mode);
FRESULT     (*f_close)(FIL* fp);
FRESULT     (*f_read)(FIL* fp, void* buff, UINT btr, UINT* br);
FRESULT     (*f_write)(FIL* fp, const void* buff, UINT btw, UINT* bw);
FRESULT     (*f_lseek)(FIL* fp, FSIZE_t ofs);
FRESULT     (*f_truncate)(FIL* fp);
FRESULT     (*f_sync)(FIL* fp);
FRESULT     (*f_opendir)(DIR* dp, const TCHAR* path);
FRESULT     (*f_closedir)(DIR* dp);
FRESULT     (*f_readdir)(DIR* dp, FILINFO* fno);
FRESULT     (*f_findfirst)(DIR* dp, FILINFO* fno, const TCHAR* path, const TCHAR* pattern);
FRESULT     (*f_findnext)(DIR* dp, FILINFO* fno);
FRESULT     (*f_mkdir)(const TCHAR* path);
FRESULT     (*f_unlink)(const TCHAR* path);
FRESULT     (*f_rename)(const TCHAR* path_old, const TCHAR* path_new);
FRESULT     (*f_stat)(const TCHAR* path, FILINFO* fno);
FRESULT     (*f_chmod)(const TCHAR* path, BYTE attr, BYTE mask);
FRESULT     (*f_utime)(const TCHAR* path, const FILINFO* fno);
FRESULT     (*f_chdir)(const TCHAR* path);
FRESULT     (*f_chdrive)(const TCHAR* path);
FRESULT     (*f_getcwd)(TCHAR* buff, UINT len);
FRESULT     (*f_getfree)(const TCHAR* path, DWORD* nclst, FATFS** fatfs);
FRESULT     (*f_getlabel)(const TCHAR* path, TCHAR* label, DWORD* vsn);
FRESULT     (*f_setlabel)(const TCHAR* label);
FRESULT     (*f_forward)(FIL* fp, UINT(*func)(const BYTE*,UINT), UINT btf, UINT* bf);
FRESULT     (*f_expand)(FIL* fp, FSIZE_t szf, BYTE opt);
FRESULT     (*f_mount)(FATFS* fs, const TCHAR* path, BYTE opt);
FRESULT     (*f_mkfs)(const TCHAR* path, BYTE opt, DWORD au, void* work, UINT len);
FRESULT     (*f_fdisk)(BYTE pdrv, const DWORD* szt, void* work);
int         (*f_putc)(TCHAR c, FIL* fp);
int         (*f_puts)(const TCHAR* str, FIL* cp);
int         (*f_printf)(FIL* fp, const TCHAR* str, ...);
TCHAR*      (*f_gets)(TCHAR* buff, int len, FIL* fp);
FATFS       *SDFatFS;

#if !_FS_READONLY && !_FS_NORTC
DWORD (*get_fattime) (void);
#endif

#if _USE_LFN != 0
WCHAR       (*ff_convert) (WCHAR chr, UINT dir);
WCHAR       (*ff_wtoupper) (WCHAR chr);
#if _USE_LFN == 3
void*       (*ff_memalloc) (UINT msize);
void        (*ff_memfree) (void* mblock);
#endif
#endif

#if _FS_REENTRANT
int         (*ff_cre_syncobj) (BYTE vol, _SYNC_t* sobj);
int         (*ff_req_grant) (_SYNC_t sobj);
void        (*ff_rel_grant) (_SYNC_t sobj);
int         (*ff_del_syncobj) (_SYNC_t sobj);
#endif

void (*BMP_setFile)(FIL *_fp);
void (*BMP_zeroBMP)(BMP_t *bmp);
BMP_Err_t (*BMP_parseFile)(BMP_t *bmp);
BMP_Err_t (*BMP_check)(BMP_t *bmp);
BMP_Err_t (*BMP_readData)(BMP_t *bmp);
BMP_Err_t (*BMP_blit)(BMP_t *bmp, uint32_t _x, uint32_t _y);
void (*BMP_release)(BMP_t *bmp);

void (*UI_Menu_Init)(Menu_t *menu);
void (*UI_Menu_Draw)(Menu_t *menu);
void (*UI_Menu_Next)(Menu_t *menu);
void (*UI_Menu_Prev)(Menu_t *menu);

void (*UI_Progressbar_Init)(Progressbar_t *pb, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint32_t max);
void (*UI_Progressbar_Setvalue)(Progressbar_t *pb, uint32_t value);
void (*UI_Progressbar_Draw)(Progressbar_t *pb);

void (*UTILS_getStorageUsage)(uint32_t *free, uint32_t *total);

void (*Delay)(uint32_t ms);

int (*core_snprintf)(char *s, size_t n, const char * format, ...);

void hookFunction(uint32_t *f, const char *label) {
    *f = API_hook(label);
}

void HOOK_init(void) {
    API_hook                    = (uint32_t(*)(const char *label))API_hook_addr;

    _HOOK(sysTick)
    _HOOK(API_getLastEvents)
    _HOOK(API_updateEvents)
    _HOOK(API_Quit)

    _HOOK(API_DispERROR)

    _HOOK(API_IO_SetFlashlight)
    _HOOK(API_IO_SetLED)
    _HOOK(API_IO_ToggleLED)
    _HOOK(API_IO_ReadPB1)
    _HOOK(API_IO_ReadPB2)
    _HOOK(API_IO_ReadPB3)

    _HOOK(API_ADC_ReadA0)

    _HOOK(API_RNG_GetEntropy)
    _HOOK(API_RNG_Init)
    _HOOK(API_RNG_randRange)

    _HOOK(API_BMX_ACC_Reset)
    _HOOK(API_BMX_ACC_SetRange)
    _HOOK(API_BMX_ACC_GetRange)
    _HOOK(API_BMX_ACC_GetQuantum)
    _HOOK(API_BMX_ACC_Axis)
    _HOOK(API_BMX_ACC_X)
    _HOOK(API_BMX_ACC_Y)
    _HOOK(API_BMX_ACC_Z)
    _HOOK(API_BMX_GetTilt)

    _HOOK(API_BMX_MAG_Reset)
    _HOOK(API_BMX_MAG_ReadReg)
    _HOOK(API_BMX_MAG_WriteReg)
    _HOOK(API_BMX_MAG_ReadCTRLBits)
    _HOOK(API_BMX_MAG_WriteCTRLBits)
    _HOOK(API_BMX_MAG_getChipID)
    _HOOK(API_BMX_MAG_GetRate)
    _HOOK(API_BMX_MAG_SetRate)
    _HOOK(API_BMX_MAG_GetRepXY)
    _HOOK(API_BMX_MAG_SetRepXY)
    _HOOK(API_BMX_MAG_GetVal)
    _HOOK(API_BMX_MAG_GetMode)
    _HOOK(API_BMX_MAG_SetMode)
    _HOOK(API_BMX_MAG_ToggleSelfTest)
    _HOOK(API_BMX_MAG_SelfTest)
    _HOOK(API_BMX_MAG_X)
    _HOOK(API_BMX_MAG_Y)
    _HOOK(API_BMX_MAG_Z)

    _HOOK(ssd1306_Init)
    _HOOK(ssd1306_Fill)
    _HOOK(ssd1306_UpdateScreen)
    _HOOK(ssd1306_DrawPixel)
    _HOOK(ssd1306_WriteChar)
    _HOOK(ssd1306_WriteString)
    _HOOK(ssd1306_SetCursor)
    _HOOK(ssd1306_SetWordWrap)
    _HOOK(ssd1306_Line)
    _HOOK(ssd1306_DrawArc)
    _HOOK(ssd1306_DrawCircle)
    _HOOK(ssd1306_Polyline)
    _HOOK(ssd1306_DrawRectangle)
    _HOOK(ssd1306_DrawPlainRectangle)
    _HOOK(ssd1306_GetTextWidth)
    _HOOK(ssd1306_Reset)
    _HOOK(ssd1306_WriteCommand)
    _HOOK(ssd1306_WriteData)

    _HOOK(Font_6x8)
    _HOOK(Font_7x10)
    _HOOK(Font_11x18)
    _HOOK(Font_16x26)

    _HOOK(API_SHT_Reset)
    _HOOK(API_SHT_Write)
    _HOOK(API_SHT_Read)
    _HOOK(API_SHT_ReadUsrReg)
    _HOOK(API_SHT_ReadVal)
    _HOOK(API_SHT_ReadTemp)
    _HOOK(API_SHT_GetTemp)
    _HOOK(API_SHT_ReadRH)
    _HOOK(API_SHT_GetRH)

    _HOOK(API_LPS_Reset)
    _HOOK(API_LPS_Write)
    _HOOK(API_LPS_Read)
    _HOOK(API_LPS_OneShot)
    _HOOK(API_LPS_GetPressure)
    _HOOK(API_LPS_GetOffsetPressure)
    _HOOK(API_LPS_GetTemp)

    _HOOK(f_open)
    _HOOK(f_close)
    _HOOK(f_read)
    _HOOK(f_write)
    _HOOK(f_lseek)
    _HOOK(f_truncate)
    _HOOK(f_sync)
    _HOOK(f_opendir)
    _HOOK(f_closedir)
    _HOOK(f_readdir)
    //_HOOK(f_findfirst)
    //_HOOK(f_findnext)
    _HOOK(f_mkdir)
    _HOOK(f_unlink)
    _HOOK(f_rename)
    _HOOK(f_stat)
    //_HOOK(f_chmod)
    //_HOOK(f_utime)
    //_HOOK(f_chdir)
    //_HOOK(f_chdrive)
    //_HOOK(f_getcwd)
    _HOOK(f_getfree)
    //_HOOK(f_getlabel)
    //_HOOK(f_setlabel)
    //_HOOK(f_forward)
    //_HOOK(f_expand)
    _HOOK(f_mount)
    _HOOK(f_mkfs)
    //_HOOK(f_fdisk)
    _HOOK(f_putc)
    _HOOK(f_puts)
    _HOOK(f_printf)
    _HOOK(f_gets)
    _HOOK(SDFatFS)

#if !_FS_READONLY && !_FS_NORTC
    _HOOK(get_fattime)
#endif

#if _USE_LFN != 0
    _HOOK(ff_convert)
    _HOOK(ff_wtoupper)
#if _USE_LFN == 3
    _HOOK(ff_memalloc)
    _HOOK(ff_memfree)
#endif
#endif

#if _FS_REENTRANT
    _HOOK(ff_cre_syncobj)
    _HOOK(ff_req_grant)
    _HOOK(ff_rel_grant)
    _HOOK(ff_del_syncobj)
#endif

    _HOOK(BMP_setFile)
    _HOOK(BMP_zeroBMP)
    _HOOK(BMP_parseFile)
    _HOOK(BMP_check)
    _HOOK(BMP_readData)
    _HOOK(BMP_blit)
    _HOOK(BMP_release)

    _HOOK(UI_Menu_Init)
    _HOOK(UI_Menu_Draw)
    _HOOK(UI_Menu_Next)
    _HOOK(UI_Menu_Prev)

    _HOOK(UI_Progressbar_Init)
    _HOOK(UI_Progressbar_Setvalue)
    _HOOK(UI_Progressbar_Draw)

    _HOOK(UTILS_getStorageUsage)

    _HOOK(Delay)

    _HOOK(core_snprintf)
}
