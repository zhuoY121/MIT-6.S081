#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int
main(int argc, char *argv[]) 
{
    // Check inputs
    if (argc < 2) {
        fprintf(2, "Usage: xargs executable [options]...\n");
        exit(1);
    }

    // Init
    char arg[512];
    char *args[MAXARG];
    char buf;
    int buf_index = 0;

    for (int i = 1; i < argc; i++) {
        args[i-1] = argv[i];
    }

    args[argc-1] = arg;
    args[argc] = 0;

    while (read(0, &buf, 1) == 1) {
        if (buf == '\n') {
            arg[buf_index] = 0;

            int pid = fork();
            if (pid < 0) {
                fprintf(2, "Failed to fork...\n");
                exit(1);

            } else if (pid == 0) {
                // Child
                exec(args[0], args);
                
            } else {
                // Parent
                wait(0);
                buf_index = 0;
            }

        } else {
            arg[buf_index] = buf;
            buf_index++;
        }
    }
    
    exit(0);

}