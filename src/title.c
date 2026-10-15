#include <genesis.h>
#include "title.h"

extern const Palette title_pal;
extern const Image   title_img;

void TITLE_show(void)
{
    u16 timer = 0;
    u16 joy;

    VDP_setScreenWidth320();

    PAL_setPalette(PAL0, title_pal.data, DMA);

    VDP_drawImageEx(BG_A, &title_img,
                TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, TILE_USER_INDEX),
                0, 0, FALSE, TRUE);

    PAL_fadeIn(0, 0, title_pal.data, 30, FALSE);

    while (TRUE)
    {
        if ((timer / 30) % 2 == 0)
            VDP_drawText("PRESS START", 14, 24);
        else
            VDP_clearText(14, 24, 11);

        joy = JOY_readJoypad(JOY_1);
        if (joy & BUTTON_START) break;

        SYS_doVBlankProcess();
        timer++;
    }

    PAL_fadeOutAll(20, FALSE);
}
