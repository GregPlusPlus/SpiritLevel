#include "api_hook.h"

static void bad_hook(const char *label);

#define HOOK_CASE(labelName) HOOK_CASE_NAMED(#labelName, labelName)
#define HOOK_CASE_NAMED(customLabelName, labelName) if(strcmp(customLabelName, label) == 0) {addr = (uint32_t)&labelName;}

uint32_t API_hook(const char *label) {
    uint32_t addr = 0;

    HOOK_CASE_NAMED("sysTick", HAL_GetTick)
    HOOK_CASE(API_getLastEvents)
    HOOK_CASE(API_Quit)

    HOOK_CASE(API_DispERROR)

    HOOK_CASE(API_IO_SetFlashlight)
    HOOK_CASE(API_IO_SetLED)
    HOOK_CASE(API_IO_ToggleLED)
    HOOK_CASE(API_IO_ReadPB1)
    HOOK_CASE(API_IO_ReadPB2)
    HOOK_CASE(API_IO_ReadPB3)
    HOOK_CASE(API_ADC_ReadA0)
    HOOK_CASE(API_RNG_GetEntropy)
    HOOK_CASE(API_RNG_Init)
    HOOK_CASE(API_RNG_randRange)

    HOOK_CASE(API_BMX_ACC_Reset)
    HOOK_CASE(API_BMX_ACC_SetRange)
    HOOK_CASE(API_BMX_ACC_GetRange)
    HOOK_CASE(API_BMX_ACC_GetQuantum)
    HOOK_CASE(API_BMX_ACC_Axis)
    HOOK_CASE(API_BMX_ACC_X)
    HOOK_CASE(API_BMX_ACC_Y)
    HOOK_CASE(API_BMX_ACC_Z)
    HOOK_CASE(API_BMX_GetTilt)

    HOOK_CASE(API_BMX_MAG_Reset)
    HOOK_CASE(API_BMX_MAG_ReadReg)
    HOOK_CASE(API_BMX_MAG_WriteReg)
    HOOK_CASE(API_BMX_MAG_ReadCTRLBits)
    HOOK_CASE(API_BMX_MAG_WriteCTRLBits)
    HOOK_CASE(API_BMX_MAG_getChipID)
    HOOK_CASE(API_BMX_MAG_GetRate)
    HOOK_CASE(API_BMX_MAG_SetRate)
    HOOK_CASE(API_BMX_MAG_GetRepXY)
    HOOK_CASE(API_BMX_MAG_SetRepXY)
    HOOK_CASE(API_BMX_MAG_GetVal)
    HOOK_CASE(API_BMX_MAG_GetMode)
    HOOK_CASE(API_BMX_MAG_SetMode)
    HOOK_CASE(API_BMX_MAG_ToggleSelfTest)
    HOOK_CASE(API_BMX_MAG_SelfTest)
    HOOK_CASE(API_BMX_MAG_X)
    HOOK_CASE(API_BMX_MAG_Y)
    HOOK_CASE(API_BMX_MAG_Z)

    HOOK_CASE(ssd1306_Init)
    HOOK_CASE(ssd1306_Fill)
    HOOK_CASE(ssd1306_UpdateScreen)
    HOOK_CASE(ssd1306_DrawPixel)
    HOOK_CASE(ssd1306_WriteChar)
    HOOK_CASE(ssd1306_WriteString)
    HOOK_CASE(ssd1306_SetCursor)
    HOOK_CASE(ssd1306_SetWordWrap)
    HOOK_CASE(ssd1306_Line)
    HOOK_CASE(ssd1306_DrawArc)
    HOOK_CASE(ssd1306_DrawCircle)
    HOOK_CASE(ssd1306_Polyline)
    HOOK_CASE(ssd1306_DrawRectangle)
    HOOK_CASE(ssd1306_DrawPlainRectangle)
    HOOK_CASE(ssd1306_GetTextWidth)
    HOOK_CASE(ssd1306_Reset)
    HOOK_CASE(ssd1306_WriteCommand)
    HOOK_CASE(ssd1306_WriteData)
    HOOK_CASE(Font_6x8)
    HOOK_CASE(Font_7x10)
    HOOK_CASE(Font_11x18)
    HOOK_CASE(Font_16x26)

    HOOK_CASE(API_SHT_Reset)
    HOOK_CASE(API_SHT_Write)
    HOOK_CASE(API_SHT_Read)
    HOOK_CASE(API_SHT_ReadUsrReg)
    HOOK_CASE(API_SHT_ReadVal)
    HOOK_CASE(API_SHT_ReadTemp)
    HOOK_CASE(API_SHT_GetTemp)
    HOOK_CASE(API_SHT_ReadRH)
    HOOK_CASE(API_SHT_GetRH)

    HOOK_CASE(API_LPS_Reset)
    HOOK_CASE(API_LPS_Write)
    HOOK_CASE(API_LPS_Read)
    HOOK_CASE(API_LPS_OneShot)
    HOOK_CASE(API_LPS_GetPressure)
    HOOK_CASE(API_LPS_GetOffsetPressure)
    HOOK_CASE(API_LPS_GetTemp)

    HOOK_CASE(f_open)
    HOOK_CASE(f_close)
    HOOK_CASE(f_read)
    HOOK_CASE(f_write)
    HOOK_CASE(f_lseek)
    HOOK_CASE(f_truncate)
    HOOK_CASE(f_sync)
    HOOK_CASE(f_opendir)
    HOOK_CASE(f_closedir)
    HOOK_CASE(f_readdir)
    //HOOK_CASE(f_findfirst)
    //HOOK_CASE(f_findnext)
    HOOK_CASE(f_mkdir)
    HOOK_CASE(f_unlink)
    HOOK_CASE(f_rename)
    HOOK_CASE(f_stat)
    //HOOK_CASE(f_chmod)
    //HOOK_CASE(f_utime)
    //HOOK_CASE(f_chdir)
    //HOOK_CASE(f_chdrive)
    //HOOK_CASE(f_getcwd)
    HOOK_CASE(f_getfree)
    //HOOK_CASE(f_getlabel)
    //HOOK_CASE(f_setlabel)
    //HOOK_CASE(f_forward)
    //HOOK_CASE(f_expand)
    HOOK_CASE(f_mount)
    HOOK_CASE(f_mkfs)
    //HOOK_CASE(f_fdisk)
    HOOK_CASE(f_putc)
    HOOK_CASE(f_puts)
    HOOK_CASE(f_printf)
    HOOK_CASE(f_gets)

#if !_FS_READONLY && !_FS_NORTC
    HOOK_CASE(get_fattime)
#endif

#if _USE_LFN != 0
    HOOK_CASE(ff_convert)
    HOOK_CASE(ff_wtoupper)
#if _USE_LFN == 3
    HOOK_CASE(ff_memalloc)
    HOOK_CASE(ff_memfree)
#endif
#endif

#if _FS_REENTRANT
    HOOK_CASE(ff_cre_syncobj)
    HOOK_CASE(ff_req_grant)
    HOOK_CASE(ff_rel_grant)
    HOOK_CASE(ff_del_syncobj)
#endif

    HOOK_CASE(SDFatFS)

    HOOK_CASE(BMP_setFile)
    HOOK_CASE(BMP_zeroBMP)
    HOOK_CASE(BMP_parseFile)
    HOOK_CASE(BMP_check)
    HOOK_CASE(BMP_readData)
    HOOK_CASE(BMP_blit)
    HOOK_CASE(BMP_setAlphaColor)
    HOOK_CASE(BMP_release)

    HOOK_CASE(UI_Menu_Init)
    HOOK_CASE(UI_Menu_Draw)
    HOOK_CASE(UI_Menu_Next)
    HOOK_CASE(UI_Menu_Prev)

    HOOK_CASE(UI_Progressbar_Init)
    HOOK_CASE(UI_Progressbar_Setvalue)
    HOOK_CASE(UI_Progressbar_Draw)

    HOOK_CASE(UTILS_getStorageUsage)
    HOOK_CASE(UTILS_checkExtension)
    HOOK_CASE(UTILS_readFile8)
    HOOK_CASE(UTILS_readFile16)
    HOOK_CASE(UTILS_readFile32)
    HOOK_CASE(UTILS_drawBMP)

    HOOK_CASE(API_updateEvents)

    HOOK_CASE_NAMED("Delay", HAL_Delay)

    HOOK_CASE_NAMED("core_snprintf", snprintf)

    if(!addr) {
        bad_hook(label);
    }

    return addr;
}

void bad_hook(const char *label) {
    API_DispERROR("FATAL ERROR: Unable to resolve hook label.\n[Requested : %s]", label);
}
