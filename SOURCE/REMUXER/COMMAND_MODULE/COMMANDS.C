#include <ctype.h>
#include "REMUXER/DRAW_MODULE/DRAW_PUBLIC.H"

#include "COM_PRIVATE.H"
#include "COM_PUBLIC.H"


static 
create_com(setname, 
    "Sets the filename of the output file", {
    char *ref = remux->core.options.file_name;

    copy_arg(ref, args, MAX_FILENAME);
});

static
create_com(setproject, 
    "Places output file in a directory of this name", {
    char *ref = remux->core.options.project;

    copy_arg(ref, args, MAX_FILENAME);
    cache_core(&remux->core);
});

static
create_com(setextension,
    "Sets the output files extension", {
    char *ref = remux->core.options.extension;

    copy_arg(ref, args, MAX_EXTENSION);
    cache_core(&remux->core);
});

static
create_com(setseektime, 
    "Sets the beginning timecode for output file. Previewable.", {
    char *ref = remux->core.options.seek_time;

    copy_arg(ref, args, MAX_NUMBER);
});

static
create_com(setduration, 
    "Sets the end timecode of the output video. Previewable", {
    char *ref = remux->core.options.duration;

    copy_arg(ref, args, MAX_NUMBER);
});

static
create_com(setbitrate, 
    "sets output bitrate. example: 8M == 8000kbps. Not previewable", {
    char *ref = remux->core.options.bitrate;

    if (!isalnum(args[0])
    || args[1] != 'M')
    {
        set_status_message(&remux->com, 
                           "bitrate format: {NUM}M (8M == 8000kbps)");
        return;
    }

    copy_arg(ref, args, 30);
});

static
create_com(mute,
    "Toggles if output should be muted.", {
    remux->core.options.mute = !remux->core.options.mute;
});

static
create_com(unmute,
    "Unmutes output file.", {
    remux->core.options.mute = 0;
});

static
create_com(play, 
    "Launches mpv with preview of output file.", {
    launch_mpv_preview(&remux->core);
});

static
create_com(remux, 
    "Launches ffmpeg with remux arguments.", {
    launch_ffmpeg(&remux->core);
});

static
create_com(clearcache, 
    "clears the cache file", {
    
    clear_cache(&remux->core);
});

static
create_com(debug,
    "Toggles debug mode (internal)", {
    remux->core.debug = 1;
});

static
create_com(back,
    "Goes back to main screen", {
    set_screen(&remux->ui, SCR_MAIN);
});

static
create_com(exit, 
    "Exits program", {
    remux->exit_signal = 1;
});

static
create_com(help, "what are we doin here man..", {
    set_screen(&remux->ui, SCR_HELP);
});


void register_commands(command_module *com)
{
    register_com(com, &com_setname);
    register_com(com, &com_setproject);
    register_com(com, &com_setextension);
    register_com(com, &com_setseektime);
    register_com(com, &com_setduration);
    register_com(com, &com_setbitrate);
    register_com(com, &com_mute);
    register_com(com, &com_unmute);
    register_com(com, &com_play);
    register_com(com, &com_remux);
    register_com(com, &com_clearcache);
    register_com(com, &com_exit);
    register_com(com, &com_back);
    register_com(com, &com_help);
    register_com(com, &com_debug);

}