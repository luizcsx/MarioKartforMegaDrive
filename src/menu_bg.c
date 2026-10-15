#include <genesis.h>
#include "menu_bg.h"
#include "menu_bg_res.h"

void MENU_BG_draw(void)
{
    PAL_setPalette(PAL0, menu_bg_pal.data, DMA);
    VDP_drawImageEx(BG_A, &menu_bg,
                    TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, TILE_USER_INDEX),
                    0, 0, FALSE, TRUE);
}
