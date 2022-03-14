#include "functiiCoada.h"
#include "functiiLG.h"
#include "structuri.h"

/*- macrodefinitii utile -*/
/*- acces la campuri -*/
#define IC(a) (((AQ)(a))->ic)
#define SC(a) (((AQ)(a))->sc)
#define DIME(a) (((AQ)(a))->dime)

void *InitQ(size_t d)
{
    AQ c;
    c = (AQ)malloc(sizeof(TCoada));
    if (!c)
        return NULL;
    c->dime = d;
    c->ic = c->sc = NULL;
    return (void *)c;
}

int InsQ(void *c, void *ae)
{
    TL aux;
    aux = (TL)malloc(sizeof(TCelulaG));
    if (!aux)
        return 0;

    aux->info = ae;
    aux->urm = NULL;

    if (IC(c) == NULL && SC(c) == NULL) //daca coada e vida
    {
        IC(c) = aux;
        SC(c) = aux;
        return 1;
    }

    SC(c)->urm = aux;
    SC(c) = aux;
    return 1;
}

int ExtrQ(void *c, void *ae)
{
    if (IC(c) == NULL && SC(c) == NULL)
        return 0;

    TL aux = IC(c);
    IC(c) = aux->urm;

    memcpy(ae, aux->info, DIME(c));
    free(aux);

    if (IC(c) == NULL) //Test daca a fost un singur element in coada
        SC(c) = NULL;
    return 1;
}

void ResetQ(void *c, TF free_element)
{
    TL aux = IC(c);
    while (aux)
    {
        TL p = aux;
        aux = aux->urm;
        
        free_element(p->info);
        free(p);
    }

    IC(c) = SC(c) = NULL;
}

void DistrQ(void **c, TF free_element)
{
    ResetQ(*c, free_element);
    free(*c);
    *c = NULL;
}

void ConcatQ(void *d, void *s)
{
    if (IC(s) == NULL && SC(s) == NULL)
        return;
    if (IC(d) == NULL && SC(d) == NULL)
    {
        IC(d) = IC(s);
        SC(d) = SC(s);
        IC(s) = SC(s) = NULL;
        return;
    }

    SC(d)->urm = IC(s);
    SC(d) = SC(s);
    IC(s) = SC(s) = NULL;
}

void AfiQ(void *c, TAF afiEL, FILE *outputFile)
{
    fprintf(outputFile, "[");

    TL aux = IC(c);
    while (aux)
    {
        afiEL(aux->info, outputFile);
        if (aux->urm != NULL)
            fprintf(outputFile, ", ");
        aux = aux->urm;
    }

    fprintf(outputFile, "].\n");
}

void *CautareElemQ(void *c, void *nume, TFCmp comp)
{
    TL aux = IC(c);
    while (aux)
    {
        if (comp(aux->info, nume) == 0)
            return (void *)aux->info;
        aux = aux->urm;
    }
    return NULL;
}

int LungimeQ(void *c)
{
    int l = 0;
    TL aux = IC(c);
    while (aux)
    {
        l++;
        aux = aux->urm;
    }
    return l;
}

void EliminareQ(void *c, void *nume, TFCmp comp/* , TF free_element */)
{
    void *c_aux = InitQ(DIME(c));
    TL aux;

    while (!(IC(c) == NULL && SC(c) == NULL))
    {
        aux = malloc(sizeof(TCelulaG));
        aux->info = malloc(sizeof(TSerial));

        ExtrQ(c, aux->info);

        if (comp(aux->info, nume) != 0)
            InsQ(c_aux, aux->info);
        else
            free(aux->info);

        free(aux);
    }
    ConcatQ(c, c_aux);
    free(c_aux);
    //DistrQ(&c_aux, free_element);
}

