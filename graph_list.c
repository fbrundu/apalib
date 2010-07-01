/*** GRAPH.C ***/
#include "graph_list.h"

#define  NOT_EXPLORED    1
#define  EXPLORED   0
#define  TERMINATED    -1
#define  INF  10000

#define  ERROR_TYPING -1 
#define  NOT_TYPED 0
#define  TREE  1
#define  FORWARD  2
#define  BACKWARD 3
#define  CROSS 4

typedef struct _NODE *node_t;
struct _NODE {
   dato_t d;
   int color;
   int group;
   int distance;
   edge_t l;
   node_t next;
};

struct _GRAPH {
  node_t nodes;
  int v;
};

struct _EDGE {
   node_t n;
   int type;
   edge_t next;
};

static node_t new_node_g(dato_t, edge_t, node_t);
static edge_t new_node_e(node_t, edge_t);
static node_t insert_node_g(node_t, node_t);
static edge_t insert_node_e(edge_t, edge_t);
static node_t search_node_g(node_t, dato_t);
static edge_t search_node_e(edge_t, node_t);
static node_t delete_node_g(node_t, dato_t,node_t*);
static edge_t delete_node_e(edge_t, node_t);
static int deep_visit (node_t,int);
static void breadth_visit (node_t,int);
static void clean_graph(node_t);
static void node_print(FILE*,node_t);
static void edge_print(FILE*,edge_t);
static void print_list_n(FILE*, node_t);
static node_t purge_graph(node_t, node_t);
static edge_t purge_list(edge_t,node_t);

/*** INIT ***/
/***********/
graph_t
graph_init(void) {
  graph_t g = malloc(sizeof(*g));
  if(g==NULL) return NULL;
  g->nodes=NULL;
  g->v=0;
  return g;
}

/*** READ ***/
graph_t
graph_read(FILE *fp,graph_t g) {
  dato_t d1 = malloc(sizeof(*d1)),
              d2 = malloc(sizeof(*d2));
  if(fp==NULL) return g;
  if(g==NULL) g = graph_init();
  while((data_read(fp,&d1)!=DATA_ERROR)
      &&(data_read(fp,&d2)!=DATA_ERROR)) {
    g_insert_e(g,d1,d2);
  }
  return g;
}

/*** PRINT ***/
void
graph_print(FILE *fpout,graph_t g) {
  if(fpout==NULL) fpout = stdout;
  fprintf(fpout, "Grafo in fase di stampa***\n");
  if(g==NULL) {
    fprintf(fpout, "Grafo non inizializzato\n");
    return;
  }
  fprintf(fpout, "Numero nodi presenti: %d\n",g->v);
  if(g->v==0) return;
  node_print(fpout,g->nodes);
}

void
node_print(FILE *fpout,node_t n) {
  if(fpout==NULL) fpout = stdout;
  while(n!=NULL) {
    fprintf(fpout,"Nodo: ");
    data_print(fpout,n->d);
    putchar('\n');
    fprintf(fpout,"Colore: ");
    switch(n->color) {
      case NOT_EXPLORED:
        fprintf(fpout,"BIANCO");
      break;
      case EXPLORED:
        fprintf(fpout,"GRIGIO");
      break;
      case TERMINATED:
        fprintf(fpout,"NERO");
      break;
      default:
        fprintf(fpout,"UNDEFINED");
      break;
    }
    putchar('\n');
    fprintf(fpout,"Distanza: ");
    if(n->distance == INF) fprintf(fpout,"infinita (in caso di visita in ampiezza)");
    else fprintf(fpout,"%d",n->distance);
    putchar('\n');
    fprintf(fpout,"Nodi raggiungibili:\n");
    if((n->l) == NULL) printf("NESSUNO\n");
    edge_print(fpout,n->l);
    n = n->next;
  }
  putchar('\n');
}

void
edge_print(FILE *fpout,edge_t e) {
  if(fpout==NULL) fpout = stdout;
  while(e!=NULL) {
    fprintf(fpout,"* ");
    data_print(fpout,e->n->d);
    putchar('\n');
    fprintf(fpout,"Tipo: ");
    switch(e->type) {
      case TREE:
        fprintf(fpout,"TREE");
      break;
      case FORWARD:
        fprintf(fpout,"FORWARD");
      break;
      case BACKWARD:
        fprintf(fpout,"BACKWARD");
      break;
      case CROSS:
        fprintf(fpout,"CROSS");
      break;
      default:
        fprintf(fpout,"UNDEFINED");
      break;
    }
    putchar('\n');
    e = e->next;
  }
}

void
print_list_n(FILE* fpout, node_t n) {
  if(n==NULL) return;
  if(fpout==NULL) fpout = stdout;
  data_print(fpout,n->d);
  putchar('-');
  print_list_n(fpout,n->next);
}

/*** INSERT ***/
/***********/
graph_t
g_insert_n(graph_t g,dato_t d) {
  node_t n = NULL;
  if((g==NULL)||(d==NULLdato)) return g;
  n = new_node_g(d,NULL,NULL);
  (g->v)++;
  if(g->nodes == NULL) {
    g->nodes = n;
    return g; 
  }
  g->nodes = insert_node_g(g->nodes, n);
  return g;
}

graph_t 
g_insert_e(graph_t g,dato_t sa,dato_t av) {
  dato_t st_d = malloc(sizeof(*st_d)),
              ar_d = malloc(sizeof(*ar_d));  
  node_t s = NULL,
                st = NULL,
                ar = NULL;
  edge_t n = NULL,
                l = NULL;
  st_d = data_copy(st_d,sa);
  ar_d = data_copy(ar_d,av);
  if(g==NULL) return g;
  st = search_node_g(g->nodes,st_d);
  ar = search_node_g(g->nodes,ar_d);
  if(st==NULL) {
    g = g_insert_n(g,st_d);
    st = search_node_g(g->nodes,st_d);
  }
  if(ar==NULL) {
    g = g_insert_n(g,ar_d);
    ar = search_node_g(g->nodes,ar_d);
  }
  if((st==NULL)||(ar==NULL)) return g;
  n = new_node_e(ar,NULL);
  s = g->nodes;
  while(s!=NULL) {
    if(s == st) {
      l = s->l;
      s->l = insert_node_e(l,n);
      return g;
    }
    s = s->next;
  }
  return g;
}

node_t 
new_node_g(dato_t d, edge_t l, node_t next) {
   node_t node = malloc(sizeof(*node));
   if(node==NULL) return NULL;
   node->d = d;
   node->color = NOT_EXPLORED;
   node->group = -1;
   node->distance = INF;
   node->l = l;
   node->next = next;
   return node;
}

edge_t 
new_node_e(node_t n, edge_t next) {
   edge_t node = malloc(sizeof(*node));
   if(node==NULL) return NULL;
   node->n = n;
   node->type = NOT_TYPED;
   node->next = next;
   return node;
}

node_t 
insert_node_g(node_t top, node_t node) {
   node_t s = top;
   if(s==NULL) return node;
   while(s->next!=NULL) s=s->next;
   s->next=node;
   return top;
}

edge_t 
insert_node_e(edge_t top, edge_t node) {
   edge_t s = top;
   if(s==NULL) return node;
   while(s->next!=NULL) s=s->next;
   s->next=node;
   return top;
}

/*** SEARCH  ***/
/***********/
int
g_search_n(graph_t g,dato_t d) {
  if(g==NULL) return 0;
  return (search_node_g(g->nodes,d)!=NULL);
}

node_t 
search_node_g(node_t top, dato_t d) {
   node_t s = top;
   if(s==NULL) return NULL;
   while(s!=NULL) { 
      if(data_compare(s->d,d,DATO_TYPE)==0) {
         return s;
      }
      s=s->next;
   }
   return NULL;
}

int
g_search_e(graph_t g,dato_t st_d,dato_t ar_d) {
  node_t st = NULL;
  node_t ar = NULL;
  if(g==NULL) return 0;
  st = search_node_g(g->nodes,st_d);
  ar = search_node_g(g->nodes,ar_d);
  if((st == NULL) || (ar == NULL)) return 0;
  return (search_node_e(st->l,ar)!=NULL);
}

edge_t 
search_node_e(edge_t top, node_t n) {
   edge_t s = top;
   if(s==NULL) return NULL;
   while(s!=NULL) { 
      if((s->n)==n)
         return s;
      s=s->next;
   }
   return NULL;
}

/*** DELETE ***/
/***********/
graph_t
g_delete_n(graph_t g,dato_t d) {
  node_t trsh = NULL;
  if(g==NULL) return g;
  g->nodes = delete_node_g(g->nodes,d,&trsh);
  if(trsh!=NULL) {
    g->nodes = purge_graph(g->nodes,trsh);
    (g->v)--;
  }
  return g;
}

node_t 
delete_node_g(node_t top, dato_t d,node_t *tr) {
   node_t s = top, pr = NULL;
   if(s==NULL) return NULL;
   if(data_compare(s->d,d,DATO_TYPE)==0) {
      pr=s;
      s=s->next;
      *tr = pr;
      data_free(pr->d);
      free(pr);
      return s;
   }
   while(s!=NULL) { 
      if(data_compare(s->d,d,DATO_TYPE)==0) {
         pr->next=s->next;
         *tr = s;
         data_free(s->d);
         free(s);
         return top;
      }
      pr=s;
      s=s->next;
   }
   return top;
}

graph_t
g_delete_e(graph_t g,dato_t st_d,dato_t ar_d) {
  node_t st = NULL;
  node_t ar = NULL;
  if(g==NULL) return g;
  st = search_node_g(g->nodes,st_d);
  ar = search_node_g(g->nodes,ar_d);
  if((st == NULL) || (ar == NULL)) return g;
  delete_node_e(st->l,ar);
  return g;
}

edge_t 
delete_node_e(edge_t top, node_t n) {
   edge_t s = top, pr = NULL;
   if(s==NULL) return NULL;
   if((s->n)==n) {
      pr=s;
      s=s->next;
      free(pr);
      return s;   
   }
   while(s!=NULL) { 
      if((s->n)==n) {
         pr->next=s->next;
         free(s);
         return top;
      }
      pr=s;   
      s=s->next;
   }
   return top;
}

node_t
purge_graph(node_t n, node_t tr) {
  if(n==NULL) return n;
  n->l = purge_list(n->l,tr);
  purge_graph(n->next,tr);
  return n;
} 

edge_t
purge_list(edge_t l,node_t tr) {
  edge_t temp;
  if(l==NULL) return l;
  if((l->n != tr)&&(l->n != NULL)) 
    l->next = purge_list(l->next,tr);
  else {
    temp = l->next;
    free(l);
    return (temp = purge_list(temp,tr));
  }
  return l;
}

/*** DEEP FIRST VISIT ***/
/***********/
graph_t
graph_dfs(graph_t g,dato_t d) {
  int end = 0,group = 0;
  node_t n = NULL;
  if((g==NULL)||(d==NULL)) return g;
  n = search_node_g(g->nodes,d);
  if(n!=NULL)
    deep_visit(n,group);
  while(!end) {
    end = 1;
    n=g->nodes;
    while(n!=NULL) {
      if(n->color == NOT_EXPLORED) {
        end = 0;
        group++;
        deep_visit(n,group);
      }
      n = n->next;
    }
  }
  graph_print(stdout,g);
  clean_graph(g->nodes);
  return g;
}

int
deep_visit (node_t top,int group) {
  edge_t list = NULL;
  if (top == NULL) return ERROR_TYPING;
  list = top->l;
  if (top->color==TERMINATED) {
    if(top->group != group) return CROSS;
    else return FORWARD;
  }
  if (top->color==EXPLORED) return BACKWARD;
  else {
    top->color=EXPLORED;
    top->group = group;
  }
  while (list != NULL) {
    list->type = deep_visit (list->n,group);
    list = list->next;
  }
  top->color=TERMINATED;
  return TREE;
}

/*** BREADTH FIRST VISIT ***/
/***********/
graph_t
graph_bfs(graph_t g,dato_t d) {
  node_t n = NULL;
  if((g==NULL)||(d==NULL)) return g;
  n = search_node_g(g->nodes,d);
  if(n!=NULL)
    breadth_visit(n,0);
  graph_print(stdout,g);
  clean_graph(g->nodes);
  return g;
}

void
breadth_visit (node_t top, int distance) {
  edge_t list = NULL;
  if(top == NULL) return;
  list = top->l;
  if(top->distance < distance) return;
  top->distance = distance;
  while (list != NULL) {
    if(list->n->distance > distance+1)
      list->n->distance = distance+1;
    list = list->next;
  }
  while (list != NULL) {
    if(!(list->n->distance < distance+1))
      breadth_visit(list->n,distance+1);
    list = list->next;
  } 
}

/*** CLEAN ***/
/***********/
void 
clean_graph(node_t t) {
  while(t!=NULL) {
    t->color = NOT_EXPLORED;
    t->group = -1;
    t = t->next;
  }
}

/*** REVERSE ***/
/***********/
graph_t 
graph_reverse(graph_t g) { 
  node_t s = NULL;
  edge_t l = NULL;
  graph_t r = graph_init();
  if(g==NULL) return g;
  s = g->nodes;
  while(s!=NULL) {
    l = s->l;
    while(l!=NULL) {
      r = g_insert_e(r,l->n->d,s->d);
      l = l->next;
    }
    s = s->next;
  }
  graph_print(stdout,r);
  return r;
}

