#include <string.h>
#include "REMUXER/REMUX_MODULE.H"
#include "DRAW_PUBLIC.H"


void draw_section(remux_module *remux, section_t *section)
{
    section->draw_fn(remux, section);
}

void clear_section(remux_module *remux, section_t *section)
{
    con_ui *cui = &remux->ui.cui;

    cui_store_cursor(cui);


}

void draw_interface(remux_module *remux)
{
    draw_module *draw = &remux->ui;
    con_ui *cui = &remux->ui;

    while (1) 
    {
        cui_clear_screen(cui);
        
        screen_t *screen = draw->active_screen;

        draw_section(remux, screen->header);
        draw_section(remux, screen->body);
        draw_section(remux, screen->footer);

        if (remux->exit_signal) {
            break;
        }
    }
}

void draw_init(draw_module *draw_fn)
{
    cui_init(&draw_fn->cui);

    init_screens(draw_fn);
}