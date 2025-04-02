#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>



void* thread_function(void *arg){
    global_variable++;
    printf("global varible updated to %d by thread %ld\n", global_variable, (long)arg);
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




gcc -pthread -o thread_example_3 threading3.count

docs.kernal.org/userspace-api/netlink/intro.html

github.com/mwarnig/netlink-examples (why and to use )