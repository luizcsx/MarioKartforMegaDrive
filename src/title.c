#include <genesis.h>
#include "title.h"
#include "title_res.h"

#define PCM_INTRO  64
#define PCM_LOOP   65

void TITLE_show(void)
{
    u16 timer = 0;
    u16 joy;
    bool in_loop = FALSE;

    SYS_disableInts();

    VDP_setScreenWidth320();
    PAL_setPalette(PAL0, title_pal.data, DMA);
    VDP_drawImageEx(BG_A, &title_img,
                    TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, TILE_USER_INDEX),
                    0, 0, FALSE, TRUE);

    XGM_setPCM(PCM_INTRO, music_intro, sizeof(music_intro));
    XGM_setPCM(PCM_LOOP,  music_loop,  sizeof(music_loop));

    XGM_startPlayPCM(PCM_INTRO, 1, SOUND_PCM_CH1);

    SYS_enableInts();

    PAL_fadeIn(0, 0, title_pal.data, 30, FALSE);

    while (TRUE)
    {
        if (!in_loop)
        {
            if (!XGM_isPlayingPCM(SOUND_PCM_CH1_MSK))
            {
                XGM_startPlayPCM(PCM_LOOP, 1, SOUND_PCM_CH1);
                in_loop = TRUE;
            }
        }
        else
        {
            if (!XGM_isPlayingPCM(SOUND_PCM_CH1_MSK))
                XGM_startPlayPCM(PCM_LOOP, 1, SOUND_PCM_CH1);
        }

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
