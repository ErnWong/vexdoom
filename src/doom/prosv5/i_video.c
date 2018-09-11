#include <stdlib.h>
#include "doom/doomdef.h"
#include "doom/d_think.h"
#include "doom/p_pspr.h"
#include "doom/doomstat.h"
#include "doom/r_data.h"
#include "doom/r_draw.h"
#include "doom/v_video.h"
#include "doom/st_stuff.h"
#include "doom/i_system.h"
#include "doom/i_video.h"

#define NO_PALETTE_CHANGE 1000

int SCREENWIDTH = 320;
int SCREENHEIGHT = 200;
int SCREENPITCH = 320;
static int newpal = 0;
static int frameno;

static boolean skipframe(void)
{

    frameno++;

    switch (gamestate)
    {

    case GS_LEVEL:
        return false;

    default:
        return (frameno & 1) ? true : false;

    }

}

void I_StartTic(void)
{
    // Noop.
}

void I_FinishUpdate(void)
{

    if (skipframe())
        return;

    // TODO

}

void I_SetPalette(int pal)
{

    newpal = pal;

}

void I_PreInitGraphics(void)
{

    // TODO

}

void I_CalculateRes(unsigned int width, unsigned int height)
{

    SCREENWIDTH = (width + 15) & ~15;
    SCREENHEIGHT = height;

    if (!(SCREENWIDTH % 1024))
        SCREENPITCH = SCREENWIDTH + 32;
    else
        SCREENPITCH = SCREENWIDTH;

}

void I_InitGraphics(void)
{

    int i;

    V_InitMode();
    V_FreeScreens();
    I_CalculateRes(SCREENWIDTH, SCREENHEIGHT);

    for (i = 0; i < 3; i++)
    {

        screens[i].width = SCREENWIDTH;
        screens[i].height = SCREENHEIGHT;
        screens[i].byte_pitch = SCREENPITCH;

    }

    V_AllocScreens();
    R_InitBuffer(SCREENWIDTH, SCREENHEIGHT);

}

