#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int initialized_global = 42;         // .data
int uninitialized_global;            // .bss

void sample_function() {
    // Dummy function just to get its address
}

void print_addresses(int param) {
    static int static_local = 10;    // .data
    int local_var = 20;              // stack
    int *heap_var = malloc(sizeof(int));  // heap
    *heap_var = 99;

    printf("Function address:                 %p\n", (void *)sample_function);
    printf("Initialized global variable:      %p\n", (void *)&initialized_global);
    printf("Uninitialized global variable:    %p\n", (void *)&uninitialized_global);
    printf("Function parameter address:       %p\n", (void *)&param);
    printf("Static local variable address:    %p\n", (void *)&static_local);
    printf("Dynamically allocated address:    %p\n", (void *)heap_var);

    // Infinite loop to allow checking memory map
    while (1) {
        sleep(1);
    }
}

int main() {
    print_addresses(100);
    return 0;
}
