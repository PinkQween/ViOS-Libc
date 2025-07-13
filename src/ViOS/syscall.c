#include "syscall.h"

// Process Management
void vios_sys_exit(int code)
{
    __asm__ volatile(
        "int $0x80"
        :
        : "a"(SYSTEM_COMMAND0_EXIT), "b"(code));
}

int vios_sys_process_load_start(const char *filename)
{
    int result;
    __asm__ volatile(
        "int $0x80"
        : "=a"(result)
        : "a"(SYSTEM_COMMAND1_PROCESS_LOAD_START), "b"(filename));
    return result;
}

int vios_sys_invoke_system_command(int command, void *args)
{
    int result;
    __asm__ volatile(
        "int $0x80"
        : "=a"(result)
        : "a"(SYSTEM_COMMAND2_INVOKE_SYSTEM_COMMAND), "b"(command), "c"(args));
    return result;
}

// I/O Operations
int vios_sys_getkey(void)
{
    int key;
    __asm__ volatile(
        "int $0x80"
        : "=a"(key)
        : "a"(SYSTEM_COMMAND3_GETKEY));
    return key;
}

void vios_sys_putchar(char c)
{
    __asm__ volatile(
        "int $0x80"
        :
        : "a"(SYSTEM_COMMAND4_PUTCHAR), "b"(c));
}

void vios_sys_serial_print(const char *str)
{
    __asm__ volatile(
        "int $0x80"
        :
        : "a"(SYSTEM_COMMAND5_PRINT_SERIAL), "b"(str));
}

void vios_sys_serial_print_char(char c)
{
    __asm__ volatile(
        "int $0x80"
        :
        : "a"(SYSTEM_COMMAND6_PRINT_CHAR_SERIAL), "b"(c));
}

// Memory Management
void *vios_sys_malloc(uint32_t size)
{
    void *result;
    __asm__ volatile(
        "int $0x80"
        : "=a"(result)
        : "a"(SYSTEM_COMMAND7_MALLOC), "b"(size));
    return result;
}

void vios_sys_free(void *ptr)
{
    __asm__ volatile(
        "int $0x80"
        :
        : "a"(SYSTEM_COMMAND8_FREE), "b"(ptr));
}

// File Operations
int vios_sys_read(const char *filename, void *buffer, uint32_t size)
{
    int result;
    __asm__ volatile(
        "int $0x80"
        : "=a"(result)
        : "a"(SYSTEM_COMMAND9_READ), "b"(filename), "c"(buffer), "d"(size));
    return result;
}

// System Utilities
void vios_sys_sleep(uint32_t milliseconds)
{
    __asm__ volatile(
        "int $0x80"
        :
        : "a"(SYSTEM_COMMAND10_SLEEP), "b"(milliseconds));
}

char *vios_sys_get_program_arguments(void)
{
    char *result;
    __asm__ volatile(
        "int $0x80"
        : "=a"(result)
        : "a"(SYSTEM_COMMAND11_GET_PROGRAM_ARGUMENTS));
    return result;
}