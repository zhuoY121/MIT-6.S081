# lab2-syscall-notes

## syscall - trace

User space:

- ```user/user.h```
- ```user/trace.c```
- ```user/usys.pl``` => ecall => syscall(kernel)

Kernel space:

- ```kernel/syscall.h``` => Define syscall number
- ```kernel/syscall.c``` =>
  - Add new syscall function
  - Print traced syscall info
- ```kernel/sysproc.c``` => Implement new syscall function
- ```kernel/proc.h``` => Add traced syscall number to proc structure
- ```kernel/proc.c``` => Copy traced syscall number to child process

## syscall - sysinfo

User space:

- ```user/user.h```
- ```user/sysinfotest.c```
- ```user/usys.pl```

Kernel space:

- ```kernel/syscall.h``` => Define syscall number
- ```kernel/syscall.c``` => Add new syscall function
- ```kernel/sysproc.c``` => Implement new syscall function ```sys_sysinfo()```
  - ```kernel/kalloc.c``` => Implement new function ```get_freemem()```
  - ```kernel/proc.c``` => Implement new function ```get_nproc()```
  - Add function declaration into ```defs.h```
