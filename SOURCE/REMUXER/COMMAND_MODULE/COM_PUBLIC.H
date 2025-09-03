#pragma once

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

void set_status_message(command_module *com, 
                        const char *str);

void reset_status_message(command_module *com);


void com_init(command_module *com);

void com_parse(struct remux_module_s *remux, 
               const char *comamnd);