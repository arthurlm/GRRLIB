#include <grrlib.h>

#include <stdlib.h>
#include <wiiuse/wpad.h>

#include "logo_352x89_png.h"
#include "logo_352x90_png.h"
#include "logo_352x91_png.h"
#include "logo_352x92_png.h"
#include "BMfont_png.h"

#define max(a, b) (a >= b ? a : b)
#define min(a, b) (a <= b ? a : b)

int main(int argc, char **argv)
{
    GRRLIB_Init();
    WPAD_Init();

    GRRLIB_texImg *tex_logo_352x89_png = GRRLIB_LoadTexture(logo_352x89_png);
    GRRLIB_texImg *tex_logo_352x90_png = GRRLIB_LoadTexture(logo_352x90_png);
    GRRLIB_texImg *tex_logo_352x91_png = GRRLIB_LoadTexture(logo_352x91_png);
    GRRLIB_texImg *tex_logo_352x92_png = GRRLIB_LoadTexture(logo_352x92_png);

    GRRLIB_texImg *tex_BMfont = GRRLIB_LoadTexture(BMfont_png);
    GRRLIB_InitTileSet(tex_BMfont, 8, 16, 0);

    int select = 0;

    while (1)
    {
        WPAD_ScanPads();
        uint32_t btn_down = WPAD_ButtonsDown(WPAD_CHAN_0);

        if (btn_down & WPAD_BUTTON_HOME)
            break;

        if (btn_down & WPAD_BUTTON_UP)
            select++;
        if (btn_down & WPAD_BUTTON_DOWN)
            select--;

        select = max(min(select, 3), 0);

        GRRLIB_Printf(5, 460, tex_BMfont, 0xFFFFFFFF, 1,
                      "logo ptr: %p %p %p %p",
                      tex_logo_352x89_png,
                      tex_logo_352x90_png,
                      tex_logo_352x91_png,
                      tex_logo_352x92_png);

        GRRLIB_texImg *ptr = NULL;
        int w = 0, h = 0;

        switch (select)
        {
        case 0:
            ptr = tex_logo_352x89_png;
            w = 352;
            h = 89;
            break;
        case 1:
            ptr = tex_logo_352x90_png;
            w = 352;
            h = 90;
            break;
        case 2:
            ptr = tex_logo_352x91_png;
            w = 352;
            h = 91;
            break;
        case 3:
            ptr = tex_logo_352x92_png;
            w = 352;
            h = 92;
            break;
        }

        GRRLIB_Printf(5, 400, tex_BMfont, 0xFFFFFFFF, 1,
                      "Texture size: %d x %d (original size: %d x %d)",
                      ptr->w, ptr->h, w, h);
        GRRLIB_DrawImg(5, 100, ptr, 0.0, 1.0, 1.0, 0xFFFFFFFF);

        GRRLIB_Render();
    }

    GRRLIB_FreeTexture(tex_logo_352x89_png);
    GRRLIB_FreeTexture(tex_logo_352x90_png);
    GRRLIB_FreeTexture(tex_logo_352x91_png);
    GRRLIB_FreeTexture(tex_logo_352x92_png);
    GRRLIB_Exit();
    exit(0);
}
