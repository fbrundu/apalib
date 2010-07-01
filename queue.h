/***** QUEUE.H ****/

#ifndef _QUEUE_INCLUDED
#define _QUEUE_INCLUDED

#include "dato.h"

#define QUEUE_ERROR 0

typedef struct queue *queue_t;

queue_t queue_alloc(int);
void queue_free(queue_t);
int queue_insert(queue_t, dato_t d);
int queue_extract(queue_t, dato_t*);
void queue_print(FILE*, queue_t);
queue_t queue_load(FILE*);

#endif
