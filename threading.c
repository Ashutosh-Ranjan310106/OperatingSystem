#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void* threadd_function(void *arg){
    printf("thread number %ld\n", (long)arg);
    return arg;
}

int main(void){
    pthread_t thread[5];
    for (long i=0; i<5; i++){
        pthread_create(&threads[i], NULL, thread_function, (void*)i);
    }
    for (int i=0; i<5; i++){
        pthread_join(threads[i], NULL);
    }
    return 0;  
}