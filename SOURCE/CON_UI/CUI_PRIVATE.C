#include "CUI_PRIVATE.H"
#include "CUI_PUBLIC.H"

HANDLE h_input, h_output;

void cui_init_internal(con_ui *cui)
{
    h_input  = GetStdHandle(STD_INPUT_HANDLE);
    h_output = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCP(CP_UTF8);
}

void cui_refresh_cursor_internal(con_ui *cui)
{
    COORD cursor_position = {
        .X = cui->cur_x, 
        .Y = cui->cur_y
    };

    SetConsoleCursorPosition(h_output, cursor_position);
}