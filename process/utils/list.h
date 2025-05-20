#ifndef LIST_H
#define LIST_H

typedef struct node {
    void *info;
    struct node *next;
} Node;


typedef struct list{
    Node *head; 
    Node *tail;
    int size;
} List;