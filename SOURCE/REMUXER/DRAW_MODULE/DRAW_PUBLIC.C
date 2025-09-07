#include <string.h>
#include "REMUXER/REMUX_MODULE.H"
#include "DRAW_PUBLIC.H"


void draw_section(remux_module *remux, section_t *section) {
    section->draw_fn(remux, section);
}

// not implemented
void clear_section(remux_module *remux, section_t *section) {}

/* input is handled by interface footer functions */
void draw_interface(remux_module *remux)
{
    con_ui *cui = &remux->ui;
    screen_t *screen = remux->ui.active_screen;

    cui_clear_screen(cui);

    draw_section(remux, screen->header);
    draw_section(remux, screen->body);
    draw_section(remux, screen->footer);
}

void draw_init(draw_module *draw_fn)
{
    cui_init(&draw_fn->cui);

    init_screens(draw_fn);
}