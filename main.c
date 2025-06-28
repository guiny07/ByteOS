#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "include/utils.h"
#include "include/list.h"
#include "include/kernel.h"
#include "include/process.h"
#include "include/semaph.h"
#include "include/memory.h"

void debugList(List *list, void (*printFunction)(void *value)){
    Node *aux = list->head;
    while (aux){
        printFunction(aux->info);
        aux = aux->next;
    }
}

int main()
{
    pthread_t process_create_thread, mem_load_req_thread, mem_load_finish_thread;

    char* program = "sint2";
    pthread_create(&process_create_thread, NULL, Process__processCreateThread, (void*)program); // Thread para ProcessCreate
    pthread_create(&mem_load_req_thread, NULL, Memory__memLoadReqThread, NULL); // Thread para MemLoadReq.
    pthread_create(&mem_load_finish_thread, NULL, Memory__memLoadFinishThread, NULL); // Thread para MemLoadFinish.

    Semaph__semaph_table_init();

    sleep(1);
    Kernel__dispatch(PROCESS_CREATE);
    sleep(2);

    return 0; 
}