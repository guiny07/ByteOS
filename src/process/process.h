#ifndef PROCESS_H
#define PROCESS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "../kernel/kernel.h"
#include "../utils/list.h"
#include "../utils/utils.h"
#include "../semaphore/semaph.h"


extern List* ready_queue;
extern List* blocked_queue;
extern List* all_processes;


typedef enum {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
} ProcessState;

// For the operations performed by the synthetic program. 
typedef enum {
    EXEC,
    READ,
    WRITE,
    SEM_P,
    SEM_V,
    PRINT
} Operation;

// For a single instruction from the synthetic program. 
typedef struct {
    Operation operation;
    int value;
    char sem; //Semaphores added.
    int remaining_time; // In case the instruction is not completely read. 
    bool loaded; // Flag to know if the instructions is completely loaded in to page table.   
} Instruction;

typedef struct ProcessControlBlock
{
    char *name;
    int pid;
    int priority;
    ProcessState state;
    int segment_size;
    int segment_id;
    int rw_count;

    Node *current_page;
    Node *current_instruction;

    List *instructions;

} PCB;

void Process__process_init();
void* Process__processCreateThread(void *arg);
void Process__processCreate(char *name);

#endif