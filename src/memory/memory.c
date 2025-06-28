#include "../../include/memory.h"
#include "../../include/process.h"


PageTable* Memory__init_pageTable()
{
    printf("Entrei na init_pageTable \n");
    PageTable* page_table = (PageTable*)malloc(sizeof(PageTable));
    page_table->page_count = 0;
    page_table->last_loaded_instruction = NULL;
    page_table->missing_instructions = false;
    page_table->pages = List__createList();

    printf("\n Retornei a pageTable \n");
    return page_table;
}

void Memory__init_page(Page *page, int page_number)
{
    page->instruction_count = 0;
    page->page_number = page_number;
    page->reference_bit = 0;
    page->instructions = List__createList();
}

void* Memory__memLoadReqThread(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&dispatcherMutex);

        while(!memLoadReqFlag)
            pthread_cond_wait(&cond_memLoadReq, &dispatcherMutex);
        
        memLoadReqFlag = 0;

        pthread_mutex_unlock(&dispatcherMutex);

        Memory__memLoadReq();
    }
}


void Memory__memLoadReq()
{
    pthread_mutex_lock(&mutex_loading_process);
    PCB *process = loading_process;
    loading_process = NULL;
    pthread_mutex_unlock(&mutex_loading_process);
    printf("\n [Memory Load Request] Cheguei no início da memLoadReq \n");
    if (process) {
        printf(">> processo existe\n");
        printf(">> pid: %d\n", process->pid);
        printf(">> segmento: %d\n", process->segment_id);
        printf(">> prioridade: %d\n", process->priority);
    }

    printf(">> logo antes de acessar page_table\n");

    if (process->page_table == NULL)
        printf(">> page_table é NULL\n");
    else
        printf(">> page_table existe\n");

    printf(">> acessando page_count...\n");
    //printf(">> endereço de page_table: %p\n", (void*)process->page_table);

    //printf(">> tentando acessar page_count...\n");
    process->page_table->page_count = 0;


    printf(">> page_count acessado com sucesso\n");


    Node* aux = process->page_table->last_loaded_instruction;
    Instruction* next_to_load;

    while(aux && process->page_table->page_count < MAX_PAGES_PROCESS)
    {
        next_to_load = (Instruction*)aux->info;

        if(next_to_load->loaded)
        {
            aux = aux->next;
            next_to_load = (Instruction*)aux->info;
        }

        if(next_to_load->operation == EXEC)
        {
            int slices = ceil((double)next_to_load->remaining_time / 1000);

            for(int i = 0; i < slices && process->page_table->page_count < MAX_PAGES_PROCESS; i++)
            {
                int remaining = next_to_load->value - (1000 * i);
                int slice = remaining >= 1000 ? 1000 : remaining;

                next_to_load->remaining_time -= remaining >= 1000 ? 1000 : remaining;

                if(next_to_load->remaining_time == 0)
                    next_to_load->loaded = true;
                
                Page *page = (Page *)malloc(sizeof(Page));
                Memory__init_page(page, process->page_table->page_count);
                
                Instruction* new_instr = next_to_load;
                List_append(page->instructions, (void *) new_instr);
                page->instruction_count++;
                List_append(process->page_table->pages, (void *) page);
                process->page_table->page_count++;
            }

            if(next_to_load->loaded == 1)
                aux = aux->next;
        }
        else if(process->page_table->page_count == 0)
        {
            Page *page = (Page *)malloc(sizeof(Page));
            
            next_to_load->loaded = true;

            Memory__init_page(page, process->page_table->page_count);
            Instruction* new_instr = next_to_load;       
            List_append(page->instructions, (void *) new_instr);
            page->instruction_count++;
            List_append(process->page_table->pages, (void *) page);

            aux = aux->next;
        }
        else
        {
            Page* last_page = (Page*) process->page_table->pages->tail->info;
            next_to_load->loaded = true;
            Instruction* new_instr = next_to_load;
            List_append(last_page->instructions, new_instr);
            last_page->instruction_count++;

            aux = aux->next;
        }
    }

    process->page_table->missing_instructions = (aux != NULL && process->page_table->page_count == MAX_PAGES_PROCESS) ? true : false;
    process->page_table->last_loaded_instruction = aux;

    pthread_mutex_lock(&mutex_loading_process);
    loading_process = process;
    pthread_mutex_unlock(&mutex_loading_process);

    Kernel__dispatch(MEM_LOAD_FINISH);
}


void* Memory__memLoadFinishThread()
{
    while(1)
    {   
        pthread_mutex_lock(&dispatcherMutex);

        while(!memLoadFinishFlag)
            pthread_cond_wait(&cond_memLoadFinish, &dispatcherMutex);
        
        memLoadFinishFlag = 0;

        pthread_mutex_unlock(&dispatcherMutex);

        Memory__memLoadFinish();
    }
}


void Memory__memLoadFinish()
{
    pthread_mutex_lock(&mutex_loading_process);
    PCB* process = loading_process;
    pthread_mutex_unlock(&mutex_loading_process);

    process->state = READY;

    pthread_mutex_lock(&mutex_ready_queue);
    List_append(ready_queue, (void *) process);
    pthread_mutex_unlock(&mutex_ready_queue);
}