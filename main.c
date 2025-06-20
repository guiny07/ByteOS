#include <stdio.h>
#include "src/utils/utils.h"
#include "src/utils/list.h"
#include "src/kernel/kernel.h"
#include "src/process/process.h"
#include <pthread.h>
#include <unistd.h>

void debugList(List *list, void (*printFunction)(void *value)){
    Node *aux = list->head;
    while (aux){
        printFunction(aux->info);
        aux = aux->next;
    }
}

int main()
{
    pthread_t thread_create;
   
    char* program = "sint2";
    pthread_create(&thread_create, NULL, Process__processCreateThread, (void*)program);

    sleep(1);
    Kernel__dispatch(PROCESS_CREATE);
    sleep(3);

    return 0; 
}