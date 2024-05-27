#include <stdio.h>


struct q  //structura pentru un nod din coada
{
    team *front;
    team *rear;
};
typedef struct q queue;


struct stack  //structura pentru un nod din stiva
{
    team val;
    struct stack* next;
};
typedef struct stack stack;


queue* create_coada();
void enqueue(queue* q, team* aux);
int isEmpty_coada(queue* q);
void cerinta3(char* argv, team** lista, int nr_echipe, team** ultimii_8);
void free_coada(queue* q);
void push(stack** top, team* value);
team pop(stack** top);
int isEmpty_stiva(stack* top);
team dequeue(queue* q);
void meciuri(FILE* file, int nr_echipe, queue* lista_coada, stack** castigatori, stack** invinsi);
void nume(char* aux);
void free_stiva(stack** top);
void afiseaza_primii_8(team** primii_8);
