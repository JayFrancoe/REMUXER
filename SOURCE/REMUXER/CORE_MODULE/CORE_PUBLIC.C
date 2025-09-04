#include <string.h>
#include "CORE_PRIVATE.H"
#include "CORE_PUBLIC.H"

void get_path_info(path_t *path, const char *input)
{
    size_t i = 0, 
           j = 0, 
           k = 0,
           last_slash = 0;
    char c = 0;

    for (; c = input[i]; i++) 
    {
        if (i > MAX_PATH) {
            break;
        }

        if (j >= MAX_FILENAME) {
            j = 0;
        }

        if (k >= MAX_EXTENSION) {
            k = 0;
        }

        if (c == '\\') {
            c = '/';
        }

        path->file_path[i]      = c;
        path->file_directory[i] = c;
        path->file_name[j]      = c;
        path->file_extension[k] = c;

        j++;
        k++;

        if (c == '/') {
            j = 0;
            last_slash = i;
        }

        if (input[i] == '.') {
            k = 0;
        }
    }

    path->file_name[j - k - 1] = '\0';
    path->file_extension[k] = '\0';
    path->file_path[i] = '\0';
    path->file_directory[last_slash] = '\0';
}

void get_output_file(core_module *core, char *buffer, size_t max_size)
{
    const path_t *input = &core->input_file;
    const core_options *option = &core->options;

    memset(buffer, 0, max_size);

    strcat(buffer, input->file_directory);
    strcat(buffer, "/");
    
    if (*option->project) {
        strcat(buffer, option->project);
        strcat(buffer, "/");
    }
    
    if (*option->file_name) {
        strcat(buffer, option->file_name);
    } else {
        strcat(buffer, input->file_name);
    }

    strcat(buffer, ".");
    if (*option->extension) {
        strcat(buffer, option->extension);
    } else {
        strcat(buffer, input->file_extension);
    }
}

static
void get_install_dir(char *destination, char *exe_file)
{
    path_t exe_path = { 0 };
    get_path_info(&exe_path, exe_file);

    memcpy(destination, exe_path.file_directory, MAX_PATH);
}

void core_init(core_module *core, char *module, char *input_file)
{
    get_install_dir(&core->install_directory, module);

    if (NULL != input_file) {
        get_path_info(&core->input_file, input_file);
    }

    init_externals(core);

    core->options.extension[0] = 'm';
    core->options.extension[1] = 'p';
    core->options.extension[2] = '4';
    core->options.extension[3] = '\0';

    read_cache_internal(core);
}

void cache_core(core_module *core)
{
    cache_core_internal(core);
}