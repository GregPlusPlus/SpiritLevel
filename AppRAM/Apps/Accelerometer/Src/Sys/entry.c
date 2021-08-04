#include <stdint.h>
#include <stdbool.h>

#include "hook.h"

extern void app_main(void);

void app_entry(void) {
    HOOK_init();
    app_main();
}