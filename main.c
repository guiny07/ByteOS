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
   
   pthread_create(&thread_create, NULL, Process__processCreateThread, NULL);

   while(1)
   {
        Event code = Kernel__syscall();
        Kernel__dispatch(code);

        sleep(1);
   }

   return 0; 
}