#ifndef _STACK_INCLUDED
#define _STACK_INCLUDED

#include "dato.h"

#define STACK_ERROR 0

typedef struct stack *stack_t;

extern stack_t stack_alloc(int);
extern void stack_free(stack_t);
extern int stack_push(stack_t, dato_t);
extern int stack_pop(stack_t, dato_t*);
extern void stack_print(FILE*, stack_t);
extern stack_t stack_load(FILE*);

#endif
