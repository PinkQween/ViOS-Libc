# Contributing to ViOS libc

Thank you for your interest in contributing to ViOS libc! This document provides guidelines for contributing to the project.

## Getting Started

1. Fork the repository
2. Clone your fork locally
3. Create a new branch for your changes
4. Make your changes
5. Test your changes
6. Submit a pull request

## Development Setup

### Prerequisites
- GCC cross-compiler for i686-elf target
- NASM assembler
- Make

### Building
```bash
make clean
make
```

### Installing
```bash
make install
```

## Code Style

### C Code
- Use 4 spaces for indentation
- Use snake_case for function and variable names
- Use UPPER_CASE for constants and macros
- Add comments for complex logic
- Include appropriate header guards

### Assembly Code
- Use consistent indentation
- Add comments explaining complex operations
- Follow the existing naming conventions

## Commit Messages

Use clear, descriptive commit messages:
- Use the imperative mood ("Add feature" not "Added feature")
- Limit the first line to 72 characters
- Reference issues and pull requests after the first line

Example:
```
Add printf implementation with basic format support

- Implements basic string formatting for %s and %d
- Uses ViOS syscalls for output
- Fixes issue #123
```

## Pull Request Process

1. Update the README.md if needed
2. Add tests for new functionality
3. Ensure all tests pass
4. Update documentation
5. Follow the pull request template

## Testing

When adding new functionality:
- Test with different input values
- Test error conditions
- Test edge cases
- Ensure compatibility with existing code

## Reporting Issues

When reporting bugs:
- Use the bug report template
- Include steps to reproduce
- Provide environment details
- Include error messages and logs

## Feature Requests

When requesting features:
- Use the feature request template
- Explain the use case
- Consider implementation complexity
- Suggest alternatives if applicable

## License

By contributing to ViOS libc, you agree that your contributions will be licensed under the same license as the project.

## Questions?

If you have questions about contributing, please open an issue or contact the maintainers. 