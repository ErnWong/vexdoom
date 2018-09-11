#include <stdlib.h>
#include "api.h"
#include "display/lvgl.h"
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
#define USE_SERIAL_AS_DISPLAY false

int SCREENWIDTH = 320;
int SCREENHEIGHT = 200;
int SCREENPITCH = 320;
static int palette_number = 0;
static int frameno;
static uint8_t * framebuffer;
static lv_obj_t * lv_image;
static lv_img_t lv_image_info;

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

bool prev_key[1024];

void check_key(char name, controller_digital_e_t v5type, int doomtype)
{
    bool new_state = controller_get_digital(E_CONTROLLER_MASTER, v5type);
    if (prev_key[doomtype] != new_state)
    {
        event_t event;
        event.type = new_state ? ev_keydown : ev_keyup;
        event.data1 = doomtype;
        D_PostEvent(&event);
    }
    prev_key[doomtype] = new_state;
}

void update_joysticks()
{
    event_t event;
    event.type = ev_mouse;
    event.data2 = 8*controller_get_analog(E_CONTROLLER_MASTER, E_CONTROLLER_ANALOG_LEFT_X);
    event.data3 = controller_get_analog(E_CONTROLLER_MASTER, E_CONTROLLER_ANALOG_LEFT_Y);
    D_PostEvent(&event);
}

void I_StartTic(void)
{

    check_key('u', E_CONTROLLER_DIGITAL_UP, KEYD_UPARROW);
    check_key('d', E_CONTROLLER_DIGITAL_DOWN, KEYD_DOWNARROW);
    check_key('l', E_CONTROLLER_DIGITAL_LEFT, KEYD_LEFTARROW);
    check_key('r', E_CONTROLLER_DIGITAL_RIGHT, KEYD_RIGHTARROW);
    check_key('x', E_CONTROLLER_DIGITAL_X, KEYD_ESCAPE); // Open menu
    check_key('y', E_CONTROLLER_DIGITAL_Y, KEYD_TAB); // Open map - not supported
    check_key('a', E_CONTROLLER_DIGITAL_A, KEYD_ENTER); // Select in menu
    check_key('r', E_CONTROLLER_DIGITAL_B, '0'); // Switch weapons
    check_key('s', E_CONTROLLER_DIGITAL_L1, KEYD_RALT); // Strafe
    check_key('S', E_CONTROLLER_DIGITAL_L2, KEYD_SPACEBAR); // Use
    check_key('R', E_CONTROLLER_DIGITAL_R2, KEYD_RSHIFT); // Run
    check_key('r', E_CONTROLLER_DIGITAL_R1, KEYD_RCTRL); // Shoot
    update_joysticks();

}

void I_FinishUpdate(void)
{

    if (skipframe())
        return;

    byte *src = screens[0].data;
    uint8_t *dest = framebuffer;

    int pplump = W_GetNumForName("PLAYPAL");
    register const byte * palette = W_CacheLumpNum(pplump);
    palette += 256 * 3 * palette_number;

    if (USE_SERIAL_AS_DISPLAY)
    {
        printf("===============================================================================\n");
        for (int y = 0; y < SCREENHEIGHT; y++)
        {
            I_Print("y=%d, offset=%lu, pitch=%d\n", y, (long unsigned)(dest - framebuffer), screens[0].byte_pitch);
            for (int x = 0; x < SCREENWIDTH; x++)
            {
                byte r = palette[*src * 3 + 0];
                byte g = palette[*src * 3 + 1];
                byte b = palette[*src * 3 + 2];
                switch ((r + g + b) * 8 / 3 / 256)
                {
                  case 4:
                    fputc(' ', stdout);
                    break;
                  case 3:
                    fputc('.', stdout);
                    break;
                  case 2:
                    fputc(':', stdout);
                    break;
                  case 1:
                    fputc('+', stdout);
                    break;
                  case 0:
                    fputc('#', stdout);
                    break;
                  default:
                    fputc(' ', stdout);
                    break;
                }
                src++;
            }
            fputc('\n', stdout);
            src += screens[0].byte_pitch - SCREENWIDTH;
        }
        printf("===============================================================================\n");
        fflush(stdout);
        delay(100);
    }
    else
    {
        for (int y = 0; y < SCREENHEIGHT; y++)
        {
            for (int x = 0; x < SCREENWIDTH; x++)
            {
                byte r = palette[*src * 3 + 0];
                byte g = palette[*src * 3 + 1];
                byte b = palette[*src * 3 + 2];
                *dest = b;
                dest++;
                *dest = g;
                dest++;
                *dest = r;
                dest++;
                dest++;
                src++;
            }
            src += screens[0].byte_pitch - SCREENWIDTH;
        }
    }

    W_UnlockLumpNum(pplump);
    lv_img_set_src(lv_image, &lv_image_info);
    delay(40);

}

void I_SetPalette(int pal)
{

    palette_number = pal;

}

void I_PreInitGraphics(void)
{

    framebuffer = malloc(SCREENHEIGHT * SCREENPITCH * 4);

}

void I_CalculateRes(unsigned int width, unsigned int height)
{

    SCREENWIDTH=480;
    SCREENHEIGHT=240;
    SCREENPITCH = SCREENWIDTH;
    framebuffer = realloc(framebuffer, SCREENHEIGHT * SCREENPITCH * 4);
    if (framebuffer == NULL)
    {
        I_Error("Couldn't resize framebuffer. Can't do anything now. Giving up. Goodbye\n");
    }

}

void I_InitGraphics(void)
{

    V_InitMode();
    V_FreeScreens();
    I_CalculateRes(SCREENWIDTH, SCREENHEIGHT);
    for (int i = 0; i <= 4; i++)
    {
        screens[i].not_on_heap = false;
        screens[i].byte_pitch = SCREENPITCH;
        screens[i].width = SCREENWIDTH;
        screens[i].height = SCREENHEIGHT;
    }
    V_AllocScreens();
    R_InitBuffer(SCREENWIDTH, SCREENHEIGHT);

    lv_image_info.header.w = SCREENWIDTH;
    lv_image_info.header.h = SCREENHEIGHT;
    lv_image_info.header.alpha_byte = 0;
    lv_image_info.header.chroma_keyed = 0;
    lv_image_info.header.format = LV_IMG_FORMAT_INTERNAL_RAW;
    lv_image_info.pixel_map = framebuffer;

    lv_image = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_auto_size(lv_image, true);

}
