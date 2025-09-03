#include <string.h>
#include <memory.h>
#include "REMUXER/STDINC.H"

#include <Windows.h>
#include <shellapi.h>

#include "CORE_PRIVATE.H"

#define MAX_BUFFER 500

typedef enum {MPV, FFMPEG} program_e;

typedef struct {
    const char *path;
    program_e program;
    const char *option_mute;
    const char *option_seek;
    const char *option_duration;
    const char *option_bitrate;
} launch_helper;

launch_helper mpv_launcher = {
    .program = MPV,
    .option_mute = "--no-audio",
    .option_seek = "--start=",
    .option_duration = "--end=",
    .option_bitrate = "--hls-bitrate="
};

launch_helper ffmpeg_launcher = {
    .program = FFMPEG,
    .option_mute = "-an",
    .option_seek = "-ss ",
    .option_duration = "-to ",
    .option_bitrate = "-b:v "
};

typedef struct 
{
    char c_buf[MAX_BUFFER];
    size_t index;
} buffer_t;

static
void buffer_init(buffer_t *Buf)
{
    memset(Buf->c_buf, '\0', MAX_BUFFER);
    Buf->index = 0;
}

static
void buffer_append(buffer_t *Buf, char *format, ...)
{
    read_var_args(string, 200, format);
    char c = 0;

    for (int i = 0; c = string[i]; i++) {
        if (Buf->index == MAX_BUFFER) {
            break;
        }

        Buf->c_buf[Buf->index++] = c;
    }
}

static
void _launch_ext(core_module *core, launch_helper *program) 
{
    core_options *opt = &core->options;
    
    buffer_t arg_buffer;
    buffer_init(&arg_buffer);

    if (opt->mute) {
        buffer_append(&arg_buffer, "%s ", program->option_mute);
    }
    if (*opt->seek_time) {
        buffer_append(&arg_buffer, 
            "%s%s ", program->option_seek, opt->seek_time);
    }
    if (*opt->duration) {
        buffer_append(&arg_buffer,     
            "%s%s ", program->option_duration, opt->duration);
    }

    char *exe_path = program->path;
    
    if (program->program == FFMPEG) {
        char output[MAX_PATH];
        get_output_file(core, output, MAX_PATH);

        buffer_append(&arg_buffer, "-i \"%s\" ",
        core->input_file.file_path);

        if (*opt->bitrate) {
            buffer_append(&arg_buffer,
            "%s%s ", program->option_bitrate, opt->bitrate);
        }

        buffer_append(&arg_buffer, "\"%s\"", output);

        if (*core->options.project) {
            char project_path[MAX_PATH];
            sprintf(project_path, "%s/%s", 
                    core->input_file.file_directory, opt->project);

            CreateDirectoryA(project_path, NULL);
        }

        STARTUPINFOA si = { 0 };
        PROCESS_INFORMATION pi = { 0 };
        si.cb = sizeof(si);
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_SHOW;  // Show the window

        buffer_t cmd_line;
        buffer_init(&cmd_line);

        buffer_append(&cmd_line, 
            "cmd /k %s -hide_banner %s", exe_path, arg_buffer
        );

        printf("%s", cmd_line.c_buf);

        if (CreateProcessA(
            NULL,               // Application name
            cmd_line.c_buf,     // Command line
            NULL,               // Process security attributes
            NULL,               // Thread security attributes
            FALSE,              // Inherit handles
            CREATE_NEW_CONSOLE, // Creation flags
            NULL,               // Environment
            NULL,               // Current directory
            &si,                // Startup info
            &pi                 // Process information
            ))
        {    
            WaitForSingleObject(pi.hProcess, INFINITE);

            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        } else {
            DWORD error = GetLastError();
            printf("Failed to launch ffmpeg. Error code: %lu\n", error);
        }

    } 
    else if (program->program == MPV) {
        buffer_append(&arg_buffer, 
            "--force-window \"%s\"", core->input_file.file_path);

        if (core->debug) {
            printf(arg_buffer.c_buf);
        } else {
            printf("press C to close out video player");
        }

       HINSTANCE result = ShellExecuteA(
            NULL,           // hwnd
            "open",         // operation
            exe_path,       // executable
            arg_buffer.c_buf,   // parameters
            NULL,           // directory
            SW_SHOW         // show command (ensures window is visible)
        );

        // Check for errors
        if ((intptr_t) result <= 32) {
            DWORD error = GetLastError();
            printf("Failed to launch MPV. Error code: %lu\n", error);
        }
    }

    (void)_getch();
}

void launch_mpv_preview(core_module *core)
{
    mpv_launcher.path = core->externals.mpv_path;
    _launch_ext(core, &mpv_launcher);
}

void launch_ffmpeg(core_module *core)
{
    ffmpeg_launcher.path = core->externals.ffmpeg_path;
    _launch_ext(core, &ffmpeg_launcher);
}
