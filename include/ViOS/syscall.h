#ifndef VIOS_SYSCALL_H
#define VIOS_SYSCALL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

// System command definitions
#define SYSTEM_COMMAND0_EXIT 0
#define SYSTEM_COMMAND1_PROCESS_LOAD_START 1
#define SYSTEM_COMMAND2_INVOKE_SYSTEM_COMMAND 2
#define SYSTEM_COMMAND3_GETKEY 3
#define SYSTEM_COMMAND4_PUTCHAR 4
#define SYSTEM_COMMAND5_PRINT_SERIAL 5
#define SYSTEM_COMMAND6_PRINT_CHAR_SERIAL 6
#define SYSTEM_COMMAND7_MALLOC 7
#define SYSTEM_COMMAND8_FREE 8
#define SYSTEM_COMMAND9_READ 9
#define SYSTEM_COMMAND10_SLEEP 10
#define SYSTEM_COMMAND11_GET_PROGRAM_ARGUMENTS 11

    // Process Management
    void vios_sys_exit(int code);
    int vios_sys_process_load_start(const char *filename);
    int vios_sys_invoke_system_command(int command, void *args);

    // I/O Operations
    int vios_sys_getkey(void);
    void vios_sys_putchar(char c);
    void vios_sys_serial_print(const char *str);
    void vios_sys_serial_print_char(char c);

    // Memory Management
    void *vios_sys_malloc(uint32_t size);
    void vios_sys_free(void *ptr);

    // File Operations
    int vios_sys_read(const char *filename, void *buffer, uint32_t size);

    // System Utilities
    void vios_sys_sleep(uint32_t milliseconds);
    char *vios_sys_get_program_arguments(void);

#ifdef __cplusplus
}
#endif

#endif
