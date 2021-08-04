#include "hook.h"

#include "ssd1306.h"
#include "ff.h"
#include "bmp.h"
#include "ui.h"

uint32_t    API_hook_addr;

uint32_t    (*API_hook)(uint32_t id);

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

void HOOK_init(void) {
    API_hook                    = (uint32_t(*)(uint32_t))API_hook_addr;

    sysTick                     = (uint32_t(*)(void))API_hook(API_HOOK_SYSTICK);
    API_getLastEvents           = (Event_t (*)(void))API_hook(API_HOOK_API_GET_LAST_EVENTS);
    API_updateEvents            = (void(*)(void))API_hook(API_HOOK_UPDATE_EVENTS);
    API_Quit                    = (void (*)(void))API_hook(API_HOOK_API_QUIT);

    API_DispERROR               = (void (*)(char *))API_hook(API_HOOK_API_DISPERROR);

    API_IO_SetFlashlight        = (void (*)(uint8_t))API_hook(API_HOOK_API_IO_SETFLASHLIGHT);
    API_IO_SetLED               = (void (*)(bool))API_hook(API_HOOK_API_IO_SETLED);
    API_IO_ToggleLED            = (void (*)(void))API_hook(API_HOOK_API_IO_TOGGLELED);
    API_IO_ReadPB1              = (bool (*)(void))API_hook(API_HOOK_API_IO_READPB1);
    API_IO_ReadPB2              = (bool (*)(void))API_hook(API_HOOK_API_IO_READPB2);
    API_IO_ReadPB3              = (bool (*)(void))API_hook(API_HOOK_API_IO_READPB3);

    API_ADC_ReadA0              = (uint16_t (*)(void))API_hook(API_HOOK_API_ADC_READA0);

    API_RNG_GetEntropy          = (uint32_t (*)(void))API_hook(API_HOOK_API_RNG_GETENTROPY);
    API_RNG_Init                = (void (*)(void))API_hook(API_HOOK_API_RNG_INIT);
    API_RNG_randRange           = (int32_t (*)(int32_t, int32_t))API_hook(API_HOOK_API_RNG_RANDRANGE);

    API_BMX_ACC_Reset           = (void (*)(void))API_hook(API_HOOK_API_BMX_ACC_RESET);
    API_BMX_ACC_SetRange        = (void (*)(uint8_t))API_hook(API_HOOK_API_BMX_ACC_SETRANGE);
    API_BMX_ACC_GetRange        = (uint8_t (*)(void))API_hook(API_HOOK_API_BMX_ACC_GETRANGE);
    API_BMX_ACC_GetQuantum      = (float (*)(void))API_hook(API_HOOK_API_BMX_ACC_GETQUANTUM);
    API_BMX_ACC_Axis            = (int16_t (*)(bool *, uint8_t))API_hook(API_HOOK_API_BMX_ACC_AXIS);
    API_BMX_ACC_X               = (int16_t (*)(bool *))API_hook(API_HOOK_API_BMX_ACC_X);
    API_BMX_ACC_Y               = (int16_t (*)(bool *))API_hook(API_HOOK_API_BMX_ACC_Y);
    API_BMX_ACC_Z               = (int16_t (*)(bool *))API_hook(API_HOOK_API_BMX_ACC_Z);
    API_BMX_GetTilt             = (float (*)(bool *))API_hook(API_HOOK_API_BMX_GETTILT);

    API_BMX_MAG_Reset           = (void (*)(void))API_hook(API_HOOK_API_BMX_MAG_RESET);
    API_BMX_MAG_ReadReg         = (uint8_t (*)(uint8_t))API_hook(API_HOOK_API_BMX_MAG_READREG);
    API_BMX_MAG_WriteReg        = (void (*)(uint8_t, uint8_t))API_hook(API_HOOK_API_BMX_MAG_WRITEREG);
    API_BMX_MAG_ReadCTRLBits    = (uint8_t (*)(void))API_hook(API_HOOK_API_BMX_MAG_READCTRLBITS);
    API_BMX_MAG_WriteCTRLBits   = (void (*)(uint8_t))API_hook(API_HOOK_API_BMX_MAG_WRITECTRLBITS);
    API_BMX_MAG_getChipID       = (uint8_t (*)(void))API_hook(API_HOOK_API_BMX_MAG_GETCHIPID);
    API_BMX_MAG_GetRate         = (uint8_t (*)(void))API_hook(API_HOOK_API_BMX_MAG_GETRATE);
    API_BMX_MAG_SetRate         = (void (*)(uint8_t))API_hook(API_HOOK_API_BMX_MAG_SETRATE);
    API_BMX_MAG_GetRepXY        = (uint8_t (*)(void))API_hook(API_HOOK_API_BMX_MAG_GETREPXY);
    API_BMX_MAG_SetRepXY        = (void (*)(uint8_t))API_hook(API_HOOK_API_BMX_MAG_SETREPXY);
    API_BMX_MAG_GetVal          = (uint16_t (*)(uint8_t))API_hook(API_HOOK_API_BMX_MAG_GETVAL);
    API_BMX_MAG_GetMode         = (uint8_t (*)(void))API_hook(API_HOOK_API_BMX_MAG_GETMODE);
    API_BMX_MAG_SetMode         = (void (*)(uint8_t))API_hook(API_HOOK_API_BMX_MAG_SETMODE);
    API_BMX_MAG_ToggleSelfTest  = (void (*)(bool))API_hook(API_HOOK_API_BMX_MAG_TOGGLESELFTEST);
    API_BMX_MAG_SelfTest        = (uint8_t (*)(void))API_hook(API_HOOK_API_BMX_MAG_SELFTEST);
    API_BMX_MAG_X               = (int16_t (*)(void))API_hook(API_HOOK_API_BMX_MAG_X);
    API_BMX_MAG_Y               = (int16_t (*)(void))API_hook(API_HOOK_API_BMX_MAG_Y);
    API_BMX_MAG_Z               = (int16_t (*)(void))API_hook(API_HOOK_API_BMX_MAG_Z);

    ssd1306_Init                = (void (*)(void))API_hook(API_HOOK_SSD1306_INIT);
    ssd1306_Fill                = (void (*)(SSD1306_COLOR))API_hook(API_HOOK_SSD1306_FILL);
    ssd1306_UpdateScreen        = (void (*)(void))API_hook(API_HOOK_SSD1306_UPDATESCREEN);
    ssd1306_DrawPixel           = (void (*)(int32_t, int32_t, SSD1306_COLOR))API_hook(API_HOOK_SSD1306_DRAWPIXEL);
    ssd1306_WriteChar           = (char (*)(char, FontDef, SSD1306_COLOR))API_hook(API_HOOK_SSD1306_WRITECHAR);
    ssd1306_WriteString         = (char (*)(char*, FontDef, SSD1306_COLOR))API_hook(API_HOOK_SSD1306_WRITESTRING);
    ssd1306_SetCursor           = (void (*)(int32_t, int32_t))API_hook(API_HOOK_SSD1306_SETCURSOR);
    ssd1306_SetWordWrap         = (void (*)(bool))API_hook(API_HOOK_SSD1306_SETWORDWRAP);
    ssd1306_Line                = (void (*)(uint8_t, uint8_t, uint8_t, uint8_t, SSD1306_COLOR))API_hook(API_HOOK_SSD1306_LINE);
    ssd1306_DrawArc             = (void (*)(uint8_t, uint8_t, uint8_t, uint16_t, uint16_t, SSD1306_COLOR))API_hook(API_HOOK_SSD1306_DRAWARC);
    ssd1306_DrawCircle          = (void (*)(uint8_t, uint8_t, uint8_t, SSD1306_COLOR))API_hook(API_HOOK_SSD1306_DRAWCIRCLE);
    ssd1306_Polyline            = (void (*)(const SSD1306_VERTEX *, uint16_t, SSD1306_COLOR))API_hook(API_HOOK_SSD1306_POLYLINE);
    ssd1306_DrawRectangle       = (void (*)(uint8_t, uint8_t, uint8_t, uint8_t, SSD1306_COLOR))API_hook(API_HOOK_SSD1306_DRAWRECTANGLE);
    ssd1306_DrawPlainRectangle  = (void (*)(uint8_t, uint8_t, uint8_t, uint8_t, SSD1306_COLOR))API_hook(API_HOOK_SSD1306_DRAWPLAINRECTANGLE);
    ssd1306_GetTextWidth        = (int (*)(FontDef, const char *))API_hook(API_HOOK_SSD1306_GETTEXTWIDTH);
    ssd1306_Reset               = (void (*)(void))API_hook(API_HOOK_SSD1306_RESET);
    ssd1306_WriteCommand        = (void (*)(uint8_t))API_hook(API_HOOK_SSD1306_WRITECOMMAND);
    ssd1306_WriteData           = (void (*)(uint8_t*, size_t))API_hook(API_HOOK_SSD1306_WRITEDATA);

    Font_6x8                    = (FontDef *)API_hook(API_HOOK_FONT_6X8);
    Font_7x10                   = (FontDef *)API_hook(API_HOOK_FONT_7X10);
    Font_11x18                  = (FontDef *)API_hook(API_HOOK_FONT_11X18);
    Font_16x26                  = (FontDef *)API_hook(API_HOOK_FONT_16X26);

    API_SHT_Reset               = (void (*)(void))API_hook(API_HOOK_API_SHT_RESET);
    API_SHT_Write               = (void (*)(uint8_t bits))API_hook(API_HOOK_API_SHT_WRITE);
    API_SHT_Read                = (uint8_t (*)(void))API_hook(API_HOOK_API_SHT_READ);
    API_SHT_ReadUsrReg          = (uint8_t (*)(void))API_hook(API_HOOK_API_SHT_READUSRREG);
    API_SHT_ReadVal             = (uint32_t (*)(uint8_t command))API_hook(API_HOOK_API_SHT_READVAL);
    API_SHT_ReadTemp            = (uint32_t (*)(void))API_hook(API_HOOK_API_SHT_READTEMP);
    API_SHT_GetTemp             = (float (*)(void))API_hook(API_HOOK_API_SHT_GETTEMP);
    API_SHT_ReadRH              = (uint32_t (*)(void))API_hook(API_HOOK_API_SHT_READRH);
    API_SHT_GetRH               = (float (*)(void))API_hook(API_HOOK_API_SHT_GETRH);

    API_LPS_Reset               = (void (*)(void))API_hook(API_HOOK_API_LPS_RESET);
    API_LPS_Write               = (void (*)(uint8_t addr, uint8_t bits))API_hook(API_HOOK_API_LPS_WRITE);
    API_LPS_Read                = (uint8_t (*)(uint8_t addr))API_hook(API_HOOK_API_LPS_READ);
    API_LPS_OneShot             = (void (*)(void))API_hook(API_HOOK_API_LPS_ONESHOT);
    API_LPS_GetPressure         = (int32_t (*)(void))API_hook(API_HOOK_API_LPS_GETPRESSURE);
    API_LPS_GetOffsetPressure   = (int16_t (*)(void))API_hook(API_HOOK_API_LPS_GETOFFSETPRESSURE);
    API_LPS_GetTemp             = (int16_t (*)(void))API_hook(API_HOOK_API_LPS_GETTEMP);

    f_open                      = (FRESULT (*)(FIL*, const TCHAR*, BYTE))API_hook(API_HOOK_F_OPEN);
    f_close                     = (FRESULT (*)(FIL*))API_hook(API_HOOK_F_CLOSE);
    f_read                      = (FRESULT (*)(FIL*, void*, UINT, UINT*))API_hook(API_HOOK_F_READ);
    f_write                     = (FRESULT (*)(FIL*, const void*, UINT, UINT*))API_hook(API_HOOK_F_WRITE);
    f_lseek                     = (FRESULT (*)(FIL*, FSIZE_t))API_hook(API_HOOK_F_LSEEK);
    f_truncate                  = (FRESULT (*)(FIL*))API_hook(API_HOOK_F_TRUNCATE);
    f_sync                      = (FRESULT (*)(FIL*))API_hook(API_HOOK_F_SYNC);
    f_opendir                   = (FRESULT (*)(DIR*, const TCHAR*))API_hook(API_HOOK_F_OPENDIR);
    f_closedir                  = (FRESULT (*)(DIR*))API_hook(API_HOOK_F_CLOSEDIR);
    f_readdir                   = (FRESULT (*)(DIR*, FILINFO*))API_hook(API_HOOK_F_READDIR);
    //f_findfirst                 = (FRESULT (*)(DIR*, FILINFO*, const TCHAR*, const TCHAR*))API_hook(API_HOOK_F_FINDFIRST);
    //f_findnext                  = (FRESULT (*)(DIR*, FILINFO*))API_hook(API_HOOK_F_FINDNEXT);
    f_mkdir                     = (FRESULT (*)(const TCHAR*))API_hook(API_HOOK_F_MKDIR);
    f_unlink                    = (FRESULT (*)(const TCHAR*))API_hook(API_HOOK_F_UNLINK);
    f_rename                    = (FRESULT (*)(const TCHAR*, const TCHAR*))API_hook(API_HOOK_F_RENAME);
    f_stat                      = (FRESULT (*)(const TCHAR*, FILINFO*))API_hook(API_HOOK_F_STAT);
    //f_chmod                     = (FRESULT (*)(const TCHAR*, BYTE, BYTE))API_hook(API_HOOK_F_CHMOD);
    //f_utime                     = (FRESULT (*)(const TCHAR*, const FILINFO*))API_hook(API_HOOK_F_UTIME);
    //f_chdir                     = (FRESULT (*)(const TCHAR*))API_hook(API_HOOK_F_CHDIR);
    //f_chdrive                   = (FRESULT (*)(const TCHAR*))API_hook(API_HOOK_F_CHDRIVE);
    //f_getcwd                    = (FRESULT (*)(TCHAR*, UINT))API_hook(API_HOOK_F_GETCWD);
    f_getfree                   = (FRESULT (*)(const TCHAR*, DWORD*, FATFS**))API_hook(API_HOOK_F_GETFREE);
    //f_getlabel                  = (FRESULT (*)(const TCHAR*, TCHAR*, DWORD*))API_hook(API_HOOK_F_GETLABEL);
    //f_setlabel                  = (FRESULT (*)(const TCHAR*))API_hook(API_HOOK_F_SETLABEL);
    //f_forward                   = (FRESULT (*)(FIL*, UINT(*)(const BYTE*,UINT), UINT, UINT*))API_hook(API_HOOK_F_FORWARD);
    //f_expand                    = (FRESULT (*)(FIL*, FSIZE_t, BYTE))API_hook(API_HOOK_F_EXPAND);
    f_mount                     = (FRESULT (*)(FATFS*, const TCHAR*, BYTE))API_hook(API_HOOK_F_MOUNT);
    f_mkfs                      = (FRESULT (*)(const TCHAR*, BYTE, DWORD, void*, UINT))API_hook(API_HOOK_F_MKFS);
    //f_fdisk                     = (FRESULT (*)(BYTE, const DWORD*, void*))API_hook(API_HOOK_F_FDISK);
    f_putc                      = (int (*)(TCHAR, FIL*))API_hook(API_HOOK_F_PUTC);
    f_puts                      = (int (*)(const TCHAR*, FIL*))API_hook(API_HOOK_F_PUTS);
    f_printf                    = (int (*)(FIL*, const TCHAR*, ...))API_hook(API_HOOK_F_PRINTF);
    f_gets                      = (TCHAR* (*)(TCHAR*, int, FIL*))API_hook(API_HOOK_F_GETS);
    SDFatFS                     = (FATFS*)API_hook(API_HOOK_GETFATFS);

#if !_FS_READONLY && !_FS_NORTC
    get_fattime                 = (DWORD (*)(void))API_hook(API_HOOK_GET_FATTIME);
#endif

#if _USE_LFN != 0
    ff_convert                  = (WCHAR (*)(WCHAR chr, UINT dir))API_hook(API_HOOK_FF_CONVERT);
    ff_wtoupper                 = (WCHAR (*)(WCHAR chr))API_hook(API_HOOK_FF_WTOUPPER);
#if _USE_LFN == 3
    ff_memalloc                 = (void* (*)(UINT msize))API_hook(API_HOOK_FF_MEMALLOC);
    ff_memfree                  = (void (*)(void* mblock))API_hook(API_HOOK_FF_MEMFREE);
#endif
#endif

#if _FS_REENTRANT
    ff_cre_syncobj              = (int (*)(BYTE vol, _SYNC_t* sobj))API_hook(API_HOOK_FF_CRE_SYNCOBJ);
    ff_req_grant                = (int (*)(_SYNC_t sobj))API_hook(API_HOOK_FF_REQ_GRANT);
    ff_rel_grant                = (void (*ff_rel_grant)(_SYNC_t sobj))API_hook(API_HOOK_FF_REL_GRANT);
    ff_del_syncobj              = (int (*)(_SYNC_t sobj))API_hook(API_HOOK_FF_DEL_SYNCOBJ);
#endif

    BMP_setFile                 = (void (*)(FIL *_fp))API_hook(API_HOOK_BMP_SETFILE);
    BMP_zeroBMP                 = (void (*)(BMP_t *bmp))API_hook(API_HOOK_BMP_ZEROBMP);
    BMP_parseFile               = (BMP_Err_t (*)(BMP_t *bmp))API_hook(API_HOOK_BMP_PARSEFILE);
    BMP_check                   = (BMP_Err_t (*)(BMP_t *bmp))API_hook(API_HOOK_BMP_CHECK);
    BMP_readData                = (BMP_Err_t (*)(BMP_t *bmp))API_hook(API_HOOK_BMP_READDATA);
    BMP_blit                    = (BMP_Err_t (*)(BMP_t *bmp, uint32_t _x, uint32_t _y))API_hook(API_HOOK_BMP_BLIT);
    BMP_release                 = (void (*)(BMP_t *bmp))API_hook(API_HOOK_BMP_RELEASE);

    UI_Menu_Init                = (void (*)(Menu_t *menu))API_hook(API_HOOK_UI_MENU_INIT);
    UI_Menu_Draw                = (void (*)(Menu_t *menu))API_hook(API_HOOK_UI_MENU_DRAW);
    UI_Menu_Next                = (void (*)(Menu_t *menu))API_hook(API_HOOK_UI_MENU_NEXT);
    UI_Menu_Prev                = (void (*)(Menu_t *menu))API_hook(API_HOOK_UI_MENU_PREV);

    UI_Progressbar_Init         = (void (*)(Progressbar_t *pb, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint32_t max))API_hook(API_HOOK_UI_PROGRESSBAR_INIT);
    UI_Progressbar_Setvalue     = (void (*)(Progressbar_t *pb, uint32_t value))API_hook(API_HOOK_UI_PROGRESSBAR_SETVALUE);
    UI_Progressbar_Draw         = (void (*)(Progressbar_t *pb))API_hook(API_HOOK_UI_PROGRESSBAR_DRAW);

    UTILS_getStorageUsage       = (void (*)(uint32_t *free, uint32_t *total))API_hook(API_HOOK_UTILS_GETSTORAGEUSAGE);
}
