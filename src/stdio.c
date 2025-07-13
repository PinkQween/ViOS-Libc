#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <ViOS/syscall.h>

#ifndef NULL
#define NULL ((void *)0)
#endif

// Helper function to print a string
static void print_string(const char *str)
{
    if (str != NULL)
    {
        vios_sys_serial_print(str);
    }
}

// Helper function to print a number
static void print_number(int num)
{
    char *str = itoa(num);
    print_string(str);
}

// Helper function to print a number in hex
static void print_hex(unsigned int num)
{
    char hex_str[16];
    int i = 0;

    if (num == 0)
    {
        vios_sys_putchar('0');
        return;
    }

    while (num > 0 && i < 15)
    {
        int digit = num & 0xF;
        hex_str[i++] = (digit < 10) ? '0' + digit : 'a' + (digit - 10);
        num >>= 4;
    }

    while (--i >= 0)
    {
        vios_sys_putchar(hex_str[i]);
    }
}

// Helper function to print unsigned number
static void print_unsigned(unsigned int num)
{
    char str[16];
    int i = 0;

    if (num == 0)
    {
        vios_sys_putchar('0');
        return;
    }

    while (num > 0 && i < 15)
    {
        str[i++] = '0' + (num % 10);
        num /= 10;
    }

    while (--i >= 0)
    {
        vios_sys_putchar(str[i]);
    }
}

int printf(const char *fmt, ...)
{
    if (fmt == NULL)
        return 0;

    int count = 0;
    const char *p = fmt;

    // Simple va_list simulation for basic varargs
    char **arg_ptr = (char **)&fmt + 1;

    while (*p)
    {
        if (*p != '%')
        {
            vios_sys_putchar(*p);
            count++;
            p++;
            continue;
        }

        p++; // Skip '%'

        switch (*p)
        {
        case 'd':
        case 'i':
            print_number(*(int *)arg_ptr);
            arg_ptr++;
            count++;
            break;

        case 'u':
            print_unsigned(*(unsigned int *)arg_ptr);
            arg_ptr++;
            count++;
            break;

        case 'x':
        case 'X':
            print_hex(*(unsigned int *)arg_ptr);
            arg_ptr++;
            count++;
            break;

        case 's':
            print_string(*(char **)arg_ptr);
            arg_ptr++;
            count++;
            break;

        case 'c':
            vios_sys_putchar(*(char *)arg_ptr);
            arg_ptr++;
            count++;
            break;

        case '%':
            vios_sys_putchar('%');
            count++;
            break;

        default:
            vios_sys_putchar('%');
            vios_sys_putchar(*p);
            count += 2;
            break;
        }
        p++;
    }

    return count;
}

int sprintf(char *str, const char *fmt, ...)
{
    if (str == NULL || fmt == NULL)
        return 0;

    int pos = 0;
    const char *p = fmt;

    // Simple va_list simulation for basic varargs
    char **arg_ptr = (char **)&fmt + 1;

    while (*p)
    {
        if (*p != '%')
        {
            str[pos++] = *p;
            p++;
            continue;
        }

        p++; // Skip '%'

        switch (*p)
        {
        case 'd':
        case 'i':
        {
            char *num_str = itoa(*(int *)arg_ptr);
            while (*num_str)
            {
                str[pos++] = *num_str++;
            }
            arg_ptr++;
        }
        break;

        case 's':
        {
            char *s = *(char **)arg_ptr;
            while (*s)
            {
                str[pos++] = *s++;
            }
            arg_ptr++;
        }
        break;

        case 'c':
            str[pos++] = *(char *)arg_ptr;
            arg_ptr++;
            break;

        case '%':
            str[pos++] = '%';
            break;

        default:
            str[pos++] = '%';
            str[pos++] = *p;
            break;
        }
        p++;
    }

    str[pos] = '\0';
    return pos;
}

int snprintf(char *str, unsigned int size, const char *fmt, ...)
{
    if (str == NULL || size == 0 || fmt == NULL)
        return 0;

    int pos = 0;
    const char *p = fmt;

    // Simple va_list simulation for basic varargs
    char **arg_ptr = (char **)&fmt + 1;

    while (*p && pos < (int)size - 1)
    {
        if (*p != '%')
        {
            str[pos++] = *p;
            p++;
            continue;
        }

        p++; // Skip '%'

        switch (*p)
        {
        case 'd':
        case 'i':
        {
            char *num_str = itoa(*(int *)arg_ptr);
            while (*num_str && pos < (int)size - 1)
            {
                str[pos++] = *num_str++;
            }
            arg_ptr++;
        }
        break;

        case 's':
        {
            char *s = *(char **)arg_ptr;
            while (*s && pos < (int)size - 1)
            {
                str[pos++] = *s++;
            }
            arg_ptr++;
        }
        break;

        case 'c':
            if (pos < (int)size - 1)
            {
                str[pos++] = *(char *)arg_ptr;
            }
            arg_ptr++;
            break;

        case '%':
            if (pos < (int)size - 1)
            {
                str[pos++] = '%';
            }
            break;

        default:
            if (pos < (int)size - 1)
            {
                str[pos++] = '%';
            }
            if (pos < (int)size - 1)
            {
                str[pos++] = *p;
            }
            break;
        }
        p++;
    }

    str[pos] = '\0';
    return pos;
}

int puts(const char *str)
{
    if (str != NULL)
    {
        vios_sys_serial_print(str);
        vios_sys_putchar('\n');
    }
    return 0;
}

int putchar(int c)
{
    vios_sys_putchar((char)c);
    return c;
}

int getchar(void)
{
    // This would need a syscall to read from keyboard/input
    // For now, return EOF (-1) to indicate no input available
    return -1;
}