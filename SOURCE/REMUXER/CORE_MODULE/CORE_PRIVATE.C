#include <memory.h>
#include <string.h>

#include "CORE_PRIVATE.H"

void init_externals(core_module *core)
{
    core_externals *ext = &core->externals;

    _memccpy(ext->mpv_path, core->install_directory, 0, MAX_PATH);
    _memccpy(ext->ffmpeg_path, core->install_directory, 0, MAX_PATH);

    strcat(ext->mpv_path, "/EXTERNAL/mpv.exe");
    strcat(ext->ffmpeg_path, "/EXTERNAL/ffmpeg.exe");
}
