#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int g_x;
int res;

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void *workerThread2(void *x);

void *workerThread1(void *x){

    for(int i=0;i<10000;i++){
        if(res = pthread_mutex_lock(&g_mutex)!=0){
            printf("pthread_mutex_lock error:%d\n",res);
            exit(EXIT_FAILURE);
        }
        g_x++;
        
        if(res = pthread_mutex_unlock(&g_mutex)!=0){
            printf("pthread_mutex_lock error:%d\n",res);
            exit(EXIT_FAILURE);
        }
    }
    return NULL;

}
void *workerThread2(void *x){

    for(int i=0;i<10000;i++){
        if(res = pthread_mutex_lock(&g_mutex)!=0){
            printf("pthread_mutex_lock error:%d\n",res);
            exit(EXIT_FAILURE);
        }
        g_x++;
        if(res = pthread_mutex_unlock(&g_mutex)!=0){
            printf("pthread_mutex_lock error:%d\n",res);
            exit(EXIT_FAILURE);
        }

    }
    return NULL;

}

int main(){

    pthread_t tid1,tid2;

    //res = pthread_mutex_init(&g_mutex,NULL);
    //if(res){
    //    printf("pthread_mutex_init error:%d\n",res);
    //    exit(EXIT_FAILURE);
    //}


    res = pthread_create(&tid1,NULL,workerThread1,NULL);
    if(res){
        printf("pthread_create1 error:%d\n",res);
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&tid2,NULL,workerThread2,NULL);
    if(res){
        printf("pthread_create2 error:%d\n",res);
        exit(EXIT_FAILURE);
    }
    res = pthread_join(tid1,NULL);
    if(res){
        printf("prthread_join error:%d\n",res);
        exit(EXIT_FAILURE);
    }
    res = pthread_join(tid2,NULL);
    if(res){
        printf("prthread_join error:%d\n",res);
        exit(EXIT_FAILURE);
    }

    printf("2 g_x = %d\n",g_x);



}