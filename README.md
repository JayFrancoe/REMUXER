# REMUXER 
A TUI program to edit, remux and organize video footage.

if you are a developer, make sure to read the For Developers section.

## What is remuxing?
Remuxing is the process of taking a media file and running it through ffmpeg to let it 
automatically adjust bitrate and settings to decrease the filesize. 

Simply putting a file through ffmpeg can remove up to 50% of the filesize.

## Why remuxer?
Remuxer lets you quickly change certain aspects of the footage in easy to remember commands. 
The main screen will dynamically update to display your settings, as well as the output file in order
to quickly preview the output path. 

## Features
the `setproject` and `setname` commands will let you organize your footage quickly. `setproject` automatically creates a new folder in your input
files directory and places the output file in that folder. Projects have persistance so you can do a bunch of footage in batches. 

There are certain commands such as `setseektime`, `setduration`, `setbitrate` and `mute` which lets you perform basic edits to your media file.
These are previewable through MPV using the command `play` which launches mpv.exe with the provided options.

### remuxing
Once you're happy with your preview and your output path, Type `remux` to launch a new commandline window with a generated FFMPEG command from your settings.

---

# Installation
Put the remuxer folder into a suitable install location such as your documents folder.

Place a standalone ffmpeg.exe executable and mpv.exe executable in the EXTERNAL folder if not provided.
Ensure these are named "ffmpeg.exe" and "mpv.exe".

---

# For developers
This program is written entirely in C from scratch. It is made up of some important components which can take some time getting used to.

First of all lets talk about how to open and build it.

## Tools needed:
- Windows
- MSVC or Visual Studio

The code does not support linux as I do not know or use linux. If you do, feel free to write a pull request with support, tho undoubtedly there is probably already something like 
avalible in a packagemanger.

# Understanding the source tree
The source tree is made up of the console manipulation library I wrote, and the Remux module. The remux module has three key components that manage everything.

## CON UI
The CON_UI library is a way to manipulate the console for drawing text. Each con_ui function is prefixed with `cui_` and it does not depend on any remuxer code.

## CORE MODULE
The core module has the info for each option, path information for externals and info for the path for argv[1] and install directory.
The core module also houses the code for launching MPV and FFMPEG and the cache manager.

### Cache info
---
The commmands `setproject` and `setextension` will automatically create a core_cache file. This will store your 
project name and extension for you to easier edit multple files. 

Use the commmand `clearcache` to remove this file and clear all cached settings.

## COMMAND MODULE
This module is home to the code for every command. I use the create_com macro to dynamically set up all the information as well as code for the commands.

create_com takes in the command name (which creates a {name}\_fn function prototype, and com\_{name} command_t struct), A short description for the help page,
and finally the body for the command funtion. You get two arguments. A pointer to the remux module, and a char * to the next arg. You can think of this like argv.

ex code:
```c
static 
create_com(setname, 
    "Sets the filename of the output file", {
    char *ref = remux->core.options.file_name;

    copy_arg(ref, args, MAX_FILENAME);
});
```
becomes
```c
static 
void setname_fn(remux_module *remux, char *args) {
    char *ref = remux->core.options.file_name;
    copy_arg(ref, args, 80);
}
command_t com_setname = { .word = "setname", .description = "Sets the filename of the output file", .function = setname_fn };
```
You can register this command at the bottom using `register_com()` and &com_ (your command name)


You also get access to a set_status_message() function to display messages before the screen is updated.

## DRAW MODULE
The draw module is made up in 2 parts. The `DRAW_MODULE/` directory and the `USER_INTERFACE/` directory.

For adding new interfaces, You can largely ignore the draw_module directory with the exception of the screen_e enum which lets you add a screen.

- draw_interface()
This should only be called from main and creates a loop which clears the screen and draws each section from the active_screen pointer.
Raise the exit_signal in order to exit out of loop.

- set_screen() lets you select the screen to draw in the next iteration of the loop. uses the screen_e enum.

## User Interface Code

`Make sure to include "DRAW_MODULE/UI_BUILDER.H" for helper functions when creating UI screens.`

Each interface (main, no_arg, help) is made up of three sections. The Header, Body and Footer section.

To create a new interface, create a `screen_t` struct. You can use the `default_header` and `default_footer` sections if you just want to change the body.

You can create your own header body and footer through the `section_t` struct. This has two important members.

`.draw_fn` which takes in a function pointer of `void(remux_module *, section_t *)` where section_t is itself.
`.origin_y` lets you specify where on the screen to print. Positive numbers go from the top and down, while negative numbers go from the bottom and up. 
You can also use `ORIGIN_CONTINUATION` (0x7FFF) to set the origin to wherever the cursor is after the previous section.

Inside your draw_fn you can use the `get_cui` macro to get a pointer to the con_ui instance. 
Using the `get_section_origin()` function you can parse the origin_y to get a normalized y coordinate. Pass this into `cui_set_cursor` to set the cursor to the origin point.

Now you can use `cui_draw()`, `cui_draw_horizontal()` and `cui_newline()` to draw text, dividers and newlines.

At the end of your function, you can do `section->height = get_section_height()` to dynamically calculate how many rows your section occupy.

Now register your draw function to the draw_fn function pointer, then provide your screen_t section with a pointer to your section_t object.

Inside _REGISTER.C you can now add `extern screen_t screen_name;` and add your screen enum to the set_screen switch case. 

Now just add a command or piece of logic to set_screen to your new screen and voilá, you now have a brand new screen.
