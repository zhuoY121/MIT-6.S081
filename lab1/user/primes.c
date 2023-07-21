#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
sievePrime(int left[]) {
    
    close(left[1]); // It is ecessary to close write side of the left pipe

    int right[2];
    int prime, num;

    // No more numbers from left pipe, then exit
    if (read(left[0], &prime, sizeof(int)) == 0) {
        close(left[0]);
        exit(0);
    }

    // Print out the prime numbers
    printf("prime %d\n", prime);

    // Create right pipe
    if (pipe(right) < 0) {
        fprintf(2, "Failed to create pipe\n");
        exit(1);
    }

    int pid = fork();
    if (pid < 0) {
        fprintf(2, "Failed to fork process\n");
        exit(1);

    } else if (pid == 0) {
        // child
        sievePrime(right);

        exit(0);

    } else {
        // parent
        close(right[0]);

        // Put remaining numbers in the left pipe into the right pipe
        while (read(left[0], &num, sizeof(int))) {
            if (num % prime != 0) {
                write(right[1], &num, sizeof(int));
            }
        }

        close(right[1]);

        wait(0);

        exit(0);
    }
}

int 
main(int argc, char *argv[]) {
    // Check inputs
    if (argc > 1) {
        fprintf(2, "Usage: primes\n");
        exit(1);
    }

    // Initialize variables
    int MAX_NUM = 35;
    int left[2];

    // create pipes and processes
    if (pipe(left) < 0) {
        fprintf(2, "Failed to create pipe\n");
        exit(1);
    }

    int pid = fork();
    
    if (pid < 0) {
        fprintf(2, "Failed to fork process\n");
        exit(1);

    } else if (pid == 0) {
        // child
        sievePrime(left);

        exit(0);

    } else {
        // parent
        close(left[0]);

        for (int i = 2; i <= MAX_NUM; i++) {
            write(left[1], &i, sizeof(int));
        }

        close(left[1]);

        wait(0);

        exit(0);
    }

    // printf("Finish sieving primes.\n");
    exit(0);

}
