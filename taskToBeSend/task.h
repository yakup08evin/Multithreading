#ifndef TASK_H
#define TASK_H

#include <pthread.h>

#define MAX_THREAD_COUNT 5

typedef struct {
    pthread_t threads[MAX_THREAD_COUNT];
    int threadNumber[MAX_THREAD_COUNT];
    int num_tasks;
} threadParams_t;

extern int activeThread;

extern pthread_mutex_t g_mutex;
extern pthread_cond_t g_cond;

void threadsCreate(threadParams_t *params);
void waitThreads(threadParams_t *params);
void *workerThread(void *x);
void signalHandler(int signal);
void checkthreadCount(int argc, char *argv[], threadParams_t *threadParameter);

#endif /* TASK_H */