#include "functiiStiva.h"
#include "functiiLG.h"
#include "structuri.h"

/*- macrodefinitii utile -*/
/*- acces la campuri -*/
#define DIME(a) (((ASt)(a))->dime)
#define VF(a) (((ASt)(a))->vf)

void *InitS(size_t d)
{
    ASt s;
    s = (ASt)malloc(sizeof(TStiva));
    if (!s)
        return NULL;
    s->dime = d;
    s->vf = NULL;
    return (void *)s;
}

int Push(void *s, void *ae)
{
    TL aux;
    aux = (TL)malloc(sizeof(TCelulaG));
    if (!aux)
        return 0;

    aux->info = ae;
    aux->urm = VF(s);
    VF(s) = aux;
    return 1;
}

int Pop(void *s, void *ae)
{
    TL aux = VF(s); //varful stivei
    if (aux == NULL)
        return 0;
    memcpy(ae, aux->info, DIME(s));
    VF(s) = aux->urm;
    free(aux);
    return 1;
}

void Rastoarna(void *d, void *s)
{
    TL p, u;
    p = VF(s);
    while (p)
    {
        u = p->urm;
        p->urm = VF(d);
        VF(d) = p;
        p = u;
    }
    VF(s) = NULL;
}

void ResetS(void *s, TF free_element)
{
    //distrugere lista VF(s);
    TL aux = VF(s);
    while (aux)
    {
        TL p = aux;
        aux = aux->urm;
        //eliberare p : elibverare info + celula
        free_element(p->info);
        free(p);
    }
    VF(s) = NULL;
}

void DistrS(void **s, TF free_element)
{
    ResetS(*s, free_element);
    free(*s);
    *s = NULL;
}

void AfiS(void *s, TAF afiEL, FILE *outputFile)
{
    fprintf(outputFile, "[");

    TL aux = VF(s);
    while (aux)
    {
        afiEL(aux->info, outputFile);
        if (aux->urm != NULL)
            fprintf(outputFile, ", ");
        aux = aux->urm;
    }

    fprintf(outputFile, "].\n");
}

void *CautareElemS(void *s, void *nume, TFCmp comp)/* returneaza elementul cu numele dat */
{
    TL aux = VF(s);
    while (aux)
    {
        if (comp(aux->info, nume) == 0)
            return (void *)aux->info;
        aux = aux->urm;
    }
    return NULL;
}

void EliminareS(void *s, void *nume, TFCmp comp)/* elimina elementul cu numele dat din stiva */
{

    void *s_aux = InitS(DIME(s));
    TL aux;

    while (VF(s))
    {
        aux = malloc(sizeof(TCelulaG));
        aux->info = malloc(sizeof(TSerial));

        Pop(s, aux->info);

        if (comp(aux->info, nume) != 0)
            Push(s_aux, aux->info);
        else
            free(aux->info);
        free(aux);
    }

    Rastoarna(s, s_aux); //s_aux este vida dupa
    free(s_aux);
}
