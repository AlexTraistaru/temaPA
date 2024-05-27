#include <stdio.h>
#include "bib1.h"
#include "bib2.h"


void stergere_echipa(team** lista, int* nr_echipe) //aceasta functie sterge o echipa din lista, respectand conditia impusa de functia putere_2 si reface legaturile dintre componente
{
    while (*nr_echipe > putere_2(*nr_echipe))
    {
        int i;
        int gasit = 0; //gasit imi zice daca am gasit o echipa pe care o vreau si stiu ca trebuie sters din lista
        int poz = -1; // poz este indexul echipei pe care vreau sa o sterg
        for (i = 0; i < *nr_echipe; i++)
        {
            if (lista[i] == punctajul_mic(lista, *nr_echipe))
            {
                poz = i;
                gasit = 1; //gasit devine 1 pentru ca am gasit o echipa cu un punctaj mic
                break; // ne oprim din cautare pentru ca am gasit deja o echipa si o sa o stergem
            }
        }
        if (gasit == 1)
        {
            free(lista[poz] -> team_name); //aici sterg echipa, refac legaturile dintre componente si decrementez nr de echipe
            free(lista[poz]);
            for (i = poz; i < (*nr_echipe - 1); i++)
                lista[i] = lista[i + 1];
            (*nr_echipe)--;
        }
    }
}


team* punctajul_mic(team** lista, int nr_echipe) //asa determin punctajul cel mai mic dintre toate echipele
{
    int i;
    int poz = 0;
    float minim = lista[0] -> total_points;
    for (i = 1; i < nr_echipe; i++)
        {
        if (lista[i] -> total_points <= minim)
        {
            minim = lista[i] -> total_points; //asa determin minimul
            poz = i;
        }
    }
    return lista[poz]; //lista[poz] este chiar echipa cu cel mai mic punctaj
}


void medie(team** lista, int nr_echipe) //aceasta functie determina media punctajului de echipa, facand o medie aritmetica
{
    int i;
    for (i = 0; i < nr_echipe; i++)
    {
        team* curent = lista[i];
        float suma = 0;
        while (curent != NULL)
        {
            suma = suma + curent -> val.points;
            curent = curent -> next;
        }
        lista[i] -> total_points = suma / lista[i] -> teammates;
    }
}


int putere_2(int nr_echipe) //aceasta functie calculeaza puterea maxima a lui 2, tinand cont de nr de echipe din fiecare fisier in parte
{
    int p = 1;
    while (p * 2 <= nr_echipe)
        p *= 2;
    return p;
}


void cerinta2(char* argv, team** lista, int *nr_echipe) //aceasta functie rezolva cerinta 2, apeland functiile descrise mai sus
{
    ///printf("merge 2 ");
    FILE* file = fopen(argv, "wt");
    if (file == NULL)
        eroare_file();
    int i;
    medie(lista, *nr_echipe); //mai intai calculez media ca sa stiu toate punctajele, dupa se afla minimul
    stergere_echipa(lista, nr_echipe); //dupa ce se stie cine este minimul se sterge echipa cu punctajul minim

    for (i = *nr_echipe - 1; i >= 0; i--) //asemeni exercitiului 1, afisarea o fac invers pentru ca elementele au fost adaugate la inceput
        fprintf(file, "%s\n", lista[i] -> team_name);
    fclose(file);
}
