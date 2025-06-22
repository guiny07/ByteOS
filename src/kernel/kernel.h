#ifndef KERNEL_H
#define KERNEL_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


extern int processCreateFlag;
extern int diskRequestFlag;
extern int memLoadReqFlag;

extern pthread_mutex_t dispatcherMutex;
extern pthread_cond_t cond_processCreate;
extern pthread_cond_t cond_diskRequest;
extern pthread_cond_t cond_memLoadReq;

// Código para cada evento tratado pelo núcleo. 
typedef enum {
    PROCESS_INTERRUPT = 1,
    PROCESS_CREATE = 2,
    PROCESS_FINISH = 3,
    DISK_REQUEST = 4,
    DISK_FINISH = 5,
    MEM_LOAD_REQ = 6,
    MEM_LOAD_FINISH = 7,
    SEMAPHORE_P = 10,
    SEMAPHORE_V = 11,
    PRINT_REQUEST = 14,
    PRINT_FINISH = 15
} Event;

void Kernel__init_kernel(); // Caso for ter uma struct para o kernel. 

// Tratamento dos eventos. 
void Kernel__dispatch(Event code);
// Chamadas do sistema. 
int Kernel__syscall();
// Tratamento de interrupções. 
int Kernel__interruptControl();



#endif