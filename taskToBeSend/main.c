#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int main(int argc, char *argv[]) {
    threadParams_t *threadParameter = (threadParams_t *)malloc(sizeof(threadParams_t));
    if (threadParameter == NULL) {
        printf("error malloc\n");
        exit(EXIT_FAILURE);
    }

    checkthreadCount(argc, argv, threadParameter);

    signal(SIGINT, signalHandler);
    signal(SIGTSTP, signalHandler);
    signal(SIGUSR1, signalHandler);
    signal(SIGUSR2, signalHandler);
    signal(SIGQUIT, signalHandler);

    threadsCreate(threadParameter);
    waitThreads(threadParameter);

    free(threadParameter);
    pthread_cond_destroy(&g_cond);
    pthread_mutex_destroy(&g_mutex);

    return 0;
}