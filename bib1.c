#include <stdio.h>
#include "bib1.h"


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
