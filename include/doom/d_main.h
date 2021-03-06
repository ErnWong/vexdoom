#ifndef __D_MAIN__
#define __D_MAIN__

#include "doom/d_event.h"
#include "doom/w_wad.h"

typedef struct
{

    signed char forwardmove;
    signed char sidemove;
    short angleturn;
    byte buttons;

} ticcmd_t;

void D_PostEvent(event_t *ev);
void D_DoomMain(void);

#endif
