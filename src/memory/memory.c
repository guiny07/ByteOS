#include "memory.h"



void* Memory__memLoadReqThread(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&dispatcherMutex);

        while(!memLoadReqFlag)
            pthread_cond_wait(&cond_memLoadReq, &dispatcherMutex);
        
        memLoadReqFlag = 0;

        pthread_mutex_unlock(&dispatcherMutex);

        Memory__memLoadReq();
    }
}


void Memory__memLoadReq()
{
    pthread_mutex_lock(&mutex_loading_process);
    PCB *process = loading_process;
    loading_process = NULL;
    pthread_mutex_unlock(&mutex_loading_process);

    
}


void* Memory__memLoadFinishThread()
{
    while(1)
    {   
        pthread_mutex_lock(&dispatcherMutex);

        while(!memLoadFinishFlag)
            pthread_cond_wait(&cond_memLoadFinish, &dispatcherMutex);
        
        memLoadFinishFlag = 0;

        pthread_mutex_unlock(&dispatcherMutex);

        Memory__memLoadFinish();
    }
}


void Memory__memLoadFinish()
{

}