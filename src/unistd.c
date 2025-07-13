#include "unistd.h"
#include "ViOS/syscall.h"

// Process control
void _exit(int status)
{
    vios_sys_exit(status);
}

int fork(void)
{
    // TODO: Implement process forking when supported
    return -1;
}

int execve(const char *pathname, char *const argv[] __attribute__((unused)), char *const envp[] __attribute__((unused)))
{
    // Use the process load start syscall
    return vios_sys_process_load_start(pathname);
}

// File operations
int read(int fd __attribute__((unused)), void *buf __attribute__((unused)), unsigned int count __attribute__((unused)))
{
    // TODO: Implement file descriptor based reading
    // For now, return error
    return -1;
}

int write(int fd __attribute__((unused)), const void *buf __attribute__((unused)), unsigned int count __attribute__((unused)))
{
    // TODO: Implement file descriptor based writing
    // For now, return error
    return -1;
}

int close(int fd __attribute__((unused)))
{
    // TODO: Implement file descriptor closing
    return -1;
}

int open(const char *pathname __attribute__((unused)), int flags __attribute__((unused)))
{
    // TODO: Implement file opening
    return -1;
}

// System utilities
unsigned int sleep(unsigned int seconds)
{
    vios_sys_sleep(seconds * 1000); // Convert to milliseconds
    return 0;
}

int usleep(unsigned int usec)
{
    vios_sys_sleep(usec / 1000); // Convert to milliseconds
    return 0;
}
