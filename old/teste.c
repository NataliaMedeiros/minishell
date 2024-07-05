#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

volatile bool shouldRun = true;

void sighandler(int) {
    shouldRun = false;
}

int main(int argc, char *argv[]) {
    if (signal(SIGINT, &sighandler) == SIG_ERR) {
        fprintf(stderr, "Could not set signal handler\n");
        return EXIT_FAILURE;
    }

    printf("Program started\n");
    while (shouldRun) {
        // Do something...
    }
    printf("Program is shutting down.\n");
    return EXIT_SUCCESS;
}