#include "utils.h"

int compareInt(void *a, void *b){
    if ( *(int *)a == *(int *)b )
    {
        return 0;
    }
    
    return 1;
}

