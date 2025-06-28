#ifndef PROCESS_H
#define PROCESS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "kernel.h"
#include "list.h"
#include "utils.h"
#include "semaph.h"
#include "memory.h"

extern List* ready_queue;
extern List* blocked_queue;
extern List* all_processes;

extern PCB* loading_process;

extern pthread_mutex_t mutex_ready_queue;
extern pthread_mutex_t mutex_blocked_queue;
extern pthread_mutex_t mutex_all_processes;

extern pthread_mutex_t mutex_loading_process;

//typedef struct PageTable PageTable;

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

    PageTable *page_table;
} PCB;

// To initialize the global structures.
void Process__process_init();
// Function to wake up the ProcessCreate thread based on the value of its flag.
void* Process__processCreateThread(void *arg);
// Reads a program from the synthetic programs directory and turns it in to a process in the simulator.
void Process__processCreate(char *name);
// Function to wake up the ProcessFinish thread based on the value of its flag. 
void* Process__processFinishThread();
// Process to end a process.
void Process__processFinish();

// Utilitary functions.
List* Process__read_instructions(FILE *fp);
Instruction* Process__instruction_parser(char *buffer);

void print_list(List *list); //REMOVER ISSO!

#endif