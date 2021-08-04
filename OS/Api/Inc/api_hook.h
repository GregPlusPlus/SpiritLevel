#ifndef APIT_HOOK_H
#define APIT_HOOK_H

#include <stdarg.h>

#include "api.h"
#include "api_hook_ids.h"

#include "ff.h"
#include "fatfs.h"
#include "ui.h"
#include "utils.h"

uint32_t API_hook(uint32_t id);

#endif // APIT_HOOK_H