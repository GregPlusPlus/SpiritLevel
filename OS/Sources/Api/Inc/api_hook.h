#ifndef APIT_HOOK_H
#define APIT_HOOK_H

#include <stdarg.h>

#include "api.h"

#include "ff.h"
#include "fatfs.h"
#include "ui.h"
#include "utils.h"
#include "sprite.h"

uint32_t API_hook(const char *label);

#endif // APIT_HOOK_H