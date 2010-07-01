// Example using dato_int.c  
// dato_int.h graph  graph_list.c  graph_list.h

#include <stdio.h>
#include <stdlib.h>
#include "graph_list.h"

int
main(void) {
  char s[12+1];
  FILE *fp = NULL;
  dato_t d = NULL;
  graph_t g = NULL;
  printf("Insert name of the file that contains the graph: ");
  scanf("%s",s);
  fp = fopen(s,"r");
  getc(stdin);
  g = graph_read(fp,g);
  graph_print(stdout,g);
  printf("Insert data name to start bfs: ");
  d = data_one_read();
  printf("Data read: ");
  data_print(stdout,d);
  putchar('\n');
  g = graph_bfs(g,d);
  g = graph_reverse(g);
  printf("Transposed graph is:\n");
  graph_print(stdout,g);
  return 0;
}
