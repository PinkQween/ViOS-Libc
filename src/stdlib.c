#include "stdlib.h"
#include "ViOS/syscall.h"

void *malloc(unsigned int size)
{
    return vios_sys_malloc(size);
}

void free(void *ptr)
{
    vios_sys_free(ptr);
}

void exit(int code)
{
    vios_sys_exit(code);
}

int atoi(const char *str)
{
    int result = 0;
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result;
}