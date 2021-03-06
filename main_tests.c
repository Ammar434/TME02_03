#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"

#define NB_PROIES 20
#define NB_PREDATEURS 20

int main(void)
{
  //srand(time(NULL));
  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;

  for (int i = 0; i < NB_PROIES; i++)
  {
    int x = rand() % SIZE_X;
    int y = rand() % SIZE_Y;
    int energie = rand() % 5;
    ajouter_animal(x, y, energie, &liste_proie);
  }
  for (int i = 0; i < NB_PREDATEURS; i++)
  {
    int x = rand() % SIZE_X;
    int y = rand() % SIZE_Y;
    int energie = rand() % 5;
    ajouter_animal(x, y, energie, &liste_predateur);
  }

  if (compte_animal_rec(liste_predateur) == NB_PREDATEURS && compte_animal_rec(liste_proie) == NB_PROIES)
    printf("Bon nombre\n");
  else
    printf("Mauvais nombre\n");
  liste_proie->x = 2;
  liste_proie->y = 2;

  afficher_ecosys(liste_proie, liste_predateur);

  liste_proie->dir[0] = -1;
  liste_proie->dir[1] = 1;
  bouger_animaux(liste_proie);
  afficher_ecosys(liste_proie, liste_predateur);

  liberer_liste_animaux(liste_proie);
  liberer_liste_animaux(liste_predateur);
  return 0;
}
