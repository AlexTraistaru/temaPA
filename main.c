#include <stdio.h>
#include "bib1.h"
#include "bib2.h"

int main(int argc, char *argv[])
{
    int i;
    FILE* file1 = fopen(argv[2], "rt");
    if (file1 == NULL)
        eroare_file();


    FILE* file2 = fopen(argv[3], "wt");
    if (file2 == NULL)
        eroare_file();

    FILE* file3 = fopen(argv[1], "rt");
    if (file3 == NULL)
        eroare_file();

    int cerinte[5];
    for (i = 1; i <= 5; i++) ///i <= 5 pentru ca avem 5 cerinte de facut
        fscanf(file3, "%d", &cerinte[i]);


    int nr_echipe;
    team** lista = creare_lista(file1, &nr_echipe);


    if (cerinte[1] == 1)
    {
        if (cerinte[2] == 0)
            cerinta1(file2, lista, nr_echipe);
        else if (cerinte[2] == 1)
                cerinta2(file2, lista, &nr_echipe);
    }


    fclose(file1);
    fclose(file2);
    fclose(file3);


    //printf("citirea s a facut cu succes! nr_echipe=%d", nr_echipe);
    for (i = 0; i < nr_echipe; i++)
        free(lista[i]);
    free(lista);
    return 0;
}
