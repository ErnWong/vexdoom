#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include "api.h"
#include "doom/doomtype.h"
#include "doom/doomdef.h"
#include "doom/doomstat.h"
#include "doom/m_fixed.h"
#include "doom/d_main.h"
#include "doom/i_video.h"
#include "doom/i_system.h"
#include "doom/i_sound.h"

#define MAX_MESSAGE_SIZE                1024

static unsigned int start_displaytime;
static unsigned int displaytime;
static boolean InDisplay = false;
int ms_to_next_tick;
int realtic_clock_rate = 100;
tic_vars_t tic_vars;

static void handle_signal(int s)
{

    char buf[2048];

    signal(s, SIG_IGN);
    strcpy(buf,"Exiting on signal: ");
    snprintf(buf + strlen(buf), 2000 - strlen(buf), "signal %d", s);
    I_Error("%s", buf);

}

void I_Init(void)
{

    I_InitSound();

    tic_vars.msec = realtic_clock_rate * TICRATE / 100000.0f;

}

void I_Exit(int rc)
{

    if(rc == 0)
    {
        players[consoleplayer].message = "Ha Nice Try";
        return;
    }

    printf("[INFO ] Program has terminated.\n");
    while (true)
    {
        // Idle loop. Flushes any messages.
        delay(1000);
    }

}

void I_Print(const char *s, ...)
{

    char msg[MAX_MESSAGE_SIZE];
    va_list v;

    va_start(v, s);
    vsnprintf(msg, sizeof (msg), s, v);
    va_end(v);
    fprintf(stdout, "%s\n", msg);

}

void I_Error(const char *s, ...)
{

    char msg[MAX_MESSAGE_SIZE];
    va_list v;

    va_start(v, s);
    vsnprintf(msg, sizeof (msg), s, v);
    va_end(v);
    fprintf(stderr, "%s\n", msg);
    I_Exit(-1);

}

boolean I_StartDisplay(void)
{

    if (InDisplay)
        return false;

    start_displaytime = millis();
    InDisplay = true;

    return true;

}

void I_EndDisplay(void)
{

    displaytime = millis() - start_displaytime;
    InDisplay = false;

}

void I_uSleep(unsigned long usecs)
{

    delay(usecs / 1000);

}

int I_GetTime(void)
{

    int t = millis();
    int i = t * (TICRATE / 5) / 200;

    ms_to_next_tick = (i + 1) * 200 / (TICRATE / 5) - t;

    if (ms_to_next_tick > 1000 / TICRATE || ms_to_next_tick < 1)
        ms_to_next_tick = 1;

    return i;

}

fixed_t I_GetTimeFrac(void)
{

    unsigned long now = millis();
    fixed_t frac;

    if (tic_vars.step == 0)
        return FRACUNIT;

    frac = (fixed_t)((now - tic_vars.start + displaytime) * FRACUNIT / tic_vars.step);

    if (frac < 0)
        frac = 0;

    if (frac > FRACUNIT)
        frac = FRACUNIT;

    return frac;

}

unsigned long I_GetRandomTimeSeed(void)
{

    return millis();

}

void doom_start()
{

    signal(SIGSEGV, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGFPE, handle_signal);
    signal(SIGILL, handle_signal);
    signal(SIGINT, handle_signal);
    signal(SIGABRT, handle_signal);
    I_InitFS();
    I_PreInitGraphics();
    D_DoomMain();

}

