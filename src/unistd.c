#include "unistd.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "ViOS/syscall.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

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

// Path utilities (no syscalls needed)
static char current_working_directory[256] = "/";

char *getcwd(char *buf, unsigned int size)
{
    if (buf == NULL || size == 0)
        return NULL;

    unsigned int len = strlen(current_working_directory);
    if (len >= size)
        return NULL;

    strcpy(buf, current_working_directory);
    return buf;
}

int chdir(const char *path)
{
    if (path == NULL)
        return -1;

    // Simple implementation - just store the path
    // In a real system, this would validate the path exists
    if (strlen(path) >= sizeof(current_working_directory))
        return -1;

    strcpy(current_working_directory, path);
    return 0;
}

char *basename(char *path)
{
    if (path == NULL)
        return NULL;

    char *last_slash = strrchr(path, '/');
    if (last_slash == NULL)
        return path;

    // If the path ends with '/', find the previous slash
    if (*(last_slash + 1) == '\0')
    {
        *last_slash = '\0';
        last_slash = strrchr(path, '/');
        if (last_slash == NULL)
            return path;
    }

    return last_slash + 1;
}

char *dirname(char *path)
{
    if (path == NULL)
        return NULL;

    char *last_slash = strrchr(path, '/');
    if (last_slash == NULL)
        return ".";

    // If the path ends with '/', find the previous slash
    if (*(last_slash + 1) == '\0')
    {
        *last_slash = '\0';
        last_slash = strrchr(path, '/');
        if (last_slash == NULL)
            return ".";
    }

    *last_slash = '\0';
    return path;
}

// Environment utilities (no syscalls needed)
static char environment_vars[100][256]; // Simple environment storage
static int env_count = 0;

char *getenv(const char *name)
{
    if (name == NULL)
        return NULL;

    for (int i = 0; i < env_count; i++)
    {
        char *eq_pos = strchr(environment_vars[i], '=');
        if (eq_pos != NULL)
        {
            *eq_pos = '\0';
            if (strcmp(environment_vars[i], name) == 0)
            {
                *eq_pos = '=';
                return eq_pos + 1;
            }
            *eq_pos = '=';
        }
    }

    return NULL;
}

int setenv(const char *name, const char *value, int overwrite)
{
    if (name == NULL || value == NULL)
        return -1;

    // Check if variable already exists
    for (int i = 0; i < env_count; i++)
    {
        char *eq_pos = strchr(environment_vars[i], '=');
        if (eq_pos != NULL)
        {
            *eq_pos = '\0';
            if (strcmp(environment_vars[i], name) == 0)
            {
                if (!overwrite)
                {
                    *eq_pos = '=';
                    return 0;
                }
                // Update existing variable
                sprintf(environment_vars[i], "%s=%s", name, value);
                *eq_pos = '=';
                return 0;
            }
            *eq_pos = '=';
        }
    }

    // Add new variable
    if (env_count >= 100)
        return -1;

    sprintf(environment_vars[env_count], "%s=%s", name, value);
    env_count++;
    return 0;
}

int unsetenv(const char *name)
{
    if (name == NULL)
        return -1;

    for (int i = 0; i < env_count; i++)
    {
        char *eq_pos = strchr(environment_vars[i], '=');
        if (eq_pos != NULL)
        {
            *eq_pos = '\0';
            if (strcmp(environment_vars[i], name) == 0)
            {
                // Remove variable by shifting remaining ones
                for (int j = i; j < env_count - 1; j++)
                {
                    strcpy(environment_vars[j], environment_vars[j + 1]);
                }
                env_count--;
                return 0;
            }
            *eq_pos = '=';
        }
    }

    return 0;
}
