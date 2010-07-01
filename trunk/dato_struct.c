 /***************************************************************************
 *            dato_struct.c
 *
 *  Fri May 30 19:46:24 2008
 *  Francesco Brundu
 *  francesco.brundu@studenti.polito.it
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dato_struct.h"

#define MAXC 60

/*** Declaration of struct dato ***/
struct dato {
  char stringa[21];
  int num;
};

/*** Reads struct ***/
int data_read(FILE *fp, dato_t *dp) {
  dato_t dato;
  char riga[MAXC];

  if (fgets(riga, MAXC, fp) == NULL)
    return DATA_ERROR;

  dato = (dato_t)malloc(sizeof(*dato));
  if (dato == NULL) 
    return DATA_ERROR;

  sscanf(riga, "%s %d", dato->stringa, &dato->num);
  *dp = dato;

  return !DATA_ERROR;
}

/*** Prints struct ***/
void data_print(FILE *fp, dato_t dato) {
  fprintf(fp, "%s %d\n", dato->stringa, dato->num);
}

/*** Compares two structs, requires type of field [INT | CHAR*] ***/
int data_compare(dato_t d1, dato_t d2, int key)
{
  if (key)
    return strcmp(d1->stringa, d2->stringa);
  else
    return d1->num - d2->num;
}

/*** Frees the block of memory of the struct ***/
void data_free(dato_t dato) {
  free(dato);
}
