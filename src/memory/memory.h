#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../kernel/kernel.h"
#include "../utils/list.h"
#include "../utils/utils.h"
#include "../process/process.h"

#define KB 1024
#define MB (1024 * KB)
#define MEMORY_SIZE (1 * MB)
#define OS_RESERVED_SIZE (64 * KB)

#define PAGE_SIZE (1 * KB)
#define TOTAL_PAGES (MEMORY_SIZE / PAGE_SIZE)
#define OS_RESERVED_PAGES (OS_RESERVED_SIZE / PAGE_SIZE)

#define MAX_PAGES_PROCESS 16 // Conjunto residente.

typedef struct
{
    int  page_number;
    int reference_bit;
    List* instructions;
    int instruction_count;

}Page;

typedef struct
{
    List *pages;
    int page_count;
    Node* last_loaded_instruction;
    int missing_instructions;
    
}PageTable;


void* Memory__memLoadReqThread(); 
void Memory__memLoadReq();
void* Memory__memLoadFinishThread();
void Memory__memLoadFinish();

#endif