#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Player
{
    char* firstName;
    char* secondName;
    int points;
    struct Player* next;
};
typedef struct Player player;


struct team
{
    char* team_name;
    int teammates;
    float total_points;
    player val;
    struct team* next;
};
typedef struct team team;


///functii pentru cerinta 1
void adaug_inceput(team** head, char* team_name, int teammates, float total_points, player valoare);
void afisare(team* head);
void cerinta1(FILE* file, team** lista1, int nr_echipe);
void eroare_file();
void eroare_aloc();
team** creare_lista(FILE* file, int* nr_echipe);


///functii pentru cerinta 2
void cerinta2(FILE* file, team** lista, int* nr_echipe);
int putere_2(int nr_echipe);
void stergere_echipa_1(team** lista, int* nr_echipe);
void stergere_echipa_2(team** lista, int* nr_echipe);
team* punctajul_mic(team** lista, int nr_echipe);
void medie(team** lista, int nr_echipe);
