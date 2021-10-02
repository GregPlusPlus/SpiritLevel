#ifndef UTILS_H
#define UTILS_H

extern void (*UTILS_getStorageUsage)(uint32_t *free, uint32_t *total);
extern bool (*UTILS_checkExtension)(char *fn, char *ext);
extern uint8_t (*UTILS_readFile8)(FIL *f);
extern uint16_t (*UTILS_readFile16)(FIL *f);
extern uint32_t (*UTILS_readFile32)(FIL *f);
extern BMP_Err_t (*UTILS_drawBMP)(const char *fn, uint8_t x, uint8_t y);

#endif // UTILS_H