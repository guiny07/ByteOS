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


typedef struct Process{
    
}