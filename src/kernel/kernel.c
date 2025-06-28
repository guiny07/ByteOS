#include "../../include/kernel.h"

// Global flags for each thread.
int processCreateFlag = 0;
int diskRequestFlag = 0;
int memLoadReqFlag = 0;
int memLoadFinishFlag = 0;
int processFinishFlag = 0;

// Global threads for each of the requested functions.
pthread_mutex_t dispatcherMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_processCreate = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_diskRequest = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_memLoadReq = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_memLoadFinish = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_processFinish = PTHREAD_COND_INITIALIZER;

int Kernel__syscall()
{
    return PROCESS_CREATE;
}

int Kernel__interruptControl()
{
    return DISK_FINISH;
}

void Kernel__dispatch(Event code)
{
    pthread_mutex_lock(&dispatcherMutex);

    switch(code)
    {
        case PROCESS_CREATE:
            processCreateFlag = 1;
            pthread_cond_signal(&cond_processCreate);
            break;
        case DISK_REQUEST:
            diskRequestFlag = 1;
            pthread_cond_signal(&cond_diskRequest);
            break;
        case PROCESS_INTERRUPT:
            break;
        case MEM_LOAD_REQ:
            memLoadReqFlag = 1;
            pthread_cond_signal(&cond_memLoadReq);
            break;
        case PROCESS_FINISH:
            break;
        case MEM_LOAD_FINISH:
            memLoadFinishFlag = 1;
            pthread_cond_signal(&cond_memLoadFinish);
        default:
            printf("Dispatch error: illegal event code: %d", code);
    }

    pthread_mutex_unlock(&dispatcherMutex);
}