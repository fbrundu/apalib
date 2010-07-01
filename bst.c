 /***************************************************************************
 *            bst.c
 *
 *  Tue May 20 13:55:48 2008
 *  Francesco Brundu
 *  francesco.brundu@studenti.polito.it
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "dato.h"
#include "bst.h"

/********************************************************************
  Structures' definition
********************************************************************/
typedef struct nodo *nodo_t;
struct nodo {
   dato_t val; // node's value, dato_t type defined in dato.h
   int     age; // age of node, 1 if node is the first, total number of nodes if last 
   nodo_t left; // pointer to the node's left son
   nodo_t right; // pointer to the node's right son
};

struct BST {
   nodo_t root; // pointer to the first node of the bst
   int max_age; // maximum age for a node
   int num_nodes; // total number of nodes
};

/********************************************************************
  Declaration of static functions 
********************************************************************/
static nodo_t node_alloc(dato_t d, int age); // allocs a node 
static nodo_t tree_insert(nodo_t rp, dato_t d, int age); // insert node in the bst
static nodo_t tree_remove(nodo_t rp, dato_t din, dato_t *dout); // remove node from bst
static dato_t delete_max(nodo_t *rpp, int *age_ptr); // delete node with maximum age
static dato_t tree_min(nodo_t rp); // return pointer of data with minumum value
static dato_t tree_max(nodo_t rp); // return pointer of data with maximum value
static dato_t tree_successor(nodo_t rp, dato_t din, int *found); // return pointer of successor of a data
static dato_t tree_predecessor(nodo_t rp, dato_t din, int *found); // return pointer of predecessor of a data
static nodo_t tree_oldest(nodo_t rp, nodo_t old); // return pointer of oldest node
static nodo_t tree_youngest(nodo_t rp, nodo_t young); // return pointer of youngest node
static void tree_print(nodo_t rp, FILE *fp, int way); // print node list in a specified way [pre|in|post] order
static void tree_free(nodo_t rp); // free and delete tree
static void tree_depth(nodo_t rp, int *m, int *M, int depth); // return tree depth

/********************************************************************
  Extern functions' definition (can be used by main)
********************************************************************/

/*** Allocs a new BST (empty) ***************************/
BST_t
bst_alloc(void) {
   BST_t p;
   p = malloc(sizeof(*p));
   if (p == NULL) {
      printf("bst_alloc: Error while trying to allocate memory\n");
      exit(1);
   }
   p->root = NULL;
   p->max_age = 0;
   p->num_nodes = 0;
   return p;
}

/*** Test if the BST is empty ****************************/
int 
bst_is_empty(BST_t tree) {
   return ((tree == NULL) || (tree->num_nodes == 0));
}

/*** Search data in a BST ************************************/
dato_t
bst_search(BST_t tree, dato_t d) {
   nodo_t rp = tree->root;
   while (rp != NULL) {
      if (data_compare(d, rp->val, 1) == 0)
	      return rp->val;
      if (data_compare(d, rp->val, 1) < 0)
	      rp = rp->left;
      else rp = rp->right;
   }
   return NULLdato;
}

/*** Insert data in a BST *********************************/
void 
bst_insert(BST_t tree dato_t d) {
   tree->root = tree_insert(tree->root, d, (tree->max_age)++);
   (tree->num_nodes)++;
}

/*** Extract data from BST *********************************/
dato_t
bst_remove(BST_t tree, dato_t d) {
   dato_t dout;
   tree->root = tree_remove(tree->root, d, &dout);
   if (dout != NULL) (tree->num_nodes)--;
   return dout;
}

/*** Search minimum value in a BST ********************/
dato_t
bst_min(BST_t tree) {
   if (tree->root != NULL) return tree_min(tree->root);
   return NULL;
}

/*** Search maximum value in a BST *******************/
dato_t
bst_max(BST_t tree) {
   if (tree->root != NULL)
      return tree_max(tree->root);
   return NULL;
}

/*** Search successor of a data in a BST *****************************/
dato_t 
bst_successor(BST_t tree, dato_t d) {
   int found_key = 0;
   return tree_successor(tree->root, d, &found_key);
}

/*** Search predecessor of a data in a BST ***************************/
dato_t
bst_predecessor(BST_t tree, dato_t d) {
   int found_key = 0;
   return tree_predecessor(tree->root, d, &found_key);
}

/*** Search "most ancient" value present in a BST *************/
dato_t
bst_oldest(BST_t tree) {
   nodo_t old = tree_oldest(tree->root, tree->root);
   if (old != NULL) return old->val;
   return NULL;
}

/*** Search "most recent" value present in a BST ************/
dato_t
bst_youngest(BST_t tree) {
   nodo_t young = tree_youngest(tree->root, tree->root);
   if (young != NULL) return young->val;
   return NULL;
}

/*** Print all data of given BST *****************/
void 
bst_print(BST_t tree, FILE *fp, int way) {
   tree_print(tree->root, fp, way);
}

/*** Read new BST (from a file) *****************************/
BST_t
bst_read(FILE *fp) {
   BST_t tree;
   dato_t d;
   tree = bst_alloc();
   while ((data_read(fp, &d)) != DATA_ERROR)
      bst_insert(tree, d);
   return tree;
}

/*** Calculate minima and maximum depth ********************/
int 
bst_depth(BST_t tree, int *m, int *M) {
   int min = -1, max = -1;
   if (tree->num_nodes == 0) {
      (*m) = (*M) = -1;
      return 0;
   }
   tree_depth(tree->root, &min, &max, 0);
   (*m) = min;
   (*M) = max;
   return tree->num_nodes;
}

/*** Free a BST ***************************************/
void 
bst_free(BST_t tree) {
   tree_free(tree->root);
   free(tree);
}

/********************************************************************
  Static functions' definition (used ONLY within the library)
********************************************************************/

/*** Allocs a new node for a BST **************************/
static nodo_t
node_alloc(dato_t d, int age) {
   nodo_t ptr;
   ptr = malloc(sizeof(*ptr));
   if (ptr == NULL) {
      printf("node_alloc: Error while trying to allocate memory\n");
      exit(1);
   }
   ptr->val = d;
   ptr->age = age;
   ptr->left = ptr->right = NULL;
   return ptr;
}

/*** Insert data in a BST (recursive function) ************/
static nodo_t
tree_insert(nodo_t rp, dato_t d, int age) {
   nodo_t ptr;
   if (rp == NULL) {
      ptr = node_alloc(d, age);
      return ptr;
   }
   if (data_compare(d, rp->val, 1) == 0) /* BST allows ONLY one node for the specified data value */
      return rp;
   if (data_compare(d, rp->val, 1) < 0)
      rp->left = tree_insert(rp->left, d, age);
   else rp->right = tree_insert(rp->right, d, age);
   return rp;
}

/*** Estract data from a BST (recursive function) ************/
static nodo_t
tree_remove(nodo_t rp, dato_t din, dato_t *dout) {
   nodo_t ptr;
   /* empty tree */
   if (rp == NULL) {
      (*dout) = NULL;
      return rp;
   }
   if (data_compare(din, rp->val, 1) < 0) {
      /* delete left */
      rp->left = tree_remove(rp->left, din, dout);
      return rp;
   }
   if (data_compare(din, rp->val, 1) > 0) {
      /* delete right */
      rp->right = tree_remove(rp->right, din, dout);
      return rp;
   }
   /* delete current node */
   (*dout) = rp->val;
   ptr = rp;
   if (rp->right == NULL) {
      /* no right sub-tree: return the left sub-tree */
      rp = rp->left;
      free(ptr);
      return rp;
   }
   if (rp->left == NULL) {
      /* no left sub-tree: return the right sub-tree */
      rp = rp->right;
      free(ptr);
      return rp;
   }
   /* remove the predecessor */
   rp->val = delete_max(&rp->left, &rp->age);
   return rp;
}

/*** Delete maximum value present in a (sub-)tree **/
static dato_t
delete_max(nodo_t *rpp, int *age_ptr) {
   nodo_t ptr;
   dato_t d;
   /* search the max value node */
   while ((*rpp)->right != NULL)
      rpp = &((*rpp)->right);
   ptr = (*rpp);
   d = ptr->val;
   (*age_ptr) = ptr->age;
   (*rpp) = (*rpp)->left;
   free(ptr);
   return d;
}

/*** Search minimum value present in a BST (recursive function) **/   
static dato_t
tree_min(nodo_t rp) {
   if (rp->left == NULL) return rp->val;
   return tree_min(rp->left);
}

/*** Search maximum value present in a BST (recursive function) */   
static dato_t
tree_max(nodo_t rp) {
   if (rp->right == NULL) return rp->val;
   return tree_max(rp->right);
}

/*** Search "most ancient" value present in a BST *************/
static nodo_t
tree_oldest(nodo_t rp, nodo_t old) {
   if (rp == NULL) return old;
   if (rp->age < old->age) old = rp;
   old = tree_oldest(rp->left, old);
   old = tree_oldest(rp->right, old);
   return old;
}

/*** Search "most recent" value present in a BST ************/
static nodo_t
tree_youngest(nodo_t rp, nodo_t young) {
   if (rp == NULL) return young;
   if (rp->age > young->age) young = rp;
   young = tree_youngest(rp->left, young);
   young = tree_youngest(rp->right, young);
   return young;
}

/*** Print all datas contained in a BST ***************/
static void 
tree_print(nodo_t rp, FILE *fp, int way) {
   if (rp == NULL) return;
   if (way == PREORDER) data_print(fp, rp->val);
   tree_print(rp->left, fp, way);
   if (way == INORDER) data_print(fp, rp->val);
   tree_print(rp->right, fp, way);
   if (way == POSTORDER) data_print(fp, rp->val);
}

/*** Free a BST ***************************************/
static void 
tree_free(nodo_t rp) {
   if (rp == NULL) return;
   tree_free(rp->left);
   tree_free(rp->right);
   data_free(rp->val);
   free(rp);
}

/*** Calculate minimum and maximum depth of a BST (recursive function) ********/
static void 
tree_depth(nodo_t rp, int *m, int *M, int depth) {
   if (rp->left==NULL && rp->right==NULL) {
      if (((*m) < 0) || (depth < (*m))) (*m) = depth;
      if (depth > (*M)) (*M) = depth;
      return;
   }
   if (rp->left != NULL) tree_depth(rp->left, m, M, depth + 1);
   if (rp->right != NULL) tree_depth(rp->right, m, M, depth + 1);
}

/*** Search successor of specified data *****************************/
static dato_t
tree_successor(nodo_t rp, dato_t din, int *found) {
   dato_t dout = NULL;
   if (rp == NULL) return NULL;
   if (data_compare(din, rp->val, 1) < 0) {
      dout = tree_successor(rp->left, din, found);
      if ((dout == NULL) && ((*found) == 1)) return rp->val;
      return dout;
   }
   if (data_compare(din, rp->val, 1) > 0)
      return tree_successor(rp->right, din, found);
   (*found) = 1;
   if (rp->right != NULL) return tree_min(rp->right);
   return NULL;
}

/*** Search predecessor of specified data ***************************/
static dato_t
tree_predecessor(nodo_t rp, dato_t din, int *found) {
   dato_t dout = NULL;
   if (rp == NULL) return NULL;
   if (data_compare(din, rp->val, 1) > 0) {
      dout = tree_predecessor(rp->right, din, found);
      if ((dout == NULL) && ((*found) == 1))
	     return rp->val;
      return dout;
   }
   if (data_compare(din, rp->val, 1) < 0)
      return tree_predecessor(rp->left, din, found);
   (*found) = 1;
   if (rp->left != NULL) return tree_max(rp->left);
   return NULL;
}
