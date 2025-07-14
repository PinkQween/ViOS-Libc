#include "stdlib.h"
#include <ViOS/syscall.h>

#ifndef NULL
#define NULL ((void *)0)
#endif

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
    int sign = 1;

    // Handle leading whitespace
    while (*str == ' ' || *str == '\t' || *str == '\n')
        str++;

    // Handle sign
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    else if (*str == '+')
    {
        str++;
    }

    // Convert digits
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return sign * result;
}

char *itoa(int i)
{
    // Use multiple static buffers to reduce conflicts between calls
    static char text_buffers[4][12];
    static int buffer_index = 0;
    
    char *text = text_buffers[buffer_index];
    buffer_index = (buffer_index + 1) % 4;
    
    int loc = 11;
    text[11] = 0;
    char neg = 1;

    if (i >= 0)
    {
        neg = 0;
        i = -i;
    }

    while (i)
    {
        text[--loc] = '0' - (i % 10);
        i /= 10;
    }

    if (loc == 11)
        text[--loc] = '0';

    if (neg)
        text[--loc] = '-';

    return &text[loc];
}

int abs(int x)
{
    return (x < 0) ? -x : x;
}

long labs(long x)
{
    return (x < 0) ? -x : x;
}

// Helper function for qsort
static void swap(void *a, void *b, unsigned int size)
{
    char *p1 = (char *)a;
    char *p2 = (char *)b;
    char tmp;

    while (size--)
    {
        tmp = *p1;
        *p1++ = *p2;
        *p2++ = tmp;
    }
}

void qsort(void *base, unsigned int nmemb, unsigned int size, int (*compar)(const void *, const void *))
{
    if (nmemb <= 1)
        return;

    char *arr = (char *)base;
    char *pivot = arr + (nmemb - 1) * size;
    char *i = arr - size;

    for (char *j = arr; j < pivot; j += size)
    {
        if (compar(j, pivot) <= 0)
        {
            i += size;
            if (i != j)
                swap(i, j, size);
        }
    }

    i += size;
    if (i != pivot)
        swap(i, pivot, size);

    unsigned int pivot_index = (i - arr) / size;
    qsort(arr, pivot_index, size, compar);
    qsort(i + size, nmemb - pivot_index - 1, size, compar);
}

void *bsearch(const void *key, const void *base, unsigned int nmemb, unsigned int size, int (*compar)(const void *, const void *))
{
    char *arr = (char *)base;
    unsigned int left = 0;
    unsigned int right = nmemb - 1;

    while (left <= right)
    {
        unsigned int mid = (left + right) / 2;
        char *mid_ptr = arr + mid * size;
        int cmp = compar(key, mid_ptr);

        if (cmp == 0)
            return mid_ptr;
        else if (cmp < 0)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return NULL;
}