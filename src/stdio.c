#include "stdio.h"
#include "ViOS/syscall.h"

int printf(const char *fmt, ...)
{
    // Simple implementation - just print the format string
    // TODO: Implement proper format string parsing
    vios_sys_serial_print(fmt);
    return 0;
}

int puts(const char *str)
{
    vios_sys_serial_print(str);
    vios_sys_serial_print_char('\n');
    return 0;
}

int putchar(int c)
{
    vios_sys_putchar((char)c);
    return c;
}