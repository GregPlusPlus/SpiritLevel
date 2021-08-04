#include "api_hook.h"

static void bad_hook(uint32_t id);

#define HOOK_CASE(labelName, id) case id : \
                                    addr = (uint32_t)&labelName; \
                                    break;

int core_snprintf(char * s, size_t n, const char *format, ...);

uint32_t API_hook(uint32_t id) {
    uint32_t addr = 0;

    switch(id) {
        HOOK_CASE(HAL_GetTick, API_HOOK_SYSTICK)
        HOOK_CASE(API_getLastEvents, API_HOOK_API_GET_LAST_EVENTS)
        HOOK_CASE(API_Quit, API_HOOK_API_QUIT)

        HOOK_CASE(API_DispERROR, API_HOOK_API_DISPERROR)

        HOOK_CASE(API_IO_SetFlashlight, API_HOOK_API_IO_SETFLASHLIGHT)
        HOOK_CASE(API_IO_SetLED, API_HOOK_API_IO_SETLED)
        HOOK_CASE(API_IO_ToggleLED, API_HOOK_API_IO_TOGGLELED)
        HOOK_CASE(API_IO_ReadPB1, API_HOOK_API_IO_READPB1)
        HOOK_CASE(API_IO_ReadPB2, API_HOOK_API_IO_READPB2)
        HOOK_CASE(API_IO_ReadPB3, API_HOOK_API_IO_READPB3)
        HOOK_CASE(API_ADC_ReadA0, API_HOOK_API_ADC_READA0)
        HOOK_CASE(API_RNG_GetEntropy, API_HOOK_API_RNG_GETENTROPY)
        HOOK_CASE(API_RNG_Init, API_HOOK_API_RNG_INIT)
        HOOK_CASE(API_RNG_randRange, API_HOOK_API_RNG_RANDRANGE)

        HOOK_CASE(API_BMX_ACC_Reset, API_HOOK_API_BMX_ACC_RESET)
        HOOK_CASE(API_BMX_ACC_SetRange, API_HOOK_API_BMX_ACC_SETRANGE)
        HOOK_CASE(API_BMX_ACC_GetRange, API_HOOK_API_BMX_ACC_GETRANGE)
        HOOK_CASE(API_BMX_ACC_GetQuantum, API_HOOK_API_BMX_ACC_GETQUANTUM)
        HOOK_CASE(API_BMX_ACC_Axis, API_HOOK_API_BMX_ACC_AXIS)
        HOOK_CASE(API_BMX_ACC_X, API_HOOK_API_BMX_ACC_X)
        HOOK_CASE(API_BMX_ACC_Y, API_HOOK_API_BMX_ACC_Y)
        HOOK_CASE(API_BMX_ACC_Z, API_HOOK_API_BMX_ACC_Z)
        HOOK_CASE(API_BMX_GetTilt, API_HOOK_API_BMX_GETTILT)
        
        HOOK_CASE(API_BMX_MAG_Reset, API_HOOK_API_BMX_MAG_RESET)
        HOOK_CASE(API_BMX_MAG_ReadReg, API_HOOK_API_BMX_MAG_READREG)
        HOOK_CASE(API_BMX_MAG_WriteReg, API_HOOK_API_BMX_MAG_WRITEREG)
        HOOK_CASE(API_BMX_MAG_ReadCTRLBits, API_HOOK_API_BMX_MAG_READCTRLBITS)
        HOOK_CASE(API_BMX_MAG_WriteCTRLBits, API_HOOK_API_BMX_MAG_WRITECTRLBITS)
        HOOK_CASE(API_BMX_MAG_getChipID, API_HOOK_API_BMX_MAG_GETCHIPID)
        HOOK_CASE(API_BMX_MAG_GetRate, API_HOOK_API_BMX_MAG_GETRATE)
        HOOK_CASE(API_BMX_MAG_SetRate, API_HOOK_API_BMX_MAG_SETRATE)
        HOOK_CASE(API_BMX_MAG_GetRepXY, API_HOOK_API_BMX_MAG_GETREPXY)
        HOOK_CASE(API_BMX_MAG_SetRepXY, API_HOOK_API_BMX_MAG_SETREPXY)
        HOOK_CASE(API_BMX_MAG_GetVal, API_HOOK_API_BMX_MAG_GETVAL)
        HOOK_CASE(API_BMX_MAG_GetMode, API_HOOK_API_BMX_MAG_GETMODE)
        HOOK_CASE(API_BMX_MAG_SetMode, API_HOOK_API_BMX_MAG_SETMODE)
        HOOK_CASE(API_BMX_MAG_ToggleSelfTest, API_HOOK_API_BMX_MAG_TOGGLESELFTEST)
        HOOK_CASE(API_BMX_MAG_SelfTest, API_HOOK_API_BMX_MAG_SELFTEST)
        HOOK_CASE(API_BMX_MAG_X, API_HOOK_API_BMX_MAG_X)
        HOOK_CASE(API_BMX_MAG_Y, API_HOOK_API_BMX_MAG_Y)
        HOOK_CASE(API_BMX_MAG_Z, API_HOOK_API_BMX_MAG_Z)

        HOOK_CASE(ssd1306_Init, API_HOOK_SSD1306_INIT)
        HOOK_CASE(ssd1306_Fill, API_HOOK_SSD1306_FILL)
        HOOK_CASE(ssd1306_UpdateScreen, API_HOOK_SSD1306_UPDATESCREEN)
        HOOK_CASE(ssd1306_DrawPixel, API_HOOK_SSD1306_DRAWPIXEL)
        HOOK_CASE(ssd1306_WriteChar, API_HOOK_SSD1306_WRITECHAR)
        HOOK_CASE(ssd1306_WriteString, API_HOOK_SSD1306_WRITESTRING)
        HOOK_CASE(ssd1306_SetCursor, API_HOOK_SSD1306_SETCURSOR)
        HOOK_CASE(ssd1306_SetWordWrap, API_HOOK_SSD1306_SETWORDWRAP)
        HOOK_CASE(ssd1306_Line, API_HOOK_SSD1306_LINE)
        HOOK_CASE(ssd1306_DrawArc, API_HOOK_SSD1306_DRAWARC)
        HOOK_CASE(ssd1306_DrawCircle, API_HOOK_SSD1306_DRAWCIRCLE)
        HOOK_CASE(ssd1306_Polyline, API_HOOK_SSD1306_POLYLINE)
        HOOK_CASE(ssd1306_DrawRectangle, API_HOOK_SSD1306_DRAWRECTANGLE)
        HOOK_CASE(ssd1306_DrawPlainRectangle, API_HOOK_SSD1306_DRAWPLAINRECTANGLE)
        HOOK_CASE(ssd1306_GetTextWidth, API_HOOK_SSD1306_GETTEXTWIDTH)
        HOOK_CASE(ssd1306_Reset, API_HOOK_SSD1306_RESET)
        HOOK_CASE(ssd1306_WriteCommand, API_HOOK_SSD1306_WRITECOMMAND)
        HOOK_CASE(ssd1306_WriteData, API_HOOK_SSD1306_WRITEDATA)
        HOOK_CASE(Font_6x8, API_HOOK_FONT_6X8)
        HOOK_CASE(Font_7x10, API_HOOK_FONT_7X10)
        HOOK_CASE(Font_11x18, API_HOOK_FONT_11X18)
        HOOK_CASE(Font_16x26, API_HOOK_FONT_16X26)

        HOOK_CASE(API_SHT_Reset, API_HOOK_API_SHT_RESET)
        HOOK_CASE(API_SHT_Write, API_HOOK_API_SHT_WRITE)
        HOOK_CASE(API_SHT_Read, API_HOOK_API_SHT_READ)
        HOOK_CASE(API_SHT_ReadUsrReg, API_HOOK_API_SHT_READUSRREG)
        HOOK_CASE(API_SHT_ReadVal, API_HOOK_API_SHT_READVAL)
        HOOK_CASE(API_SHT_ReadTemp, API_HOOK_API_SHT_READTEMP)
        HOOK_CASE(API_SHT_GetTemp, API_HOOK_API_SHT_GETTEMP)
        HOOK_CASE(API_SHT_ReadRH, API_HOOK_API_SHT_READRH)
        HOOK_CASE(API_SHT_GetRH, API_HOOK_API_SHT_GETRH)

        HOOK_CASE(API_LPS_Reset, API_HOOK_API_LPS_RESET)
        HOOK_CASE(API_LPS_Write, API_HOOK_API_LPS_WRITE)
        HOOK_CASE(API_LPS_Read, API_HOOK_API_LPS_READ)
        HOOK_CASE(API_LPS_OneShot, API_HOOK_API_LPS_ONESHOT)
        HOOK_CASE(API_LPS_GetPressure, API_HOOK_API_LPS_GETPRESSURE)
        HOOK_CASE(API_LPS_GetOffsetPressure, API_HOOK_API_LPS_GETOFFSETPRESSURE)
        HOOK_CASE(API_LPS_GetTemp, API_HOOK_API_LPS_GETTEMP)

        HOOK_CASE(f_open, API_HOOK_F_OPEN)
        HOOK_CASE(f_close, API_HOOK_F_CLOSE)
        HOOK_CASE(f_read, API_HOOK_F_READ)
        HOOK_CASE(f_write, API_HOOK_F_WRITE)
        HOOK_CASE(f_lseek, API_HOOK_F_LSEEK)
        HOOK_CASE(f_truncate, API_HOOK_F_TRUNCATE)
        HOOK_CASE(f_sync, API_HOOK_F_SYNC)
        HOOK_CASE(f_opendir, API_HOOK_F_OPENDIR)
        HOOK_CASE(f_closedir, API_HOOK_F_CLOSEDIR)
        HOOK_CASE(f_readdir, API_HOOK_F_READDIR)
        //HOOK_CASE(f_findfirst, API_HOOK_F_FINDFIRST)
        //HOOK_CASE(f_findnext, API_HOOK_F_FINDNEXT)
        HOOK_CASE(f_mkdir, API_HOOK_F_MKDIR)
        HOOK_CASE(f_unlink, API_HOOK_F_UNLINK)
        HOOK_CASE(f_rename, API_HOOK_F_RENAME)
        HOOK_CASE(f_stat, API_HOOK_F_STAT)
        //HOOK_CASE(f_chmod, API_HOOK_F_CHMOD)
        //HOOK_CASE(f_utime, API_HOOK_F_UTIME)
        //HOOK_CASE(f_chdir, API_HOOK_F_CHDIR)
        //HOOK_CASE(f_chdrive, API_HOOK_F_CHDRIVE)
        //HOOK_CASE(f_getcwd, API_HOOK_F_GETCWD)
        HOOK_CASE(f_getfree, API_HOOK_F_GETFREE)
        //HOOK_CASE(f_getlabel, API_HOOK_F_GETLABEL)
        //HOOK_CASE(f_setlabel, API_HOOK_F_SETLABEL)
        //HOOK_CASE(f_forward, API_HOOK_F_FORWARD)
        //HOOK_CASE(f_expand, API_HOOK_F_EXPAND)
        HOOK_CASE(f_mount, API_HOOK_F_MOUNT)
        HOOK_CASE(f_mkfs, API_HOOK_F_MKFS)
        //HOOK_CASE(f_fdisk, API_HOOK_F_FDISK)
        HOOK_CASE(f_putc, API_HOOK_F_PUTC)
        HOOK_CASE(f_puts, API_HOOK_F_PUTS)
        HOOK_CASE(f_printf, API_HOOK_F_PRINTF)
        HOOK_CASE(f_gets, API_HOOK_F_GETS)

#if !_FS_READONLY && !_FS_NORTC
        HOOK_CASE(get_fattime, API_HOOK_GET_FATTIME)
#endif

#if _USE_LFN != 0
        HOOK_CASE(ff_convert, API_HOOK_FF_CONVERT)
        HOOK_CASE(ff_wtoupper, API_HOOK_FF_WTOUPPER)
#if _USE_LFN == 3
        HOOK_CASE(ff_memalloc, API_HOOK_FF_MEMALLOC)
        HOOK_CASE(ff_memfree, API_HOOK_FF_MEMFREE)
#endif
#endif

#if _FS_REENTRANT
        HOOK_CASE(ff_cre_syncobj, API_HOOK_FF_CRE_SYNCOBJ)
        HOOK_CASE(ff_req_grant, API_HOOK_FF_REQ_GRANT)
        HOOK_CASE(ff_rel_grant, API_HOOK_FF_REL_GRANT)
        HOOK_CASE(ff_del_syncobj, API_HOOK_FF_DEL_SYNCOBJ)
#endif

        HOOK_CASE(SDFatFS, API_HOOK_GETFATFS)

        HOOK_CASE(BMP_setFile, API_HOOK_BMP_SETFILE)
        HOOK_CASE(BMP_zeroBMP, API_HOOK_BMP_ZEROBMP)
        HOOK_CASE(BMP_parseFile, API_HOOK_BMP_PARSEFILE)
        HOOK_CASE(BMP_check, API_HOOK_BMP_CHECK)
        HOOK_CASE(BMP_readData, API_HOOK_BMP_READDATA)
        HOOK_CASE(BMP_blit, API_HOOK_BMP_BLIT)
        HOOK_CASE(BMP_release, API_HOOK_BMP_RELEASE)

        HOOK_CASE(UI_Menu_Init, API_HOOK_UI_MENU_INIT)
        HOOK_CASE(UI_Menu_Draw, API_HOOK_UI_MENU_DRAW)
        HOOK_CASE(UI_Menu_Next, API_HOOK_UI_MENU_NEXT)
        HOOK_CASE(UI_Menu_Prev, API_HOOK_UI_MENU_PREV)

        HOOK_CASE(UI_Progressbar_Init, API_HOOK_UI_PROGRESSBAR_INIT)
        HOOK_CASE(UI_Progressbar_Setvalue, API_HOOK_UI_PROGRESSBAR_SETVALUE)
        HOOK_CASE(UI_Progressbar_Draw, API_HOOK_UI_PROGRESSBAR_DRAW)

        HOOK_CASE(UTILS_getStorageUsage, API_HOOK_UTILS_GETSTORAGEUSAGE)

        HOOK_CASE(API_updateEvents, API_HOOK_UPDATE_EVENTS)

        HOOK_CASE(HAL_Delay, API_HOOK_DELAY);

        HOOK_CASE(snprintf, API_HOOK_CORE_SNPRINTF);

        default:
        addr = 0;
            break;
    }

    if(!addr) {
        bad_hook(id);
    }

    return addr;
}

void bad_hook(uint32_t id) {
    char msg[200];
    snprintf(msg, sizeof(msg), "FATAL ERROR : Invalid function hook ID\n[id : 0x%08X]", (unsigned int)id);
    API_DispERROR(msg);
}

int core_snprintf(char * s, size_t n, const char *format, ...) {
        int ret = 0;

        va_list args;
        va_start(args, format);

        //ret = vsnprintf(s, n, format, args);

        va_end(args);

        return ret;
}
