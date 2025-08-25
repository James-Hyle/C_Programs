#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * Spawns a child that is never waited for by the parent.
 * The child is never reaped, therefore leaving it a zombie
 */
int main(void) {
    int pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // child

        exit(EXIT_SUCCESS);
    } else {
        //parent
        while (1) {
            sleep(60);
        }
    }
}
