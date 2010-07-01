 /***************************************************************************
 *            bst.h
 *
 *  Tue May 20 14:03:28 2008
 *  Francesco Brundu
 *  francesco.brundu@studenti.polito.it
 ****************************************************************************/
 
#ifndef _BST_INCLUDED
#define _BST_INCLUDED

#define PREORDER  -1
#define INORDER    0
#define POSTORDER  1

typedef struct BST *BST_t;

extern BST_t bst_alloc(void);
extern int bst_is_empty(BST_t);
extern dato_t bst_search(BST_t, dato_t);
extern void bst_insert(BST_t, dato_t);
extern dato_t bst_remove(BST_t, dato_t);
extern dato_t bst_min(BST_t);
extern dato_t bst_max(BST_t);
extern dato_t bst_successor(BST_t, dato_t);
extern dato_t bst_predecessor(BST_t, dato_t);
// third argument: PREORDER, INORDER,POSTORDER
extern void bst_print(BST_t, FILE*, int);
extern BST_t bst_read(FILE*);
extern void bst_free(BST_t);
extern dato_t bst_oldest(BST_t);
extern dato_t bst_youngest(BST_t);
// second argument: min_depth, third argument: max_depth
extern int bst_depth(BST_t, int*, int*);

#endif

