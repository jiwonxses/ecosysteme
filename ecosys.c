// Jiwon KIM et Nguyen Hanh Dung 

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ecosys.h"

/* PARTIE 1*/

/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na); //éviter erreur de segmentation
  // la fonction est arrêtée lorsque assert est fausse
  // vérifie que le pointeur retouné par malloc n'est pas NULL

  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1; // -1 0 ou 1
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;

  return na;
}


/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  /*A Completer*/
  // ajout d'un animal à la position x et y

  Animal *na = creer_animal(x, y, energie);
  assert(na);
  assert(na->x >= 0 && na->x < SIZE_X); 
  assert(na->y >= 0 && na->y < SIZE_Y);
  // vérifier que les coordonnées sont correctes

  *liste_animal = ajouter_en_tete_animal(*liste_animal, na);
  // modifie directement la liste dans la fonction
  // on ne retourne pas l'adresse du premier element de la liste

  return ;
}


/* A Faire. Part 1, exercice 5 (Exercice 6), question 5 (question 7) */
void enlever_animal(Animal **liste, Animal *animal) {
  /*A Completer*/
  // enlever un animal de la liste et de libérer la mémoire associée

  if (*liste == NULL || animal == NULL) return;
  // si la liste ou l'animal est vide, on retourne sans rien faire

  Animal *tmp = *liste; 
  Animal *prec = NULL;

  while((tmp) && (tmp != animal)){
    prec = tmp;
    tmp = tmp ->suivant;
  }
  // on cherche l'animal dans la liste

  if (tmp == NULL) return;
  // si l'animal n'est pas dans la liste, on retourne sans rien faire

  if (prec == NULL) {
    *liste = (*liste)->suivant;
  }
  // si l'animal est le premier élément de la liste

  else {
    prec->suivant = tmp->suivant;
  }
  // sinon, on relie l'élément précédent au suivant de l'animal
  
  free(tmp);
  // libération de la mémoire associée à l'animal

  return ;
}

/* A Faire. Part 1, exercice 6, question 7 (question 4) */
Animal* liberer_liste_animaux(Animal *liste) {
  /*A Completer*/
  // libérer la mémoire allouée pour la liste 

  Animal *tmp;

	while (liste != NULL){
    tmp = liste;
    liste = liste -> suivant;
    free(tmp);
  }

	return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
// la correction était de bien mettre i avec SIZE_X et j avec SIZE_Y
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*'; // au moins une proie
    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@'; // des proies et et des prédateurs
      } else {
        ecosys[pa->x][pa->y] = 'O'; // au moins un prédateur
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  
  printf("Nb proies (*) : %5d\tNb predateurs (0) : %5d\n", nbproie, nbpred);

  return ;
}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Faire. Part 2, Exercice 3, question 1 */

void ecrire_ecosys(const char* nom_fichier, Animal* liste_predateurs, Animal* liste_proies) {
  FILE *f = fopen(nom_fichier,"w"); //écriture
  Animal *tmp = NULL;

  if (f == NULL){
    printf("Problème ouverture fichier %s \n", nom_fichier);
    return; 
    //pas besoin de continuer
  }

  // écriture proies :
  fprintf(f, "<proies>\n");

  tmp = liste_proies;
  while(tmp) {
    fprintf(f, "x=%d y=%d dir=[%d %d] e=%f\n", tmp->x, tmp->y, tmp->dir[0], tmp->dir[1], tmp->energie);
    tmp = tmp->suivant;
  }

  fprintf(f, "</proies>\n");

  // écriture prédateurs :
  fprintf(f, "<predateurs>\n");

  tmp = liste_predateurs;
  while(tmp) {
    fprintf(f, "x=%d y=%d dir=[%d %d] e=%f\n", tmp->x, tmp->y, tmp->dir[0], tmp->dir[1], tmp->energie);
    tmp = tmp->suivant;
  }

  fprintf(f, "</predateurs>\n");
  
  fclose(f);
}


void lire_ecosys(const char *nom_fichier, Animal **liste_predateur, Animal **liste_proie){
  FILE *f = fopen (nom_fichier, "r"); //lecture

  if (f == NULL){
    printf ("Erreur ouverture (lecture) : %s\n", nom_fichier);
    return; 
  }

  char buffer[256];
  // suffisemment grand pour mettre toute la chaine dedans
  int x_lu, y_lu, dir_lu[2];
  float e_lu;

  // lecture proies : 
  fgets(buffer, 256, f); // lit "<proies>\n" 
  assert(strncmp(buffer, "<proies>\n", 8) == 0);
  fgets(buffer, 256, f); //lecture 1ère proie

  while (strncmp(buffer, "</proies>", 9) != 0) { // pour trouver la fin des proies
    // Extraire donnée
    sscanf(buffer, "x=%d y=%d dir=[%d %d] e=%f\n", &x_lu, &y_lu, &dir_lu[0], &dir_lu[1], &e_lu);

    // Création Animal
    Animal *a_lu = creer_animal(x_lu, y_lu, e_lu);
    a_lu->dir[0] = dir_lu[0]; //car creer_animal met dir[0 1] aléatoirement, on doit donc les remettre bien
    a_lu->dir[1] = dir_lu[1];

    // Ajout animal en tête de la liste
    a_lu->suivant = *liste_proie; 
    *liste_proie = a_lu; 

    // Lecture de la ligne suivante
    fgets(buffer, 256, f);
  }

  // lecture prédateurs :

  fgets(buffer, 256,f); // lit "<predateur>\n" 
  assert(strncmp(buffer,"<predateurs>\n", 12) == 0); 
  fgets(buffer, 256, f); //lecture 1er prédateur

  while (strncmp(buffer, "</predateurs>", 13) != 0) {
    sscanf(buffer, "x=%d y=%d dir=[%d %d] e=%f\n", &x_lu, &y_lu, &dir_lu[0], &dir_lu[1], &e_lu); 
    
    Animal *a_lu = creer_animal(x_lu, y_lu, e_lu);
    a_lu->dir[0] = dir_lu[0]; 
    a_lu->dir[1] = dir_lu[1];
    
    a_lu->suivant = *liste_predateur; 
    *liste_predateur = a_lu; 
    
    fgets(buffer, 256, f);
  }
    
  fclose(f);
}


/* Part 2. Exercice 4 (Exercice 2), question 1 */
void bouger_animaux(Animal *la) {
  /*A Completer*/
  // bouger tous les animaux contenus dans la liste

  while (la) {
    if ((rand() / (float)RAND_MAX) <= p_ch_dir) { 
    // si le nombre aleatoire compris entre 0 et 1 est inferieur a la probabilite de changer de direction de deplacement
      
      la->dir[0] = (rand()%3)-1; 
      // pour un tirage entre -1 0 et 1
      la->dir[1] = (rand()%3)-1;
    }

    la->x = (la->x + la->dir[0] + SIZE_X) % SIZE_X;
    //pour respecter la toricité du monde 
    assert(la->x >= 0 && la->x < SIZE_X);
    la->y = (la->y + la->dir[1] + SIZE_Y) % SIZE_Y;
    assert(la->y >= 0 && la->y < SIZE_Y);

    la = la->suivant;
  }

  return ;
}

/* Part 2. Exercice 4 (Exercice 2), question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
  /*A Completer*/
  // permet de gérer la reproduction des animaux

  Animal *ani = liste_animal ? *liste_animal : NULL;
  // teste si liste_animal est différent de NULL
  // Si liste_animal est non-NULL, l'expression retourne *liste_animal, 
  // c'est-à-dire la valeur pointée par liste_animal

  while (ani) {
    if ((rand() / (float)RAND_MAX) <= p_reproduce) {
      ajouter_animal(ani->x, ani->y, ani->energie / 2.0, liste_animal);
      ani -> energie /= 2.0;
    }
    
    ani = ani->suivant;
  }
  
  return ;
}

/* Part 2. Exercice 6 (Exercice 5), question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  /*A Completer*/
  // mise à jour des proies

  assert(liste_proie); // on vérifie que la liste n'est pas vide
  Animal *tmp = *liste_proie;
  Animal *mort;

  bouger_animaux(*liste_proie);

  while (tmp) { 
    tmp->energie--;

    int nbHerbe = monde[tmp->x][tmp->y];
    if (nbHerbe >= 0) { // cas où il y a de l'herbe sur la case de la proie
      tmp->energie += nbHerbe; //la proie récupère l'energie de l'herbe
      monde[tmp->x][tmp->y] = temps_repousse_herbe;
    }

    if (tmp->energie <= 0){ //cas où la proie n'a plus d'énergie, on la supprime
      mort = tmp;
      tmp = tmp->suivant;
      enlever_animal(liste_proie, mort);
    }

    else {
      tmp = tmp->suivant;
    }
  }
  reproduce(liste_proie, p_reproduce_proie);
}

/* Part 2. Exercice 7 (Exercice 6), question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
  /*A Completer*/
  // Renvoie un pointeur sur une premiere proie en x et y

  while (l) {
    if (l->x == x && l->y == y) { //on retourne l'animal en position x y si il existe
      return l;
    }
    l = l->suivant;
  }  

  return NULL;
} 

/* Part 2. Exercice 7 (Exercice 6), question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  /*A Completer*/
  
  assert(liste_predateur); // on vérifie que la liste n'est pas vide
  
  Animal *tmp = *liste_predateur;
  Animal *mort, *proie;

  bouger_animaux(*liste_predateur);

  while (tmp) { 
    tmp->energie--;
    proie = animal_en_XY(*liste_proie,tmp->x, tmp->y); 
    if(proie) { //si il y a une proie sur la case du prédateur
      mort = proie;
      tmp->energie += mort->energie; // absorption de l'energie de la proie
      enlever_animal(liste_proie, mort);
    }

    if (tmp->energie <= 0) { //cas où le prédateur n'a plus d'energie
      mort = tmp;
      tmp = tmp->suivant;
      enlever_animal(liste_predateur, mort);
    }
    else {
      tmp = tmp->suivant;
    }
  }

  reproduce(liste_predateur, p_reproduce_predateur);
}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]) {
  /*A Completer*/
  // A chaque iteration, la quantite d'herbe de chaque case est incrementee de 1

  for (int i = 0; i < SIZE_X; i++) {
    for (int j = 0; j < SIZE_Y; j++) {
      monde[i][j]++; //on ajoute un à chaque case du monde
    }
  }
}
