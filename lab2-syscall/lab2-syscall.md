# lab2-syscall-notes

User space:

- user/user.h
- user/trace.c
- user/usys.pl => ecall => syscall(kernel)

Kernel space:

- kernel/syscall.h => Define syscall number
- kernel/sysproc.c => Implement new syscall function
- kernel/proc.h => Add traced syscall number to proc structure
- kernel/proc.c => Copy traced syscall number to child process
- kernel/syscall.c => Print traced syscall info

