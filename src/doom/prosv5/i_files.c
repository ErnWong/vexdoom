#include "api.h"
#include "miniz.h"
#include "doom1wad.h"
#include "doom/i_system.h"
#include <fcntl.h>

#define WAD_FILE_SIZE 1024 * 1024 * 5
FILE * wadfd = (FILE *)1;
char * wadname = "doom1.wad";
unsigned char * waddata;
size_t wadpos = 0;
size_t wadlen = WAD_FILE_SIZE;

void I_InitFS()
{

    int status;
    mz_ulong len = wadlen;
    waddata = malloc(WAD_FILE_SIZE * sizeof(waddata[0]));
    status = uncompress(waddata, &len, res_doom1_zlib, res_doom1_zlib_len);
    wadlen = len;
    if (status != Z_OK)
    {
        I_Error("Error decompressing file: %s", zError(status));
    }

}

void I_LSeek(int fd, size_t offset, int whence)
{

    I_FSeek((FILE*)fd, (long)offset, whence);

}

int I_Open(const char * filename, int mode)
{

    if (mode != O_RDONLY)
    {
        I_Error("IOpen: unrecognized mode %d", mode);
    }

    int fd = (int)I_FOpen(filename, "r");

    if (fd == 0)
    {
        return -1;
    }
    return fd;

}

void I_Read(int fd, void *vbuf, size_t sz)
{

    unsigned char *buf = vbuf;

    while (sz)
    {

        int rc = (int)I_FRead(buf, sizeof(char), sz, (FILE*)fd);

        if (rc <= 0)
            I_Error("I_Read: read failed: %s", rc ? strerror(errno) : "EOF");

        sz -= rc;
        buf += rc;

    }

}

int I_FSeek(FILE *file, long offset, int origin)
{

    if (origin != SEEK_SET)
    {
        return 1;
    }
    wadpos = offset;
    return 0;

}

FILE *I_FOpen(const char *filename, const char *mode)
{

    if (strcmp(filename, wadname) != 0)
    {
        return NULL;
    }

    wadpos = 0;
    return wadfd;

}

int I_FClose(FILE *file)
{

    return 0;

}

size_t I_FRead(void *buf, size_t sz, size_t count, FILE * file)
{

    if (file != wadfd)
    {
        return 0;
    }
    if (count * sz + wadpos > wadlen)
    {
       count = (wadlen - wadpos) / sz;
    }
    memcpy(buf, waddata + wadpos, count * sz);
    wadpos += count * sz;
    return count;

}

int I_Filelength(int handle)
{

    if ((FILE*)handle != wadfd)
    {
        return 0;
    }
    return wadlen;

}

char *I_FindFile(const char *wfname, const char *ext)
{

    return strcpy(malloc(strlen(wadname)), wadname);

}
