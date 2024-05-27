#include "bib1.h"
#include "bib2.h"
#include "bib3.h"


void nume(char* aux) //aceasta functie este folosita pentru a trata cazurile cand numele unei echipe are alte caractere in plus de care nu am nevoie
{
    char* ch;
    if ((ch = strchr(aux, '\n')) != NULL) //caracterul \n
        *ch = '\0';
    if ((ch = strchr(aux, '\r')) != NULL) //carriage return, muta cursorul la inceputul liniei
       *ch = '\0';
    int lungime = strlen(aux);
    if (aux[lungime - 1] == ' ') //un spatiu
        aux[lungime - 1] = '\0';
}


queue* create_coada() //functie prntru creearea cozii, din curs
{
    queue *q = (queue*) malloc(sizeof(queue));
    if (q == NULL)
        eroare_aloc();
    q -> front = q -> rear = NULL;
    return q;
}


void enqueue(queue* q, team* aux) //functie pentru adaugarea elementelor in coada, din curs
{
    team* nou = (team*) malloc(sizeof(team));
    if (nou == NULL)
        eroare_aloc();
    nou -> team_name = strdup(aux -> team_name);
    if (nou -> team_name == NULL)
        eroare_aloc();
    nou -> teammates = aux -> teammates;
    nou -> total_points = aux -> total_points;
    nou -> val.firstName = strdup(aux -> val.firstName);
    if (nou -> val.firstName == NULL)
        eroare_aloc();
    nou -> val.secondName = strdup(aux -> val.secondName);
    if (nou -> val.secondName == NULL)
        eroare_aloc();
    nou -> val.points = aux -> val.points;
    nou -> next = NULL;
    if (q -> rear == NULL)
        q -> rear = nou;
    else
    {
        (q -> rear) -> next = nou;
        q -> rear = nou;
    }
    if (q -> front == NULL)
        q -> front = q -> rear;
}


team dequeue(queue* q) //functie pentru scoaterea elementelor din coada, din curs
{
    if (isEmpty_coada(q))
        exit(1);
    team aux1;
    team* aux2 = q -> front;
    aux1.team_name = strdup(aux2 -> team_name);
    if (aux1.team_name == NULL)
        eroare_aloc();
    aux1.teammates = aux2 -> teammates;
    aux1.total_points = aux2 -> total_points;
    aux1.val.firstName = strdup(aux2 -> val.firstName);
    if (aux1.val.firstName == NULL)
        eroare_aloc();
    aux1.val.secondName = strdup(aux2 -> val.secondName);
    if (aux1.val.secondName == NULL)
        eroare_aloc();
    aux1.val.points = aux2 -> val.points;
    q -> front = q -> front -> next;
    if (q -> front == NULL)
        q -> rear = NULL;
    free(aux2 -> team_name);
    free(aux2 -> val.firstName);
    free(aux2 -> val.secondName);
    free(aux2);
    return aux1;
}



int isEmpty_coada(queue* q) //functie care verifica daca coada este goala, din curs
{
    return q -> front == NULL;
}


int isEmpty_stiva(stack* top) //functie care verifica daca stiva este goala, din curs
{
    return top == NULL;
}


void push(stack** top, team* value) //aceasta functie adauga elemente in stiva, din curs
{
    stack *nou = (stack*) malloc (sizeof(stack));
    if (nou == NULL)
        eroare_aloc();
    nou -> val.teammates = value -> teammates;
    nou -> val.total_points = value -> total_points;
    nou -> val.team_name = strdup(value -> team_name);
    if (nou -> val.team_name == NULL)
        eroare_aloc();
    nou -> val.val.firstName = strdup(value -> val.firstName);
    if (nou -> val.val.firstName == NULL)
        eroare_aloc();
    nou -> val.val.secondName = strdup(value -> val.secondName);
    if (nou -> val.val.secondName == NULL)
        eroare_aloc();
    nou -> val.val.points = value -> val.points;
    nou -> next = *top;
    *top = nou;
}


team pop(stack** top) //aceasta functie scoate elemente din stiva, din curs
{
    if (isEmpty_stiva(*top))
        exit(1);
    team value = (*top) -> val;
    stack *temp = *top;
    *top = (*top) -> next;
    free(temp);
    return value;
}


void meciuri(FILE *file, int nr_echipe, queue *lista_coada, stack **castigatori, stack **invinsi) //functia aceasta simuleaza petrecerea meciurilor, conform cerintei date
{
    for (int i = 0; i < nr_echipe; i = i + 2)
    {
        team prima_echipa = dequeue(lista_coada); //scot o echipa din coada
        nume(prima_echipa.team_name); //aplic functia nume pentru a retine doar numele echipei fara alte caractere suplimentare
        team a_doua_echipa = dequeue(lista_coada);//scot alta echipa din coada, adica urmatoarea
        nume(a_doua_echipa.team_name); //aplic functia nume pentru a retinr doar numele echipei fara alte caractere suplimentare
        fprintf(file, "%-33s-%33s\n", prima_echipa.team_name, a_doua_echipa.team_name);
        if (prima_echipa.total_points > a_doua_echipa.total_points)
        {
            prima_echipa.total_points = prima_echipa.total_points + 1; //echipa castigatoare primeste un punct in plus
            push(castigatori, &prima_echipa); //in cazul nostru prima echipa a fost castigatare, deci o introduc in stiva de castigatori
            push(invinsi, &a_doua_echipa); //iar a doua echipa a fost invinsa deci merge la pierzatori
        } else //aici se intampla identic cu ce e mai sus doar ca se inverseaza rolurile
            {
                a_doua_echipa.total_points = a_doua_echipa.total_points + 1;
                push(castigatori, &a_doua_echipa);
                push(invinsi, &prima_echipa);
            }
    }
}


void free_stiva(stack** top) //aceasta functie elibereaza stiva
{
    while (*top != NULL)
    {
        stack* temp = *top;
        *top = (*top)->next;
        free(temp -> val.team_name);
        free(temp -> val.val.firstName);
        free(temp -> val.val.secondName);
        free(temp);
    }
}


void free_coada(queue* q) //functie care elibereaza coada
{
    while (!isEmpty_coada(q))
    {
        team aux = dequeue(q);
        free(aux.team_name);
        free(aux.val.firstName);
        free(aux.val.secondName);
    }
    free(q);
}


void afiseaza_primii_8(team** primii_8) //aceasta functie afiseaza primii_8 in caz ca vreau sa ma asigur ca se retin ok cele mai bune 8 echipe din joc
{
    int i;
    for (i = 0; i < 8; i++)
        printf("%s\n", primii_8[i] -> team_name);
}


void cerinta3(char* argv, team** lista, int nr_echipe, team** primii_8) //aceasta functie rezolva cerinta 3, apeland functiile descrise mai sus
{
    ///printf("merge 3 ");
    stack* castigatori = NULL; //la inceput stiva este goala
    stack* invinsi = NULL; //la fel ca mai sus
    int runda = 1; //prima runda este nr 1
    queue* lista_coada = create_coada();
    for (int i = nr_echipe - 1; i >= 0; i--)
        enqueue(lista_coada, lista[i]);
    FILE *file = fopen(argv, "at");
    if (file == NULL)
        eroare_file();
    while (nr_echipe > 1)
    {
        fprintf(file, "\n--- ROUND NO:%d\n", runda);
        meciuri(file, nr_echipe, lista_coada, &castigatori, &invinsi);
        fprintf(file, "\nWINNERS OF ROUND NO:%d\n", runda);
        nr_echipe = nr_echipe / 2;  //dupa fiecare runda nr de echipe se injumatateste pentru ca jumatate merg la castigatori si restul al invinsi
        runda++;
        stack* castiga = castigatori;
        while (castiga != NULL)  //asa afisez castigatorii fiecare runde in parte
        {
            fprintf(file, "%-34s-  %.2f\n", castiga -> val.team_name, castiga -> val.total_points);
            if (nr_echipe == 8) //daca am ajuns la doar 8 echipe ramase, atunci ei sunt cei mai buni 8
            {
                adaug_inceput(primii_8, castiga -> val.team_name, castiga -> val.teammates, castiga -> val.total_points, castiga -> val.val); //dupa ce ii stiu cine sunt ii adaug la inceput intr-o lista
                //printf("%s\n", castiga -> val.team_name);
            }
            castiga = castiga -> next;
        }
        free_coada(lista_coada); //mutam castigatorii in coada pentru urm runda
        lista_coada = create_coada();
        while (castigatori != NULL)
        {
            team temp = pop(&castigatori);
            enqueue(lista_coada, &temp);
        }
        free_stiva(&invinsi); //eliberam stiva de invinsi
    }
    fclose(file);
}
