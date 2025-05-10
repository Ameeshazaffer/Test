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
    id = rand() % 100 + 1;// Génère un entier aléatoire entre 1 et 100
    existe = 0;
    for(int i = 0; i < taille; i++){ // Boucle qui parcourt le tableau pour vérifier si l'identifiant est déjà utilisé
        if((*(tableau + i))->num_id == id){ // Si l'identifiant existe déjà, on sort de la boucle
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
printf(" ID :                       %d\n", a->num_id);
printf(" NOM :                      %s\n", a->nom);
printf(" ESPECE :                   %s\n", a->espece);
printf(" ANNEE DE NAISSANCE :       %d\n", a->naissance);
printf(" AGE :                      %d\n", a->age);
printf(" POIDS :                    %.2f\n", a->poids);
printf(" TRANCHE D'AGE :            %s\n", a->tranche_age);
printf(" QUANTITES DE NOURRITURES : %.2f\n", a->quantites_nourriture);
printf(" TRAVAIL JOURNALIER :       %d\n", a->travail_journalier);
printf(" TRAVAIL HEBDOMADAIRE :     %d\n", a->travail_hebdomadaire);
printf(" COMMENTAIRE :              %s\n", a->commentaire);
printf(" ___________________________________________________________________________________________________________\n");
}

// Fonction qui crée un nouvel animal et remplit toutes ses informations
Animal* constructeur(Animal **tableau, int taille){

// Alloue de la mémoire, si l'allocation échoue, affiche un message d'erreur et quitte le programme
Animal *a = (Animal*)malloc(sizeof(Animal));
if (a == NULL) {
    printf("Erreur d'allocation de la memoire.\n");
    exit(1);
}

a->num_id = generer_id(tableau, taille);// Génère un ID unique

//Alloue de la mémoire pour le nom et consomme le caractère '\n' laissé dans le tampon grâce à getchar
printf("Veuillez saisir le nom avec majuscule: ");
a->nom = (char*)malloc(50 * sizeof(char));
scanf("%49s", a->nom);
getchar();

int valide = 0;
a->espece = malloc(50 * sizeof(char)); // Alloue de la mémoire pour l'espèce
do{
    printf("Veuillez saisir l'espece (chien, chat, autruche, hamster) sans majuscule: ");
    scanf("%49s", a->espece);
    getchar();
    // Vérifie que l'utilisateur saisie une espèce valide
    if (strcmp(a->espece, "chien") == 0 || strcmp(a->espece, "chat") == 0 || strcmp(a->espece, "autruche") == 0 || strcmp(a->espece, "hamster") == 0) {
        valide = 1;
    }else{
        printf("Espece invalide. Veuillez reessayer.\n");
    }
}while(valide!=1);  // Boucle qui se répète tant que l'espèce n'est pas valide

do{
    printf("Veuillez saisir l'annee de naissance: ");
    scanf("%d", &a->naissance);
    getchar();
    if (a->naissance < 1950 || a->naissance > 2025) {
        printf("Annee invalide. Veuillez entrer une annee entre 1950 et 2025.\n");
    }
}while(a->naissance < 1950 || a->naissance > 2025); // Boucle qui se répète tant que l'année de naissance est invalide

//Saisie du poids et consomme le caractère '\n' laissé dans le tampon grâce à getchar
printf("Veuillez saisir le poids: ");
scanf("%f", &a->poids);
getchar();

char buffer[256];// Chaîne temporaire pour stocker le commentaire
printf("Veuillez saisir un commentaire (taper 'X' si vous ne voulez pas inclure de commentaire): ");
fgets(buffer, 256, stdin);// Lecture du commentaire avec espaces
buffer[strcspn(buffer, "\n")] = '\0';// Retire le retour à la ligne à la fin de la chaîne et termine proprement la chaîne de caractères
a->commentaire = malloc(strlen(buffer) + 1);// Allocation mémoire pour stocker le commentaire
strcpy(a->commentaire, buffer);// Copie du commentaire dans la structure

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

