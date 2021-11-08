#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"

/* PARTIE 1*/
/* Fourni: Part 1, exercice 3, question 2 */
Animal *creer_animal(int x, int y, float energie)
{
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}

/* Fourni: Part 1, exercice 3, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal)
{
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 5, question 1 */
void ajouter_animal(int x, int y, float energie, Animal **liste_animal)
{
  Animal *tmp_animal = creer_animal(x, y, energie);
  *liste_animal = ajouter_en_tete_animal(*liste_animal, tmp_animal);
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal)
{
  Animal *prev;
  Animal *to_find;
  if (*liste != NULL)
  {
    if ((*liste)->x == animal->x && (*liste)->y == animal->y)
    {
      to_find = *liste;
      *liste = (*liste)->suivant;
      free(to_find);
    }
    else
    {
      prev = *liste;
      to_find = (*liste)->suivant;
      while (to_find)
      {
        if ((to_find)->x = animal->x && to_find->y == animal->y)
        {
          prev->suivant = to_find->suivant;
          free(to_find);
          break;
        }
        prev = to_find;
        to_find = to_find->suivant;
      }
    }
  }
}

/* A Faire. Part 1, exercice 5, question 2 */
Animal *liberer_liste_animaux(Animal *liste)
{
  Animal *tmp = NULL;
  while (liste)
  {
    tmp = liste->suivant;
    free(liste);
    liste = tmp;
  }
  return NULL;
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_rec(Animal *la)
{
  if (!la)
    return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_it(Animal *la)
{
  int cpt = 0;
  while (la)
  {
    ++cpt;
    la = la->suivant;
  }
  return cpt;
}

/* Part 1. Exercice 4, question 1 */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur)
{
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  int nbpred = 0, nbproie = 0;
  Animal *pa = NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; i++)
  {
    for (j = 0; j < SIZE_Y; j++)
    {
      ecosys[i][j] = ' ';
    }
  }

  /* on ajoute les proies */
  while (liste_proie)
  {
    Animal *tmp = liste_proie->suivant;
    ecosys[liste_proie->x][liste_proie->y] = 'H';
    liste_proie = tmp;
  }

  /* on ajoute les predateurs */
  while (liste_predateur)
  {
    Animal *tmp = liste_predateur->suivant;
    ecosys[liste_predateur->x][liste_predateur->y] = 'C';
    liste_predateur = tmp;
  }

  /* on affiche le tableau */
  for (j = 0; j <= SIZE_Y + 1; j++)
  {
    for (i = 0; i <= SIZE_X + 1; i++)
    {
      if ((i == 0 && j == 0) || (i == 0 && j == SIZE_Y + 1) || (i == SIZE_X + 1 && j == SIZE_Y + 1) || (i == SIZE_X + 1 && j == 0))
        printf("+");
      else if ((i == 0 && j < SIZE_Y + 2) || (i == SIZE_X + 1 && j < SIZE_Y + 2))
        printf("|");
      else if ((i != 0 && j == 0) || (i != 0 && j == SIZE_Y + 1))
        printf("-");
      else
        printf("%c", ecosys[i - 1][j - 1]);
    }
    printf("\n");
  }
}

void clear_screen()
{
  printf("\x1b[2J\x1b[1;1H"); /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/
/* Part 2. Exercice 4, question 1 */
void move(Animal *la)
{
  if (la->x == 0 && la->y == 0 && la->dir[0] >= 1 && la->dir[1] <= -1)
  {
    la->x = SIZE_X - 1;
    la->y = SIZE_Y - 1;
  }
  else if (la->x == SIZE_X - 1 && la->y == 0 && la->dir[0] >= 1 && la->dir[1] >= 1)
  {
    la->x = 0;
    la->y = SIZE_Y - 1;
  }
  else if (la->x == 0 && la->y == SIZE_Y - 1 && la->dir[0] <= -1 && la->dir[1] <= -1)
  {
    la->x = SIZE_X - 1;
    la->y = 0;
  }
  else if (la->x == SIZE_X - 1 && la->y == SIZE_Y - 1 && la->dir[0] <= -1 && la->dir[1] >= 1)
  {
    la->x = 0;
    la->y = 0;
  }
  else if (la->x + la->dir[1] >= SIZE_X)
    la->x = 0;
  else if (la->x + la->dir[1] < 0)
    la->x = SIZE_X - 1;
  else if (la->y == 0 && la->dir[0] > 0)
    la->y = SIZE_Y - 1;
  else if (la->y + la->dir[1] >= SIZE_Y)
    la->y = 0;
  else
  {
    la->x = la->x + la->dir[1];
    la->y = la->y - la->dir[0];
  }
}

void change_direction(Animal *la)
{
  if ((float)rand() / (float)RAND_MAX < p_ch_dir)
  {
    la->dir[0] = rand() % 3 - 1;
    la->dir[1] = rand() % 3 - 1;
  }
}

void bouger_animaux(Animal *la)
{
  Animal *liste_debut = la;
  while (liste_debut)
  {
    change_direction(liste_debut);
    move(liste_debut);
    liste_debut = liste_debut->suivant;
  }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce)
{
  Animal *liste_debut = *liste_animal;
  while (*liste_animal)
  {
    if ((float)rand() / (float)RAND_MAX < p_reproduce)
    {
      ajouter_animal((*liste_animal)->x, (*liste_animal)->y, (*liste_animal)->energie / 2, &liste_debut);
      (*liste_animal)->energie = (*liste_animal)->energie / 2;
    }
    (*liste_animal) = (*liste_animal)->suivant;
  }
  *liste_animal = liste_debut;
}

/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y])
{
  Animal *liste_debut = *liste_proie;
  bouger_animaux(*liste_proie);

  while (*liste_proie != NULL)
  {
    (*liste_proie)->energie--;
    //Manger
    if (monde[(*liste_proie)->x][(*liste_proie)->y] > 0)
    {
      (*liste_proie)->energie = (*liste_proie)->energie + monde[(*liste_proie)->x][(*liste_proie)->y];
      monde[(*liste_proie)->x][(*liste_proie)->y] = temps_repousse_herbe;
    }
    //Enleve les morts
    if ((*liste_proie)->energie < 0)
      enlever_animal(&liste_debut, (*liste_proie));
    (*liste_proie) = (*liste_proie)->suivant;
  }
  reproduce(&liste_debut, 1);
  *liste_proie = liste_debut;
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y)
{
  /*A Completer*/

  return NULL;
}

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie)
{
  /*A Completer*/
}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y])
{
  for (int i = 0; i < SIZE_X; i++)
  {
    for (int j = 0; j < SIZE_Y; j++)
    {
      monde[i][j] = monde[i][j] + 1;
    }
  }
}

void init_tab(int tab[SIZE_X][SIZE_Y], int value)
{
  for (int i = 0; i < SIZE_X; i++)
  {
    for (int j = 0; j < SIZE_Y; j++)
    {
      tab[i][j] = 0;
    }
  }
}
