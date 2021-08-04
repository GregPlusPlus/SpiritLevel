#ifndef API_HOOK_IDS_H
#define API_HOOK_IDS_H

// API

#define API_HOOK_SYSTICK                        0X00000001
#define API_HOOK_API_QUIT                       0x00000003

#define API_HOOK_API_DISPERROR                  0x00000004

#define API_HOOK_API_IO_SETFLASHLIGHT           0x00000005
#define API_HOOK_API_IO_SETLED                  0x00000006
#define API_HOOK_API_IO_TOGGLELED               0x00000007
#define API_HOOK_API_IO_READPB1                 0x00000008
#define API_HOOK_API_IO_READPB2                 0x00000009
#define API_HOOK_API_IO_READPB3                 0x0000000A

#define API_HOOK_API_ADC_READA0                 0x0000000B

#define API_HOOK_API_RNG_GETENTROPY             0x0000000C
#define API_HOOK_API_RNG_INIT                   0x0000000D
#define API_HOOK_API_RNG_RANDRANGE              0x0000000E

/// BMX

#define API_HOOK_API_BMX_ACC_RESET              0x0000000F
#define API_HOOK_API_BMX_ACC_SETRANGE           0x00000010
#define API_HOOK_API_BMX_ACC_GETRANGE           0x00000011
#define API_HOOK_API_BMX_ACC_GETQUANTUM         0x00000012
#define API_HOOK_API_BMX_ACC_AXIS               0x00000013
#define API_HOOK_API_BMX_ACC_X                  0x00000014
#define API_HOOK_API_BMX_ACC_Y                  0x00000015
#define API_HOOK_API_BMX_ACC_Z                  0x00000016
#define API_HOOK_API_BMX_GETTILT                0x00000017

#define API_HOOK_API_BMX_MAG_RESET              0x00000018
#define API_HOOK_API_BMX_MAG_READREG            0x00000019
#define API_HOOK_API_BMX_MAG_WRITEREG           0x0000001A
#define API_HOOK_API_BMX_MAG_READCTRLBITS       0x0000001B
#define API_HOOK_API_BMX_MAG_WRITECTRLBITS      0x0000001C
#define API_HOOK_API_BMX_MAG_GETCHIPID          0x0000001D
#define API_HOOK_API_BMX_MAG_GETRATE            0x0000001E
#define API_HOOK_API_BMX_MAG_SETRATE            0x0000001F
#define API_HOOK_API_BMX_MAG_GETREPXY           0x00000020
#define API_HOOK_API_BMX_MAG_SETREPXY           0x00000021
#define API_HOOK_API_BMX_MAG_GETVAL             0x00000022
#define API_HOOK_API_BMX_MAG_GETMODE            0x00000023
#define API_HOOK_API_BMX_MAG_SETMODE            0x00000024
#define API_HOOK_API_BMX_MAG_TOGGLESELFTEST     0x00000025
#define API_HOOK_API_BMX_MAG_SELFTEST           0x00000026
#define API_HOOK_API_BMX_MAG_X                  0x00000027
#define API_HOOK_API_BMX_MAG_Y                  0x00000028
#define API_HOOK_API_BMX_MAG_Z                  0x00000029

// SSD2306

#define API_HOOK_SSD1306_INIT                   0x0000002A
#define API_HOOK_SSD1306_FILL                   0x0000002B
#define API_HOOK_SSD1306_UPDATESCREEN           0x0000002C
#define API_HOOK_SSD1306_DRAWPIXEL              0x0000002D
#define API_HOOK_SSD1306_WRITECHAR              0x0000002E
#define API_HOOK_SSD1306_WRITESTRING            0x0000002F
#define API_HOOK_SSD1306_SETCURSOR              0x00000030
#define API_HOOK_SSD1306_SETWORDWRAP            0x00000031
#define API_HOOK_SSD1306_LINE                   0x00000032
#define API_HOOK_SSD1306_DRAWARC                0x00000033
#define API_HOOK_SSD1306_DRAWCIRCLE             0x00000034
#define API_HOOK_SSD1306_POLYLINE               0x00000035
#define API_HOOK_SSD1306_DRAWRECTANGLE          0x00000036
#define API_HOOK_SSD1306_DRAWPLAINRECTANGLE     0x00000037
#define API_HOOK_SSD1306_GETTEXTWIDTH           0x00000039
#define API_HOOK_SSD1306_RESET                  0x0000003A
#define API_HOOK_SSD1306_WRITECOMMAND           0x0000003B
#define API_HOOK_SSD1306_WRITEDATA              0x0000003C

#define API_HOOK_FONT_6X8                       0x0000003D
#define API_HOOK_FONT_7X10                      0x0000003E
#define API_HOOK_FONT_11X18                     0x0000003F
#define API_HOOK_FONT_16X26                     0x00000040

// SHT

#define API_HOOK_API_SHT_RESET                  0x00000041
#define API_HOOK_API_SHT_WRITE                  0x00000042
#define API_HOOK_API_SHT_READ                   0x00000043
#define API_HOOK_API_SHT_READUSRREG             0x00000044
#define API_HOOK_API_SHT_READVAL                0x00000045
#define API_HOOK_API_SHT_READTEMP               0x00000046
#define API_HOOK_API_SHT_GETTEMP                0x00000047
#define API_HOOK_API_SHT_READRH                 0x00000048
#define API_HOOK_API_SHT_GETRH                  0x00000049

// LPS

#define API_HOOK_API_LPS_RESET                  0x0000004A
#define API_HOOK_API_LPS_WRITE                  0x0000004B
#define API_HOOK_API_LPS_READ                   0x0000004C
#define API_HOOK_API_LPS_ONESHOT                0x0000004D
#define API_HOOK_API_LPS_GETPRESSURE            0x0000004E
#define API_HOOK_API_LPS_GETOFFSETPRESSURE      0x0000004F
#define API_HOOK_API_LPS_GETTEMP                0x00000050

// FATFS

#define API_HOOK_F_OPEN                         0x00000051
#define API_HOOK_F_CLOSE                        0x00000052
#define API_HOOK_F_READ                         0x00000053
#define API_HOOK_F_WRITE                        0x00000054
#define API_HOOK_F_LSEEK                        0x00000055
#define API_HOOK_F_TRUNCATE                     0x00000056
#define API_HOOK_F_SYNC                         0x00000057
#define API_HOOK_F_OPENDIR                      0x00000058
#define API_HOOK_F_CLOSEDIR                     0x00000059
#define API_HOOK_F_READDIR                      0x0000005A
#define API_HOOK_F_FINDFIRST                    0x0000005B
#define API_HOOK_F_FINDNEXT                     0x0000005C
#define API_HOOK_F_MKDIR                        0x0000005D
#define API_HOOK_F_UNLINK                       0x0000005E
#define API_HOOK_F_RENAME                       0x0000005F
#define API_HOOK_F_STAT                         0x00000060
#define API_HOOK_F_CHMOD                        0x00000061
#define API_HOOK_F_UTIME                        0x00000062
#define API_HOOK_F_CHDIR                        0x00000063
#define API_HOOK_F_CHDRIVE                      0x00000064
#define API_HOOK_F_GETCWD                       0x00000065
#define API_HOOK_F_GETFREE                      0x00000066
#define API_HOOK_F_GETLABEL                     0x00000067
#define API_HOOK_F_SETLABEL                     0x00000068
#define API_HOOK_F_FORWARD                      0x00000069
#define API_HOOK_F_EXPAND                       0x0000006A
#define API_HOOK_F_MOUNT                        0x0000006B
#define API_HOOK_F_MKFS                         0x0000006C
#define API_HOOK_F_FDISK                        0x0000006D
#define API_HOOK_F_PUTC                         0x0000006E
#define API_HOOK_F_PUTS                         0x0000006F
#define API_HOOK_F_PRINTF                       0x00000070
#define API_HOOK_F_GETS                         0x00000071

#define API_HOOK_GET_FATTIME                    0x00000072
#define API_HOOK_FF_CONVERT                     0x00000073
#define API_HOOK_FF_WTOUPPER                    0x00000074
#define API_HOOK_FF_MEMALLOC                    0x00000075
#define API_HOOK_FF_MEMFREE                     0x00000076
#define API_HOOK_FF_CRE_SYNCOBJ                 0x00000077
#define API_HOOK_FF_REQ_GRANT                   0x00000078
#define API_HOOK_FF_REL_GRANT                   0x00000079
#define API_HOOK_FF_DEL_SYNCOBJ                 0x0000007A

#define API_HOOK_GETFATFS                       0x0000007B

// UI / BMP

#define API_HOOK_BMP_SETFILE                    0x0000007C
#define API_HOOK_BMP_ZEROBMP                    0x0000007D
#define API_HOOK_BMP_PARSEFILE                  0x0000007E
#define API_HOOK_BMP_CHECK                      0x0000007F
#define API_HOOK_BMP_READDATA                   0x00000080
#define API_HOOK_BMP_BLIT                       0x00000081
#define API_HOOK_BMP_RELEASE                    0x00000082

// UI / MENU

#define API_HOOK_UI_MENU_INIT                   0x00000083
#define API_HOOK_UI_MENU_DRAW                   0x00000084
#define API_HOOK_UI_MENU_NEXT                   0x00000085
#define API_HOOK_UI_MENU_PREV                   0x00000086

// UI / PROGRESSBAR

#define API_HOOK_UI_PROGRESSBAR_INIT            0x00000087
#define API_HOOK_UI_PROGRESSBAR_SETVALUE        0x00000088
#define API_HOOK_UI_PROGRESSBAR_DRAW            0x00000089

// UTILS

#define API_HOOK_UTILS_GETSTORAGEUSAGE          0x0000008A

// API EVENTS
#define API_HOOK_API_GET_LAST_EVENTS            0x00000002
#define API_HOOK_UPDATE_EVENTS                  0x0000008B

// TIMING
#define API_HOOK_DELAY                          0x0000008C

// TEXT OUTPUT
#define API_HOOK_CORE_SNPRINTF                  0x0000008D

//#define API_HOOK_

#endif // API_HOOK_IDS_H