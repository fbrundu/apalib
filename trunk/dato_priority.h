 /***************************************************************************
 *            dato_priority.h
 *
 *  Fri May 30 19:43:04 2008
 *  Francesco Brundu
 *  francesco.brundu@studenti.polito.it
 ****************************************************************************/

#ifndef _DATO_INCLUDED
#define _DATO_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  DATA_ERROR  0
#define  NULLdato  NULL

typedef struct data *dato_t;

extern int data_read(FILE*, dato_t*);
extern void data_print(FILE*, dato_t);
extern void data_free(dato_t);
extern int data_priority(dato_t);

#endif
