#include "memory.h"


PageTable* Memory__init_pageTable()
{
    PageTable* page_table = (PageTable*)malloc(sizeof(PageTable));
    page_table->page_count = 0;
    page_table->last_loaded_instruction = NULL;
    page_table->missing_instructions = false;
    page_table->pages = List__createList();
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

    process->page_table->page_count = 0;

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
    }
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

}