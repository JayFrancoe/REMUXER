#pragma once
#include "REMUXER/DRAW_MODULE/DRAW_PUBLIC.H"
#include "REMUXER/CORE_MODULE/CORE_PUBLIC.H"
#include "REMUXER/COMMAND_MODULE/COM_PUBLIC.H"

typedef struct remux_module_s remux_module;

struct remux_module_s
{
    core_module    core;
    command_module com;
    draw_module    ui;

    bool exit_signal;
};