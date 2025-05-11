
//FICHIER refuge.h
#ifndef REFUGE_H
#define REFUGE_H

#include "animal.h"

// Structure pour compter le nombre d'animaux par espèce
typedef struct {
    char* espece;
    int   nb;
} Tableau_espece;

// Structure pour compter le nombre d'animaux par tranche d'âge
typedef struct {
    char* tranche_age;
    int   nb;
} Tableau_age;

// Prototypes des fonctions liées à la gestion du refuge
void tableau_espece(Animal **tableau, int taille);
void tableau_age(Animal **tableau, int taille);
Animal** ajouter_Animal(Animal **tableau, int *taille, Animal *a);
Animal** enlever_Animal(Animal **tableau, int *taille, int id);
void rechercher_Animal(Animal **tableau, int taille, char *nom, char *espece, char *tranche_age);
void sauvegarder_refuge(Animal **tableau, int taille, const char *nom_fichier);
Animal **charger_refuge(int *taille, const char *nom_fichier);

#endif
