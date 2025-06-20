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
    FILE *fp;
    char *file_path = strcat("../../synthetic_programs/", name);
    fp = fopen(file_path, "r");

    if(fp == NULL){
        printf("%s is not a valid program, please select an existing synthetic program.", name);
        return;
    }

    char buffer[256];
    PCB *newProcess = (PCB*) malloc(sizeof(PCB));

    newProcess->state = NEW;
    
    fgets(buffer, sizeof(buffer), fp);
    strcpy(newProcess->name, buffer);

    fgets(buffer, sizeof(buffer), fp);
    newProcess->segment_id = atoi(buffer);

    fgets(buffer, sizeof(buffer), fp);
    newProcess->priority = atoi(buffer);

    fgets(buffer, sizeof(buffer), fp);
    newProcess->segment_size = atoi(buffer);

    
}





