#include "stdlib.h"

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
    int operation;
    int value;
    char sem; //Semaphores added.
    int remaining_time; // In case the instruction is not completely read. 
    bool loaded; // Flag to know if the instructions is completely loaded in to page table.   
} Instruction;

typedef struct Process{
    
} Process;