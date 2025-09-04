#include "REMUXER/DRAW_MODULE/DRAW_PUBLIC.H"


extern screen_t main_screen;
extern screen_t help_screen;
extern screen_t no_arg_screen;

void set_screen(draw_module *draw, screen_e screen)
{
    screen_t *screen_ref = NULL;
    switch (screen)
    {
        case SCREEN_HELP:
            screen_ref = &help_screen;
            break;
        case SCREEN_MAIN:
            screen_ref = &main_screen;
            break;
        case SCREEN_NO_ARGS:
            screen_ref = &no_arg_screen;
        default:
            break;
    }
    
    draw->active_screen = screen_ref;
}

void init_screens(draw_module *draw)
{
    if (draw->active_screen != NULL) {
        return;
    }
    draw->active_screen = &main_screen;
}