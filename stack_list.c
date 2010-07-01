/********************************************************************/
/**                          STACK.C                               **/
/********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct nodo *nodo_t;

struct nodo {
   dato_t  val;
   nodo_t next;
};

struct stack {
   nodo_t head;
   int num;
};

static nodo_t alloc(dato_t val);
static void load_recur(FILE *fp, stack_t sp);

stack_t 
stack_alloc(int size) {
   stack_t sp;

   sp = malloc(sizeof(*sp));
   if (sp == NULL) {
      printf("Errore di allocazione di memoria\n");
      return NULL;
   }

   sp->head = NULL;
   sp->num = 0;

   return sp;
}

void 
stack_free(stack_t sp) {
   nodo_t node, head;

   if (sp == NULL) return;

   head = sp->head;
   while (head != NULL) {
      node = head;
      head = head->next;
      data_free(node->val);
      free(node);
   }
   free(sp);
}

int 
stack_push(stack_t sp, dato_t d) {
   nodo_t node;

   if (sp == NULL) return STACK_ERROR;

   node = alloc(d);
   if (node == NULL) return STACK_ERROR;

   node->next = sp->head;
   sp->head = node;
   sp->num++;

   return !STACK_ERROR;
}

int 
stack_pop(stack_t sp, dato_t *dp) {
   nodo_t node;

   if (sp == NULL) return STACK_ERROR;

   node = sp->head;
   if (node == NULL) return STACK_ERROR;
   *dp = node->val;
   sp->head = node->next;

   free(node);
   sp->num--;

   return !STACK_ERROR;
}

void 
stack_print(FILE *fp, stack_t sp) {
   nodo_t node;
   int i;

   if (sp == NULL) return;

   if (fp == stdout) {
      fprintf(fp, "STACK senza dimensione\n");
      fprintf(fp, "Elenco a partire dai dati in testa\n\n");
   }

   node = sp->head;
   i = sp->num-1;
   while (node != NULL) {
      if (fp == stdout)
         fprintf(fp, "indice: %2d - dato: ", i--);
      data_print(fp, node->val);
      node = node->next;
   }
}

stack_t 
stack_load(FILE *fp) {
   stack_t sp;

   sp = stack_alloc(0);
   if (sp == NULL) return NULL;

   load_recur(fp, sp);
   return sp;
}

static nodo_t 
alloc(dato_t val) {
   nodo_t p;

   p = malloc(sizeof(*p));
   if (p == NULL) {
      printf ("Errore: memoria dinamica insufficiente\n");
      return NULL;
   }

   p->val = val;
   p->next = NULL;
   return p;
}

static void 
load_recur(FILE *fp, stack_t sp) {
   dato_t d;

   if ((data_read(fp, &d)) == DATA_ERROR)
      return;

   load_recur(fp, sp);
   stack_push(sp, d);
}
