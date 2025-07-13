#include "vios.h"

// Global error code storage
static int vios_last_error = VIOS_SUCCESS;

const char *vios_get_version(void)
{
    return VIOS_VERSION;
}

int vios_get_error_code(void)
{
    return vios_last_error;
}

void vios_clear_error(void)
{
    vios_last_error = VIOS_SUCCESS;
}

// Internal function to set error code
void vios_set_error(int error_code)
{
    vios_last_error = error_code;
} 