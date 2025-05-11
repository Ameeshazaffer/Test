//FICHIER animal.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "animal.h"
#include "refuge.h"

// Fonction qui génère un identifiant unique aléatoire entre 1 et 100 pour un animal
int generer_id(Animal **tableau, int taille){
int id;
int existe;
do{
    id = rand() % 100 + 1;
    existe = 0;
    for(int i = 0; i < taille; i++){
        if((*(tableau + i))->num_id == id){
            existe = 1;
            break;
        }
    }
} while(existe == 1); // Boucle qui se répète tant que l'identifiant est déjà pris
    return id;
}

// Fonction qui retourne la tranche d'âge d'un animal en fonction de son âge
char* tranche_age(int age){
if(age >= 0 && age <= 2){
    return "bebe";
}else if(age >= 3 && age <= 5){
    return "jeune";
}else if(age >= 6 && age <= 9){
    return "adulte";
}else if(age >= 10){
    return "senior";
}
    return NULL; //Retourne NULL si l'âge ne correspond à aucune tranche
}


// Procédure qui affiche toutes les informations d'un animal passé en paramètre
void afficher(Animal *a){
printf(" __________________________________________________ANIMAL__________________________________________________\n");
printf(" ID :                                                 %d\n", a->num_id);
printf(" NOM :                                                %s\n", a->nom);
printf(" ESPECE :                                             %s\n", a->espece);
printf(" ANNEE DE NAISSANCE :                                 %d\n", a->naissance);
printf(" AGE :                                                %d\n", a->age);
// Affichage du poids en fonction de l'animal
if (strcmp(a->espece, "hamster") == 0) {
    printf(" POIDS (g) :                                          %.2f\n", a->poids);
} else {
    printf(" POIDS (kg) :                                         %.2f\n", a->poids);
}
printf(" TRANCHE D'AGE :                                      %s\n", a->tranche_age);
printf(" QUANTITES DE NOURRITURES (g) :                       %.2f\n", a->quantites_nourriture);
printf(" TEMPS DE NETTOYAGE d'ABRIS JOURNALIER (min/jour) :   %d\n", a->travail_journalier);
printf(" TEMPS DE NETTOYAGE d'ABRIS HEBDOMADAIRE (min/sem) :  %d\n", a->travail_hebdomadaire);
printf(" COMMENTAIRE :                                        %s\n", a->commentaire);
printf(" ___________________________________________________________________________________________________________\n");
}

// Fonction qui crée un nouvel animal et remplit toutes ses informations
Animal* constructeur(Animal **tableau, int taille){

// Alloue de la mémoire, si l'allocation échoue, affiche un message d'erreur et quitte le programme
Animal *a = (Animal*)malloc(sizeof(Animal));
if (a == NULL) {
    printf("\nErreur d'allocation de la memoire.\n");
    exit(1);
}

a->num_id = generer_id(tableau, taille);// Génère un ID unique

//Alloue de la mémoire pour le nom et consomme le caractère '\n' laissé dans le tampon grâce à getchar
printf("\nVeuillez saisir le nom : ");
a->nom = (char*)malloc(50 * sizeof(char));
scanf("%49s", a->nom);
getchar();

int valide = 0;
a->espece = malloc(50 * sizeof(char)); // Alloue de la mémoire pour l'espèce
do{
    printf("\nVeuillez saisir l'espece (chien, chat, autruche, hamster) en miniscule: ");
    scanf("%49s", a->espece);
    getchar();
    // Vérifie que l'utilisateur saisie une espèce valide
    if (strcmp(a->espece, "chien") == 0 || strcmp(a->espece, "chat") == 0 || strcmp(a->espece, "autruche") == 0 || strcmp(a->espece, "hamster") == 0) {
        valide = 1;
    }else{
        printf("\nEspece invalide. Veuillez reessayer.\n");
    }
}while(valide!=1);  // Boucle qui se répète tant que l'espèce n'est pas valide

//Saisie de l'annee de naissance
do{
    printf("\nVeuillez saisir l'annee de naissance: ");
    scanf("%d", &a->naissance);
    getchar();
    if (a->naissance < 1950 || a->naissance > 2025) {
        printf("\nAnnee invalide. Veuillez entrer une annee entre 1950 et 2025.\n");
    }
}while(a->naissance < 1950 || a->naissance > 2025); // Boucle qui se répète tant que l'année de naissance est invalide

//Saisie du poids
do{
    if (strcmp(a->espece, "hamster") == 0) {
        printf("\nVeuillez saisir le poids en grammes: ");// Si c'est un hamster, demander en grammes
        scanf("%f", &a->poids);
        getchar();
    } else {
        printf("\nVeuillez saisir le poids en kilogrammes: ");// Sinon, demander en kilogrammes
        scanf("%f", &a->poids);
        getchar();
    }
    if (a->poids < 0 || a->poids > 250) {
        printf("\nPoids invalide. Veuillez entrer un poids compris entre 0 et 250 kg/g.\n");
    }
}while (a->poids < 0 || a->poids > 250);// Boucle qui se répète tant que le poids est invalide

//Saisie du commentaire
char buffer[256];
printf("\nVeuillez saisir un commentaire (taper 'X' si vous ne voulez pas inclure de commentaire): ");
fgets(buffer, 256, stdin);
buffer[strcspn(buffer, "\n")] = '\0';
a->commentaire = malloc(strlen(buffer) + 1);
strcpy(a->commentaire, buffer);

a->age = 2025 - a->naissance;// Calcule l'âge de l'animal (en 2025)

a->tranche_age = tranche_age(a->age);// Détermine la tranche d'âge de l'animal

// Détermine la quantité de nourriture quotidienne selon l'espèce et l'âge de l'animal
if (strcmp(a->espece, "chien") == 0 || strcmp(a->espece, "chat") == 0){
    if(a->age < 2){
        a->quantites_nourriture = 500;
    }else{
        a->quantites_nourriture = (a->poids * 10) / 100;
    }
}else if(strcmp(a->espece, "hamster") == 0){
        a->quantites_nourriture = 20;
}else if(strcmp(a->espece, "autruche") == 0){
        a->quantites_nourriture = 2500;
}

// Détermine le travail journalier et hebdomadaire en fonction de l'espèce
if (strcmp(a->espece, "chien") == 0){
    a->travail_journalier = 5;
    a->travail_hebdomadaire = 20;
}else if(strcmp(a->espece, "chat") == 0){
    a->travail_journalier = 10;
    a->travail_hebdomadaire = 20;
}else if(strcmp(a->espece, "hamster") == 0){
    a->travail_journalier = 10;
    a->travail_hebdomadaire = 20;
}else if(strcmp(a->espece, "autruche") == 0){
    a->travail_journalier = 20;
    a->travail_hebdomadaire = 45;
}

    return a;// Retourne le pointeur vers le nouvel animal
}
