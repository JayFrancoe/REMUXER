#pragma once
#include <inttypes.h>
#include "CON_UI/CUI_PUBLIC.H"

#include "REMUXER/STRUCTS.H"

struct section_s
{
    ui_draw_fn draw_fn;
    short int  origin_y;
    short int  height;
};

struct ui_screen_s
{
    const char *name;
    section_t  *header;
    section_t  *body;
    section_t  *footer;
};

struct draw_module_s
{   
    con_ui    cui;
    screen_t  screens[8];
    size_t    screen_count;
    screen_t *active_screen;
};

typedef enum {
    SCREEN_NO_ARGS,
    SCREEN_MAIN,
    SCREEN_HELP
} screen_e;

// implement in _REGISTER.C file
extern void init_screens(draw_module *);

void draw_init(draw_module *);
void draw_interface(remux_module *);


void set_screen(draw_module *, screen_e);

void draw_section(remux_module *, section_t *);
void clear_section(remux_module *, section_t *);
