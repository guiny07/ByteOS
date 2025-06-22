#include "semaph.h"

static pthread_mutex_t semaphore_mutex = PTHREAD_MUTEX_INITIALIZER;

List* semaphore_table = NULL;

void Semaph__semaph_table_init() {
    semaphore_table = List__createList();
}

Semaphore* Semaph__semaph_init(char sem_name) {

    Semaphore *sem = (Semaphore*) malloc(sizeof(Semaphore));

    sem->name = sem_name;
    sem->waiters = List__createList();
    sem_init(&sem->mutex, 0, 1); 

    return sem;
}

Semaphore* Semaph__search_semaph(char sem) {

    for(Node *n = semaphore_table->head; n != NULL; n = n->next)
    {
        Semaphore *semaph = (Semaphore*) n->info;
        if(semaph->name = sem)
            return semaph;
    }

    return NULL;
}

void Semaph__load_semaphores(char *buffer, List* semaphores) {

    pthread_mutex_lock(&semaphore_mutex);

    int max_buffer = strlen(buffer);
    Semaphore *semaph;

    for(int i = 0; i < max_buffer; i+=2)
    {
        if(Semaph__search_semaph(buffer[i]) == NULL)
        {
            semaph = Semaph__semaph_init(buffer[i]);
            List_append(semaphores, (void *) semaph);
        }
    }

    pthread_mutex_unlock(&semaphore_mutex);
}
