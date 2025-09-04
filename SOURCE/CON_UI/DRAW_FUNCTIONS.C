#include <ctype.h>
#include <stdio.h>
#include "CUI_PRIVATE.H"
#include "CUI_PUBLIC.H"

#define process_args_out_len(_Buffername, _size, _format, _len)\
char _Buffername##[_size] = {0}; int _len = 0;\
{ va_list args; va_start(args, _format);\
_len = vsprintf(_Buffername, _format, args); va_end(args);}

#define read_var_args(_Buffername, _size, _format)\
process_args_out_len(_Buffername, _size, _format, __UNUSED);


static
void _cui_print(con_ui *cui, const char *str)
{
    char c = 0;
    while (c = *str++) {
        cui_emit(cui, c);
    }
}

inline
void cui_emit(con_ui *cui, const char c)
{
    putchar(c);
    cui->cur_x++;
}

void cui_draw_f(con_ui *cui, const char *str, ...)
{
    read_var_args(buffer, 800, str);
    cui_draw_ex(cui, 0, left, buffer);
}

void cui_draw(con_ui *cui, const char *string)
{
    cui_draw_ex(cui, 0, left, string);
}

void cui_draw_ex(con_ui *cui, 
                 int offset, text_alignment alignment,
                 const char *text)
{
    if (alignment == left)
    {
        if (offset > 0) {
            cui_set_x(cui, cui->cur_x + offset);
        }

        _cui_print(cui, text);
        return;        
    }

    size_t len = strlen(text);

    if (alignment == center)
    {
        short int center = (cui->max_x - len) / 2;
        cui_set_x(cui, center + offset);
    }

    if (alignment == right)
    {
        cui_set_x(cui, (cui->max_x - offset) - len);
    }

    _cui_print(cui,text);
    return;
}

void cui_draw_ex_f(con_ui *cui, 
                   int offset, text_alignment alignment, 
                   const char *text, ...)
{
    read_var_args(buffer, 800, text);

    cui_draw_ex(cui, offset, alignment, buffer);
}

int cui_newline(con_ui *cui)
{
    return cui_newline_ex(cui, 0, 1);
}

int cui_newline_ex(con_ui *cui, 
                   short int indent, short int num_newlines)
{
    cui->cur_x = 0;

    cui->cur_x += indent;
    cui->cur_y += num_newlines;

    cui_refresh_cursor_internal(cui);

    return 1;
}

void cui_clear_screen(con_ui *cui)
{
    cui_refresh(cui);
    system("cls");
    cui_set_cursor(cui, 0, 0);
}

void cui_clear_line(con_ui *cui)
{
    cui_draw_horizontal(cui, ' ');
}

void cui_clear_char(con_ui *cui)
{
    cui_dec_x(cui);
    putchar(' ');
    cui_dec_x(cui);
}

/* store last info to avoid division math */
static 
struct {
    short int cached_width;
    short int width;
    short int div;
    short int rest;
} hz_cache;


void cui_draw_horizontal(con_ui *cui, char c)
{
    if (hz_cache.cached_width != cui->max_x)
    {
        hz_cache.cached_width = cui->max_x;
        hz_cache.div = cui->max_x / 4;
        hz_cache.rest = hz_cache.cached_width % hz_cache.div;

        hz_cache.width = hz_cache.cached_width / hz_cache.div;
    }

    char buffer_t[80];
    memset(buffer_t, c, 80);

    buffer_t[hz_cache.div] = '\0';

    for (int i = 0; i < hz_cache.width; i++)
    {
        cui_draw(cui, buffer_t);
    }

    for (int i = 0; i < hz_cache.rest; i++)
    {
        cui_emit(cui, c);
    }

}