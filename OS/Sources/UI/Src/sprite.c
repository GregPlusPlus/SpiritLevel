#include "sprite.h"

static int SPRITE_private_loadBMP(BMP_t **bmp, const char *fn);

int SPRITE_load(Sprite_t *s, const char *fn_b, const char *fn_w) {
    if(fn_b) {
        int err = SPRITE_private_loadBMP(&s->BMP_B, fn_b);

        if(err) {
            return err;
        }
    } else {
        s->BMP_B = NULL;
    }

    if(fn_w) {
        int err = SPRITE_private_loadBMP(&s->BMP_W, fn_w);

        if(err) {
            return err;
        }
    } else {
        s->BMP_W = NULL;
    }

    return BMP_Err_OK;
}

int SPRITE_blit(Sprite_t *s, uint8_t x, uint8_t y) {
    if(s->BMP_B) {
        int err = BMP_blit(s->BMP_B, x, y);

        if(err) {
            return err;
        }
    }

    if(s->BMP_W) {
        int err = BMP_blit(s->BMP_W, x, y);

        if(err) {
            return err;
        }
    }

    return BMP_Err_OK;
}

void SPRITE_free(Sprite_t *s) {
    if(s->BMP_B) {
        BMP_release(s->BMP_B);

        free(s->BMP_B);
    }

    if(s->BMP_W) {
        BMP_release(s->BMP_B);

        free(s->BMP_W);
    }
}

static int SPRITE_private_loadBMP(BMP_t **bmp, const char *fn) {
    FIL fil;

    *bmp = (BMP_t*)malloc(sizeof(BMP_t));

    if(!(*bmp)) {
        return 1;
    }

    BMP_zeroBMP(*bmp);

    if(f_open(&fil, fn, FA_READ) != FR_OK) {
        return BMP_Err_IO;
    }

    BMP_setFile(&fil);

    BMP_Err_t err;
    err = BMP_parseFile(*bmp);

    if(err) {
        return err;
    }
    
    err = BMP_readData(*bmp);

    if(err) {
        return err;
    }

    f_close(&fil);

    return BMP_Err_OK;
}
