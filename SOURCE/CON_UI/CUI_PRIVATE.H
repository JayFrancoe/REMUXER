#pragma once
#include "CUI_PUBLIC.H"
#include "Windows.h"

extern
HANDLE h_input, h_output;

void cui_init_internal(con_ui *cui);

void cui_refresh_cursor_internal(con_ui *cui);