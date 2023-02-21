// Ina Campan 21108406
// Sarah Kaci Chaouche 21108956

#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"

#define NB_PREDATEURS 20
#define NB_PROIES 20
/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;


int main(void){
    
    printf("PARTIE 1 des tests\n");
    Animal *liste_proie = NULL;
    Animal *liste_predateur = NULL;
    int energie=10;
    srand(time(NULL));
    int i ;
    for(i = 0; i<NB_PROIES; i++){
        ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_proie);
    }

    for(i = 0; i<NB_PREDATEURS; i++){
        ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_predateur);
    }
    
    assert(compte_animal_it(liste_predateur)==NB_PREDATEURS);
    assert(compte_animal_it(liste_proie)==NB_PROIES);

    afficher_ecosys(liste_proie, liste_predateur);

    liste_predateur = liberer_liste_animaux(liste_predateur);
    liste_proie = liberer_liste_animaux(liste_proie);
    
    assert(liste_predateur == NULL);
    assert(liste_proie == NULL);

    printf("\nPARTIE 2 des tests (entrees-sorties)\n");
    lire_ecosys("lecture.txt", &liste_predateur, &liste_proie);
    afficher_ecosys(liste_proie, liste_predateur);
    ecrire_ecosys("ecriture.txt", liste_predateur, liste_proie);

    liste_predateur = liberer_liste_animaux(liste_predateur);
    liste_proie = liberer_liste_animaux(liste_proie);

    assert(liste_predateur == NULL);
    assert(liste_proie == NULL);

    return 0;
}