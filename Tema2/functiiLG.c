/*--- functiiLG.c -- operatii de baza pentru lista simplu inlantuita generica---*/
#include "functiiLG.h"

int InsLG(TL *aL, void *ae, TFCmp f)/* returneaza pozitia pe care a fost inserat elementul */
{
	TL aux = malloc(sizeof(TCelulaG));
	if (!aux)
		return 0;
	if (*aL == NULL || f(ae, (*aL)->info) < 0)
	{
		aux->info = ae;
		aux->urm = *aL;
		*aL = aux;
		return 1;
	}

	int poz = 2;
	TL p, ant;
	for (ant = *aL, p = (*aL)->urm; p != NULL; p = p->urm, ant = ant->urm)
	{
		if (f(ae, p->info) < 0) //inseram inaintea lui p
		{
			aux->info = ae;
			aux->urm = p;
			ant->urm = aux;
			return poz;
		}
		poz++;
	}

	{
		aux->info = ae;
		ant->urm = aux;
		aux->urm = NULL;
		return poz;
	}
}

int InsLG_top10(TL *aL, void *ae, int poz)	/* insereaza elementul in lista pe pozitia data */
{
	if(poz > 10)
		return 0;

	TL aux = malloc(sizeof(TCelulaG));
	if (!aux)
		return 0;
	
	if(poz == 1)
	{
		aux->info = ae;
		aux->urm = *aL;
		*aL = aux;
		return 1;
	}
	TL p = *aL;
	int i;
	for(i = 1; i < poz - 1 && p != NULL; i++) 
		p = p->urm;		
	/*la iesirea din for p este elem de pe pozitia poz - 1 */

	{ /* inseram dupa elementul p */
		aux->info = ae;
		aux->urm = p->urm;
		p->urm = aux;
		return 1;
	}
}

void DistrugeLG(TL *aL, TF free_elem) /* distruge lista */
{
	while (*aL != NULL)
	{
		TL aux = *aL; /* adresa celulei eliminate */
		if (!aux)
			return;

		free_elem(aux->info); /* elib.spatiul ocupat de element*/
		*aL = aux->urm;		  /* deconecteaza celula din lista */
		free(aux);			  /* elibereaza spatiul ocupat de celula */
	}
}

size_t LungimeLG(TL a) /* numarul de elemente din lista */
{
	size_t lg = 0;
	TL p = a;

	/* parcurge lista, numarand celulele */
	for (; p != NULL; p = p->urm)
		lg++;

	return lg;
}

void AfisareLG(TL aL, TAF afiEL, FILE *outputFile)	/* afiseaza elementele listei */
{
	fprintf(outputFile, "[");
	TL p = aL;
	for (; p; p = p->urm)
	{
		afiEL(p->info, outputFile);
		if (p->urm != NULL)
			fprintf(outputFile, ", ");
	}
	fprintf(outputFile, "].\n");
}

void* CautareElemLG(TL a, void* nume, TFCmp comp)	/* cauta si returneaza elementul cu numele dat */
{
	TL p = a;
	for( ; p != NULL; p = p->urm)
		if(comp(p->info, nume) == 0)
			return (void*)p->info;
	
	return NULL;
}

void* EliminareLG(TL *aL, void *nume, TFCmp comp)	/* elimina elementul cu numele dat din lista si il returneaza */
{
	TL p, ant;
	for (ant = NULL, p = *aL; p != NULL; ant = p, p = p->urm)
		if (comp(p->info, nume) == 0)
		{
			if (ant == NULL)
				*aL = p->urm;
			else
				ant->urm = p->urm;
			void* element = (void *)p->info;
			free(p);
			return element;
		}
	return NULL;
}

void EliminareLG_top10(TL aL, TF free_element)	/* elimina elementul de pe ultima pozitie */
{
	TL p = aL;
	while(p->urm->urm != NULL)
        p = p->urm;

	TL last = p->urm;
	free_element(last->info);
	free(last);
    p->urm = NULL;
}
