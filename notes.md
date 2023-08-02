# Notes

## gdb

CMDs:

- Text user interface for debugging
  - Open TUI
    - tui enable
  - Open layout
    - layout <layout_name>
      - layout asm
      - layout reg
  - Switch between layouts
    - focus <layout_name>
      - focus asm

- Breakpoints
  - Set breakpoints
    - b <func_name>
  - Check breakpoints
    - info breakpoints
  - Delete breakpoints
    - delete

- Continue
  - c
- Step instructions
  - si
