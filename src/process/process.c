#include "process.h"


void Process__process_init()
{
    ready_queue = List__createList();
    blocked_queue = List__createList();
    all_processes = List__createList();
}

void* Process__processCreateThread(void *arg)
{
    while(1){
        
        pthread_mutex_lock(&dispatcherMutex);

        while(!processCreateFlag)
            pthread_cond_wait(&cond_processCreate, &dispatcherMutex);
        
        processCreateFlag = 0;
        pthread_mutex_unlock(&dispatcherMutex);

        //Process__processCreate();
    }
}

void Process__processCreate(char *name)
{
    static int pid_counter = 0;

    printf("[ProcessCreate] Criando processo com PID %d\n", pid_counter++);
}





