#pragma once
#include "CON_UI/CUI_PUBLIC.H"
#include "DRAW_PUBLIC.H"

#define ORIGIN_CONTINUATION 0x7FFF

#define get_cui(remux) &remux->ui.cui;

extern section_t default_header;
extern section_t default_footer;

short int get_section_origin(con_ui *, short int);
short int get_section_height(con_ui *, short int);
