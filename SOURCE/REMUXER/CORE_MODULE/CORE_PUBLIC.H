#pragma once
#include "REMUXER/STDINC.H"


typedef struct core_options_s   core_options;
typedef struct core_module_s    core_module;
typedef struct core_externals_s core_externals;

struct core_options_s
{
    char project[MAX_FILENAME];
    char file_name[MAX_FILENAME];
    char extension[MAX_EXTENSION];

    char seek_time[MAX_NUMBER];
    char duration[MAX_NUMBER];

    char bitrate[MAX_NUMBER];

    bool mute;
};

struct core_externals_s
{
    char mpv_path[MAX_PATH];
    char ffmpeg_path[MAX_PATH];
};


struct core_module_s
{
    path_t input_file;
    char   install_directory[MAX_PATH];
    
    core_externals externals;
    core_options options;

    bool debug;
};

void get_output_file(core_module *, char *Buffer, size_t MaxSize);

void core_init(core_module *, int argc, char **argv);

void launch_mpv_preview(core_module *);
void launch_ffmpeg(core_module *);

void cache_core(core_module *);
void clear_cache(core_module *);