#pragma once

typedef struct con_ui_s con_ui;
typedef enum text_alignment_e text_alignment;


struct con_ui_s
{
    short int max_y, max_x;
    short int cur_y, cur_x;
    short int stor_y, stor_x;
};

enum text_alignment_e
{
    left,
    center,
    right
};

 

void cui_init(con_ui *);

void cui_draw(con_ui *, const char *text);

void cui_draw_f(con_ui *, const char *format, ...);

void cui_draw_ex(con_ui *,
                       int offset, text_alignment alignment,
                       const char *text);

void cui_draw_ex_f(con_ui *,
                       int offset, text_alignment alignment,
                       const char *format, ...);


void cui_emit(con_ui *, const char c);

int  cui_newline(con_ui *);

int cui_newline_ex(con_ui *, 
                   short int indent, 
                   short int num_newlines);

void cui_refresh(con_ui *);
void cui_clear_screen(con_ui *);
void cui_clear_line(con_ui *);
void cui_clear_char(con_ui *);

void cui_store_cursor(con_ui *);
void cui_restore_cursor(con_ui *);

void cui_set_cursor(con_ui *, 
                    short int y, short int x);

void cui_set_y(con_ui *, short int y);
void cui_set_x(con_ui *, short int x);

void cui_inc_y(con_ui *);
void cui_dec_y(con_ui *);

void cui_inc_x(con_ui *);
void cui_dec_x(con_ui *);

void cui_draw_horizontal(con_ui *, char c);

