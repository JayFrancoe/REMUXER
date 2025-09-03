#include <stdio.h>
#include <string.h>
#include "REMUXER/CORE_MODULE/CORE_PRIVATE.H"
#include "REMUXER/CORE_MODULE/CORE_PUBLIC.H"

static
void get_cache_file(core_module *core, char *buffer)
{
    sprintf(buffer, "%s/%s", core->install_directory, "core_cache");
}

static
bool open_cache(FILE **fp, core_module *core, const char *method)
{
    char path[MAX_PATH] = {0};
    get_cache_file(core, path);

    if (!( *fp = fopen(path, method) )) {
        return false;
    }

    return true;
}

static
void write_string(FILE *fp, const char *string)
{
    size_t len = strlen(string) + 1;
    fwrite(&len, 1, 1, fp);

    fwrite(string, 1, len, fp);
}

static
void read_string(FILE *fp, char *buffer, size_t max)
{
    size_t len = 0;
    fread(&len, 1, 1, fp);

    if (len > max) {
        return;
    }

    fread(buffer, 1, len, fp);
}

void read_cache_internal(core_module *core)
{
    FILE *fp = 0;

    if (!open_cache(&fp, core, "rb")) {
        return;
    }

    read_string(fp, core->options.extension, MAX_EXTENSION);
    read_string(fp, core->options.project, MAX_FILENAME);

    fclose(fp);
}

void cache_core_internal(core_module *core)
{
    FILE *fp = 0;

    if (!open_cache(&fp, core, "wb")) {
        return;
    }
    
    write_string(fp, core->options.extension);
    write_string(fp, core->options.project);

    fclose(fp);
}


void clear_cache(core_module *core)
{
    char path[260];
    get_cache_file(core, path);

    remove(path);

    core_options *opt = &core->options;

    memset(opt->project, 0, MAX_FILENAME);
    memmove(opt->extension, "mp4", sizeof("mp4"));
}

