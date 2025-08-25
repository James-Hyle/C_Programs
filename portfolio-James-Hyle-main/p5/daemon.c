#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

static int fd;

/**
 * Spawns a child that uses the daemon pattern to read random numbers
 * from the system random number generator
 */
int main(void) {
    int pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid != 0) {
        //parent
        exit(EXIT_SUCCESS);
    } else {
        // child
        pid = fork();

        
        if (pid < 0) {
            perror("second fork");
            exit(EXIT_FAILURE);
        } else if (pid != 0) {
            //parent
            exit(EXIT_SUCCESS);
        } else {

            if (setsid() < 0) {
                perror("setsid");
                exit(EXIT_FAILURE);
            }

            if (chdir("/") < 0) {
                perror("chdir");
                exit(EXIT_FAILURE);
            }

            fd = open("/dev/random", O_RDONLY);
            if (fd < 0) {
                perror("open");
                exit(EXIT_FAILURE);
            }

            while(1) {
                int random_value;
                ssize_t result = read(fd, &random_value, sizeof(int));
                if (result < 0) {
                    perror("read");
                    close(fd);
                    exit(EXIT_FAILURE);
                }

                printf("\ndaemon random number was %d\n", random_value);

                sleep(10);
            }
        }
    }
}