#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct Player //structura pentru un jucator al fiecarei echipe
{
    char* firstName;
    char* secondName;
    int points;
    struct Player* next;
};
typedef struct Player player;


struct team //structura unei echipe
{
    char* team_name;
    int teammates;
    float total_points;
    player val;
    struct team* next;
};
typedef struct team team;


void adaug_inceput(team** head, char* team_name, int teammates, float total_points, player valoare);
void afisare(team* head);
void cerinta1(char* argv, team** lista1, int nr_echipe);
void eroare_file();
void eroare_aloc();
team** creare_lista(char* argv, int* nr_echipe);
