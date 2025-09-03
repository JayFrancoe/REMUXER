#include "CUI_PRIVATE.H"
#include "CUI_PUBLIC.H"


void cui_init(con_ui *cui)
{
    cui_init_internal(cui);

    cui_refresh(cui);
}

void cui_refresh(con_ui *cui)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi = { 0 };

    GetConsoleScreenBufferInfo(h_output, &csbi);

    cui->cur_y = csbi.dwCursorPosition.Y;
    cui->cur_x = csbi.dwCursorPosition.X;

    cui->max_y = csbi.srWindow.Bottom - csbi.srWindow.Top;
    cui->max_x = csbi.srWindow.Right;
}