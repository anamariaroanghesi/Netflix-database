#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

typedef struct 
{
    int ID;
    char *nume;
    double rating;
    int nr_sez;
    int durata_serial;
    void *coada_sez;
}TSerial;

typedef struct 
{
    int nr_ep;
    int durata_sezon;
    void *coada_ep;
}TSezon;

