#include "REMUXER/REMUX_MODULE.H"

remux_module remux;

int main(int argc, char **argv)
{
    char *input_file = (argc > 1) ? argv[1] : NULL;

    core_init(&remux.core, argv[0], input_file);
    comm_init(&remux.com);
    draw_init(&remux.ui);
    
    if (input_file == NULL) {
        set_screen(&remux.ui, SCREEN_NO_ARGS);
    }

    while (!remux.exit_signal) {
        draw_interface(&remux); 
    }
}