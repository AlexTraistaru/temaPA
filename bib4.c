#include <stdio.h>
#include "bib1.h"
#include "bib2.h"
#include "bib3.h"
#include "bib4.h"


BST* create(team aux)
{
    BST* nou = (BST*) malloc (sizeof(BST));
    if (nou == NULL)
        eroare_aloc();
    nou -> val = aux;
    nou -> left = nou -> right = NULL;
    return nou;
}


BST* insert(BST* nod, team aux)
{
    if (nod == NULL)
        return create(aux);
    if (aux.total_points < nod -> val.total_points)
        nod -> left = insert(nod -> left, aux);
    else if (aux.total_points > nod -> val.total_points)
        nod -> right = insert(nod -> right, aux);
    else if (strcmp(aux.team_name, nod -> val.team_name) < 0)
        nod -> left = insert(nod -> left, aux);
        else
            nod -> right = insert(nod -> right, aux);
    return nod;
}


void free_BST(BST* root)
{
    if (root == NULL)
        return;
    free_BST(root -> left);
    free_BST(root -> right);
    free(root -> val.team_name);
    free(root -> val.val.firstName);
    free(root -> val.val.secondName);
    free(root);
}


void afisare_BST(FILE* file, BST* root)
{
	if(root != NULL)
    {
        afisare_BST(file, root -> right);
        fprintf(file, "%-34s-  %.2f\n", root -> val.team_name, root -> val.total_points);
        afisare_BST(file, root -> left);
	}
}


void cerinta4(char* argv, team* primii_8, BST* tree)
{
    printf("merge 4");
    FILE *file = fopen(argv, "at");
    if (file == NULL)
        eroare_file();
    fprintf(file, "\nTOP 8 TEAMS:\n");
    while (primii_8 != NULL)
    {
        tree = insert(tree, *primii_8);
        primii_8 = primii_8 -> next;
    }
    afisare_BST(file, tree);
    free(primii_8);
    fclose(file);
}
