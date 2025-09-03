#include "memory.h"
#include "REMUXER/REMUX_MODULE.H"
#include "REMUXER/DRAW_MODULE/UI_BUILDER.H"

static
void no_arg_body_interface(remux_module *remux, section_t *section)
{
    con_ui *cui = get_cui(remux);

    short int half = (cui->max_y - 2) / 2.0f;

    cui_set_cursor(cui, half, 0);

    cui_draw_ex(cui, 0, center, 
        "No input argument given");
    cui_newline(cui);

    cui_draw_ex(cui, 0, center, 
        "Drag media file onto the executable to use program");

    section->height = get_section_height(cui, half);
}

static 
void no_arg_footer_interface(remux_module *remux, section_t *section)
{
    con_ui *cui = get_cui(remux);

    short int origin_y = get_section_origin(cui, section->origin_y);

    cui_set_cursor(cui, origin_y, 0);

    cui_draw_horizontal(cui, '-');
    cui_newline(cui);

    cui_draw(cui, "Press any key to exit");
    
    cui_set_x(cui, 0);

    (void)_getch();

    remux->exit_signal = 1;

    section->height = get_section_height(cui, origin_y);
}

section_t no_arg_body = {
    .draw_fn  = no_arg_body_interface,
    .origin_y = ORIGIN_CONTINUATION
};

section_t no_arg_footer = {
    .draw_fn = no_arg_footer_interface,
    .origin_y = -2
};

screen_t no_arg_screen = {
    .name   = "no_arg",
    .header = &default_header,
    .body   = &no_arg_body ,
    .footer = &no_arg_footer
};