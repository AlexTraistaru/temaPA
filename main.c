#include <stdio.h>
#include <stdlib.h>
#include "bib1.h"


int main(int argc, char *argv[])
{
    FILE *file1 = fopen(argv[2], "rt");
    if (file1 == NULL)
        eroare_file();


    FILE *file2 = fopen(argv[3], "wt");
    if (file2 == NULL)
        eroare_file();


    int nr_echipe;
    team** lista = creare_lista(file1, &nr_echipe);


    cerinta1(file2, lista, nr_echipe);


    fclose(file1);
    fclose(file2);
    int i;
    //printf("citirea s a facut cu succes! nr_echipe=%d", nr_echipe);
    for (i = 0; i < nr_echipe; i++)
        free(lista[i]);
    free(lista);
    return 0;
}
