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

    PAL_fadeIn(0, 3, menu_bg_pal0.data, 20, FALSE);

    while (TRUE)
    {
        SYS_doVBlankProcess();
    }

    return 0;
}
