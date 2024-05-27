#include <stdio.h>
#include "bib1.h"
#include "bib2.h"
#include "bib3.h"
#include "bib4.h"
#include "bib5.h"


int main(int argc, char *argv[])
{
    int i;
    FILE* file = fopen(argv[1], "rt");
    if (file == NULL)
        eroare_file();


    int nr_echipe;
    team** lista = creare_lista(argv[2], &nr_echipe);


    int cerinte[5];  //cerinte este legat de fisierul c.in, unde ni se soun ce exercitii trebuie sa rezolvam
    for (i = 0; i < 5; i++) ///i < 5 pentru ca avem 5 cerinte de facut
        fscanf(file, "%d", &cerinte[i]);


    if (cerinte[0] == 1)
    {
        //printf("1 ");
        cerinta1(argv[3], lista, nr_echipe);
    }


    if (cerinte[1] == 1)
    {
        //printf("2 ");
        cerinta2(argv[3], lista, &nr_echipe);
    }


    team* primii_8 = NULL;
    if (cerinte[2] == 1)
    {
        //printf("3 ");
        cerinta3(argv[3], lista, nr_echipe, &primii_8);
    }


    BST* tree = NULL;
    if (cerinte[3] == 1)
    {
        //printf("4 ");
        cerinta4(argv[3], primii_8, tree);
    }


    AVL* tree_avl = NULL;
    team* lista_bst = NULL;
    if (cerinte[4] == 1)
    {
        //printf("5 ");
        cerinta5(argv[3], &tree_avl, primii_8, lista_bst, tree);
    }


    fclose(file);


    //printf("citirea s a facut cu succes! nr_echipe=%d", nr_echipe);
    for (i = 0; i < nr_echipe; i++)
        free(lista[i]);
    free(lista);
    return 0;
}
