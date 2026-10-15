#include <genesis.h>
#include "title.h"
#include "title_res.h"

#define MUSIC_PCM_ID  64

void TITLE_show(void)
{
    u16 timer = 0;
    u16 joy;

    SYS_disableInts();

    VDP_setScreenWidth320();
    PAL_setPalette(PAL0, title_pal.data, DMA);

    VDP_drawImageEx(BG_A, &title_img,
                    TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, TILE_USER_INDEX),
                    0, 0, FALSE, TRUE);

    XGM_setPCM(MUSIC_PCM_ID, theme_music, sizeof(theme_music));
    XGM_startPlayPCM(MUSIC_PCM_ID, 1, SOUND_PCM_CH1);

    SYS_enableInts();

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

    XGM_stopPlayPCM(SOUND_PCM_CH1);
    PAL_fadeOutAll(20, FALSE);
}
