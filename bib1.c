#include <stdio.h>
#include "bib1.h"

/// functii cerinta 1
void eroare_file()
{
    printf("fisierul nu a putut fi deschis!");
    exit(1);
}


void eroare_aloc()
{
    printf("nu a putut fi alocat spatiu!");
    exit(1);
}


void adaug_inceput(team** head, char* team_name, int teammates, float total_points, player valoare)
{
    team* nou = (team*) malloc (sizeof(team));
    if (nou == NULL)
        eroare_aloc();
    nou -> team_name = strdup(team_name);
    nou -> teammates = teammates;
    nou -> total_points = total_points;
    nou -> val.firstName = strdup(valoare.firstName);
    nou -> val.secondName = strdup(valoare.secondName);
    nou -> val.points = valoare.points;
    nou -> next = *head;
    *head = nou;
}


void afisare(team* head)
{
    while (head != NULL)
    {
        printf("%d", head -> teammates);
        printf("%s", head -> team_name);
        player* curent = &(head -> val);
        while (curent != NULL)
        {
            printf("%s %s %d", curent -> firstName, curent -> secondName, curent -> points);
            curent = curent -> next;
        }
        head = head -> next;
    }
    printf("\n");
}


team** creare_lista(FILE* file, int* nr_echipe)
{
    int i, j;
    fscanf(file, "%d", nr_echipe); ///in acest fel determin numar de echipe din fiecare fisier, acesta fiind primul numar care apare in respectivul fisier
    team** lista = (team**) malloc ((*nr_echipe) * sizeof(team*));
    if (lista == NULL)
        eroare_aloc();
    for (i = 0; i < (*nr_echipe); i++)
    {
        int nr_coechipieri;
        char team_name[50];
        lista[i] = NULL;
        fscanf(file, "%d ", &nr_coechipieri);
        fgets(team_name, 50, file);
        player *p = malloc (nr_coechipieri * sizeof(player));
        if (p == NULL)
            eroare_aloc();
        for (j = 0; j < nr_coechipieri; j++)
        {
            p[j].firstName = malloc(50 * sizeof(char));
            if (p[j].firstName == NULL)
                eroare_aloc();
            p[j].secondName = malloc(50 * sizeof(char));
            if (p[j].secondName == NULL)
                eroare_aloc();
            fscanf(file, "%s %s %d", p[j].firstName, p[j].secondName, &p[j].points);
            adaug_inceput(&(lista[i]), team_name, nr_coechipieri, 0.0, p[j]);
        }
        free(p);
    }
    return lista;
}


void cerinta1(FILE* file, team** lista, int nr_echipe)
{
    int i;
    for (i = 0; i < nr_echipe; i++)
    {
        int lungime = strlen(lista[i] -> team_name);
        if (lungime == 0)
            printf("numele echipei este un sir gol ");
        else if (lista[i] -> team_name[lungime - 1] == '\n') ///daca ultimul caracter din sir este newline
                lista[i] -> team_name[lungime - 1] = '\0'; ///atunci acel newline se inlocuieste cu '\0' pentru a incheia sirul si a afisa numele echipelor corect
    }
    for (i = nr_echipe - 1; i >= 0; i--)
        fprintf(file, "%s\n", lista[i] -> team_name);
}


/// functii cerinta 2
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
