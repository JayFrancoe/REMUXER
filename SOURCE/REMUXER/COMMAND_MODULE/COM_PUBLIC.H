#pragma once
#include "REMUXER/STRUCTS.H"

#define MAX_COMMANDS 32

typedef struct command_module_s command_module;
typedef void( *command_fn )(struct remux_module_s *, 
                            const char *);


struct command_s
{
    const char *word;
    const char *description;
    command_fn function;
};

typedef struct command_s command_t;


struct command_module_s
{
    command_t *commands[MAX_COMMANDS];
    size_t com_count;

    char status_message[100];
};

void set_status_message(command_module *, const char *str);

void reset_status_message(command_module *);

const char *get_status_message(command_module *);

void comm_init(command_module *);

void com_parse(remux_module *, const char *command);