#include <ViOS/ViOS.h>

#ifndef NULL
#define NULL ((void *)0)
#endif

// Generic syscall wrapper: passes up to N arguments using the stack
static inline int vios_syscallN(uint32_t syscall_number, uint32_t *args, uint32_t argc)
{
    for (int i = argc; i > 0; i--)
    {
        __asm__ volatile("push %0" ::"r"(args[i - 1]));
    }

    int result;
    __asm__ volatile(
        "mov %[num], %%eax\n"
        "int $0x80\n"
        : "=a"(result)
        : [num] "r"(syscall_number)
        : "memory");

    __asm__ volatile("add %0, %%esp" ::"r"(argc * 4));
    return result;
}

// ───────────────────────────────────────────────
// Process Management
// ───────────────────────────────────────────────

void vios_sys_exit(int code)
{
    uint32_t args[] = {(uint32_t)code};
    vios_syscallN(SYSTEM_COMMAND0_EXIT, args, 1);
}

int vios_sys_process_load_start(const char *filename)
{
    uint32_t args[] = {(uint32_t)filename};
    return vios_syscallN(SYSTEM_COMMAND1_PROCESS_LOAD_START, args, 1);
}

int vios_sys_invoke_system_command(int command, void *args_ptr)
{
    uint32_t args[] = {(uint32_t)command, (uint32_t)args_ptr};
    return vios_syscallN(SYSTEM_COMMAND2_INVOKE_SYSTEM_COMMAND, args, 2);
}

// ───────────────────────────────────────────────
// I/O Operations
// ───────────────────────────────────────────────

int vios_sys_getkey(void)
{
    return vios_syscallN(SYSTEM_COMMAND3_GETKEY, NULL, 0);
}

void vios_sys_putchar(char c)
{
    uint32_t args[] = {(uint32_t)(uint8_t)c};
    vios_syscallN(SYSTEM_COMMAND4_PUTCHAR_SERIAL, args, 1);
}

void vios_sys_serial_print(const char *str)
{
    uint32_t args[] = {(uint32_t)str};
    vios_syscallN(SYSTEM_COMMAND5_PRINT_SERIAL, args, 1);
}

// ───────────────────────────────────────────────
// Memory Management
// ───────────────────────────────────────────────

void *vios_sys_malloc(uint32_t size)
{
    uint32_t args[] = {size};
    return (void *)vios_syscallN(SYSTEM_COMMAND7_MALLOC, args, 1);
}

void vios_sys_free(void *ptr)
{
    uint32_t args[] = {(uint32_t)ptr};
    vios_syscallN(SYSTEM_COMMAND8_FREE, args, 1);
}

// ───────────────────────────────────────────────
// File Operations
// ───────────────────────────────────────────────

int vios_sys_read(const char *filename, void *buffer, uint32_t size)
{
    uint32_t args[] = {(uint32_t)filename, (uint32_t)buffer, size};
    return vios_syscallN(SYSTEM_COMMAND9_READ, args, 3);
}

// ───────────────────────────────────────────────
// System Utilities
// ───────────────────────────────────────────────

void vios_sys_sleep(uint32_t milliseconds)
{
    uint32_t args[] = {milliseconds};
    vios_syscallN(SYSTEM_COMMAND10_SLEEP, args, 1);
}

void vios_sys_get_program_arguments(struct process_arguments *arguments)
{
    uint32_t args[] = {(uint32_t)arguments};
    vios_syscallN(SYSTEM_COMMAND11_GET_PROGRAM_ARGUMENTS, args, 1);
}