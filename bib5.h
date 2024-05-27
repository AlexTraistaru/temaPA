#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct AVL  //structura pentru un nod din arbore AVL
{
    int inaltime;
    team val; //datele efective memorate
    struct AVL* left;//legaturi subarbori
    struct AVL* right;
};
typedef struct AVL AVL;


int nod_inaltime(AVL* root);
int max(int a, int b);
AVL* left_rotation(AVL* z);
AVL* right_rotation(AVL* z);
AVL* LR_rotation(AVL* z);
AVL* RL_rotation(AVL* z);
AVL* inserare(AVL* nod, team* key);
void cerinta5(char* argv, AVL** tree_avl, team* primii_8, team* lista_bst, BST* tree);
void afisare_nivel2(FILE* file, AVL* nod, int level);
