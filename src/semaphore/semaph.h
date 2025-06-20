#ifndef SEMAPH_H
#define SEMAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "../kernel/kernel.h"
#include "../utils/utils.h"
#include "../utils/list.h"
#include "../process/process.h"

extern List* semaphore_table;

typedef struct {
    char name;
    sem_t mutex;
    List *waiters;
} Semaphore;

void Semaph__semaph_table_init();
Semaphore* Semaph__semaph_init(char sem_name);
Semaphore* Semaph__search_semaph(char sem);
Semaphore* Semaph__get_or_create(char sem);
void Semaph__semaphoreP(char sem, PCB *process);
void Semaph__semaphoreV(char sem);

#endif