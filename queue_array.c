/********************************************************************/
/**                          QUEUE.C      (array)                         **/
/********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct queue {
   dato_t *dati;
   int     head;
   int     tail;
   int     num;
   int     size;
};

queue_t 
queue_alloc(int size) {
   queue_t qp;

   qp = malloc(sizeof(*qp));
   if (qp == NULL) {
      printf("Errore di allocazione di memoria\n");
      return NULL;
   }

   qp->size = size;
   qp->head = qp->tail = qp->num = 0;
   qp->dati = (dato_t *)malloc(size*sizeof(dato_t));
   if (qp->dati == NULL) {
      printf("Errore di allocazione di memoria\n");
      free(qp); /* libera memoria gia' allocata per qp */
      return NULL;
   }

   return qp;
}

void 
queue_free(queue_t qp) {
   int i;

   if (qp == NULL) return;

   if (qp->dati != NULL) {
      for (i=qp->head; qp->num>0; i=(i+1)%qp->size) {
         data_free(qp->dati[i]);
         qp->num--;
      }
      free(qp->dati);
   }
   free(qp);
}

int 
queue_insert(queue_t qp, dato_t d) {
   if (qp == NULL) return QUEUE_ERROR;
   if (qp->num >= qp->size) return QUEUE_ERROR;

   qp->dati[qp->tail] = d;
   qp->tail = (qp->tail+1) % (qp->size);
   qp->num++;

   return !QUEUE_ERROR;
}

int 
queue_extract(queue_t qp, dato_t *dp) {
   if (qp == NULL) return QUEUE_ERROR;
   if (qp->num <= 0) return QUEUE_ERROR;

   (*dp) = qp->dati[qp->head];
   qp->head = (qp->head+1) % (qp->size);
   qp->num--;

   return !QUEUE_ERROR;
}

void 
queue_print(FILE *fp, queue_t qp) {
   int i, j = 0;

   if (qp == NULL) return;

   if (fp == stdout) {
      fprintf(fp, "CODA di dimensione %d\n", qp->size);
      fprintf(fp, "Elenco a partire dai dati in testa\n\n");
   } 
   else {
      fprintf(fp, "%d\n", qp->size);
   }
   for (i = 0; i < qp->num; i++) {
      j = (qp->head+i) % (qp->size);
      if (fp == stdout) fprintf(fp, "indice: %2d  -  dato: ", j);
      data_print(fp, qp->dati[j]);
   }
}

queue_t 
queue_load(FILE *fp) {
   int size = 0;
   dato_t d;
   queue_t qp;
   char riga[20];

   if (fgets(riga, 20, fp) == NULL) return NULL;
   sscanf(riga, "%d", &size);
   qp = queue_alloc(size);
   if (qp == NULL) return NULL;

   while ((data_read(fp, &d)) != DATA_ERROR && size>0) {
      queue_insert(qp, d);
      size--;
   }

   return qp;
}
