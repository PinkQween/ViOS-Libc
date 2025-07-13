#ifndef UNISTD_H
#define UNISTD_H

#ifdef __cplusplus
extern "C"
{
#endif

    // Process control
    void _exit(int status);
    int fork(void);
    int execve(const char *pathname, char *const argv[], char *const envp[]);

    // File operations
    int read(int fd, void *buf, unsigned int count);
    int write(int fd, const void *buf, unsigned int count);
    int close(int fd);
    int open(const char *pathname, int flags);

    // System utilities
    unsigned int sleep(unsigned int seconds);
    int usleep(unsigned int usec);

#ifdef __cplusplus
}
#endif

#endif
