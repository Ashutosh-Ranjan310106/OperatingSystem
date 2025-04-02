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
    unsigned int pid; 
    int brust_time; 
    int arival_time;  
} CPUSchedulingInfo;


typedef struct{
    unsigned int pid;
    CPUSchedulingInfo sch_info;
    ProcessState state;
    unsigned int program_counter;
} PCB;
typedef struct {
    PCB** pcb_pointer;
    int length;
} PriorityQueue;

int swap_pcb(PCB** pcb_arr,int a, int b){
    PCB* temp = pcb_arr[a];
    pcb_arr[a] = pcb_arr[b];
    pcb_arr[b] = temp;
}
PCB* create_pcb(int pid, int brust_time, int arival_time, ProcessState state){
    PCB* pcb = (PCB*)malloc(sizeof(PCB));
    pcb->pid = pid;
    pcb->sch_info.brust_time = brust_time;
    pcb->sch_info.arival_time = arival_time;
    pcb->sch_info.pid = pid;
    pcb->state = state; 
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
        if (priority_queue->pcb_pointer[parent]->sch_info.brust_time > priority_queue->pcb_pointer[index]->sch_info.brust_time){
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
        if (left < priority_queue->length && priority_queue->pcb_pointer[left]->sch_info.brust_time< priority_queue->pcb_pointer[smallest]->sch_info.brust_time)
            smallest = left;
        if (right < priority_queue->length && priority_queue->pcb_pointer[right]->sch_info.brust_time < priority_queue->pcb_pointer[smallest]->sch_info.brust_time)
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
        printf("brust time: %d, ", pcb->sch_info.brust_time);
        printf("arival time: %d, ", pcb->sch_info.arival_time);
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
            printf("brust time: %d\n", pcb->sch_info.brust_time);
            
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
            printf("\n");
        

            printf("\n--- CPU Scheduling Info ---\n");
            printf("CPU Time Used: %d ms\n", pcb->sch_info.brust_time);
            printf("Time Quantum: %d ms\n", pcb->sch_info.arival_time);
            printf("\n======================================");
        }
        printf("\n");
    }
int main(){
    srand(time(0));
    PriorityQueue* ready_queue = create_priority_queue(); 
    PCB* all_process_arr[] = {create_pcb(1, 5, 0, READY), create_pcb(2, 2, 2, READY), create_pcb(3, 1, 3, READY)};   
    /*
    PCB* all_process_arr[3];   
    for (int i=0; i<3;i++){
        PCB* pcb = create_pcb(i+1, rand() % 20 + 1, rand() % 20, READY);
        all_process_arr[i] = pcb;
    }
    */
    //bubble short
    for (int i=0; i<3; i++){
        for (int j=i; j<3; j++){
            if (all_process_arr[i]->sch_info.arival_time > all_process_arr[j]->sch_info.arival_time){
                swap_pcb(all_process_arr,i,j);    
            }
        }
    }

    for (int i=0; i<3; i++){
        print_PCB(all_process_arr[i],0);
    }
    PCB* cpu_process = NULL;
    int time=0;
    int p=0;
    while (p<2 || cpu_process){
        printf("{time:- %d} -",time);
        while (all_process_arr[p]->sch_info.arival_time == time){
            append_in_priority_queue(ready_queue, all_process_arr[p]);
            p++;
        }
        if (!cpu_process){
            deque(ready_queue, &cpu_process);
            if (cpu_process){
                printf("pid:- %d is start running\n",cpu_process->pid);
                cpu_process->state = RUNNING;
            }
        }
        else if (ready_queue->pcb_pointer && ready_queue->pcb_pointer[0]->sch_info.brust_time < cpu_process->sch_info.brust_time){
            printf("pid:- %d is blocked and moved to ready\n",cpu_process->pid);
            cpu_process->state = READY;    
            print_PCB(cpu_process,0);
            append_in_priority_queue(ready_queue, cpu_process);
            deque(ready_queue, &cpu_process);
            cpu_process->state = RUNNING;
            printf("pid:- %d is start running\n",cpu_process->pid);
        }
        else if (cpu_process->sch_info.brust_time <= 0){
            printf("pid:- %d is terminated",cpu_process->pid);
            cpu_process->state = TERMINATED;
            print_PCB(cpu_process,0);
            deque(ready_queue, &cpu_process);
            if (!cpu_process){
                continue;
            }
            printf("pid:- %d is start running\n",cpu_process->pid);
            cpu_process->state = RUNNING;
            print_PCB(cpu_process,0);
        }
        if (cpu_process){
            //print_PCB(cpu_process,0);
            cpu_process->sch_info.brust_time--;
        }

        time++;
        printf("\n");
    }
    return 0;
}