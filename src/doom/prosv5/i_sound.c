#include <math.h>
#include "doomdef.h"
#include "d_think.h"
#include "p_pspr.h"
#include "doomstat.h"
#include "s_sound.h"
#include "i_system.h"
#include "i_sound.h"

int snd_card = 1;
int mus_card = 0;
int snd_samplerate = 11025;

void I_UpdateSoundParams(int handle, int volume, int seperation, int pitch)
{
    // Noop.
}

void I_SetChannels(void)
{
    // Noop.
}

int I_StartSound(int id, int channel, int vol, int sep, int pitch, int priority)
{
    // Noop.
}

void I_StopSound(int handle)
{
    // Noop.
}

boolean I_SoundIsPlaying(int handle)
{

    return false;

}

boolean I_AnySoundStillPlaying(void)
{

    return false;

}

void I_InitSound(void)
{
    // Noop.
}

void I_ShutdownMusic(void)
{
    // Noop.
}

void I_InitMusic(void)
{
    // Noop.
}

void I_PlaySong(int handle, int looping)
{
    // Noop.
}

void I_PauseSong(int handle)
{
    // Noop.
}

void I_ResumeSong(int handle)
{
    // Noop.
}

void I_StopSong(int handle)
{
    // Noop.
}

void I_UnRegisterSong(int handle)
{
    // Noop.
}

int I_RegisterSong(const void *data, size_t len)
{

    return 0;

}

int I_RegisterMusic(const char *filename, struct musicinfo *song)
{

    return 1;

}

void I_SetMusicVolume(int volume)
{
    // Noop.
}
