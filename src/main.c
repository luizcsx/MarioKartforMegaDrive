#include <genesis.h>
#include "title.h"

int main(bool hard)
{
    TITLE_show();

    while (TRUE)
    {
        SYS_doVBlankProcess();
    }

    return 0;
}
