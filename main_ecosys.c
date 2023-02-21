// Ina Campan 21108406
// Sarah Kaci Chaouche 21108956

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"

#define NB_PROIES 50
#define NB_PREDATEURS 20
#define T_WAIT 2000000
#define MAX_ITER 200

/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.1;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;


int main(void) {
 
  /* A completer. Part 2:
   * exercice 4, questions 2 et 4 
   * exercice 6, question 2
   * exercice 7, question 3
   * exercice 8, question 1
   */
  //Exercice 4 Q1
  srand(time(NULL));
  Animal *a = creer_animal(19, 49, 10.); //variable de test
  a->dir[0] = 1;
  a->dir[1] = 1;
  a->suivant = NULL;
  printf("Test deplacement\n");
  //On affiche du deplacement
  for(int i = 0; i<10; i++){
    bouger_animaux(&*a);
    printf("direction : (%d,%d)\n", a->dir[0], a->dir[1]);
    printf("X : %d, Y : %d\n", a->x, a->y);
  }

  //Exercice 4 Q2
  Animal *b = creer_animal(0, 0, 10.);
  printf("Test reproduce\n");
  for(int j = 0; j<4; j++){
    reproduce(&b, 1.);
    printf("Nb d'animaux : %d\n", compte_animal_it(b));
  }

  a = liberer_liste_animaux(a);
  b = liberer_liste_animaux(b);

  printf("Exercice 5 Question 2 - Test rafraichir\n");
  Animal *liste_proie = NULL;
  int energie=10;
  int i,j;
  for(i = 0; i<NB_PROIES; i++){
    ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_proie);
  }
  Animal *liste_predateur = NULL;
  for(i = 0; i<NB_PREDATEURS; i++){
    ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_predateur);
  }
  afficher_ecosys(liste_proie,liste_predateur);

  int nb = 0;
  int monde[SIZE_X][SIZE_Y];
   for(i = 0; i<SIZE_X; i++){
    for(j = 0; j<SIZE_Y; j++){
      monde[i][j] = 0;
    }
  }

  while((nb<MAX_ITER)&&((liste_proie)||(liste_predateur))){
    rafraichir_proies(&liste_proie, monde);
    rafraichir_predateurs(&liste_predateur, &liste_proie);
    rafraichir_monde(monde);
    afficher_ecosys(liste_proie,liste_predateur);
    usleep(T_WAIT);
    nb++;
  }

  if(liste_predateur){
    liste_predateur = liberer_liste_animaux(liste_predateur);
  }
  if(liste_proie){
    liste_proie = liberer_liste_animaux(liste_proie);
  }
  assert(liste_predateur == NULL);
  assert(liste_proie == NULL);

  return 0;
}

