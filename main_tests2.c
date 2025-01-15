// Jiwon KIM et Nguyen Hanh Dung 

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"

/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir = 0.01;
float p_reproduce_proie = 0.4;
float p_reproduce_predateur = 0.5;
int temps_repousse_herbe = -15;

int main(void) {
    int i;
    Animal *liste_proie = NULL;
	Animal *liste_predateur = NULL;
	int energie = 10;
	srand(time(NULL));
	
    /* Faire. Part 1, exercice 6, question 3 */
    // Création de 20 proies et 20 prédateurs à des positions aléatoires
	for(i = 0; i < 20; i++){
		ajouter_animal(rand()%SIZE_X, rand()%SIZE_Y, energie, &liste_proie);
        ajouter_animal(rand()%SIZE_X, rand()%SIZE_Y, energie, &liste_predateur);
	}

    assert(liste_proie != NULL);
    assert(liste_predateur != NULL);

    // Vérification des nombres de proies et des prédateurs
    int nbproie = compte_animal_it(liste_proie);
    int nbpred = compte_animal_it(liste_predateur);
  
    printf("Nb proies (*) : %5d\tNb predateurs (0) : %5d\n", nbproie, nbpred);

    // Affichage de l'écosystème
    printf("\n Ecosysteme initiale : \n");
	if (liste_proie != NULL || liste_predateur != NULL) {
        afficher_ecosys(liste_proie, liste_predateur);
    }

    /* Faire. Part 1, exercice 6, question 7 */ 
    printf("\nSupression de trois proies et deux predateurs\n");

    // On enlève 3 proies et 2 prédateurs avant la libération de la liste
    enlever_animal(&liste_proie, liste_proie);
    enlever_animal(&liste_proie, liste_proie);
    enlever_animal(&liste_proie, liste_proie);
    enlever_animal(&liste_predateur, liste_predateur);
    enlever_animal(&liste_predateur, liste_predateur);

    // Vérifier que les comptages sont corrects
    //printf("Nb proies (*) : %5d\tNb predateurs (0) : %5d\n", compte_animal_rec(liste_proie), compte_animal_rec(liste_predateur));
    // %5d : nombre affiché avec minimum 5 caractères de large
    //       si nombre < 3 chiffres, des espaces seront ajoutés à gauche

    //Affichage de l'écosystème après avoir enlevé quelques animaux
    if (liste_proie != NULL || liste_predateur != NULL) {
        afficher_ecosys(liste_proie, liste_predateur);
    }

    /* Faire. Part 1, Exercice 6, question 5 */
    //Libération de toute la mémoire allouée
    /*
    liste_proie = liberer_liste_animaux(liste_proie);
    liste_predateur = liberer_liste_animaux(liste_predateur);
    */

    /* Faire. Part 2, Exercice 3, question 1 */
    //ecriture et lecture ecosys
    ecrire_ecosys("ecosysteme.txt", liste_predateur, liste_proie);

    Animal *liste_predateur2 = NULL;
    Animal *liste_proie2 = NULL;

    lire_ecosys("ecosysteme.txt", &liste_predateur2, &liste_proie2);

    printf("\n Vérification que les écosystèmes lus et écris sont les mêmes \n");
    afficher_ecosys(liste_proie2, liste_predateur2);
    printf("\n");
 
    liste_predateur = liberer_liste_animaux(liste_predateur);
    liste_proie = liberer_liste_animaux(liste_proie);
    liste_predateur2 = liberer_liste_animaux(liste_predateur2);
    liste_proie2 = liberer_liste_animaux(liste_proie2);

    return 0;
}