#include <genesis.h>
#include "menu_bg.h"
#include "menu_bg_res.h"

#define PCM_MENU  70

#define IMG_W   40
#define IMG_H   28
#define PLANE_W 64
#define PLANE_H 32

static u16 hscroll = 0;
static u16 vscroll = 0;

void MENU_BG_draw(void)
{
    u16 attr = TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, TILE_USER_INDEX);

    PAL_setPalette(PAL0, menu_bg_pal.data, DMA);

    VDP_loadTileSet(menu_bg.tileset, TILE_USER_INDEX, DMA);

    VDP_setTileMapEx(BG_A, menu_bg.tilemap, attr, 0, 0,  0,  0,  IMG_W, IMG_H, DMA);
    VDP_setTileMapEx(BG_A, menu_bg.tilemap, attr, 0, 0,  IMG_W, 0,  IMG_W, IMG_H, DMA);
    VDP_setTileMapEx(BG_A, menu_bg.tilemap, attr, 0, 0,  0,  IMG_H, IMG_W, IMG_H, DMA);
    VDP_setTileMapEx(BG_A, menu_bg.tilemap, attr, 0, 0,  IMG_W, IMG_H, IMG_W, IMG_H, DMA);

    hscroll = 0;
    vscroll = 0;
    VDP_setHorizontalScroll(BG_A, 0);
    VDP_setVerticalScroll(BG_A, 0);
}

void MENU_BG_scrollUpdate(void)
{
    hscroll = (hscroll - 1) & 511;
    vscroll = (vscroll + 1) & 255;

    VDP_setHorizontalScroll(BG_A, hscroll);
    VDP_setVerticalScroll(BG_A, vscroll);
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
