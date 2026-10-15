#include <genesis.h>
#include "title.h"
#include "title_res.h"

#define PCM_INTRO    64
#define PCM_LOOP     65
#define PCM_NAV_SFX  80
#define PCM_CONFIRM  81

#define OPT_Y        20

static const char *opts[3] = { "START GAME", "RECORDS", "OPTIONS" };
static const u16 optX[3]   = { 4, 18, 29 };
static const u16 optLen[3] = { 10, 7, 7 };

static void drawOptions(void)
{
    VDP_clearText(2, OPT_Y, 36);

    for (u16 i = 0; i < 3; i++)
        VDP_drawText(opts[i], optX[i], OPT_Y);

    VDP_drawText("<", optX[0] - 1, OPT_Y);
    VDP_drawText(">", optX[0] + optLen[0], OPT_Y);
}

void TITLE_show(void)
{
    u16 timer = 0;
    u16 joy = 0;
    bool in_loop = FALSE;
    bool in_menu = FALSE;

    SYS_disableInts();

    VDP_setScreenWidth320();
    PAL_setPalette(PAL0, title_pal.data, DMA);
    VDP_drawImageEx(BG_A, &title_img,
                    TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, TILE_USER_INDEX),
                    0, 0, FALSE, TRUE);

    XGM_setPCM(PCM_INTRO,   music_intro, sizeof(music_intro));
    XGM_setPCM(PCM_LOOP,    music_loop,  sizeof(music_loop));
    XGM_setPCM(PCM_NAV_SFX, sfx_nav,     sizeof(sfx_nav));
    XGM_setPCM(PCM_CONFIRM, sfx_confirm, sizeof(sfx_confirm));
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

        joy = JOY_readJoypad(JOY_1);

        if (!in_menu)
        {
            if ((timer / 30) % 2 == 0)
                VDP_drawText("PRESS START", 14, 24);
            else
                VDP_clearText(14, 24, 11);

            if (joy & BUTTON_START)
            {
                VDP_clearText(14, 24, 11);
                drawOptions();
                in_menu = TRUE;
            }
        }
        else
        {
            if (joy & BUTTON_A)
            {
                XGM_startPlayPCM(PCM_CONFIRM, 15, SOUND_PCM_CH2);

                u16 timeout = 120;
                while (XGM_isPlayingPCM(SOUND_PCM_CH2_MSK) && timeout--)
                    SYS_doVBlankProcess();

                break;
            }
        }

        SYS_doVBlankProcess();
        timer++;
    }

    XGM_stopPlayPCM(SOUND_PCM_CH1);
    XGM_stopPlayPCM(SOUND_PCM_CH2);
    PAL_fadeOutAll(20, FALSE);
}
