#include <genesis.h>
#include "menu_bg.h"
#include "menu_bg_res.h"

#define PCM_MENU  70

void MENU_BG_draw(void)
{
    PAL_setPalette(PAL0, menu_bg_pal.data, DMA);
    VDP_drawImageEx(BG_A, &menu_bg,
                    TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, TILE_USER_INDEX),
                    0, 0, FALSE, TRUE);
}

void MENU_BG_startMusic(void)
{
    SYS_disableInts();

    XGM_setPCM(PCM_MENU, menu_music, sizeof(menu_music));
    XGM_startPlayPCM(PCM_MENU, 1, SOUND_PCM_CH1);

    SYS_enableInts();
}

void MENU_BG_updateMusic(void)
{
    if (!XGM_isPlayingPCM(SOUND_PCM_CH1_MSK))
        XGM_startPlayPCM(PCM_MENU, 1, SOUND_PCM_CH1);
}

void MENU_BG_stopMusic(void)
{
    XGM_stopPlayPCM(SOUND_PCM_CH1);
}
