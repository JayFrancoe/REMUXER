# REMUXER 
A program to edit, remux and organize video footage.

## What is remuxing?
Remuxing is the process of taking a media file and running it through ffmpeg to let it 
automatically adjust bitrate and settings to decrease the filesize. 

Simply putting a file through ffmpeg can remove up to 50% of the filesize.

## Why remuxer?
Remuxer lets you quickly change certain aspects of the footage in easy to remember commands. 
The main screen will dynamically update to display your settings, as well as the output file in order
to quickly preview the output path. 

## Features
the `setproject` and `setname` commands will let you organize your footage quickly. Projects have persistance 
so you can do a bunch of footage in batches. `setproject` automatically creates a new folder in your input
files directory.

There are certain commands such as `setseektime`, `setduration`, `setbitrate` and `mute` which lets you perform basic edits to your media file.
These are previewable through MPV using the command `play` which launches mpv.exe with the provided options.

Once you're happy with your preview and your output path, Type `remux` to launch a new commandline window with a generated FFMPEG command from your settings.

---

# Installation
Put the remuxer folder into a suitable install location such as your documents folder.

Place a standalone ffmpeg.exe executable and mpv.exe executable in the EXTERNAL folder if not provided.
Ensure these are named "ffmpeg.exe" and "mpv.exe".

Drag a media file onto `remuxer.exe` and type your commands to modify the settings.  

## cache
The commmands `setproject` and `setextension` will automatically create a core_cache file. This will store your 
project name and extension for you to easier edit multple files. 

Use the commmand `clearcache` to remove this file and clear all cached settings.

