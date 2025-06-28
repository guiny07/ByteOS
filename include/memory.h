#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "kernel.h"
#include "list.h"
#include "utils.h"
#include "types.h"

#define KB 1024
#define MB (1024 * KB)
#define MEMORY_SIZE (1 * MB)
#define OS_RESERVED_SIZE (64 * KB)

#define PAGE_SIZE (1 * KB)
#define TOTAL_PAGES (MEMORY_SIZE / PAGE_SIZE)
#define OS_RESERVED_PAGES (OS_RESERVED_SIZE / PAGE_SIZE)

#define MAX_PAGES_PROCESS 16 // Conjunto residente.

void* Memory__memLoadReqThread(); 
void Memory__memLoadReq();
void* Memory__memLoadFinishThread();
void Memory__memLoadFinish();

PageTable* Memory__init_pageTable();
void Memory__init_page(Page *page, int page_number);


#endif