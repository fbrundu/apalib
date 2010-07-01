 /***************************************************************************
 *            dato_string.c
 *
 *  Fri May 30 19:43:21 2008
 *  Francesco Brundu
 *  francesco.brundu@studenti.polito.it
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dato_string.h"

#define MAXC 60

/*** Reads string ***/
int 
data_read(FILE *fp, dato_t *dp) {
  dato_t dato;
  char riga[MAXC];

  if (fgets(riga, MAXC, fp) == NULL)
    return DATA_ERROR;

  dato = (char *)malloc((strlen(riga)+1)*sizeof(char));
  if (dato == NULL)
    return DATA_ERROR;

  /* eventually filters newline character  */
  if (riga[strlen(riga)-1] == '\n')
    riga[strlen(riga)-1] = '\0';
  strcpy(dato, riga);
  *dp = dato;

  return !DATA_ERROR;
}

/*** Prints string ***/
void 
data_print(FILE *fp, dato_t dato) {
  fprintf(fp, "%s\n", dato);
}

/*** Compares two strings ***/
int 
data_compare(dato_t d1, dato_t d2, int key) {
  return strcmp(d1, d2);
}

/*** Free memory block used by the string ***/
void 
data_free(dato_t dato) {
  free(dato);
}
