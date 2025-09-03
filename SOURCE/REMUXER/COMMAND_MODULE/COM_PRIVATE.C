#include <memory.h>

#include "COM_PRIVATE.H"

size_t copy_arg(char *destination, char *arg, size_t size)
{
    memset(destination, '\0', size);

    _memccpy(destination, arg, '\0', size);
}

void register_com(command_module *com, command_t *command)
{
    if (com->com_count + 1 > MAX_COMMANDS) {
        return;
    }

    com->commands[com->com_count++] = command;
}