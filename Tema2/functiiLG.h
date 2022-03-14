/*--- LISTA SIMPLU INLANTUITA GENERICA ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct celulag
{
  void *info;          /* adresa informatie */
  struct celulag *urm; /* adresa urmatoarei celule */
} TCelulaG, *TL;       /* tipurile Celula, Lista  */

typedef int (*TFElem)(void *);        /* functie prelucrare element */
typedef int (*TFCmp)(void *, void *); /* functie de comparare doua elemente */
typedef void (*TF)(void *);           /*eliberare un element */
typedef void (*TAF)(void *, FILE *);  /* functie afisare */

/* functii lista generica */
int InsLG(TL *, void *, TFCmp); /* returneaza pozitia pe care a fost inserat elementul */
void DistrugeLG(TL *aL, TF fe);   /* distruge lista */
size_t LungimeLG(TL );         /* numarul de elemente din lista */
void AfisareLG(TL, TAF, FILE *outputFile);/* afiseaza elementele din lista*/

void* CautareElemLG(TL a, void* nume, TFCmp comp); /* cauta si returneaza elementul cu numele dat */
void* EliminareLG(TL *l, void *nume, TFCmp comp); /* elimina elementul cu numele dat si il returneaza */

int InsLG_top10(TL *aL, void *ae, int poz); /* insereaza elementul in lista pe pozitia data */
void EliminareLG_top10(TL aL, TF free_element); /* elimina elementul de pe ultima pozitie */

#endif
