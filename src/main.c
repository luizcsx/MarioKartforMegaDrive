#include <genesis.h>
#include "title.h"
#include "menu_bg.h"
#include "menu_bg_res.h"

int main(bool hard)
{
    TITLE_show();

    VDP_clearPlane(BG_A, TRUE);
    VDP_clearPlane(BG_B, TRUE);

    MENU_BG_draw();
    MENU_BG_startMusic();

    PAL_fadeIn(0, 0, menu_bg_pal.data, 20, FALSE);

    while (TRUE)
    {
        MENU_BG_updateMusic();
        SYS_doVBlankProcess();
    }

    return 0;
}
