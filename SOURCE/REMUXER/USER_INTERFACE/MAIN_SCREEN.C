#include "REMUXER/REMUX_MODULE.H"
#include "REMUXER/DRAW_MODULE/UI_BUILDER.H"

static
void _draw_nullable(con_ui *ui, const char *key, const char *string)
{
    cui_draw(ui, key);

    if (string == NULL
    || *string == '\0')
    {
        cui_draw(ui, "[empty]");
        return;
    }

    cui_emit(ui, '"');
    cui_draw(ui, string);
    cui_emit(ui, '"');
}

const 
int indent = 8;

static
void main_body_interface(remux_module *remux, section_t *section)
{
    con_ui *cui = get_cui(remux);
    short int origin_y = get_section_origin(cui, section->origin_y);

    core_options *opt = &remux->core.options;

    cui_draw_ex(cui, indent, left, "FILE SETTINGS");
    cui_newline_ex(cui, indent, 1);

    cui_draw(cui, "-------------");
    cui_newline_ex(cui, indent, 1);

    _draw_nullable(cui, "Project: ", opt->project);
    cui_newline_ex(cui, indent, 1);

    _draw_nullable(cui, "Filename: ", opt->file_name);
    cui_newline_ex(cui, indent, 1);

    _draw_nullable(cui, "Extension: ", opt->extension);
    

    cui_newline_ex(cui, indent, 3);
    cui_draw(cui, "VIDEO SETTINGS:");
    cui_newline_ex(cui, indent, 1);
 
    cui_draw(cui, "---------------");
    cui_newline_ex(cui, indent, 1);

    _draw_nullable(cui, "seek time: ", opt->seek_time);
    cui_newline_ex(cui, indent, 1);

    _draw_nullable(cui, "duration: ", opt->duration);
    cui_newline_ex(cui, indent, 1);

    cui_draw(cui, "muted: ");
    if (opt->mute) {
        cui_draw(cui, "true");
    } else {
        cui_draw(cui, "false");
    }
    cui_newline_ex(cui, indent, 1);

    _draw_nullable(cui, "bitrate: ", opt->bitrate);
    cui_newline_ex(cui, indent, 1);


    short int y = cui->max_y - 4;
    cui_set_cursor(cui, y, indent);

    char output_buffer[MAX_PATH];
    get_output_file(&remux->core, output_buffer, MAX_PATH);
    
    cui_draw(cui, "Output file: ");
    cui_draw(cui, output_buffer);

    section->height = get_section_height(cui, origin_y);
}

static
section_t help_body = {
    .draw_fn  = main_body_interface,
    .origin_y = ORIGIN_CONTINUATION
};

screen_t main_screen = {
    .name   = "Main",
    .header = &default_header,
    .body   = &help_body,
    .footer = &default_footer
};