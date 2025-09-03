#pragma once
#include "REMUXER/REMUX_MODULE.H"

#define create_com(name, desc, def) \
void name##_fn(remux_module *remux, char *args)\
def command_t com_##name = { .word = #name, .description = desc, .function = name##_fn}

void register_commands(command_module *);
void register_com(command_module *, command_t *);
size_t copy_arg(char *destination, char *arg, size_t size);