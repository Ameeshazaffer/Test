
//FICHIER animal.h
#ifndef ANIMAL_H
#define ANIMAL_H


// Structure représentant un animal
typedef struct {
    int   num_id;
    char* nom;
    char* espece;
    int   naissance;
    int   age;
    char* tranche_age;
    float poids;
    char* commentaire;
    float quantites_nourriture;
    int   travail_journalier;
    int   travail_hebdomadaire;
} Animal;

// Prototypes des fonctions liées à la gestion des animaux
int generer_id(Animal **tableau, int taille);
char* type_age(int age);
void afficher(Animal *a);
Animal* constructeur(Animal **tableau, int taille);

#endif
