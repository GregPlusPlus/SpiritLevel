#include "console.h"

WRITE_PROTOTYPE {
    for(int i = 0; i < len; i ++) {
        SWO_PrintChar(data[i]);
    }

    return len;
}

READ_PROTOTYPE {
    return 0;
}
