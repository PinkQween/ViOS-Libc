#include <ViOS/ViOS.h>

extern int main(int argc, char **argv);

void c_start()
{
    struct process_arguments arguments;
    vios_sys_get_program_arguments(&arguments);

    int res = main(arguments.argc, arguments.argv);
    vios_sys_exit(res);
}
