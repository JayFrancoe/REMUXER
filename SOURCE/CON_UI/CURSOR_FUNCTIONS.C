#include "CUI_PRIVATE.H"
#include "CUI_PUBLIC.H"

void cui_store_cursor(con_ui *cui)
{
    cui_refresh(cui);

    cui->stor_y = cui->cur_y;
    cui->stor_x = cui->cur_x;
}

void cui_restore_cursor(con_ui *cui)
{
    cui->cur_y = cui->stor_y;
    cui->cur_x = cui->stor_x;
    cui_refresh_cursor_internal(cui);
}

void cui_set_cursor(con_ui *cui, short int y, short int x)
{
    cui->cur_y = y;
    cui->cur_x = x;
    
    cui_refresh_cursor_internal(cui);
}

void cui_set_y(con_ui *cui, short int y)
{
    cui->cur_y = y;
    cui_refresh_cursor_internal(cui);
}

void cui_set_x(con_ui *cui, short int x)
{
    cui->cur_x = x;
    cui_refresh_cursor_internal(cui);
}

void cui_inc_y(con_ui *cui)
{
    cui->cur_y++;
    cui_refresh_cursor_internal(cui);
}

void cui_inc_x(con_ui *cui)
{
    cui->cur_x++;
    cui_refresh_cursor_internal(cui);
}

void cui_dec_y(con_ui *cui)
{
    cui->cur_y--;
    cui_refresh_cursor_internal(cui);
}

void cui_dec_x(con_ui *cui)
{
    cui->cur_x--;
    cui_refresh_cursor_internal(cui);
}