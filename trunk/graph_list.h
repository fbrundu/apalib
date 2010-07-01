#ifndef _GRAPH_INCLUDED
#define _GRAPH_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "dato_int.h"

typedef struct _GRAPH *graph_t;
typedef struct _EDGE *edge_t;

extern graph_t graph_init(void);
extern graph_t graph_read(FILE*,graph_t);
extern graph_t g_insert_n(graph_t,dato_t);
extern graph_t g_insert_e(graph_t,dato_t,dato_t);
extern int g_search_n(graph_t,dato_t);
extern int g_search_e(graph_t,dato_t,dato_t);
extern graph_t g_delete_n(graph_t,dato_t);
extern graph_t g_delete_e(graph_t,dato_t,dato_t);
extern void graph_print(FILE*,graph_t);
extern graph_t graph_dfs(graph_t,dato_t);
extern graph_t graph_bfs(graph_t,dato_t);
extern graph_t graph_reverse(graph_t);

#endif
