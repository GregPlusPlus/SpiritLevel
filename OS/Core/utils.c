#include "utils.h"

void UTILS_getStorageUsage(uint32_t *free, uint32_t *total) {
    FATFS *fs;
    DWORD fre_clust, fre_sect, tot_sect;
    HAL_SD_CardInfoTypeDef info;

    HAL_SD_GetCardInfo(&hsd, &info);

    f_mount(&SDFatFS, "/", 1);
    f_getfree("/", &fre_clust, &fs);

    tot_sect = (fs->n_fatent - 2) * fs->csize;
    fre_sect = fre_clust * fs->csize;

    *free = (fre_sect * info.LogBlockSize);
    *total = (tot_sect * info.LogBlockSize);
}

bool UTILS_checkExtension(char *fn, char *ext) {
    const char *dot = strrchr(fn, '.');

    return strcmp(dot, ext) == 0;
}

uint8_t UTILS_readFile8(FIL *f) {
    UINT br;
    uint8_t c;
    
    f_read(f, &c, 1, &br);

    return c;
}

uint16_t UTILS_readFile16(FIL *f) {
    uint16_t val = 0;

    val |= ((uint16_t)UTILS_readFile8(f) << 8);
    val |= ((uint16_t)UTILS_readFile8(f));

    return val;
}

uint32_t UTILS_readFile32(FIL *f) {
    uint16_t val = 0;

    val |= ((uint16_t)UTILS_readFile16(f) << 16);
    val |= ((uint16_t)UTILS_readFile16(f));

    return val;
}
