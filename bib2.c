#include <stdio.h>
#include "bib1.h"
#include "bib2.h"


void stergere_echipa_1(team** lista, int* nr_echipe)
{
    int i;
    int gasit = 0;
    int poz = -1; ///poz este indexul echipei pe care vreau sa o sterg
    for (i = 0; i < *nr_echipe; i++)
        if (lista[i] == punctajul_mic(lista, *nr_echipe))
        {
            poz = i;
            gasit = 1;
            break; ///ne oprim din cautare pentru ca am gasit deja o echipa si o sa o stergem
        }
    if (gasit == 1)
    {
        if (poz >= 0)
            lista[poz - 1] -> next = lista[poz] -> next; ///refac legaturile intre componente
        free(lista[poz] -> team_name);
        free(lista[poz]);
        for (i = poz; i < (*nr_echipe - 1); i++)
            lista[i] = lista[i + 1];
        (*nr_echipe)--;
    }
}


void stergere_echipa_2(team** lista, int* nr_echipe)
{
    while (*nr_echipe > putere_2(*nr_echipe))
    {
        team* echipa_de_sters = punctajul_mic(lista, *nr_echipe);
        stergere_echipa_1(lista, nr_echipe);
    }
}

team* punctajul_mic(team** lista, int nr_echipe)
{
    int i;
    int poz = 0;
    float minim = lista[0] -> total_points;
    for(i = 1; i < nr_echipe; i++)
        if(lista[i] -> total_points <= minim)
        {
            minim = lista[i] -> total_points;
            poz = i;
        }
    return lista[poz];
}


void medie(team** lista, int nr_echipe)
{
    int i;
    for(i = 0; i < nr_echipe; i++)
    {
        team* curent = lista[i];
        float suma = 0;
        while(curent != NULL)
        {
            suma = suma + curent -> val.points;
            curent = curent->next;
        }
        lista[i] -> total_points = (float)(suma / lista[i] -> teammates);
    }
}


int putere_2(int nr_echipe)
{
    //printf("nr echipe=%d\n", nr_echipe);
    int p = 1;
    while (p * 2 <= nr_echipe)
         p = p * 2;
    //printf("p=%d", p);
    return p;
}


void cerinta2(FILE* file, team** lista, int *nr_echipe)
{
    int i;
    medie(lista, *nr_echipe);
    stergere_echipa_2(lista, nr_echipe);
    for(i = *nr_echipe - 1; i >= 0; i--)
        fprintf(file, "%s", lista[i] -> team_name);
}
