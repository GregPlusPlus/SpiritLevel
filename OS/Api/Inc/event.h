#ifndef EVENTS_H
#define EVENTS_H

#include "pb.h"

typedef enum {
    EV_NONE         = 0x00,
    EV_PB_LEFT      = 0x01,
    EV_PB_MID       = 0x02,
    EV_PB_RIGHT     = 0x04
} Event_t;

Event_t Events_computeEvents();

#endif // EVENTS_H