#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t g_cond = PTHREAD_COND_INITIALIZER;

int activeThread;

void checkthreadCount(int argc, char *argv[],threadParams_t * threadParameter){
    if(argc != 2){
        printf("Usage: %s <num_tasks>\r\n",argv[0]);
        free(threadParameter);
        exit(EXIT_FAILURE);
    }
    threadParameter->num_tasks = atoi(argv[1]);
    if (threadParameter->num_tasks <= 1 || threadParameter->num_tasks > 5) {
        printf("Invalid number of tasks. Please enter a value between 1 and 5.\n");
        free(threadParameter);
        exit(EXIT_FAILURE);
    }

}

void threadsCreate(threadParams_t *params){
    for(int i=0 ;i<params->num_tasks ;i++){
        params->threadNumber[i] = i+1;
        if(pthread_create(&params->threads[i],NULL,workerThread,&params->threadNumber[i]) != 0){
            printf("thread create error\r\n");
            exit(EXIT_FAILURE);
        }
    }
}

void waitThreads(threadParams_t *params){
    for(int i=0 ;i<params->num_tasks ;i++){
        if(pthread_join(params->threads[i],NULL) != 0){
            printf("thread join error\r\n");
            exit(EXIT_FAILURE);
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
        else if((*(int *)x) == 3){
            pthread_mutex_lock(&g_mutex);
            while(activeThread != 3){
                pthread_cond_wait(&g_cond,&g_mutex);
            }
            pthread_mutex_unlock(&g_mutex);
            printf("thread %d is active\r\n",(*(int *)x));
        }
        else if((*(int *)x) == 4){
            pthread_mutex_lock(&g_mutex);
            while(activeThread != 4){
                pthread_cond_wait(&g_cond,&g_mutex);
            }
            pthread_mutex_unlock(&g_mutex);
            printf("thread %d is active\r\n",(*(int *)x));
        }
        else if((*(int *)x) == 5){
            pthread_mutex_lock(&g_mutex);
            while(activeThread != 5){
                pthread_cond_wait(&g_cond,&g_mutex);
            }
            pthread_mutex_unlock(&g_mutex);
            printf("thread %d is active\r\n",(*(int *)x));
        }

    }
    
}

void signalHandler(int signal) {
   switch (signal) {
        case SIGINT:
            activeThread = 1;
            break;
        case SIGTSTP:
            activeThread = 2;
            break;
        case SIGUSR1:
            activeThread = 3;
            break;
        case SIGUSR2:
            activeThread = 4;
            break;
        case SIGQUIT:
            activeThread = 5;
            break;
        default:
            break;
    }
    pthread_cond_broadcast(&g_cond);
}