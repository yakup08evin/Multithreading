#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct Data{
    char str1[30];
    char str2[30];
}Data_t;

//Data_t myData = {"thread1","thread2"};

void *workerThread1(void *x){
    pthread_t tid = pthread_self();
    printf("Worker thread id : %lu\n",(unsigned long)tid);
    Data_t *param = (Data_t *)x;
    for(int i=0;i<5;++i){
        printf("%s = %d\n",param->str1,i);
        sleep(1);
    }
    return NULL;
}
void *workerThread2(void *x){
    pthread_t tid = pthread_self();
    printf("Worker thread id : %lu\n",(unsigned long)tid);
    Data_t *param = (Data_t *)x;
    for(int i=0;i<5;++i){
        printf("%s = %d\n",param->str2,i);
        sleep(1);
    }
    return NULL;
}

int main(){

    Data_t * myData = (Data_t *)malloc(sizeof(Data_t));
    if(myData == NULL){
        printf("error malloc \r\n");
        exit(EXIT_FAILURE);
    }
    strcpy(myData->str1,"THREAD 1");
    strcpy(myData->str2,"THREAD 2");

    pthread_t tid1,tid2,main;
    int res;
    res = pthread_create(&tid1,NULL,workerThread1,myData);

    if(res){
        printf("pthread didn't created = %d",res);
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&tid2,NULL,workerThread2,myData);

    if(res){
        printf("pthread didn't created = %d",res);
        exit(EXIT_FAILURE);
    }

    main = pthread_self();
    printf("main thread id = %lu\n",(unsigned long)main);

    for(int i=0;i<3;++i){
        printf("Main thread = %d\n",i);
        sleep(1);
    }

    return 0;
}