#include <math.h>
#include "doom/doomdef.h"
#include "doom/d_think.h"
#include "doom/p_pspr.h"
#include "doom/doomstat.h"
#include "doom/s_sound.h"
#include "doom/i_system.h"
#include "doom/i_sound.h"

#include "api.h"

int snd_card = 1;
int mus_card = 0;
int snd_samplerate = 11025;

task_t clicker_task;

void clicker_click()
{
    motor_set_brake_mode(3, E_MOTOR_BRAKE_BRAKE);
    motor_move_voltage(3, 12000);
    delay(80);
    motor_move_voltage(3, 0);
}

void clicker_run(void *unused)
{
    while (true)
    {
        task_notify_take(true, TIMEOUT_MAX);
        clicker_click();
    }
}

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

    task_notify(clicker_task);
    return -1;

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

    clicker_task = task_create(clicker_run, NULL,
            TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, NULL);

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
