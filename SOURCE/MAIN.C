#include "REMUXER/REMUX_MODULE.H"

remux_module remux;

int main(int argc, char **argv)
{
    char *input_file = NULL;

    if (argc > 1) {
        input_file = argv[1];
    } else {
        set_screen(&remux.ui, SCREEN_NO_ARGS);
    }

    core_init(&remux.core, argv[0], input_file);
    com_init(&remux.com);
    draw_init(&remux.ui);
    
    draw_interface(&remux);
}