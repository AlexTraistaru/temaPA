#include <stdio.h>


struct q
{
    team *front;
    team *rear;
};
typedef struct q queue;


struct stack
{
    team val;
    struct stack* next;
};
typedef struct stack stack;


queue* create_coada();
void enqueue(queue* q, team* aux);
void afisare_coada(queue* q, FILE* file);
int isEmpty_coada(queue* q);
void cerinta3(char* argv, team** lista, int nr_echipe, team** ultimii_8);
void free_coada(queue* q);
void push(stack** top, team* value);
team pop(stack** top);
int isEmpty_stiva(stack* top);
team dequeue(queue* q);
void meciuri(FILE* file, int nr_echipe, queue* lista_coada, stack** castigatori, stack** invinsi);
void createStack(stack** top, team* value);
void enQueueStack(queue* q, stack* s);
void nume(char* aux);
void free_stiva(stack** top);
