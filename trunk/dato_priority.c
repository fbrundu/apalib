 /***************************************************************************
 *            dato_priority.c
 *
 *  Fri May 30 19:40:01 2008
 *  Francesco Brundu
 *  francesco.brundu@studenti.polito.it
 ****************************************************************************/

#include "dato_priority.h"

#define MAX_LEN   100

struct data {
   char *name;
   int priority;
};

/*** Reads data ***********************/
int
data_read(FILE *fp, dato_t *dp) {
   char line[MAX_LEN], name[MAX_LEN];
   int priority;
   dato_t d;

   if (fp == stdin)
      printf("Inserire nome e priorita': ");
   if (fgets(line, MAX_LEN, fp) == NULL)
      return DATA_ERROR;
   if (sscanf(line, "%s %d", name, &priority) != 2)
      return DATA_ERROR;
   d = malloc(sizeof(*d));
   if (d == NULL) return DATA_ERROR;
   d->name = (char*)malloc((strlen(name)+1)*sizeof(char));
   if (d->name == NULL) {
      free(d);
      return DATA_ERROR;
   }
   strcpy(d->name, name);
   d->priority = priority;
   (*dp) = d;
   return !DATA_ERROR;
}

/*** Prints data ******************************/
void 
data_print(FILE *fp, dato_t d) {
   if (fp!=stdout) {
      fprintf(fp, "%s %d\n", d->name, d->priority);
      return;
   }

   fprintf(fp, "nome = %s, ", d->name);
   fprintf(fp, "priorita' = %d\n", d->priority);
}

/*** Deallocates memory cell used by data ***********************/
void 
data_free(dato_t d) {
   free(d->name);
   free(d);
}

/*** Returns data priority ***********************/
int 
data_priority(dato_t d) {
   return d->priority;
}

