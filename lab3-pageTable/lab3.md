# Lab 3 - Page Tables

## Speed up system calls

- Add ```struct usyscall *usyscall;``` to ```proc.h```
- In ```allocproc()```, allocate and initialize the page
- In ```proc_pagetable()```, perform the mapping
- In ```freeproc()```, free the proc resources
  - In ```proc_freepagetable()```, free the page table

## vmprint

Idea from the function ```freewalk()``` in ```vm.c```

## Detecting which pages have been accessed

- In ```sys_pgaccess()```
  - Parse arguments: ```va```, ```n``` and ```mask_addr```
  - Define a varaible ```abits``` to store the access bits
  - Define ```PTE_A```, the access bit, in ```kernel/riscv.h```. Consult the RISC-V manual to determine its value (Page 31 of riscv-book).
  - Find PTE using ```walk()``` function in ```vm.c```
    - set the access bit
    - clear PTE_A
  - Write ```abits``` to user space (```mask_addr```) using ```copyout()``` function.
