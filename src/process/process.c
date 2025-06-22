#include "process.h"

// Global structures managed by process.h
static int pid_counter = 0;
List* ready_queue = NULL;
List* blocked_queue = NULL;
List* all_processes = NULL;

pthread_mutex_t mutex_ready_queue = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_blocked_queue = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_all_processes = PTHREAD_MUTEX_INITIALIZER;

// To initialize the global structures.
void Process__process_init()
{
    ready_queue = List__createList();
    blocked_queue = List__createList();
    all_processes = List__createList();
}

// Function to wake up the ProcessCreate thread based on the value of its flag.
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

// Reads a program from the synthetic programs directory and turns it in to a process in the simulator.
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
    newProcess->pid = pid_counter++; // Atribui o atual PID disponível e incrementa para o próximo. 

    //Carregando os metadados. 
    fgets(buffer, sizeof(buffer), fp);
    newProcess->name = strdup(buffer);
    newProcess->name[strcspn(newProcess->name, "\n")] = '\0';

    fgets(buffer, sizeof(buffer), fp);
    newProcess->segment_id = atoi(buffer);

    fgets(buffer, sizeof(buffer), fp);
    newProcess->priority = atoi(buffer);

    fgets(buffer, sizeof(buffer), fp);
    newProcess->segment_size = atoi(buffer);

    //Carregando os semáforos usados pelo processo. 
    fgets(buffer, sizeof(buffer), fp);
    Semaph__load_semaphores(buffer, semaphore_table);

    //Carregando instruções.
    fgets(buffer, sizeof(buffer), fp);

    newProcess->instructions = Process__read_instructions(fp); 

    fclose(fp);

    
    //CRIAR LÓGICA PARA A MEMÓRIA.
    //INSERIR NA all_process VIA EXCLUSÃO MÚTUA.


}



// Utilitary functions

List* Process__read_instructions(FILE *fp) {

    List* instruction_list = List__createList();
    Instruction* instr;
    char buffer[256];

    while(fgets(buffer, sizeof(buffer), fp))
    {
        instr = Process__instruction_parser(buffer);
        
        // Only EXEC, READ or WRITE have remaining time.
        if(instr->operation == EXEC)
            instr->remaining_time = instr->value; // initially the remaining time is the entire instruction time value.
        else if(instr->operation == READ || instr->operation == WRITE)
            instr->remaining_time = 4000; // Each I/O operation has a minimum duration of 4000 time units. 
        
        instr->loaded = false;

        List_append(instruction_list, (void *) instr);
    }

    return instruction_list;
}


Instruction* Process__instruction_parser(char *buffer) {

    Instruction *instruction_read = (Instruction*)malloc(sizeof(Instruction));
    char *token = " ";
    char *operation = strtok(buffer, token);

    if(!strcmp("exec", operation)) {
        instruction_read->operation = EXEC;
        instruction_read->sem = '\0';
    }
    else if(!strcmp("read", operation)){
        instruction_read->operation = READ;
        instruction_read->sem = '\0';
    }
    else if(!strcmp("write", operation)){
        instruction_read->operation = WRITE;
        instruction_read->sem = '\0';
    }
    else if(!strcmp("print", operation)){
        instruction_read->operation = PRINT;
        instruction_read->sem = '\0';
    }
    else if(!strncmp("P(", operation, 2)){
        instruction_read->operation = SEM_P;
        instruction_read->sem = operation[2];
        instruction_read->value = 0;
        
        return instruction_read;
    }
    else if(!strncmp("V(", operation, 2)){
        instruction_read->operation = SEM_V;
        instruction_read->sem = operation[2];
        instruction_read->value = 0;

        return instruction_read;
    }

    int value = atoi(strtok(NULL, token));

    instruction_read->value = value;

    return instruction_read;
}


// REMOVER ISSO.
void print_list(List *list)
{
    Node *aux = list->head;

    while(aux)
    {
        Instruction* instr = (Instruction*) aux->info;

        switch(instr->operation)
        {
            case EXEC:
                printf("exec ");
                break;
            case WRITE:
                printf("write ");
                break;
            case READ:
                printf("read ");
                break;
            case PRINT:
                printf("print ");
                break;
            case SEM_P:
                printf("P(");
                break;
            case SEM_V:
                printf("V(");
                break;
        }

        if(instr->operation == SEM_P || instr->operation == SEM_V)
            printf("%c)", instr->sem);
        else
            printf("%d", instr->value);
        
        printf(" | Loaded: %s", instr->loaded ? "True" : "False");

        if(instr->operation != SEM_P && instr->operation != SEM_V)
            printf(" | Remaining time: %d", instr->remaining_time);
        
        printf("\n");

        aux = aux->next;
    }
}


