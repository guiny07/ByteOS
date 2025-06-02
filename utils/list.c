#include "list.h"
#include <stdlib.h> 

List *createList() {
    List *list = (List *) malloc(sizeof(List));

    list->tail = list->head = NULL;
    list->size = 0;
    
    return list;
}

void List_append(List *list, void *value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->info = value;
    newNode->next = NULL;

    if (list->size == 0) {
        list->head = list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->size++;
}

int List__remove(List *list, void *value, int (*compareFunction)(void *a, void *b)){
    if (list->size == 0)
        return -1;

    Node *current, *last;

    last = current = list->head;
    while (current && compareFunction(current->info, value) != 1)
    {
        last = current;
        current = current->next;    
    }

    // Node not found
    if(!current)
        return -1;

    if(current == list->head){
        list->head = current->next;
    }

    if (current == list->tail)
    {
        list->tail = last;
    }
    
    //Removing from the middle of the list
    if (last)
    {
        last->next = current->next;
    }

    list->size--;
    free(current);
    return 0; 
}

void List__InsertSorted(List *list, void *value, int (*compareFunction)(void *a, void *b)){
    Node *newValue = (Node *) malloc(sizeof(Node));
    newValue->info = value;

    if (list->size == 0)
    {
        newValue->next = NULL;
        list->tail = list->head = newValue;
        list->size++;
        return;
    }
        
    Node *current, *last;
    last = current = list->head;
    
    while (current && compareFunction(current->info, value) < 0)
    {
        last = current;
        current = current->next;
    }

    if (current == list->head)
    {
        newValue->next = list->head;
        list->head = newValue;
    }

    if (current == list->tail)
    {
        newValue->next = NULL;
        list->tail->next = newValue;
        list->tail = newValue;
    }
    
    if (last)
    {
        newValue->next = last->next;
        last->next = newValue;
    }

    list->size++;
    
}

int List__containsValue(List *list, void *value, int (*compareFunction)(void *a, void *b)){
    if(!list || list->size == 0)
        return 0;

    Node *aux = list->head;

    while (aux && compareFunction(value, aux->info) != 0){
        aux = aux->next;
    }

    if (aux == NULL)
        return 0; // Item IS NOT in the list.
    
    return 1;

}

Node *List__returnItem(List *list, void *value, int (*compareFunction)(void *a, void *b)){
    if(!list || list->size == 0)
        return NULL;

    Node *aux = list->head;

    while (aux && compareFunction(value, aux->info) != 0){
        aux = aux->next;
    }

    return aux;
    
}


void *List__removeHead(List *list)
{
    if (list== NULL || list->size == 0)
        return NULL;
    
    Node *aux = list->head;
    void *content = list->head->info;
    list->head = list->head->next;
    free(aux);

    list->size--;

    if(list->head == NULL)
        list->tail = NULL;
    
    return content;  
}

void List__clear(List *list)
{
    Node *cur = list->head;

    while (cur)
    {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }

    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    
}

