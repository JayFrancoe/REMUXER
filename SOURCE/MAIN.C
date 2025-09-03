#include "REMUXER/REMUX_MODULE.H"

remux_module remux;

int main(int argc, char **argv)
{
    core_init(&remux.core, argc, argv);
    com_init(&remux.com);
    draw_init(&remux.ui);
    
    if (argc < 2) {
        set_screen(&remux.ui, SCR_NO_ARG);
    }

    draw_interface(&remux);
}