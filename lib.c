#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

#define  SIZE  15

FILE* 
wfopen_r (char *name) {
   FILE *fp = NULL;
   char s[SIZE + 1];
   
   if (name!=NULL) return (fp = fopen (name, "r"));
   printf ("Inserisci il nome del file da leggere\n> ");
   scanf ("%s", s);
   fp = fopen (s, "r");
   
   return fp;
}

FILE* 
wfopen_w (char *name) {
   FILE *fp = NULL;
   char s[SIZE + 1];
   
   if (name!=NULL) return (fp = fopen (name, "w")); 
   printf ("Inserisci il nome del file dove scrivere\n> ");
   scanf ("%s", s);
   fp = fopen (s, "w");
      
   return fp;
}

char*
wread_s (FILE *fp) {
   char t[SIZE + 1], *s = NULL;
   int len;
   
   if ((fscanf (fp, "%s", t)) == EOF) return NULL;
   len = strlen (t);
   s = malloc (len * sizeof (char));
   strcpy (s, t);
   return s;
}

char*
wget_s (FILE *fp) {
   char t[SIZE+1], *s = NULL;
   int len;
   
   strcpy (t, "\n\0");
   while (t[0] == '\n') 
      { if ((fgets (t, MAX_LEN, fp)) == NULL) return NULL; }
   len = strlen (t);
   if(t[len-1]=='\n') t[--len]='\0';
   s = malloc (len * sizeof (char));
   strcpy (s, t);
   return s;
}

dato_t**
wmalloc_2d (dato_t **m, int dim_1, int dim_2, dato_t init_dato) {
   int i, j;
   
   if ((m = malloc (dim_1 * sizeof (dato_t*))) == NULL) return NULL;
   for (i = 0; i < dim_1; i++) {
      if ((m[i] = malloc (dim_2 * sizeof (dato_t))) == NULL) {
         wfree_2d (m, i);
         return NULL;
      }
      for (j = 0; j < dim_2; j++) m[i][j] = init_dato;
   }
   return m;
}

void
wfree_2d (dato_t **m, int dim_1) {
   int i;
   
   if (m == NULL) return;
   for (i = 0; i < dim_1; i++) {
      if (m[i] != NULL) {
         free (m[i]);
         m[i] = NULL;
      }
   }
   free (m);
   
   return;
}

dato_t** 
wread_matrix(dato_t **m, FILE *fp, int dim_1, int dim_2, dato_t init_dato) {
   int i, j;
   
   if ((fp == NULL) || (m == NULL)) return m;
   
   for (i = 0; i < dim_1; i++) { 
      for (j = 0; j < dim_2; j++) {
         if ((data_read(fp, &m[i][j])) == DATA_ERROR)
            m[i][j] = init_dato;
      }
   }
   return m;
}

void 
wprint_2d (dato_t **m, int dim_1, int dim_2, FILE *fp) {
   int i, j;
   
   if (fp == NULL) return;
   for (i = 0; i < dim_1; i++) {
      for (j = 0; j < dim_2; j++)
         data_print(fp, m[i][j]);
      fputc ('\n', fp);
   }
   fputc ('\n', fp);
   return;
}

dato_t*
wread_array(void) {
   FILE *fp = wfopen_r();
   int i = 0, dim = wreturn_dim_array(fp);
   dato_t *array = NULL;
   
   if (dim < 1) return NULL;
   array = malloc(dim * sizeof(*array));
   if (array == NULL) return NULL;
   while (((fscanf (fp, "%d", &array[i])) != EOF) && i < dim) i++;
   
   return array;
}

int
wreturn_dim_array(FILE *fp) {
   int dim = 0, val;
   if (fp == NULL) return 0;
   while ((fscanf (fp, "%d", &val)) != EOF) dim++;
   rewind (fp);
   return dim;
}

