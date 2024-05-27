#include <stdio.h>
#include "bib1.h"
#include "bib2.h"
#include "bib3.h"
#include "bib4.h"
#include "bib5.h"


int nod_inaltime(AVL* root)  //functie pentru aflarea inaltimii unui nod, din curs
{
    if (root == NULL)
        return -1;
    else
        return root -> inaltime;
}


int max(int a, int b) //aceasta functie determina maximul dintre 2 noduri, din curs
{
    return ((a > b) ? a : b);
}


AVL* left_rotation(AVL* z) //din curs
{
    AVL* y = z -> right;
    AVL* T2 = y -> left;
    y -> left = z;
    z -> right = T2;
    z -> inaltime = max(nod_inaltime(z -> left), nod_inaltime(z -> right)) + 1;
    y -> inaltime = max(nod_inaltime(y -> left), nod_inaltime(y -> right)) + 1;
    return y;
}


AVL* right_rotation(AVL* z) //din curs
{
    AVL* y = z -> left;
    AVL* T3 = y -> right;
    y -> right = z; //roteste
    z -> left = T3;
    z -> inaltime = max(nod_inaltime(z -> left), nod_inaltime(z -> right)) + 1; //modifica inaltimile pentru z si y
    y -> inaltime = max(nod_inaltime(y -> left), nod_inaltime(y -> right)) + 1;
    return y;
}


AVL* LR_rotation(AVL *z) //din curs
{
    z -> left = left_rotation(z -> left);
    return right_rotation(z);
}


AVL* RL_rotation(AVL *z) //din curs
{
    z -> right = right_rotation(z -> right);
    return left_rotation(z);
}


AVL* inserare(AVL* nod, team* key) //functie care "construieste" arborele, din curs
{
    if (nod == NULL) //daca arborele este gol, il creez
    {
        nod = (AVL*) malloc (sizeof(AVL));
        nod -> val = *key;
        nod -> inaltime = 0;
        nod -> left = nod -> right = NULL;
        return nod;
    }
    if (key -> total_points < nod -> val.total_points)  //daca este mai mic
        nod -> left = inserare(nod -> left, key);
    else if (key -> total_points > nod -> val.total_points)
        nod -> right = inserare(nod -> right, key);
    else if (key -> total_points == nod -> val.total_points) //in cazul in care sunt egale le comparam dupa nume
        {
            if (strcmp(key -> team_name, nod -> val.team_name) < 0)
                nod -> left = inserare(nod -> left, key);
            else if (strcmp(key -> team_name, nod -> val.team_name) > 0)
                nod -> right = inserare(nod -> right, key);
        }
    nod -> inaltime = 1 + max(nod_inaltime(nod -> left), nod_inaltime(nod -> right)); //determin inaltimea unui nod
    int k = (nod_inaltime(nod -> left) - nod_inaltime(nod -> right));
    if ((k > 1) && (key -> total_points < (nod -> left) -> val.total_points))
        return right_rotation(nod);
    if ((k > 1) && (key -> total_points == (nod -> left) -> val.total_points))
    {
        if (strcmp(key -> team_name, (nod -> left) -> val.team_name) < 0)
            return right_rotation(nod);
    }
    if ((k < -1) && (key -> total_points > (nod -> right) -> val.total_points))
        return left_rotation(nod);
    if ((k < -1) && (key -> total_points == (nod -> right) -> val.total_points))
    {
        if (strcmp(key -> team_name, (nod -> right) -> val.team_name) > 0)
            return left_rotation(nod);
    }
    if ((k > 1) && (key -> total_points > (nod -> left) -> val.total_points))
        return LR_rotation(nod);
    if ((k < -1) && (key -> total_points < (nod -> right) -> val.total_points))
        return RL_rotation(nod);
    return nod;
}


void afisare_nivel2(FILE* file, AVL* nod, int level)  //aceasta functie afiseaza echipele de pe nivelul 2 al arborelui
{
    if (nod != NULL)
    {
        level++;  //cresc nivelul pentru ca parcurg arborele
        afisare_nivel2(file, nod -> right, level);
        if (level == 2)
            fprintf(file, "%s\n", nod -> val.team_name);
        afisare_nivel2(file, nod -> left, level);
    }
}


void cerinta5(char* argv, AVL** tree_avl, team* primii_8, team* lista_bst, BST* tree) //aceasta functie rezolva cerinta 5, apeland functiile descrise mai sus
{
    ///printf("merge 5 ");
    FILE* file = fopen(argv, "at");
    if (file == NULL)
        eroare_file();
    fprintf(file, "\nTHE LEVEL 2 TEAMS ARE: \n");
    while (primii_8 != NULL)
    {
        tree = insert(tree, *primii_8);
        primii_8 = primii_8 -> next;
    }
    BST_lista(tree, &lista_bst);  //fac din BST de la exerciul 4, o lista
    /*team* current = lista_bst;
    while (current != NULL)
    {
        printf("%s %.2f\n", current -> team_name, current -> total_points);
        current = current -> next;
    }*/
    while (lista_bst != NULL)  //introduc lista creata din BST in arborele AVL si dupa fac afisarea echipelor de pe nuvelul 2, conform cerintei
    {
        *tree_avl = inserare(*tree_avl, lista_bst);
        lista_bst = lista_bst -> next;
    }
    afisare_nivel2(file, *tree_avl, -1);  //aici incep de pe nivelul -1 pentru ca inca nu am intrat in arbore AVL
    fclose(file);
}
