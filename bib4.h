#include <stdio.h>


struct BST
{
    team val;
    struct BST* left;
    struct BST* right;
};
typedef struct BST BST;


BST*  create(team aux);
BST* insert(BST* nod, team aux);
void free_BST(BST* root);
void cerinta4(char* argv, team* primii_8, BST* tree);
void afisare_BST(FILE* file, BST* root);
