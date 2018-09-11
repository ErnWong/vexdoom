#ifndef __I_SYSTEM__
#define __I_SYSTEM__

#include "doom/doomtype.h"
#include "doom/m_fixed.h"
#include <stdio.h>

typedef struct
{

    unsigned int start;
    unsigned int next;
    unsigned int step;
    fixed_t frac;
    float msec;

} tic_vars_t;

extern tic_vars_t tic_vars;

int I_GetTime(void);
void I_Init(void);
void I_Exit(int rc);
void I_Print(const char *s, ...) __attribute__((format(printf, 1, 2)));
void I_Error(const char *s, ...) __attribute__((format(printf, 1, 2)));
boolean I_StartDisplay(void);
void I_EndDisplay(void);
fixed_t I_GetTimeFrac(void);
unsigned long I_GetRandomTimeSeed(void);
void I_uSleep(unsigned long usecs);
char *I_FindFile(const char *wfname, const char *ext);
void I_LSeek(int fd, size_t offset, int whence);
int I_FSeek(FILE *file, long offset, int origin);
int I_Open(const char *filename, int mode);
FILE *I_FOpen(const char *filename, const char *mode);
int I_FClose(FILE *file);
void I_Read(int fd, void *buf, size_t sz);
size_t I_FRead(void *buf, size_t sz, size_t count, FILE * file);
int I_Filelength(int handle);
void doom_start();

extern int ms_to_next_tick;

#endif
