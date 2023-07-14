#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {
    if (argc > 1) {
        fprintf(2, "Usage: pingpong\n");
        exit(1);
    }

    int parentToChild[2];
    int childToParent[2];
    int n;

    // Create the pipes
    if (pipe(parentToChild) < 0 || pipe(childToParent) < 0) {
        fprintf(2, "Failed to create pipes\n");
        exit(1);
    }

    int pid = fork();
    if (pid < 0) {
        fprintf(2, "Failed to fork process\n");
    }

    if (pid == 0) {  // child
        // Close write end of the pipe
        close(parentToChild[1]);    // close write end of parent-to-child pipe
        close(childToParent[0]);    // close read end of child-to-parent pipe
        
        // Read byte from parent
        char byte;
        n = read(parentToChild[0], &byte, 1);
        if (n == 1) {
            //  the child should print "<pid>: received ping"
            // fprintf(1, "%d: (%c) received ping\n", getpid(), byte);
            fprintf(1, "%d: received ping\n", getpid());
        } else {
            fprintf(1, "n = %d\n", n);
        }
        

        // write the byte on the pipe to the parent, and exit
        byte = 'C';
        write(childToParent[1], &byte, 1);
        
        close(parentToChild[0]);
        close(childToParent[1]);
        
        exit(0);

    } else {    // parent
        // The parent should send a byte to the child

        close(parentToChild[0]);    // close read end of parent-to-child pipe
        close(childToParent[1]);    // close write end of child-to-parent pipe
        
        char byte = 'P';
        write(parentToChild[1], &byte, 1);
        
        // the parent should read the byte from the child, print "<pid>: received pong", and exit.
        wait(0);

        n = read(childToParent[0], &byte, 1);
        if (n == 1) {
            // fprintf(1, "%d: (%c) received pong\n", getpid(), byte);
            fprintf(1, "%d: received pong\n", getpid());
        } else {
            fprintf(1, "n = %d\n", n);
        }
        
        close(parentToChild[1]);
        close(childToParent[0]);

        exit(0);
    }
}