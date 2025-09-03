#pragma once
#include <conio.h>
#include <stdio.h>
#include <stdarg.h>

#define PROCESS_ARGS_OUT_LEN(_Buffername, _size, _format, _len)\
char _Buffername##[_size] = {0}; int _len = 0;\
{ va_list args; va_start(args, _format);\
_len = vsprintf(_Buffername, _format, args); va_end(args);}

#define READ_VAR_ARGS(_Buffername, _size, _format)\
PROCESS_ARGS_OUT_LEN(_Buffername, _size, _format, __UNUSED);


#define MAX_COMMANDS  16
#define MAX_NUMBER    30
#define MAX_EXTENSION 10
#define MAX_FILENAME  80
#define MAX_PATH      260

typedef enum { false, true } bool;

typedef struct path_s path_t;

struct path_s
{
    char file_extension[MAX_EXTENSION];
    char file_name[MAX_FILENAME];
    char file_directory[MAX_PATH];
    char file_path[MAX_PATH];
};
