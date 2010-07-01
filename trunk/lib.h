// francesco 'wtf' brundu

#ifndef _GENERIC_LIB_INCLUDED
#define _GENERIC_LIB_INCLUDED

#include <stdio.h>
#include "dato.h"

// function prototypes
extern FILE* wfopen_r (char*);
extern FILE* wfopen_w (char*);
extern char* wread_s (FILE*);
extern char* wget_s (FILE*);
extern dato_t** wmalloc_2d (dato_t**, int, int, dato_t);
extern void wfree_2d (dato_t**, int);
extern dato_t** wread_matrix(dato_t**, FILE*, int, int, dato_t);
extern void wprint_2d (dato_t**, int, int, FILE*);
extern dato_t* wread_array(void);
extern int wreturn_dim_array(FILE*);

#endif
