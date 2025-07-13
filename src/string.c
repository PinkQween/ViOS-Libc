#include "string.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

unsigned int strlen(const char *str)
{
    unsigned int len = 0;
    while (str[len])
        len++;
    return len;
}

int strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int strncmp(const char *s1, const char *s2, unsigned int n)
{
    while (n-- > 0)
    {
        if (*s1 != *s2)
            return *(unsigned char *)s1 - *(unsigned char *)s2;
        if (*s1 == '\0')
            return 0;
        s1++;
        s2++;
    }
    return 0;
}

char *strcpy(char *dest, const char *src)
{
    char *original = dest;
    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return original;
}

char *strncpy(char *dest, const char *src, unsigned int n)
{
    char *original = dest;
    unsigned int i;

    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];

    for (; i < n; i++)
        dest[i] = '\0';

    return original;
}

char *strcat(char *dest, const char *src)
{
    char *original = dest;

    // Find end of dest
    while (*dest)
        dest++;

    // Copy src to end of dest
    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';

    return original;
}

char *strncat(char *dest, const char *src, unsigned int n)
{
    char *original = dest;

    // Find end of dest
    while (*dest)
        dest++;

    // Copy at most n characters from src
    while (n-- > 0 && *src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';

    return original;
}

char *strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    if ((char)c == '\0')
        return (char *)s;
    return NULL;
}

char *strrchr(const char *s, int c)
{
    char *last = NULL;
    while (*s)
    {
        if (*s == (char)c)
            last = (char *)s;
        s++;
    }
    if ((char)c == '\0')
        return (char *)s;
    return last;
}

char *strstr(const char *haystack, const char *needle)
{
    if (*needle == '\0')
        return (char *)haystack;

    while (*haystack)
    {
        const char *h = haystack;
        const char *n = needle;

        while (*h && *n && *h == *n)
        {
            h++;
            n++;
        }

        if (*n == '\0')
            return (char *)haystack;

        haystack++;
    }

    return NULL;
}

static char *strtok_save = NULL;

char *strtok(char *str, const char *delim)
{
    char *token_start;

    if (str != NULL)
        strtok_save = str;
    else if (strtok_save == NULL)
        return NULL;

    // Skip leading delimiters
    while (*strtok_save && strchr(delim, *strtok_save))
        strtok_save++;

    if (*strtok_save == '\0')
    {
        strtok_save = NULL;
        return NULL;
    }

    token_start = strtok_save;

    // Find end of token
    while (*strtok_save && !strchr(delim, *strtok_save))
        strtok_save++;

    if (*strtok_save != '\0')
    {
        *strtok_save = '\0';
        strtok_save++;
    }
    else
    {
        strtok_save = NULL;
    }

    return token_start;
}

void *memset(void *s, int c, unsigned int n)
{
    unsigned char *p = s;
    while (n--)
        *p++ = (unsigned char)c;
    return s;
}

void *memcpy(void *dest, const void *src, unsigned int n)
{
    char *d = dest;
    const char *s = src;
    while (n--)
        *d++ = *s++;
    return dest;
}

int memcmp(const void *s1, const void *s2, unsigned int n)
{
    const unsigned char *p1 = s1;
    const unsigned char *p2 = s2;

    while (n-- > 0)
    {
        if (*p1 != *p2)
            return *p1 - *p2;
        p1++;
        p2++;
    }
    return 0;
}

void *memchr(const void *s, int c, unsigned int n)
{
    const unsigned char *p = s;
    while (n-- > 0)
    {
        if (*p == (unsigned char)c)
            return (void *)p;
        p++;
    }
    return NULL;
}

char tolower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}

char toupper(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 32;
    return c;
}

int isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

int isalpha(int c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int isalnum(int c)
{
    return (isalpha(c) || isdigit(c));
}

int isspace(int c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}