#include <stdio.h>
#include "bib1.h"


void eroare_file() //functie pentru afisarea unui mesaj corspunzator in caz ca fisierul nu se poate deschide
{
    printf("fisierul nu a putut fi deschis!");
    exit(1);
}


void eroare_aloc() //afisarea unui mesaj corspunzator in caz ca nu se poate aloca spatiu
{
    printf("nu a putut fi alocat spatiu!");
    exit(1);
}


void adaug_inceput(team** head, char* team_name, int teammates, float total_points, player valoare) //functie pentru adaugarea la inceput intr-o lista
{
    team* nou = (team*) malloc (sizeof(team));
    if (nou == NULL)
        eroare_aloc();
    nou -> team_name = strdup(team_name);
    if (nou -> team_name == NULL)
        eroare_aloc();
    nou -> teammates = teammates;
    nou -> total_points = total_points;
    nou -> val.firstName = strdup(valoare.firstName);
    if (nou -> val.firstName == NULL)
        eroare_aloc();
    nou -> val.secondName = strdup(valoare.secondName);
    if (nou -> val.secondName == NULL)
        eroare_aloc();
    nou -> val.points = valoare.points;
    nou -> next = *head;
    *head = nou;
}


void afisare(team* head) //functie pentru afisarea unei liste
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


team** creare_lista(char* argv, int* nr_echipe) //aceasta functie creeaza lista conform fisierului d.in, folosind datele din el
{
    FILE* file = fopen(argv, "rt");
    if (file == NULL)
        eroare_file();
    int i, j;
    fscanf(file, "%d", nr_echipe); ///in acest fel determin numar de echipe din fiecare fisier, acesta fiind primul numar care apare in respectivul fisier
    team** lista = (team**) malloc ((*nr_echipe) * sizeof(team*));
    if (lista == NULL)
        eroare_aloc();
    for (i = 0; i < (*nr_echipe); i++) //i este folosit pentru a parcurge toate echipele, la modul general
    {
        int nr_coechipieri;
        char *team_name;
        team_name=(char*)malloc(sizeof(char)*40);
        lista[i] = NULL;
        fscanf(file, "%d ", &nr_coechipieri);
        fscanf(file, " %[^\n]s", team_name); //citesc un sir de caractere pana la intalnirea unui caracter de linie noua. acel spatiu de la " %[^\n]" ne asigura ca se ignora orice spatii inainte de a incepe citirea
        player *p = malloc (nr_coechipieri * sizeof(player));
        if (p == NULL)
            eroare_aloc();
        for (j = 0; j < nr_coechipieri; j++) //j este folosit pentru a parcurge fieacre jucator al fiecarei echipe
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
    fclose(file);
    return lista;
}


void cerinta1(char* argv, team** lista, int nr_echipe) //aceasta functie rezolva cerinta 1, apeland functiile descrise mai sus, necesare lui
{
    ///printf("merge 1 ");
    FILE* file = fopen(argv, "wt");
    if (file == NULL)
        eroare_file();
    int i;
    for (i = 0; i < nr_echipe; i++)
    {
        int lungime = strlen(lista[i] -> team_name); //lungime este lungimea numelui de echipa
        if (lungime == 0)
            printf("numele echipei este un sir gol ");
        else if (lista[i] -> team_name[lungime - 1] == '\n') ///daca ultimul caracter din sir este newline
                lista[i] -> team_name[lungime - 1] = '\0'; ///atunci acel newline se inlocuieste cu '\0' pentru a incheia sirul si a afisa numele echipelor corect
    }
    for (i = nr_echipe - 1; i >= 0; i--) //am adaugat elemente la inceput cu functia adaug_inceput deci fac afisarea invers penyru a afisa numele echipelor in ordinea dorita
        fprintf(file, "%s\n", lista[i] -> team_name);
    fclose(file);
}
