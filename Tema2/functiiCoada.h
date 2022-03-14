#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include "functiiLG.h"

typedef struct coada
{
    size_t dime; /* dim.element */
    TL ic, sc; /* adr.prima, ultima celula */
} TCoada, *AQ;


typedef void (*TF)(void*);     /*eliberare un element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TAF)(void*, FILE*);   /* functie afisare */


void *InitQ(size_t d);  /* creeaza coada vida cu elemente de dimensiune d */
int InsQ(void *c, void *ae);  /* adauga element la sfarsitul cozii */  
int ExtrQ(void *c, void *ae); /* extrage primul element din coada la adresa ae */
void ConcatQ(void *ad, void *as); /* concatenare (muta toate elem.din sursa) */
void ResetQ(void *c, TF free_element);  /* transforma coada in coada vida */
void DistrQ(void **c, TF free_element); /* elibereaza intregul spatiu ocupat de coada */

void AfiQ(void *c, TAF afiEL, FILE *outputFile); /* afiseaza elementele din coada */
void *CautareElemQ(void *c, void *nume, TFCmp comp); /* returneaza elementul cu numele dat */
void EliminareQ(void *c, void *nume, TFCmp comp); /* elimina elementul cu numele dat din coada */
int LungimeQ(void* c);  /* numarul de elemente din coada */


