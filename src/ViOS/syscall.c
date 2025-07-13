#include "ViOS/syscall.h"
#include "ViOS/ViOS.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

// Process Management
void vios_sys_exit(int code)
{
    vios_sys_serial_print("DEBUG: vios_sys_exit called with code: ");
    // ... print the code ...
    vios_sys_serial_print("\n");

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
        : "a"(SYSTEM_COMMAND4_PUTCHAR_SERIAL), "b"(c));
}

void vios_sys_serial_print(const char *str)
{
    __asm__ volatile(
        "int $0x80"
        :
        : "a"(SYSTEM_COMMAND5_PRINT_SERIAL), "b"(str));
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

void vios_sys_get_program_arguments(struct process_arguments *arguments)
{
    // TODO: Implement argument retrieval from system
    // For now, this is a placeholder implementation
    if (arguments)
    {
        arguments->argc = 0;
        arguments->argv = NULL;
    }
}