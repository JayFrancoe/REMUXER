#pragma once
// REMUX
typedef struct remux_module_s remux_module;

// DRAW
typedef struct draw_module_s draw_module;
typedef struct ui_screen_s   screen_t;
typedef struct section_s     section_t;

// CORE
typedef struct core_options_s core_options;
typedef struct core_module_s  core_module;
typedef struct core_externals_s core_externals;

// COMMMAND
typedef struct command_module_s command_module;
typedef void( *command_fn )( remux_module *,
                             const char * );

typedef void( *ui_draw_fn )( remux_module *, 
                              section_t *);