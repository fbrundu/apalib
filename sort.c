/*** SORT.H ***/
#ifndef _SORT_INCLUDED
#define _SORT_INCLUDED

#include "dato.h"

extern void insertion_sort(dato_t*, int);
extern void selection_sort(dato_t*, int);
extern void bubble_sort(dato_t*, int);

#endif
/*** SORT.C ***/
#include <stdlib.h>
#include "sort.h"

/* macro per gestione heap */
#define LEFT(i)    (2*(i)+1)
#define RIGHT(i)   (2*(i)+2)

/* dichiarazione delle funzioni statiche */
static void swap(dato_t*, int, int);

/* funzioni interne di quick sort */
static void quick_sort_recur(dato_t*, int, int);
static int partition(dato_t*, int, int);

/* funzioni interne di merge sort */
static void merge_sort_recur(dato_t*, dato_t*, int, int);
static void merge(dato_t*, dato_t*, int, int, int);

/* funzioni interne di heap sort */
static void build_heap(dato_t*, int);
static void heapify(dato_t*, int, int);


/********************************************************************/
/**  Insertion Sort     *********************************************/
/********************************************************************/
void 
insertion_sort(dato_t *array, int size) {
   int i, j;
   dato_t key;

   for (i = 1; i < size; i++) {
      key = array[i];
      j = i;
      while ((--j >= 0) && (data_compare(array[j], key, DATO_TYPE) > 0)) {
	     array[j+1] = array[j];
      }
      array[j+1] = key;
   }
}


/********************************************************************/
/**  Selection Sort     *********************************************/
/********************************************************************/
void 
selection_sort(dato_t *array, int size) {
   int i, j, min; 

   for (i = 0; i < size-1; i++) {
      min = i;   
      for (j = i+1; j < size; j++) {
         if (data_compare(array[j], array[min], DATO_TYPE) < 0) {
	        min = j;
         }
      }
      swap(array, i, min);
   }
}


/********************************************************************/
/**  Bubble Sort     ************************************************/
/********************************************************************/
void 
bubble_sort(dato_t *array, int size) {
   int i, j; 

   for (i = size-1; i >= 1; i--) {
      for (j = 0; j < i; j++) {
	     if (data_compare(array[j], array[j+1], DATO_TYPE) > 0) {
	        swap(array, j, j+1);
         }
      }
   }
}


/********************************************************************/
/**  Quick Sort     *************************************************/
/********************************************************************/
void 
quick_sort(dato_t *array, int size) {
   int p = 0, r = size-1;

   quick_sort_recur(array, p, r);
}

/*** Quick Sort, funzione recursiva   *******************************/
static void 
quick_sort_recur(dato_t *array, int p, int r) {
   int q;

   if (p < r) {
      q = partition(array, p, r);
      quick_sort_recur(array, p, q);
      quick_sort_recur(array, q+1, r);      
   }
}

/*** Funzione "Partition" (Quick Sort)   ****************************/
static int 
partition(dato_t *array, int p, int r) {
   int i, j;
   dato_t x;

   x = array[p]; i = p-1; j = r+1;
   while (i < j) {
      while (data_compare(array[++i], x, DATO_TYPE) < 0);
      while (data_compare(array[--j], x, DATO_TYPE) > 0);
      if (i < j) {
  	     swap(array, i, j);
      }
   }
   return j;
}


/********************************************************************/
/**  Merge Sort     *************************************************/
/********************************************************************/
void 
merge_sort(dato_t *array, int size) {
   int p = 0, r = size-1;
   dato_t *merged;

   merged = malloc(size*sizeof(dato_t));
   merge_sort_recur(array, merged, p, r);
   free(merged);
}

/*** Merge Sort, funzione recursiva   *******************************/
static void 
merge_sort_recur(dato_t *array, dato_t *merged, int p, int r) {
   int q;

   if (p < r) {
      q = (p + r) / 2;
      merge_sort_recur(array, merged, p, q);
      merge_sort_recur(array, merged, q+1, r);      
      merge(array, merged, p, q, r);      
   }
}

/*** Funzione "Merge" (Merge Sort)   ********************************/
static void 
merge(dato_t *array, dato_t *merged, int p, int q, int r) {
   int i, j, k;
   
   for (i = p, j = q+1, k = 0; (i <= q) && (j <= r); ) {
      if (data_compare(array[i], array[j], DATO_TYPE) < 0) {
	     merged[k++] = array[i++];
      } 
      else {
	     merged[k++] = array[j++];
      }
   }

   for ( ; i <= q; ) merged[k++] = array[i++];
   for ( ; j <= r; ) merged[k++] = array[j++];
   for (k = 0; k <= r-p; k++) array[k+p] = merged[k];
}


/********************************************************************/
/**  Heap Sort     **************************************************/
/********************************************************************/
void 
heap_sort(dato_t *array, int size) {
   int i;

   build_heap(array, size);
   for (i = size-1; i > 0; i--) {
      swap(array, i, 0);
      heapify(array, 0, --size);
   }
}

/*** Funzione "BuildHeap" (Heap Sort)   *****************************/
static void 
build_heap(dato_t *array, int heap_size) {
   int i;

   for (i = heap_size/2-1; i >= 0; i--) {
      heapify(array, i, heap_size);
   }
}

/*** Funzione "Heapify" (Heap Sort)   *******************************/
static void 
heapify (dato_t *array, int i, int heap_size) {
   int l, r, key;

   l = LEFT(i); r = RIGHT(i); key = i;

   if ((l < heap_size) && (data_compare(array[l], array[key], DATO_TYPE) > 0)) {
      key = l;
   }
   if ((r < heap_size) && (data_compare(array[r], array[key], DATO_TYPE) > 0)) {
      key = r;
   }
   if (key != i) {
      swap(array, i, key);
      heapify(array, key, heap_size);
   }
}


/*** Funzione di scambio  *******************************************/
static void 
swap(dato_t *array, int i, int j) {
   dato_t temp;

   temp = array[i];
   array[i] = array[j];
   array[j] = temp;
}

