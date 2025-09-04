#include <memory.h>
#include <string.h>
#include "REMUXER/REMUX_MODULE.H"

#include "COM_PRIVATE.H"
#include "COM_PUBLIC.H"


void com_init(command_module *com)
{
   register_commands(com);

   return;
}

char *get_status_message(command_module *com)
{
    if ('\0' == *com->status_message) {
        return NULL;
    }

    return com->status_message;
}

void set_status_message(command_module *com, const char *str)
{
    strcpy(com->status_message, str);
}


void reset_status_message(command_module *com)
{
    memset(com->status_message, '\0', 100);
}

void com_parse(remux_module *remux, const char *command)
{
    reset_status_message(&remux->com);

    char command_buffer[25] = {0};
    size_t i = 0;
    char c = 0;
    while (c = *command++) 
    {
        if (c == ' ') {
            break;
        }

        command_buffer[i++] = c;
    }

    while (*command == ' ') {
        command++;
    }

    for (int i = 0; i < remux->com.com_count; i++) 
    {
        command_t *com = remux->com.commands[i];
        
        if (!_strcmpi(com->word, command_buffer)) {
            com->function(remux, command);
            return;
        }
    }

    set_status_message(&remux->com, "Could not find the specified command");
    return;
}
