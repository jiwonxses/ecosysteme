// Jiwon KIM et Nguyen Hanh Dung 

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000
#define MAXIT 200


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir = 0.01;
float p_reproduce_proie = 0.4;
float p_reproduce_predateur = 0.5;
int temps_repousse_herbe = -15;



int main(void) {

  /* A completer. Part 2:
   * exercice 4, questions 2 et 4 
   * exercice 6, question 2
   * exercice 7, question 3
   * exercice 8, question 1
   */

  int energie = 10;
  Animal *liste_predateurs = NULL;
  Animal *liste_proies = NULL;

  /* Faire. Part 2, Exercice 4, question 1 */
  // création d'un seul animal
  /*
  Animal *a = creer_animal(0, 0, energie);
  liste_predateurs = a;

  afficher_ecosys(liste_proies, liste_predateurs);
  */
  // on va modifier bouger_animaux :
  //  la->dir[0] = -1; la->dir[1] = -1;
  // Pour vérifier que le déplacement fonctionne dans une distance donée
  // on va mettre p_ch_dir = 1 pour que l'animal bouge
  /*
  bouger_animaux(a); 

  printf("Le prédateur va bouger.\n");

  afficher_ecosys(liste_proies, liste_predateurs);
  */
  /* Faire. Part 2, Exercice 4, question 2 */
  /*
  for (int i = 0; i < 4; i++) {
    reproduce(&liste_predateurs, p_reproduce_predateur);
    afficher_ecosys(liste_proies, liste_predateurs);
  }
  */
  // on va mettre p_reproduce_predateur = 1 pour vérifier que le nombre d'animaux est bien multiplié par 2 à chaque mise à jour

  /* Faire. Part 2, Exercice 5, question 2 */
  srand(time(NULL));

  // création des 20 proies et prédateurs
  for (int i = 0; i < 20; i++) { 
    ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y, energie, &liste_proies);
    ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y, energie, &liste_predateurs);
  }

  afficher_ecosys(liste_proies,liste_predateurs);

  int nbIt = 0;
  int monde[SIZE_X][SIZE_Y]={0}; // Initialisation du monde et de l'herbe
  
  FILE *f = fopen("Evol_Pop.txt", "w"); // Ouverture du fichier avec l'évolution du nombre d'animaux
  if (f == NULL) {
    printf ("Erreur ouverture : %s\n", "Evol_Pop.txt");
  }

  while (liste_proies && liste_predateurs && nbIt++ <= MAXIT){
    clear_screen();

    //évolution des populations
    rafraichir_proies(&liste_proies, monde); 
    rafraichir_predateurs(&liste_predateurs, &liste_proies);
    rafraichir_monde(monde);

    //écriture dans le fichier
    fprintf(f, "%d\t%d\t%d\n", nbIt, compte_animal_rec(liste_proies), compte_animal_rec(liste_predateurs)); 

    
    printf ("\nItération n°%d\n", nbIt);
    afficher_ecosys(liste_proies, liste_predateurs);
    usleep(T_WAIT);
  }

  fclose(f);

  /* Faire. Part 2, Exercice 7, question 1 */
  /*
  int herbe[SIZE_X][SIZE_Y];
  int i,j;
  for (i = 0; i < SIZE_X; i++) {
    for (j = 0; j < SIZE_Y; j++) {
      herbe[i][j] = 0;
    }
  }
  */

  FILE *gnuplot = popen("gnuplot -persistent", "w");

  if (gnuplot == NULL){
    perror("Erreur lors de l'ouverture de gnuplot");
    return 1;
  }

  //envoyer des commandes à gnuplot
  fprintf(gnuplot, "set title 'Simulation ecosystème'\n");
  fprintf(gnuplot, "plot 'Evol_pop.txt' using 1:2 with lines title 'proies'\n");
  fprintf(gnuplot, "replot 'Evol_pop.txt' using 1:3 with lines title 'prédateurs'\n");

  //fermer le pipe
  pclose(gnuplot);
  
  //Pour libérer la mémoire
  liste_predateurs = liberer_liste_animaux(liste_predateurs);
  liste_proies = liberer_liste_animaux(liste_proies);

  return 0;
}

