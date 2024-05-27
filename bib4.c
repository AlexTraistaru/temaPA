#include <stdio.h>
#include "bib1.h"
#include "bib2.h"
#include "bib3.h"
#include "bib4.h"


BST* create(team aux) //aceasta functie creeaza arborele
{
    BST* nou = (BST*) malloc (sizeof(BST));
    if (nou == NULL)
        eroare_aloc();
    nou -> val = aux;
    nou -> left = nou -> right = NULL;
    return nou;
}


BST* insert(BST* nod, team aux) //aceasta functie introduce elementele in arbore respectand conditia unui arbore BST
{
    if (nod == NULL)
        return create(aux);
    if (aux.total_points < nod -> val.total_points) //elementele mai mici ca parintele merg in stanga
        nod -> left = insert(nod -> left, aux);
    else if (aux.total_points > nod -> val.total_points) //iar cele mai mari ca parintele merg in dreapta
        nod -> right = insert(nod -> right, aux);
    else if (strcmp(aux.team_name, nod -> val.team_name) < 0)  //daca si el si parintele lui sunt egali ca punctae le compar dupa nume si procedez la fel si cu numele ca la punctaj
        nod -> left = insert(nod -> left, aux);
        else
            nod -> right = insert(nod -> right, aux);
    return nod;
}


void free_BST(BST* root) //aceasta functie elibereaza tot arborele
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


void afisare_BST(FILE* file, BST* root)  //aceasta functie afiseaza arborele BST
{
	if(root != NULL)
    {
        afisare_BST(file, root -> right);
        fprintf(file, "%-34s-  %.2f\n", root -> val.team_name, root -> val.total_points);
        afisare_BST(file, root -> left);
	}
}


team* echipa(BST* root) //aceasta functie este foosita pentru a "copia" arborele BST creat anterior intr o lista pe care o sa o folosesc la cerinta5
{
    team* nou = (team*) malloc(sizeof(team));
    if (nou == NULL)
        eroare_aloc();
    nou -> total_points = root -> val.total_points;
    nou -> team_name = strdup(root -> val.team_name);
    nou -> next = NULL;
    return nou;
}


void BST_lista(BST* root, team** head) //aceasta functie creeaza acea lista, de mai sus
{
    if (root != NULL)
    {
        BST_lista(root -> left, head); //inordine
        team* nou = echipa(root);
        nou -> next = *head;
        *head = nou;
        BST_lista(root -> right, head);
    }
}


void cerinta4(char* argv, team* primii_8, BST* tree)  //aceasta functie rezolva cerinta 4, apeland functiile descrise mai sus
{
    ///printf("merge 4 ");
    FILE *file = fopen(argv, "at");
    if (file == NULL)
        eroare_file();
    fprintf(file, "\nTOP 8 TEAMS:\n");
    while (primii_8 != NULL) //introduc primii_8 in arborele BST
    {
        tree = insert(tree, *primii_8);
        primii_8 = primii_8 -> next;
    }
    afisare_BST(file, tree); //dupa ce am creeat arborele, il afisez
    fclose(file);
}
