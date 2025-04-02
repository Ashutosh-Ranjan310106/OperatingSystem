#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define debug 1

typedef enum {   
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
} ProcessState;

typedef struct {
    int priority;      
    int cpu_time_used; 
    int time_quantum;  
    int last_execution;
} CPUSchedulingInfo;

typedef struct {
    unsigned int base_register;  // Starting address of the process in memory
    unsigned int limit_register; // End address (Memory boundary)

    void *heap_pointer; // Points to dynamic memory allocation (malloc/free)
    void *stack_pointer;// Points to stack top (for function calls)
} MemoryManagement;

typedef struct {
    int pid;                 // Process ID
    int uid;                 // User ID of process owner
    time_t start_time;       // Process start time
    double cpu_time_used;    // Total CPU time used by the process
    double execution_time;   // Estimated total execution time
    int memory_used;         // Memory usage in KB
    int io_operations;       // Number of I/O operations performed
    int exit_status;         // Exit code (0 = success, non-zero = error)
} AccountingBlock;

typedef struct {
    int parent_pid;
    int child_pids[5];  
} ParentChildInfo;

typedef struct{
    int pid;
    CPUSchedulingInfo sch_info;
    ProcessState state;
    unsigned int program_counter;
    int cpu_registers[8];
    MemoryManagement memory_block;
    AccountingBlock acc_block;
    ParentChildInfo parent_child_info;
} PCB;
typedef struct 
{
    PCB** pcb_pointer;
    int length;
} PriorityQueue;

int swap_pcb(PCB** pcb_arr,int a, int b){
    PCB* temp = pcb_arr[a];
    pcb_arr[a] = pcb_arr[b];
    pcb_arr[b] = temp;
}
PCB* create_pcb(){
    PCB* pcb = (PCB*)malloc(sizeof(PCB));
    return pcb;
}
PriorityQueue* create_priority_queue(){
    PriorityQueue* priority_queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    priority_queue->pcb_pointer = NULL;
    priority_queue->length = 0;
    return priority_queue;
}
PriorityQueue* append_in_priority_queue(PriorityQueue* priority_queue, PCB* pcb){

    priority_queue->length += 1;
    PCB** temp = realloc(priority_queue->pcb_pointer, (priority_queue->length) * sizeof(PCB*));
    if (temp == NULL) {
        printf("Memory allocation failed! during appending\n");
        priority_queue->length--; 
        return priority_queue; 
    }
    priority_queue->pcb_pointer = temp;
    priority_queue->pcb_pointer[priority_queue->length - 1] = pcb;
    int index = priority_queue->length - 1;

    while (index > 0){
        int parent = (index - 1) / 2; 
        if (priority_queue->pcb_pointer[parent]->sch_info.priority > priority_queue->pcb_pointer[index]->sch_info.priority){
            swap_pcb(priority_queue->pcb_pointer,parent,index);
            index = parent;
        }else{
            break;
        }
    }

    return priority_queue;
}

PriorityQueue* deque(PriorityQueue* priority_queue,PCB** pcb){
    int index = 0;
    if (priority_queue->length == 0){
        *pcb = NULL;
        return priority_queue;
    }


    *pcb = priority_queue->pcb_pointer[index];
    printf("deque %d\n",priority_queue->length);
    priority_queue->length--;
    if (priority_queue->length == 0){
        priority_queue->pcb_pointer = NULL;
        return priority_queue;
    }
    swap_pcb(priority_queue->pcb_pointer,index,priority_queue->length);

    
    PCB** temp = realloc(priority_queue->pcb_pointer, (priority_queue->length) * sizeof(PCB*));
    if (temp == NULL) {
        printf("Memory allocation failed! during deque %d\n",priority_queue->length);
        swap_pcb(priority_queue->pcb_pointer,index,priority_queue->length);
        *pcb = NULL;
        return priority_queue; 
    }
    priority_queue->pcb_pointer = temp;

    


    while (1){
        int left = index*2 +1; 
        int right = index*2 +2; 
        int smallest = index;
        if (left < priority_queue->length && priority_queue->pcb_pointer[left]->sch_info.priority < priority_queue->pcb_pointer[smallest]->sch_info.priority)
            smallest = left;
        if (right < priority_queue->length && priority_queue->pcb_pointer[right]->sch_info.priority < priority_queue->pcb_pointer[smallest]->sch_info.priority)
            smallest = right;
        if (smallest != index) {
            swap_pcb(priority_queue->pcb_pointer, index, smallest);
            index = smallest;
        }else{
            break;
        }
    }
    return priority_queue;
}
void print_PCB(PCB* pcb, int full) {
    if (! pcb){
        return ;
    }
    if  (full != 1){
        printf("{PID: %d, ", pcb->pid);
        printf("Priority: %d, ", pcb->sch_info.priority);
        
        // Process State
        printf("State: ");
        switch (pcb->state) {
            case NEW:        printf("NEW"); break;
            case READY:      printf("READY"); break;
            case RUNNING:    printf("RUNNING"); break;
            case WAITING:    printf("WAITING"); break;
            case TERMINATED: printf("TERMINATED"); break;
        }
        printf(" }");
    }
    if (full){
            printf("\n===== Process Control Block (PCB) =====\n");
            printf("PID: %d\n", pcb->pid);
            printf("Priority: %d\n", pcb->sch_info.priority);
            
            // Process State
            printf("State: ");
            switch (pcb->state) {
                case NEW:        printf("NEW\n"); break;
                case READY:      printf("READY\n"); break;
                case RUNNING:    printf("RUNNING\n"); break;
                case WAITING:    printf("WAITING\n"); break;
                case TERMINATED: printf("TERMINATED\n"); break;
            }
        
            printf("Program Counter: 0x%X\n", pcb->program_counter);

            printf("CPU Registers: ");
            for (int i = 0; i < 8; i++) {
                printf("R%d=0x%X ", i, pcb->cpu_registers[i]);
            }
            printf("\n");
        

            printf("\n--- Memory Management ---\n");
            printf("Base Register: 0x%X\n", pcb->memory_block.base_register);
            printf("Limit Register: 0x%X\n", pcb->memory_block.limit_register);
            printf("Heap Pointer: %p\n", pcb->memory_block.heap_pointer);
            printf("Stack Pointer: %p\n", pcb->memory_block.stack_pointer);
        

            printf("\n--- CPU Scheduling Info ---\n");
            printf("CPU Time Used: %d ms\n", pcb->sch_info.cpu_time_used);
            printf("Time Quantum: %d ms\n", pcb->sch_info.time_quantum);
            printf("Last Execution: %d ms\n", pcb->sch_info.last_execution);
        

            printf("\n--- Accounting Information ---\n");
            printf("User ID: %d\n", pcb->acc_block.uid);
            printf("Start Time: %s", ctime(&pcb->acc_block.start_time)); // Convert timestamp to readable format
            printf("CPU Time Used: %.2f sec\n", pcb->acc_block.cpu_time_used);
            printf("Execution Time: %.2f sec\n", pcb->acc_block.execution_time);
            printf("Memory Used: %d KB\n", pcb->acc_block.memory_used);
            printf("I/O Operations: %d\n", pcb->acc_block.io_operations);
            printf("Exit Status: %d\n", pcb->acc_block.exit_status);
        
            printf("\n--- Parent-Child Process Info ---\n");
            printf("Parent PID: %d\n", pcb->parent_child_info.parent_pid);
            printf("Child PIDs: ");
            for (int i = 0; i < 5; i++) {
                if (pcb->parent_child_info.child_pids[i] != 0) {
                    printf("%d ", pcb->parent_child_info.child_pids[i]);
                }
            }
            printf("\n======================================");
        }
        printf("\n");
    }
int main(){
    PriorityQueue* ready_queue = create_priority_queue();    
    for (int i=0; i<10;i++){
        PCB* pcb = create_pcb();
        pcb->pid = i;
        pcb->sch_info.priority = rand() % 100 + 1;
        pcb->state = READY;//(ProcessState)i%5; 

        ready_queue = append_in_priority_queue(ready_queue, pcb);
    }
    PriorityQueue* wating_queue = create_priority_queue();
    PCB* cpu_process;
    int exit=1;
    PCB* wating_process;
    while (exit){
        deque(ready_queue, &cpu_process);
        int ch=4;
        if (cpu_process){
            cpu_process->state = RUNNING;
            printf("current process \n");
            print_PCB(cpu_process,0);
            printf("\n\nchoose from these operation to perform on running process \nmove process to block/wating - 1 \nmove process to ready - 2 \nterminate process - 3 \nto quit - 0\n");
            scanf("%d",&ch);
        }
        switch (ch){
            case 0:
                exit = 0;
                break;
            case 1:
                printf("pid:%d is blocked/wating",cpu_process->pid);
                cpu_process->state = WAITING;
                append_in_priority_queue(wating_queue, cpu_process);
                break;
            case 2:
                printf("pid:%d is moved to ready",cpu_process->pid);
                cpu_process->state = READY;
                ready_queue = append_in_priority_queue(ready_queue, cpu_process);
                break;
            case 3:
                printf("pid:%d is terminated",cpu_process->pid);
                cpu_process->state = TERMINATED;
                free(cpu_process);
                break;
            case 4:
                printf("no running process");
                break;
        }

        printf("\n");

        printf("\n\nmanage wating queue");
        if (wating_queue->length){
            printf("choose from these operation to perform on wating queue \nmove process to running queue - 1 \ndo noting - 2 \n");
            scanf("%d",&ch);
        }else{
            ch = 2;
        }
        switch (ch){
            case 1:
                deque(wating_queue ,&wating_process);
                printf("pid:%d moved from wating queu to ready queue",wating_process->pid);
                wating_process->state = READY;
                append_in_priority_queue(ready_queue, wating_process);
                break;
        }
        printf("\n");


        printf("ready queue \n");
        for (int i=0;i<ready_queue->length;i++){
            print_PCB(ready_queue->pcb_pointer[i],0);
        }

        printf("wating queue \n");
        for (int i=0;i<wating_queue->length;i++){
            print_PCB(wating_queue->pcb_pointer[i],0);
        }
        printf("=================== next quantum =====================\n");
    }
    printf("good bye");
    return 0;
}