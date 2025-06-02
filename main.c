#include <stdio.h>
#include "utils/utils.h"
#include "utils/list.h"

void debugList(List *list, void (*printFunction)(void *value)){
    Node *aux = list->head;
    while (aux){
        printFunction(aux->info);
        aux = aux->next;
    }
}

int main(){

}