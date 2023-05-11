#include <malloc.h>
#include <limits.h>
#include <string.h>
#include "lab5-q2.h"
#include "stdio.h"
#define MAX_OUTPUT_SIZE 1000000
void tree_init(BTree **T, int key, double value, int max_size) {
    *T = (BTree*)malloc(sizeof(BTree));
    (*T)->key = (int*)malloc(sizeof(int) * max_size);
    (*T)->value = (double*)malloc(sizeof(double) * max_size);
    (*T)->max_size = max_size;
    (*T)->key[0] = key;
    (*T)->value[0] = value;
    int i;
    for (i = 1; i < max_size; i++) {
        (*T)->key[i] = INT_MAX;
        (*T)->value[i] = -2100.0;
    }
}

void tree_init_with_array(BTree **T, int *key, double *value, int n, int max_size) {
    *T = (BTree*)malloc(sizeof(BTree));
    (*T)->key = (int*)malloc(sizeof(int) * max_size);
    (*T)->value = (double*)malloc(sizeof(double) * max_size);
    (*T)->max_size = max_size;
    for (int i = 0; i < max_size; i++) {
        (*T)->key[i] = INT_MAX;
        (*T)->value[i] = -2100.0;
    }
    for (int i = 0; i < n; i++) {
        (*T)->key[i] = key[i];
        (*T)->value[i] = value[i];
    }
}

void tree_init_with_height(BTree **T, int height) {
    *T = (BTree*)malloc(sizeof(BTree));
    int max_size = (1 << (height+1)) - 1;
    (*T)->key = (int*)malloc(sizeof(int) * max_size);
    (*T)->value = (double*)malloc(sizeof(double) * max_size);
    (*T)->max_size = max_size;
    int i;
    for (i = 0; i < max_size; i++) {
        (*T)->key[i] = INT_MAX;
        (*T)->value[i] = -2100.0;
    }
}

int tree_parent(BTree *T, int child_index) {
    if(child_index<=0||child_index>=T->max_size)
        return -2100;
    int ans=(child_index - 1) / 2;
    if(ans<0||ans>=T->max_size)
        return -2100;
    if(T->key[ans]==INT_MAX)
        return -2100;
    return ans;
}

int tree_lchild(BTree *T, int parent_index) {
    if(parent_index<0||parent_index>=T->max_size)
        return -2100;
    int ans=parent_index * 2 + 1;
    if(ans<=0||ans>=T->max_size)
        return -2100;
    if(T->key[ans]==INT_MAX)
        return -2100;
    return ans;
}

int tree_rchild(BTree *T, int parent_index) {
    if(parent_index<0||parent_index>=T->max_size)
        return -2100;
    int ans=parent_index * 2 + 2;
    if(ans<=0||ans>=T->max_size)
        return -2100;
    if(T->key[ans]==INT_MAX)
        return -2100;
    return ans;
}

void tree_insert_lchild(BTree *T, int parent_index, int key, double value) {
    for (int i = 0; i < T->max_size; i++) {
        if (T->key[i] == key) {
            T->value[i] = value;
        }
    }
    if (parent_index < 0 || parent_index >= T->max_size) {
        return;
    }
    if(tree_lchild(T, parent_index)!=-2100)
        return;
    int child_index =2* parent_index+1;
    if (child_index >= T->max_size||child_index<0) {
        return;
    }
    T->key[child_index] = key;
    T->value[child_index] = value;
}

void tree_insert_rchild(BTree *T, int parent_index, int key, double value) {
    for (int i = 0; i < T->max_size; i++) {
        if (T->key[i] == key) {
            T->value[i] = value;
        }
    }
    if (parent_index < 0 || parent_index >= T->max_size) {
        return;
    }
    if(tree_rchild(T, parent_index)!=-2100)
        return;
    int child_index =2* parent_index+2;
    if (child_index >= T->max_size||child_index<0) {
        return;
    }
    T->key[child_index] = key;
    T->value[child_index] = value;
}

double tree_key_find(BTree *T, int key) {
    for (int i = 0; i < T->max_size; i++) {
        if (T->key[i] == key) {
            return T->value[i];
        }
    }
    return -2100;
}

// Returns the value associated with the node at the given index.
double tree_index_find(BTree *T, int index) {
    if (index >= T->max_size||index<0||T->key[index]==INT_MAX) {
        return -2100; // Return a default value if index is out of bounds.
    }
    return T->value[index];
}

// Frees the memory allocated for the tree.
void tree_free(BTree **T) {
    free((*T)->key);
    free((*T)->value);
    free(*T);
    *T = NULL;
}

void tree_postorder_print(BTree *T, int index, char *output) {
    if (index<0) {
        return;
    }
    tree_postorder_print(T, tree_lchild(T, index), output); // traverse left subtree
    tree_postorder_print(T, tree_rchild(T, index), output); // traverse right subtree
    sprintf(output, "%s(%d)%.2f ",output, T->key[index], T->value[index]);
}
char *tree_print(BTree *T) {
    char *output = malloc(MAX_OUTPUT_SIZE * sizeof(char));
    tree_postorder_print(T, 0, output);
    return output;
}