#include"lab5-q2.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<math.h>

int main(int argc, char *argv[]){

    FILE *fout;
    BTree *T;
    int isCorrect, i;
    fout = fopen(argv[1], "w");
    /* default, your program is correct */
    isCorrect = 1;

    /* check the function, tree_init() */
    T = NULL;
    tree_init(&T,0,0.0,100);
    tree_insert_lchild(T,0,1,1.2);
    tree_insert_lchild(T,1,4,0);

    tree_insert_rchild(T,0,2,1.8);
    tree_insert_rchild(T,2,6,5);

    tree_insert_lchild(T,2,3,2);
    fprintf(fout, "%s\n", tree_print(T));
    tree_insert_lchild(T,0,12,1.34);
    fprintf(fout, "%s\n", tree_print(T));
    /* output "Correct" if the tree_init() is correctly implemented */
    if (isCorrect == 1) {
        fprintf(fout, "Tree: Correct\n");
    } else {
        fprintf(fout, "Tree: Wrong Answer\n");
    }
    fclose(fout);

    return 0;
}
