#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_var = 42; // Global variable (data segment)
int uninitialized_var; // Uninitialized global variable (bss)


int visualize_memory() {

    // Text segment
    printf("Text Segment (Code):  %p\n", (void*)visualize_memory);

    // Data segment
    printf("Initialized Data:     %p\n", (void*)&global_var);

    // BSS (uninitialized data)
    printf("Uninitialized Data:   %p\n", (void*)&uninitialized_var);

    // Heap
    void *heap_var = malloc(1);
    printf("Heap:                 %p\n", heap_var);
    free(heap_var);

    // Stack
    int stack_var = 0;
    printf("Stack:                %p\n", (void*)&stack_var);

    printf("\nUse `/proc/%d/maps` to see the full memory map.\n", getpid());

    return 0;
}


int main(int argc, char *argv[]) {
    
    printf("Memory layout visualization:\n");

	// High Memory segment
    printf("High Mem Segment (in Stack):     %p\n", (void*)&argc);	
	
	visualize_memory();
    	
	while (1); // Keep the process alive for inspection
    return 0;
}