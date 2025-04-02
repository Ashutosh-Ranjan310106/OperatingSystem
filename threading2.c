void recurcive_function(int count){
    int local_var = count;
    if (count>0){
        printf("thread stack level %d address of variable:%p\n", count, &local_var);
        recurcive_function(count-1);
    }
}

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* thread_function(void *arg){
    int local = 0;
    printf("Starting thread, unique stack fram: %p\n", &local);
    recurcive_function(3);
    return NULL;
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
