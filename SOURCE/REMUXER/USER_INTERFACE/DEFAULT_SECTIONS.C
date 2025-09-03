#include "REMUXER/DRAW_MODULE/UI_BUILDER.H"

#include "REMUXER/REMUX_MODULE.H"
#include "CON_UI/CUI_INPUT.H"

static
void draw_top_bar(remux_module *remux, section_t *section)
{
    con_ui *cui = get_cui(remux);

    short int origin_y = get_section_origin(cui, section->origin_y);

    cui_set_cursor(cui, origin_y, 0);
    
    cui_draw_ex(cui, 0, center, "REMUXER");
    section->height += cui_newline(cui);

    if (NULL != remux->core.input_file.file_path) {
        cui_draw_ex(cui, 0, center, remux->core.input_file.file_path);
        section->height += cui_newline(cui);
    }

    cui_draw_horizontal(cui, '-');
    section->height += cui_newline(cui);

    return;
}

section_t default_header = {
    .draw_fn = draw_top_bar,
    .origin_y = 0,
};

static
void read_command(remux_module *remux)
{
    con_ui *cui = get_cui(remux);

    while (1)
    {
        char command_buffer[80] = { 0 };

        cui_read(cui, command_buffer, 80, NONE);

        com_parse(remux, command_buffer);

        if ('\0' == *remux->com.status_message) {
            return;
        }

        cui_draw(cui, remux->com.status_message);

        (void) _getch();

        return;
    }
}

static
void draw_commandbar(remux_module *remux, section_t *section)
{
    con_ui *cui = get_cui(remux);

    short int origin_y = get_section_origin(cui, section->origin_y);
    
    cui_set_cursor(cui, origin_y, 0);

    cui_draw_horizontal(cui, '-');
    section->height += cui_newline(cui);

    cui_clear_line(cui);
    section->height += cui_newline(cui);

    cui_clear_line(cui);

    cui_set_cursor(cui, origin_y + 1, 0);

    read_command(remux);
}

section_t default_footer = {
    .draw_fn = draw_commandbar,
    .origin_y = -2,
};
