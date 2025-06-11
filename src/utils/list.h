#ifndef LIST_H
#define LIST_H

typedef struct node
{
    void *info;
    struct node *next;
} Node;

typedef struct list
{
    Node *head;
    Node *tail;
    int size; 
} List;

List *createList();
void List_append(List *list, void *value);
void List__InsertSorted(List *list, void *value, int (*compareFunction)(void *a, void *b));
int List__remove(List *list, void *value, int (*f)(void *a, void *b));
void *List__removeHead(List *list);
int List__containsValue(List *list, void *value, int (*compareFunction)(void *a, void *b));
Node *List__returnItem(List *list, void *value, int (*compareFunction)(void *a, void *b));
void List__clear(List *list);


#endif