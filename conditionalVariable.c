#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SIZE_ARRAY      20

void display_array(const int *pa,size_t size);
void bubble_sort(int *pa,size_t size);
void random_array(int *pa,size_t size);
void randoms();

int a[SIZE_ARRAY];

pthread_mutex_t sort_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t sort_cond = PTHREAD_COND_INITIALIZER;

int sortFLag = 0;


void *workerThread1(void *x){
    printf("worker thread is running\r\n");
    randoms();
    random_array(a,SIZE_ARRAY);
    pthread_mutex_lock(&sort_mutex);
    while(sortFLag == 0){

        printf("not sorting is waiting .. \r\n");
        pthread_cond_wait(&sort_cond,&sort_mutex);

    }
    pthread_mutex_unlock(&sort_mutex);
    printf("sort is okey\r\n");
    display_array(a,SIZE_ARRAY);

    return NULL;
}
void *sortThread(void *x){
    printf("sort thread is running\r\n");

    bubble_sort(a,SIZE_ARRAY);
    pthread_mutex_lock(&sort_mutex);
    sortFLag = 1;
    pthread_mutex_unlock(&sort_mutex);
    pthread_cond_signal(&sort_cond);

    printf("sort thread is okey\r\n");

    return NULL;
}


int main(){

    pthread_t threads[2];

    for(int i=0 ;i<2;i++){
        if(i == 0){
            if(pthread_create(&threads[i],NULL,workerThread1,NULL) != 0){
                printf("thread create error \r\n");
            }
        }
        else{
            if(pthread_create(&threads[i],NULL,sortThread,NULL) != 0){
                printf("thread create error \r\n");
            }
        }
        
    }
    for(int i=0;i<2;i++){
        if(pthread_join(threads[i],NULL) != 0){
            printf("thread join error\r\n");
        }
    }
    pthread_cond_destroy(&sort_cond);
    pthread_mutex_destroy(&sort_mutex);

    return 0;

}

void display_array(const int *pa,size_t size){

    for(int i=0;i<size;i++){
        printf("%d ",pa[i]);
    }
    printf("\r\n");

}
void bubble_sort(int *pa,size_t size){

    for(int i=0;i<size-1;i++){
        for(int j=0;j<size-1-i;j++){
            if(pa[j] > pa[j+1]){
                int temp = pa[j];
                pa[j] = pa[j+1];
                pa[j+1] = temp;
            }
        }
    }

}
void random_array(int *pa,size_t size){

    for(int i=0;i<size;i++){
        pa[i] = rand() % 100;
    }

}
void randoms(){

    time_t tmr;
    srand((unsigned int)(time(&tmr)));

}

