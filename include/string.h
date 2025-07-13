#ifndef VIOS_STRING_H
#define VIOS_STRING_H

#ifdef __cplusplus
extern "C"
{
#endif

    unsigned int strlen(const char *str);
    void *memset(void *s, int c, unsigned int n);
    void *memcpy(void *dest, const void *src, unsigned int n);
    int strcmp(const char *s1, const char *s2);

#ifdef __cplusplus
}
#endif

#endif