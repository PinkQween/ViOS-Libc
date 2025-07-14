#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdarg.h>
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

    // Use a temporary buffer to build the complete output string
    char buffer[1024]; // Adjust size as needed
    int pos = 0;
    const char *p = fmt;
    va_list args;
    va_start(args, fmt);

    while (*p && pos < 1023) // Leave space for null terminator
    {
        if (*p != '%')
        {
            buffer[pos++] = *p;
            p++;
            continue;
        }

        p++; // Skip '%'

        switch (*p)
        {
        case 'd':
        case 'i':
        {
            char *num_str = itoa(va_arg(args, int));
            while (*num_str && pos < 1023)
            {
                buffer[pos++] = *num_str++;
            }
            break;
        }

        case 'u':
        {
            unsigned int num = va_arg(args, unsigned int);
            char str[16];
            int i = 0;
            
            if (num == 0)
            {
                if (pos < 1023) buffer[pos++] = '0';
            }
            else
            {
                while (num > 0 && i < 15)
                {
                    str[i++] = '0' + (num % 10);
                    num /= 10;
                }
                while (--i >= 0 && pos < 1023)
                {
                    buffer[pos++] = str[i];
                }
            }
            break;
        }

        case 'x':
        case 'X':
        {
            unsigned int num = va_arg(args, unsigned int);
            char hex_str[16];
            int i = 0;
            
            if (num == 0)
            {
                if (pos < 1023) buffer[pos++] = '0';
            }
            else
            {
                while (num > 0 && i < 15)
                {
                    int digit = num & 0xF;
                    hex_str[i++] = (digit < 10) ? '0' + digit : 'a' + (digit - 10);
                    num >>= 4;
                }
                while (--i >= 0 && pos < 1023)
                {
                    buffer[pos++] = hex_str[i];
                }
            }
            break;
        }

        case 's':
        {
            char *str = va_arg(args, char*);
            if (str != NULL)
            {
                while (*str && pos < 1023)
                {
                    buffer[pos++] = *str++;
                }
            }
            break;
        }

        case 'c':
            if (pos < 1023)
            {
                buffer[pos++] = (char)va_arg(args, int);
            }
            break;

        case '%':
            if (pos < 1023)
            {
                buffer[pos++] = '%';
            }
            break;

        default:
            if (pos < 1022) // Need space for both characters
            {
                buffer[pos++] = '%';
                buffer[pos++] = *p;
            }
            break;
        }
        p++;
    }

    buffer[pos] = '\0';
    va_end(args);

    // Use the more reliable string-based syscall
    vios_sys_serial_print(buffer);
    
    return pos;
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