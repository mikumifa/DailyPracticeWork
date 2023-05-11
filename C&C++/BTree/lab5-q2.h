/* lab5-q2.h */
/* Cannot modify this file */

/* Binary tree data structure with array implementation */
/* The first element is stored in (key[0], value[0]) */
/* If key is unused, set key = INT_MAX, value = -2100 */
typedef struct _btree{
    int *key;      /* An array of keys for the nodes */
    double *value; /* An array of values for the nodes */
    int max_size;  /* The max number of nodes */
} BTree;

/* Initialize the tree with a root #1 */
/* Create an empty BTree first */
/* The root (key, value) is stored at (key[0], value[0]) */
/* If key is unused, set key = INT_MAX, value = -2100 */
void tree_init(BTree **T, int key, double value, int max_size);

/* Initialize the tree with arrays #2 */
/* Create an empty BTree first */
/* n defines the number of (key,value) pairs of the array */
/* If key is unused, set key = INT_MAX, value = -2100 */
void tree_init_with_array(BTree **T, int *key, double *value, int n, int max_size);

/* Initialize the empty tree with height of root #3 */
/* Based on the height, calculate the max_size */
/* Create an empty BTree with max_size */
/* If key is unused, set key = INT_MAX, value = -2100 */
void tree_init_with_height(BTree **T, int height);

/* Get the index of parent #4 */
/* Return the index of the parent */
/* Return -2100 if the parent index is invalid or unused */
int tree_parent(BTree *T, int child_index);

/* Get the index of left child #5 */
/* Return the index of the left child */
/* Return -2100 if the left child index is invalid or unused */
int tree_lchild(BTree *T, int parent_index);

/* Get the index of right child #6 */
/* Return the index of the right child */
/* Return -2100 if the right child index is invalid or unused */
int tree_rchild(BTree *T, int parent_index);

/* Insert or update a node #7 */
/* If key exists in T, update the value */
/* If key not in T, insert (key, double) as left child of parent_index*/
/* If the left child cannot be inserted, then do nothing */
/* If the left child is used by other key, then do nothing */
void tree_insert_lchild(BTree *T, int parent_index, int key, double value);

/* Insert or update a node #8 */
/* If key exists in T, update the value */
/* If key not in T, insert (key,double) as right child of parent_index*/
/* If the right child cannot be inserted, then do nothing */
/* If the right child is used by other key, then do nothing */
void tree_insert_rchild(BTree *T, int parent_index, int key, double value);

/* Find the value based on the key in the tree T or not #9 */
/* If key in T, return the corresponding value */
/* If key not in T, return -2100.00 */
double tree_key_find(BTree *T, int key);

/* Find the value based on the index in the tree T or not #10 */
/* If index is used, return the corresponding value */
/* If index is unused or exceeding the max_size, return -2100.00 */
double tree_index_find(BTree *T, int index);

/* Free the tree *T, if *T is not NULL #11 */
/* Assign NULL to *T after free */
void tree_free(BTree **T);

/* The print function print the tree in an output string using postorder traversal #12 */
/* The number in the bracket is key, number after bracket is value */
/* If the tree looks like */
/* (0)1.7 */
/* |       \ */
/* (1)1.2  (2)1.8  */
/* |        |     \ */
/* (4)0    (3)2   (6)5 */
/* Then, the output string is "(4)0.00 (1)1.20 (3)2.00 (6)5.00 (2)1.80 (0)1.70 " */
/* You can assume the number of nodes is not more than 100 */
char *tree_print(BTree *T);
