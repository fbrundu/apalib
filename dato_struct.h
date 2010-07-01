 /***************************************************************************
 *            dato_struct.h
 *
 *  Fri May 30 19:50:23 2008
 *  Francesco Brundu
 *  francesco.brundu@studenti.polito.it
 ****************************************************************************/

#ifndef _DATO_INCLUDED
#define _DATO_INCLUDED

#define DATA_ERROR 0
// 0 for integer type, 1 for string type, in this case has to be specified
// correctly, in order to compare two structs by the right field 
#define  DATO_TYPE   0 
#define  NULLdato    NULL

typedef struct dato *dato_t;

int data_read(FILE*, dato_t*);
void data_print(FILE*, dato_t);
int data_compare(dato_t, dato_t, int);
void data_free(dato_t);

#endif
