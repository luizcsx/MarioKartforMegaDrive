#include <genesis.h>
#include "menu_bg.h"
#include "menu_bg_res.h"

void MENU_BG_draw(void)
{
    PAL_setPalette(PAL0, menu_bg_pal0.data, DMA);
    PAL_setPalette(PAL1, menu_bg_pal1.data, DMA);
    PAL_setPalette(PAL2, menu_bg_pal2.data, DMA);
    PAL_setPalette(PAL3, menu_bg_pal3.data, DMA);

    VDP_drawImageEx(BG_A, &menu_bg,
                    TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, TILE_USER_INDEX),
                    0, 0, FALSE, TRUE);
}
