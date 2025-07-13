#ifndef VIOS_STDLIB_H
#define VIOS_STDLIB_H

#ifdef __cplusplus
extern "C"
{
#endif

    void *malloc(unsigned int size);
    void free(void *ptr);
    void exit(int status);
    int atoi(const char *str);

#ifdef __cplusplus
}
#endif

#endif
