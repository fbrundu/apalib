/********************************************************************/
/**                          QUEUE.C     (list)                          **/
/********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct nodo *nodo_t;

struct nodo {
   dato_t  val;
   nodo_t next;
};

struct queue {
   nodo_t head;
   nodo_t tail;
   int num;
};

static nodo_t alloc(dato_t val);

queue_t 
queue_alloc(int size) {
   queue_t qp;

   qp = malloc(sizeof(qp));
   if (qp == NULL) {
      printf("Errore di allocazione di memoria\n");
      return NULL;
   }

   qp->head = NULL;
   qp->tail = NULL;
   qp->num = 0;

   return qp;
}

void 
queue_free(queue_t qp) {
   nodo_t node, head;
  
   if (qp == NULL) return;

   head = qp->head;
   while (head != NULL) {
      node = head;
      head = head->next;
      data_free(node->val);
      free(node);
   }
   free(qp);
}

int 
queue_insert(queue_t qp, dato_t dato) {
   nodo_t node;

   if (qp == NULL) return QUEUE_ERROR;

   node = alloc(dato);
   if (node == NULL) return QUEUE_ERROR;

   if (qp->head == NULL) {
      /* primo inserimento */
      qp->head = node;
   } 
   else {
      qp->tail->next = node;
   }
   qp->tail = node;
   qp->num++;

   return !QUEUE_ERROR;
}

int 
queue_extract(queue_t qp, dato_t *dp) {
   nodo_t node;

   if (qp == NULL) return QUEUE_ERROR;

   node = qp->head;
   if (node == NULL) return QUEUE_ERROR;

   *dp = node->val;
   qp->head = node->next;
   /* ultima estrazione */
   if (qp->head == NULL) qp->tail = NULL;

   free(node);
   qp->num--;
   return !QUEUE_ERROR;
}

void 
queue_print(FILE *fp, queue_t qp) {
   nodo_t node;
   int i = 0;

   if (qp == NULL) return;

   if (fp == stdout) {
      fprintf(fp, "CODA senza dimensione\n");
      fprintf(fp, "Elenco a partire dai dati in testa\n\n");
   }

   node = qp->head;
   while (node != NULL) {
      if (fp == stdout)
         fprintf(fp, "indice: %2d  -  dato: ", i++);
      data_print(fp, node->val);
      node = node->next;
   }
}

queue_t 
queue_load(FILE *fp) {
   dato_t d;
   queue_t qp;

   qp = queue_alloc(0);
   if (qp == NULL) return NULL;

   while ((data_read(fp, &d)) != DATA_ERROR) {
      queue_insert(qp, d);
   }

   return qp;
}

static nodo_t 
alloc(dato_t val) {
   nodo_t p;

   p = malloc(sizeof(*p));
   if (p == NULL) {
      printf("Errore: memoria dinamica insufficiente\n");
      return NULL;
   }

   p->val = val;
   p->next = NULL;
   return p;
}
