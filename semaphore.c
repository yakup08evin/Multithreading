#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define THREAD_NUMBER       10

sem_t example_sem; 

void *workerThread(void *x){
    
    sem_wait(&example_sem);
    sleep(1);
    printf("for thread %d\r\n",*(int*)x);
    sleep(4);
    sem_post(&example_sem);
    free(x);
    printf("********************************\r\n");

}

int main(){

    pthread_t THREADS[THREAD_NUMBER];

    if(sem_init(&example_sem,0,THREAD_NUMBER) != 0){
        printf("semaphore init error\r\n");
    }


    for(int i=0 ;i<THREAD_NUMBER ;i++){
        int *ptr = (int*)malloc(sizeof(int));
        *ptr = i;
        if(pthread_create(&THREADS[i],NULL,workerThread,ptr)  != 0){
            printf("thread create error\r\n");
        }
    }

    for(int i=0; i<THREAD_NUMBER; i++){
        if(pthread_join(THREADS[i],NULL) != 0){
            printf("thread join error\r\n");
        }
    }


}