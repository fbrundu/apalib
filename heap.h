/****** HEAP.H con heap realizzato mediante array ********/
#ifndef _HEAP_INCLUDED
#define _HEAP_INCLUDED

#include <stdlib.h>
#include "dato_priority.h"

#define   HEAP_FAILURE   -1
#define   HEAP_SUCCESS    1
#define   HEAP_MAX_SIZE   100

typedef struct heap *heap_t;

extern heap_t new_heap(void);
extern void free_heap(heap_t);
extern dato_t heap_extract(heap_t);
extern int heap_insert(heap_t, dato_t) ;
extern void heap_print(FILE*, heap_t);
extern int is_empty_heap(heap_t);

#endif
