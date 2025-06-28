#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include "list.h"

/*
*   Esta .h tem como finalidade a definição de estruturas que são compartilhadas por duas ou mais bibliotecas do sistema ByteOS. 
*/

// Forward declaration. 
typedef struct Page Page;
typedef struct PageTable PageTable;
typedef struct ProcessControlBlock PCB;

/* ------------------ Enums --------------------- */
typedef enum {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
} ProcessState;

// For the operations performed by the synthetic program. 
typedef enum {
    EXEC,
    READ,
    WRITE,
    SEM_P,
    SEM_V,
    PRINT
} Operation;

// For a single instruction from the synthetic program. 
typedef struct {
    Operation operation;
    int value;
    char sem; 
    int remaining_time; // In case the instruction is not completely read. 
    bool loaded; // Flag to know if the instructions is completely loaded in to page table.   
} Instruction;

/* ------------------- Estrutura do processo (PCB) ------------------- */
typedef struct ProcessControlBlock
{
    char *name;
    int pid;
    int priority;
    ProcessState state;
    int segment_size;
    int segment_id;
    int rw_count;

    Node *current_page;
    Node *current_instruction;

    List *instructions;

    PageTable *page_table;
} PCB;


/* ----------------------- Estruturas para a memória ---------------------------- */

typedef struct Page
{
    int  page_number;
    int reference_bit;
    List* instructions;
    int instruction_count;

}Page;

typedef struct PageTable
{
    List *pages;
    int page_count;
    Node* last_loaded_instruction;
    int missing_instructions;

}PageTable;


#endif