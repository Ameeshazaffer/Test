//FICHIER refuge.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "animal.h"
#include "refuge.h"

// Fonction qui ajoute un nouvel animal dans le tableau du refuge
Animal** ajouter_Animal(Animal **tableau, int *taille, Animal *a){
if((*taille + 1) >= 50){ // Vérifie si le nombre d'animaux dans le refuge atteint la capacité maximale
    printf("\nIl n'y a plus de place dans le refuge.\n\n");
}else{
    tableau = realloc(tableau, (*taille + 1) * sizeof(Animal*)); //Redimensionnement du tableau pour accueillir un animal de plus
    if (tableau == NULL) { // Si realloc échoue, on affiche un message d'erreur et on quitte le programme
        printf("\nErreur d'allocation de la memoire.\n");
        exit(1);
    }
    tableau[*taille] = a; // Ajout du nouvel animal à la fin du tableau
    (*taille)++; // Incrémentation de la taille du refuge
    printf("\n\nInformations du nouvel animal:\n\n");
    afficher(a);
}
    return tableau; // Retour du tableau mis à jour
}

// Fonction pour enlever un animal du tableau en fonction de son identifiant
Animal** enlever_Animal(Animal **tableau, int *taille, int id) {
int index = -1; // Variable pour stocker l'index de l'animal trouvé, initialisé à -1 si non trouvé
for(int i = 0; i < *taille; i++){ // Boucle qui parcourt le tableau pour rechercher l'animal avec l'identifiant correspondant
    if((*(tableau + i))->num_id == id){
        index = i;
        break;
    }
}

if(index == -1){ // Si l'index est toujours -1, cela signifie que l'animal n'a pas été trouvé
    printf("\n\nCet animal n'a pas ete trouve.\n\n");
}else{ // Si l'animal est trouvé, on affiche ses informations avant de le supprimer
    printf("\n\nInformations de l'animal adopte :\n\n");
    afficher(*(tableau + index));
    // Libération de la mémoire allouée pour l'animal (nom, espèce, commentaire)
    free((*(tableau + index))->nom);
    free((*(tableau + index))->espece);
    free((*(tableau + index))->commentaire);
    free(*(tableau + index));
    // Décalage des éléments restants dans le tableau pour combler le vide laissé par l'animal supprimé
    for(int j = index; j < (*taille - 1); j++){
        *(tableau + j) = *(tableau + (j + 1));
    }
    (*taille)--; // Décrémentation de la taille du refuge
    if (*taille > 0) { // Si la taille du tableau est supérieure à 0, on tente de réalouer la mémoire
    tableau = realloc(tableau, (*taille) * sizeof(Animal*));
        if (tableau == NULL) {// Si realloc échoue, on affiche un message d'erreur et on quitte le programme
            printf("\nErreur d'allocation de la memoire.\n");
            exit(1);
        }
    }else{ // Si la taille du tableau est 0, on libère la mémoire du tableau et on le met à NULL
    free(tableau);
    tableau = NULL;
    }

}
    return tableau; // Retour du tableau mis à jour
}


// Fonction qui recherche un animal dans le tableau du refuge selon son nom et/ou son espèce et/ou sa tranche d'âge
void rechercher_Animal(Animal **tableau, int taille, char *nom, char* espece, char* tranche_age){
int trouve = 0; //Variable qui indique si l'animal a été trouvé

// Parcours du tableau des animaux dans le refuge
for(int i = 0 ; i < taille ; i++){
if(strcmp(nom,"X")!=0){ // Si le nom n'est pas "X" (l'utilisateur souhaite rechercher par nom)
    if(strcmp(espece,"X")!=0){ // Si l'espèce n'est pas "X" (l'utilisateur souhaite rechercher par espèce)
        if(strcmp(tranche_age,"X")!=0){ // Si la tranche d'âge n'est pas "X" (l'utilisateur souhaite rechercher par tranche d'âge)
            // Recherche d'un animal avec le nom, l'espèce et la tranche d'âge correspondants + affichage
            if(strcmp(nom,(*(tableau + i))->nom)==0 && strcmp(espece,(*(tableau + i))->espece)==0 && strcmp(tranche_age,(*(tableau + i))->tranche_age)==0){
                printf("\n\nInformations de l'animal recherche :\n\n");
                afficher(*(tableau + i));
                trouve = 1;
            }
        }else{ // Si la tranche d'âge est "X", on ignore ce critère
            // Recherche d'un animal avec le nom et l'espèce correspondants + affichage
            if(strcmp(nom,(*(tableau + i))->nom)==0 && strcmp(espece,(*(tableau + i))->espece)==0){
                printf("\n\nInformations de l'animal recherche :\n\n");
                afficher(*(tableau + i));
                trouve = 1;
            }
        }
    }else{ // Si l'espèce est "X", on ignore ce critère
        if(strcmp(tranche_age,"X")!=0){
            // Recherche d'un animal avec le nom et la tranche d'âge correspondants + affichage
            if(strcmp(nom,(*(tableau + i))->nom)==0 && strcmp(tranche_age,(*(tableau + i))->tranche_age)==0){
                printf("\n\nInformations de l'animal recherche :\n\n");
                afficher(*(tableau + i));
                trouve = 1;
            }
        }
    }
}else{ // Si le nom est "X", on ignore ce critère
    if(strcmp(espece,"X")!=0){
        if(strcmp(tranche_age,"X")!=0){
            // Recherche d'un animal avec l'espèce et la tranche d'âge correspondants + affichage
            if(strcmp(espece,(*(tableau + i))->espece)==0 && strcmp(tranche_age,(*(tableau + i))->tranche_age)==0){
                printf("\n\nInformations de l'animal recherche :\n\n");
                afficher(*(tableau + i));
                trouve = 1;

            }
        }
    }
}

}

// Si aucun animal n'a été trouvé
if(trouve==0){
    printf("\n\nL'animal recherche n'a pas ete trouve.\n");
}
}


// Fonction qui affiche le nombre d'animaux dans chaque espèce, trié par nombre décroissant
void tableau_espece(Animal **tableau, int taille){
int nb_chiens = 0, nb_chats = 0, nb_autruches = 0, nb_hamsters = 0, i, j;
printf("\nIl y a %d animal/animaux dans le refuge.\n\n", taille);

// Parcours de chaque animal dans le tableau pour compter le nombre d'animaux de chaque espèce
for(i = 0; i < taille; i++){
    if(strcmp((*(tableau + i))->espece, "chien") == 0){
        nb_chiens++;
    }else if (strcmp((*(tableau + i))->espece, "chat") == 0){
        nb_chats++;
    }else if (strcmp((*(tableau + i))->espece, "autruche") == 0){
        nb_autruches++;
    }else if (strcmp((*(tableau + i))->espece, "hamster") == 0){
        nb_hamsters++;
    }
}

// Création d'un tableau contenant les espèces et leur nombre d'animaux respectifs
Tableau_espece tab[4] = {{"chien", nb_chiens}, {"chat", nb_chats}, {"autruche", nb_autruches}, {"hamster", nb_hamsters}};

// Tri par ordre décroissant du nombre d'animaux
for(i = 0; i < 4 - 1; i++){
    for(j = 0; j < 4 - i - 1; j++){
        if(tab[j].nb < tab[j + 1].nb){
            Tableau_espece tmp = tab[j];
            tab[j] = tab[j + 1];
            tab[j + 1] = tmp;
        }
    }
}

// Affichage de chaque espèce et du nombre d'animaux correspondants
printf("_______________________________________NOMBRE D'ANIMAUX DE CHAQUE ESPECE__________________________________\n");
for(i = 0; i < 4; i++){
    printf("%s : %d\n", tab[i].espece, tab[i].nb);
}
}

// Fonction qui affiche le nombre d'animaux dans chaque tranche d'âge (bébé, jeune, adulte, senior)
void tableau_age(Animal **tableau, int taille){
int nb_bebes = 0, nb_jeunes = 0, nb_adultes = 0, nb_seniors = 0, i;

// Parcours de chaque animal dans le tableau pour compter le nombre d'animaux dans chaque tranche d'âge
for(i = 0; i < taille; i++){
    if(strcmp((*(tableau + i))->tranche_age, "bebe") == 0) {
        nb_bebes++;
    }else if(strcmp((*(tableau + i))->tranche_age, "jeune") == 0) {
        nb_jeunes++;
    }else if(strcmp((*(tableau + i))->tranche_age, "adulte") == 0) {
        nb_adultes++;
    }else if(strcmp((*(tableau + i))->tranche_age, "senior") == 0) {
        nb_seniors++;
    }
}

// Création d'un tableau contenant les tranches d'âge et leur nombre d'animaux respectifs
Tableau_age tab[4] = {{"bebes", nb_bebes}, {"jeunes", nb_jeunes}, {"adultes", nb_adultes}, {"seniors", nb_seniors}};
printf("___________________________________NOMBRE D'ANIMAUX PAR TRANCHE D'AGE _____________________________________\n");

// Affichage de chaque tranche d'âge et du nombre d'animaux correspondants
for(i = 0; i < 4; i++){
    printf("%s : %d\n", tab[i].tranche_age, tab[i].nb);
}
printf("___________________________________________________________________________________________________________\n");
}

void sauvegarder_refuge(Animal **tableau, int taille, const char *fichier) {
FILE *f = fopen(fichier, "w");
if(f == NULL){
    printf("Ouverture du fichier impossible\n");
    exit(1);
}else{
    for (int i = 0; i < taille; i++) {
        fprintf(f, "%d\n", tableau[i]->num_id);
        fprintf(f, "%s\n", tableau[i]->nom);
        fprintf(f, "%s\n", tableau[i]->espece);
        fprintf(f, "%d\n", tableau[i]->naissance);
        fprintf(f, "%d\n", tableau[i]->age);
        fprintf(f, "%s\n", tableau[i]->tranche_age);
        fprintf(f, "%.2f\n", tableau[i]->poids);
        fprintf(f, "%s\n", tableau[i]->commentaire);
        fprintf(f, "%d\n", tableau[i]->quantites_nourriture);
        fprintf(f, "%d\n", tableau[i]->travail_journalier);
        fprintf(f, "%d\n", tableau[i]->travail_hebdomadaire);
        fprintf(f, "\n\n");
    }
    fclose(f);
}
}

Animal **charger_refuge(int *taille, const char *fichier) {
FILE *f = fopen(fichier, "r");
if (f == NULL) {
    *taille = 0;
    return NULL;
}

Animal **tableau = NULL;
*taille = 0;

while(1){// Boucle qui lit chaque animal du fichier et l'ajoute au tableau
    Animal *a = malloc(sizeof(Animal));
    a->nom = malloc(50 * sizeof(char));
    a->espece = malloc(50 * sizeof(char));
    a->tranche_age = malloc(50 * sizeof(char));
    a->commentaire = malloc(256 * sizeof(char));

    // Lire les données des animaux
    if(fscanf(f, "%d %s %s %d %d %s %f %f %d %d", &a->num_id, a->nom, a->espece, &a->naissance, &a->age, a->tranche_age, &a->poids, &a->quantites_nourriture, &a->travail_journalier, &a->travail_hebdomadaire) != 10) {
            free(a);
            break;  // On quitte la boucle si une lecture échoue (fin du fichier ou erreur)
        }

        // Lire le commentaire
        fgets(a->commentaire, 256, f);
        a->commentaire[strcspn(a->commentaire, "\n")] = '\0';

        // Réallocation pour ajouter l'animal
        tableau = realloc(tableau, (*taille + 1) * sizeof(Animal*));
        tableau[*taille] = a;
        (*taille)++;
    }

fclose(f);  // Fermeture du fichier après la lecture
return tableau;
}
