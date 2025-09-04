#pragma once
#include "REMUXER/STDINC.H"
#include "CUI_PUBLIC.H"

/*
typedef enum input_rules_e input_rules;

enum input_rules_e {
    NONE,
    FILENAME,
    NUMBER,
    TIMESTAMP
};

typedef short int input_e;

#define IS_SPECIAL   0x8000
#define CURSOR_LEFT  0x0100
#define CURSOR_RIGHT 0x0200
#define SIGNAL_ENTER 0x0400
#define SIGNAL_BACK  0x0800
#define SIGNAL_SPACE 0x1000
#define MODIFY_CTRL  0x2000
#define MODIFY_SHFT  0x4000


bool breaks_rule(char c, enum input_rules Rule);

int cui_read_ex(con_ui *,
                char *Buffer, size_t maxLength,
                input_rules Rule, char TerminationChar);
*/

int cui_read(con_ui *, char *buffer, size_t max_length);
