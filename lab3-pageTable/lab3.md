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

