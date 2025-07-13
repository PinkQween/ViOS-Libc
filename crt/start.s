.section .text
.global _start
.extern c_start
.extern vios_sys_exit

_start:
    call c_start
    call vios_sys_exit
