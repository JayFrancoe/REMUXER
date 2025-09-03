#include "CON_UI/CUI_PUBLIC.H"
#include "UI_BUILDER.H"

short int get_section_origin(con_ui *cui, short int origin_y)
{
    if (origin_y > cui->max_y) {
        return cui->cur_y + 1;
    }

    if (origin_y >= 0) {
        return origin_y;
    }

    short int max = cui->max_y;

    return max + origin_y;
}

short int get_section_height(con_ui *cui, short int origin) {
    return ( cui->cur_y - origin );
}
