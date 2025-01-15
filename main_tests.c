// Jiwon KIM et Nguyen Hanh Dung 

#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "ecosys.h"

float p_ch_dir = 0.01; //probabilite de changer de direction de deplacement
float p_reproduce_proie = 0.4;
float p_reproduce_predateur = 0.5;
int temps_repousse_herbe = -15;

int main(void) {
  int i;
  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;
  int energie=10;

  srand(time(NULL));

  Animal *a1 = creer_animal(0,10, energie);
  Animal *a2 = creer_animal(15,35, energie);
  Animal *a3 = creer_animal(2,42, energie);
  Animal *a4 = creer_animal(18,13, energie);
  
  a1->suivant=a2;
  a2->suivant=a3;
  a3->suivant=a4;

  liste_proie=a1;

  Animal *a5 = creer_animal(2,5, energie);
  Animal *a6 = creer_animal(15,35, energie);
  Animal *a7 = creer_animal(9,22, energie);
  Animal *a8 = creer_animal(17,3, energie);
  
  a5->suivant=a6;
  a6->suivant=a7;
  a7->suivant=a8;

  liste_predateur=a5;
  
  printf("\n Ecosysteme initiale : \n");
  afficher_ecosys(liste_proie,liste_predateur);  

  bouger_animaux(liste_proie);
  bouger_animaux(liste_predateur);

  printf("\n Bouger proies et predateurs\n");
  afficher_ecosys(liste_proie,liste_predateur);

  enlever_animal(&liste_proie,a1);
  enlever_animal(&liste_predateur,a8);

  printf("\n Suppression d'un proie et d'un predateur \n");
  afficher_ecosys(liste_proie,liste_predateur);

  return 0;
}
