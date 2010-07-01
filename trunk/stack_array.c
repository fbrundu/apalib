/********************************************************************/
/**                           STACK.C                               **/
/********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "dato.h"

struct stack {
   dato_t *dati;
   int     index;
   int     size;
};

static void load_recur(FILE *fp, stack_t sp, int size);

stack_t 
stack_alloc(int size) {
   stack_t sp;

   sp = malloc(sizeof(*sp));
   if (sp == NULL) {
      printf("Errore di allocazione di memoria\n");
      return NULL;
   }

   sp->size = size;
   sp->index = 0;
   sp->dati = (dato_t *)malloc(size*sizeof(dato_t));
   if (sp->dati == NULL) {
      printf("Errore di allocazione di memoria\n");
      free(sp); /* libera memoria gia' allocata per sp */
      return NULL;
   }

   return sp;
}

void 
stack_free(stack_t sp) {
   int i;

   if (sp == NULL) return;

   if (sp->dati != NULL) {
      for (i = 0; i < sp->index; i++)
         data_free(sp->dati[i]);
      free(sp->dati);
   }
   free(sp);
}

int 
stack_push(stack_t sp, dato_t d) {
   if (sp == NULL) return STACK_ERROR;
   if (sp->index >= sp->size)
      return STACK_ERROR;

   sp->dati[sp->index++] = d;

   return !STACK_ERROR;
}

int 
stack_pop(stack_t sp, dato_t *dp) {
   if (sp == NULL) return STACK_ERROR;
   if (sp->index <= 0)
      return STACK_ERROR;

   *dp = sp->dati[--sp->index];

   return !STACK_ERROR;
}

void 
stack_print(FILE *fp, stack_t sp) {
   int i;

   if (sp == NULL) return;

   if (fp == stdout) {
      fprintf(fp, "STACK di dimensione %d\n", sp->size);
      fprintf(fp, "Elenco a partire dai dati in cima\n\n");
   } 
   else {
      fprintf(fp, "%d\n", sp->size);
   }

   for (i = sp->index-1; i >= 0; i--) {
      if (fp == stdout)
         fprintf(fp, "indice: %2d - dato: ", i);
      data_print(fp, sp->dati[i]);
   }
}

stack_t 
stack_load(FILE *fp) {
   int size = 0;
   stack_t sp;
   char riga[20];

   if (fgets(riga, 20, fp) == NULL)
      return NULL;
   sscanf(riga, "%d", &size);
   sp = stack_alloc(size);
   if (sp == NULL) return NULL;

   load_recur(fp, sp, size);

   return sp;
}

static void 
load_recur(FILE *fp, stack_t sp, int size) {
   dato_t d;

   if (size <= 0 || (data_read(fp, &d)) ==DATA_ERROR)
      return;

   load_recur(fp, sp, size-1);
   stack_push(sp, d);
}
