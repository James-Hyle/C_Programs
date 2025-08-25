#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * Spawns a child that lives after the parent exits successfully
 */
int main(void) {
    int pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // child
        while (1) {
            sleep(60);
        }
    } else {
        //parent
        exit(EXIT_SUCCESS);
    }
}