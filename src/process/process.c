#include "process.h"

static int pid_counter = 0;
List* ready_queue = NULL;
List* blocked_queue = NULL;
List* all_processes = NULL;

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

        Process__processCreate((char*)arg);
    }
}

void Process__processCreate(char *name)
{
    FILE *fp;
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "../synthetic_programs/%s", name);
    fp = fopen(file_path, "r");

    if(fp == NULL){
        printf("%s is not a valid program, please select an existing synthetic program.", name);
        return;
    }

    char buffer[256];
    PCB *newProcess = (PCB*) malloc(sizeof(PCB));

    newProcess->state = NEW;
    newProcess->rw_count = 0;
    newProcess->pid = pid_counter++;

    fgets(buffer, sizeof(buffer), fp);
    newProcess->name = strdup(buffer);
    newProcess->name[strcspn(newProcess->name, "\n")] = '\0';

    fgets(buffer, sizeof(buffer), fp);
    newProcess->segment_id = atoi(buffer);

    fgets(buffer, sizeof(buffer), fp);
    newProcess->priority = atoi(buffer);

    fgets(buffer, sizeof(buffer), fp);
    newProcess->segment_size = atoi(buffer);

    

}





