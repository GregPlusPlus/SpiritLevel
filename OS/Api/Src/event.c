#include "event.h"

Event_t Events_computeEvents() {
  Event_t ev = EV_NONE;

  PB_Scan();

  PB_Flags_t *pb = PB_getFlags();

  if(pb->PB1) {
    ev |= EV_PB_LEFT;
  }
  if(pb->PB2) {
    ev |= EV_PB_MID;
  }
  if(pb->PB3) {
    ev |= EV_PB_RIGHT;
  }

  return ev;
}
