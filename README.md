# ViOS libc

[![Build Status](https://github.com/yourusername/vios-libc/workflows/Build%20ViOS%20libc/badge.svg)](https://github.com/yourusername/vios-libc/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Version](https://img.shields.io/badge/version-0.0.1-blue.svg)](https://github.com/yourusername/vios-libc/releases)

A C standard library implementation for the ViOS operating system.

## Organization

All OS-specific code is organized in the `ViOS/` directory:

### Headers (`include/ViOS/`)
- `syscall.h` - System call interface definitions
- `vios.h` - Main ViOS header with constants and utility functions

### Implementation (`src/ViOS/`)
- `syscall.c` - System call implementations using inline assembly
- `vios.c` - ViOS utility functions

## System Calls

The libc implements the following system calls that correspond to the kernel's interrupt 0x80h handlers:

### Process Management
- `SYSTEM_COMMAND0_EXIT` (0) - Exit process
- `SYSTEM_COMMAND1_PROCESS_LOAD_START` (1) - Load and start a new process
- `SYSTEM_COMMAND2_INVOKE_SYSTEM_COMMAND` (2) - Invoke system command

### I/O Operations
- `SYSTEM_COMMAND3_GETKEY` (3) - Get keyboard input
- `SYSTEM_COMMAND4_PUTCHAR` (4) - Print character to display
- `SYSTEM_COMMAND5_PRINT_SERIAL` (5) - Print string to serial
- `SYSTEM_COMMAND6_PRINT_CHAR_SERIAL` (6) - Print character to serial

### Memory Management
- `SYSTEM_COMMAND7_MALLOC` (7) - Allocate memory
- `SYSTEM_COMMAND8_FREE` (8) - Free memory

### File Operations
- `SYSTEM_COMMAND9_READ` (9) - Read from file

### System Utilities
- `SYSTEM_COMMAND10_SLEEP` (10) - Sleep for specified milliseconds
- `SYSTEM_COMMAND11_GET_PROGRAM_ARGUMENTS` (11) - Get program arguments

## Standard Library Functions

The following standard library functions are implemented using ViOS syscalls:

### stdio.h
- `printf()` - Print formatted string (basic implementation)
- `puts()` - Print string with newline
- `putchar()` - Print single character

### stdlib.h
- `malloc()` - Memory allocation
- `free()` - Memory deallocation
- `exit()` - Process termination
- `atoi()` - String to integer conversion

### unistd.h
- `_exit()` - Process termination
- `execve()` - Execute program
- `sleep()` - Sleep for seconds
- `usleep()` - Sleep for microseconds

## Building

```bash
make
```

This will create a static library `libViOSlibc.a` in the `build/` directory.

### Prerequisites

- GCC cross-compiler for i686-elf target
- NASM assembler
- Make

### Quick Start

```bash
# Clone the repository
git clone https://github.com/yourusername/vios-libc.git
cd vios-libc

# Build the library
make

# Install (optional)
make install
```

## Installation

```bash
make install
```

This installs the library and headers to `/opt/ViOS/`.

## Usage

Include the appropriate headers in your C programs:

```c
#include <stdio.h>      // Standard I/O
#include <stdlib.h>     // Standard library
#include <unistd.h>     // POSIX functions
#include <ViOS/vios.h>  // ViOS-specific functions
```

## Error Handling

ViOS-specific error codes are defined in `vios.h`:

- `VIOS_SUCCESS` (0) - Operation successful
- `VIOS_ERROR` (-1) - General error
- `VIOS_ERROR_INVALID_PARAMETER` (-2) - Invalid parameter
- `VIOS_ERROR_NOT_FOUND` (-3) - Resource not found
- `VIOS_ERROR_PERMISSION_DENIED` (-4) - Permission denied
- `VIOS_ERROR_OUT_OF_MEMORY` (-5) - Out of memory

Use `vios_get_error_code()` to retrieve the last error code and `vios_clear_error()` to clear it.

## Contributing

We welcome contributions! Please see our [Contributing Guide](CONTRIBUTING.md) for details.

## Security

If you discover a security vulnerability, please see our [Security Policy](.github/SECURITY.md).

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Support

- 📖 [Documentation](README.md)
- 🐛 [Report a Bug](https://github.com/yourusername/vios-libc/issues/new?template=bug_report.md)
- 💡 [Request a Feature](https://github.com/yourusername/vios-libc/issues/new?template=feature_request.md)
- 💬 [Discussions](https://github.com/yourusername/vios-libc/discussions) 