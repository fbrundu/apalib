 /***************************************************************************
 *            dato_int.c
 *
 *  Tue May 20 14:05:36 2008
 *  Francesco Brundu
 *  francesco.brundu@studenti.polito.it
 ****************************************************************************/

#include <stdio.h>
#include "dato_int.h"

#define MAXC 30

/*** reads an int from a file and stores it in the cell w/ address stored in dp ***/
int 
data_read(FILE *fp, dato_t *dp) {
   char riga[MAXC];

   if (fgets(riga, MAXC, fp) == NULL)
      return DATA_ERROR;
   sscanf(riga, "%d", dp);
   return !DATA_ERROR;
}

/*** prints dato to file pointed by fp ***/
void 
data_print(FILE *fp, dato_t dato) {
   fprintf(fp, "%d\n", dato);
}

/*** compares d1 and d2 ***/
int 
data_compare(dato_t d1, dato_t d2, int key) {
   return d1-d2;
}

/*** frees memory (not used for int type) ***/
void 
data_free(dato_t dato) {
   return;
}
