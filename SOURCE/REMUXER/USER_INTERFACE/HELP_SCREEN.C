#include "memory.h"
#include "REMUXER/REMUX_MODULE.H"
#include "REMUXER/COMMAND_MODULE/COM_PUBLIC.H"
#include "REMUXER/DRAW_MODULE/UI_BUILDER.H"

static
void get_com_name(char *buffer, const char *name, size_t width, char spacing)
{
    memset(buffer, spacing, width);
    
    for (int i = 0; name[i]; i++) {
        buffer[i] = name[i];
    }
}

static
void help_body_interface(remux_module *remux, section_t *section)
{
    con_ui *cui = get_cui(remux);

    short int origin_y = get_section_origin(cui, section->origin_y);

    cui_set_y(cui, origin_y);

    cui_draw_ex(cui, 0, center, "COMMAND LIST:");
    cui_newline(cui);
    cui_newline(cui);

    for (int i = 0; i < remux->com.com_count; i++)
    {
        command_t *com = remux->com.commands[i];
    
        char word_buffer[21] = {0};
        get_com_name(word_buffer, com->word, 20, '.');

        cui_draw_ex_f(cui, 4, left, "%s: %s",
            word_buffer, com->description);
        cui_newline(cui);
    }

    cui_newline_ex(cui, 2, 2);

    cui_draw(cui, "use command \"back\" to return to the main screen.");

    section->height = get_section_height(cui, origin_y);

    set_screen(cui, SCREEN_MAIN);
}

section_t help_body = {
    .draw_fn = help_body_interface,
    .origin_y = ORIGIN_CONTINUATION
};

screen_t help_screen = {
    .name = "Help",
    .header = &default_header,
    .body = &help_body,
    .footer = &default_footer
};