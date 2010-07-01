/***** HEAP.C mediante array ************************************/
#include "heap.h"

#define   LEFT(i)         (2*(i)+1)
#define   RIGHT(i)        (2*(i)+2)
#define   PARENT(i)       (((i)-1)/2)

struct heap {
   dato_t *array;
   int heap_size;
};

static void heapify(heap_t, int);
static void swap(heap_t, int, int);

/*** Funzione per la creazione di un nuovo heap *********************/
heap_t
new_heap(void) {
   heap_t hp;
   int i;

   hp = malloc(sizeof(*hp));
   if (hp == NULL) return NULL;
   hp->array = malloc(HEAP_MAX_SIZE*sizeof(dato_t));
   for (i = 0; i < HEAP_MAX_SIZE; i++)
      hp->array[i] = NULL;
   hp->heap_size = 0;

   return hp;
}

/*** Funzione per la deallocazione di un heap ***********************/
void 
free_heap(heap_t hp) {
   int i;
   
   if (hp == NULL) return;

   for (i = 0; i < hp->heap_size; i++)
      data_free(hp->array[i]);
   free(hp->array);
   free(hp);
}

/*** Funzione per l'inserzione di un dato nello heap ****************/
int 
heap_insert(heap_t hp, dato_t dato) {
   int i, p;

   if (hp == NULL) return HEAP_FAILURE;

   /* empty heap */
   if (is_empty_heap(hp) == 1) {
      hp->array[0] = dato;
      hp->heap_size = 1;
      return HEAP_SUCCESS;
   } 

   if (hp->heap_size >= HEAP_MAX_SIZE)
      return HEAP_FAILURE;

   /* add dato to the heap array */
   i = hp->heap_size++; 
   p = PARENT(i);
   while ((i > 0) 
      && (data_priority(hp->array[p]) < data_priority(dato))) {
      hp->array[i] = hp->array[p];
      i = p; 
      p = PARENT(i);
   }
   hp->array[i] = dato;
   return HEAP_SUCCESS;
}

/*** Funzione per l'estrazione di un dato dallo heap ****************/
dato_t 
heap_extract(heap_t hp) {
   dato_t dato;

   if (hp == NULL) return NULL;

   if (is_empty_heap(hp)) return NULL;

   dato = hp->array[0];

   /* remake the heap */
   hp->heap_size--;
   if (hp->heap_size == 0) { /* empty heap */
      hp->array[0] = NULLdato;
   } 
   else {
      hp->array[0] = hp->array[hp->heap_size];
      hp->array[hp->heap_size] = NULLdato;
      heapify(hp, 0);
   }
   return dato;
}

/*** Funzione per la stampa dello heap ******************************/
void 
heap_print(FILE *fp, heap_t hp) {
   int i;

   if (hp == NULL) return;

   for (i = 0; i < hp->heap_size; i++) {
      if (fp == stdout) fprintf(fp, "+ indice %2d - ", i);
      data_print(fp, hp->array[i]);
   }
}


/*** Funzione per il test di heap vuoto *****************************/
int 
is_empty_heap(heap_t hp) {
   if (hp == NULL) return HEAP_FAILURE;
   return hp->heap_size == 0;
}

/*** Funzione "heapify" *********************************************/
static 
void heapify(heap_t hp, int i) {
   int l, r, key;

   l = LEFT(i); r = RIGHT(i); key = i;

   if ((l < hp->heap_size) 
      && (data_priority(hp->array[l]) > data_priority(hp->array[key])))
      key = l;
   if ((r < hp->heap_size) 
      && (data_priority(hp->array[r]) > data_priority(hp->array[key])))
      key = r;
   if (key != i) {
      swap(hp, i, key);
      heapify(hp, key);
   }
}

/*** Funzione di scambio di due dati ********************************/
static 
void swap(heap_t hp, int i, int j) {
   dato_t temp;

   temp = hp->array[i];
   hp->array[i] = hp->array[j];
   hp->array[j] = temp;   
}

