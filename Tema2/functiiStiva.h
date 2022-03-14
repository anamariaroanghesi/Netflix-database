#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include "functiiLG.h"

typedef struct stiva
{
    size_t dime; /* dim.element */
    TL vf;   /* adresa celulei din varf */
} TStiva, *ASt;


typedef void (*TF)(void*);     /*eliberare un element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TAF)(void*, FILE*);   /* functie afisare */

void *InitS(size_t d);  /* initializeaza stiva cu elem.de dimensiune d */
int Push(void *s, void *ae);    /* pune element in varful stivei */
int Pop(void *s, void *ae); /* extrage elementul din varful stivei la adresa ae */
void Rastoarna(void *d, void *s);   /* suprapune inversul sursei peste destinatie */
void ResetS(void *s, TF free_element);  /* transforma stiva in stiva vida */
void DistrS(void **s, TF free_element); /* elibereaza intregul spatiu ocupat de stiva */

void AfiS(void *s, TAF afiEL, FILE *outputFile); /* afiseaza elementele stivei */
void* CautareElemS(void* s, void* nume, TFCmp comp);    /* returneaza elementul cu numele dat */
void EliminareS(void *s, void *nume, TFCmp comp); /* elimina elementul cu numele dat din stiva */


