#ifndef _STDIO_H
#define _STDIO_H 1

#ifdef __cplusplus
extern "C"
{
#endif

    int printf(const char *fmt, ...);
    int puts(const char *str);
    int putchar(int c);

#ifdef __cplusplus
}
#endif

#endif