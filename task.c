#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define THREAD_COUNT      2

typedef struct{
    pthread_t threads[THREAD_COUNT];
    int threadNumber[THREAD_COUNT];

}threadParams_t;

int activeThread;


pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  g_cond  = PTHREAD_COND_INITIALIZER;

void threadsCreate(threadParams_t *params);
void waitThreads(threadParams_t *params);
void *workerThread(void *x);
void signalHandler(int signal);

int main(){

    threadParams_t * threadParameter = (threadParams_t *)malloc(sizeof(threadParams_t));

    signal(SIGINT,signalHandler);
    signal(SIGTSTP,signalHandler);

    threadsCreate(threadParameter);
    waitThreads(threadParameter);
    
    free(threadParameter);
    pthread_cond_destroy(&g_cond);
    pthread_mutex_destroy(&g_mutex);


}

void threadsCreate(threadParams_t *params){
    for(int i=0 ;i<THREAD_COUNT ;i++){
        params->threadNumber[i] = i+1;
        if(pthread_create(&params->threads[i],NULL,workerThread,&params->threadNumber[i]) != 0){
            printf("thread create error\r\n");
        }
    }
}

void waitThreads(threadParams_t *params){
    for(int i=0 ;i<THREAD_COUNT ;i++){
        if(pthread_join(params->threads[i],NULL) != 0){
            printf("thread join error\r\n");
        }
    }
}

void *workerThread(void *x){
    while (1)
    {
        if((*(int *)x) == 1){
            pthread_mutex_lock(&g_mutex);
            while(activeThread != 1){
                pthread_cond_wait(&g_cond,&g_mutex);
            }
            pthread_mutex_unlock(&g_mutex);
            printf("thread %d is active\r\n",(*(int *)x));
        }
        else if((*(int *)x) == 2){
            pthread_mutex_lock(&g_mutex);
            while(activeThread != 2){
                pthread_cond_wait(&g_cond,&g_mutex);
            }
            pthread_mutex_unlock(&g_mutex);
            printf("thread %d is active\r\n",(*(int *)x));
        }

    }
    
}

void signalHandler(int signal) {
    pthread_mutex_lock(&g_mutex);
    pthread_cond_broadcast(&g_cond);
    if (signal == SIGINT) {
        activeThread = 1;
    } else if (signal == SIGTSTP) {
        activeThread = 2;
    }
    pthread_mutex_unlock(&g_mutex);
}

