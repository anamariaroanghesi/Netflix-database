#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functiiStiva.h"
#include "functiiCoada.h"
#include "functiiLG.h"
#include "structuri.h"

#define len_nume 33
#define IC(a) (((AQ)(a))->ic)
#define SC(a) (((AQ)(a))->sc)

void AfisareElement(void *element, FILE *outputFile)
{
    TSerial *s = (TSerial *)element;

    fprintf(outputFile, "(%s, %0.1f)", s->nume, s->rating);
}

int CompSerial(void *element1, void *element2) //val>0 => elem1>elem2; val<0 => elem1<elem2
{
    TSerial *s1 = (TSerial *)element1;
    TSerial *s2 = (TSerial *)element2;

    if (s1->rating == s2->rating)
        return strcmp(s1->nume, s2->nume);

    if (s1->rating < s2->rating)
        return 1;
    return -1;
}

int CompNumeSerial(void *serial, void *nume)
{
    TSerial *s1 = (TSerial *)serial;

    return strcmp(s1->nume, nume);
}

void FreeSezon(void *element)
{
    TSezon *sezon = (TSezon *)element;

    TL aux = IC(sezon->coada_ep);
    while (aux)
    {
        TL p = aux;
        aux = aux->urm;
        free(p);
    }

    IC(sezon->coada_ep) = SC(sezon->coada_ep) = NULL;
    free(sezon->coada_ep);
    free(sezon);
}

void FreeSerial(void *element)
{
    TSerial *serial = (TSerial *)element;

    free(serial->nume);
    DistrQ(&(serial->coada_sez), FreeSezon);
    free(serial);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
        return -1;

    char *inputFileName = strdup(argv[1]);
    char *outputFileName = strdup(argv[2]);

    FILE *inputFile = fopen(inputFileName, "rt");
    FILE *outputFile = fopen(outputFileName, "wt");

    char *line = NULL;
    size_t len = 0;
    int i, j;

    TL tendinte = NULL;
    TL documentare = NULL;
    TL tutoriale = NULL;
    TL top10 = NULL;

    void *later = InitQ(sizeof(TSerial));
    void *watching = InitS(sizeof(TSerial));
    void *history = InitS(sizeof(TSerial));

    while (getline(&line, &len, inputFile) != -1)
    {
        int l = strlen(line);
        line[l] = ' ';
        line[l + 1] = '\0';

        char *command = strtok(line, " ");

        if (strcmp(command, "add") == 0)     /*   ADD   */
        {
            TSerial *serial = (TSerial *)malloc(sizeof(TSerial));
            if (!serial)
            {
                fprintf(outputFile, "Eroare alocare serial\n");
                return 0;
            }

            serial->nume = malloc(len_nume);
            if (!serial->nume)
            {
                fprintf(outputFile, "Eroare alocare nume serial\n");
                return 0;
            }

            serial->coada_sez = InitQ(sizeof(TSezon));
            if (!serial->coada_sez)
            {
                fprintf(outputFile, "Eroare alocare coada sezoane\n");
                return 0;
            }

            serial->ID = atoi(strtok(NULL, " "));
            strcpy(serial->nume, strtok(NULL, " "));
            serial->rating = atof(strtok(NULL, " "));
            serial->nr_sez = atoi(strtok(NULL, " "));

            serial->durata_serial = 0;

            for (i = 0; i < serial->nr_sez; i++)
            {
                TSezon *sezon = (TSezon *)malloc(sizeof(TSezon));
                if (!sezon)
                {
                    fprintf(outputFile, "Eroare alocare sezon\n");
                    return 0;
                }

                sezon->coada_ep = InitQ(sizeof(int));
                if (!sezon->coada_ep)
                {
                    fprintf(outputFile, "Eroare alocare coada episoade\n");
                    return 0;
                }

                sezon->nr_ep = atoi(strtok(NULL, " "));

                for (j = 0; j < sezon->nr_ep; j++)
                {
                    int durata_ep = atoi(strtok(NULL, " "));

                    serial->durata_serial += durata_ep;

                    InsQ(sezon->coada_ep, &durata_ep);
                }
                InsQ(serial->coada_sez, sezon);
            }

            if (serial->ID == 1)
            {
                int pozitie = InsLG(&tendinte, (void *)serial, CompSerial);
                fprintf(outputFile, "Serialul %s a fost adaugat la pozitia %d.\n", serial->nume, pozitie);
            }
            if (serial->ID == 2)
            {
                int pozitie = InsLG(&documentare, (void *)serial, CompSerial);
                fprintf(outputFile, "Serialul %s a fost adaugat la pozitia %d.\n", serial->nume, pozitie);
            }
            if (serial->ID == 3)
            {
                int pozitie = InsLG(&tutoriale, (void *)serial, CompSerial);
                fprintf(outputFile, "Serialul %s a fost adaugat la pozitia %d.\n", serial->nume, pozitie);
            }
            if (serial->ID == 4)
            {
                int pozitie = InsLG(&top10, (void *)serial, CompSerial);
                fprintf(outputFile, "Serialul %s a fost adaugat la pozitia %d.\n", serial->nume, pozitie);
            }
        }

        if (strcmp(command, "show") == 0)    /*  SHOW   */
        {
            char *token = strtok(NULL, " ");
            token[strlen(token) - 1] = '\0';

            if (strcmp(token, "1") == 0)
            {
                fprintf(outputFile, "Categoria %s: ", token);
                AfisareLG(tendinte, AfisareElement, outputFile);
            }
            if (strcmp(token, "2") == 0)
            {
                fprintf(outputFile, "Categoria %s: ", token);
                AfisareLG(documentare, AfisareElement, outputFile);
            }
            if (strcmp(token, "3") == 0)
            {
                fprintf(outputFile, "Categoria %s: ", token);
                AfisareLG(tutoriale, AfisareElement, outputFile);
            }
            if (strcmp(token, "top10") == 0)
            {
                fprintf(outputFile, "Categoria %s: ", token);
                AfisareLG(top10, AfisareElement, outputFile);
            }
            if (strcmp(token, "later") == 0)
            {
                fprintf(outputFile, "Categoria %s: ", token);
                AfiQ(later, AfisareElement, outputFile);
            }
            if (strcmp(token, "watching") == 0)
            {
                fprintf(outputFile, "Categoria %s: ", token);
                AfiS(watching, AfisareElement, outputFile);
            }
            if (strcmp(token, "history") == 0)
            {
                fprintf(outputFile, "Categoria %s: ", token);
                AfiS(history, AfisareElement, outputFile);
            }
        }

        if (strcmp(command, "add_sez") == 0) /* ADD_SEZ */
        {
            TSezon *sezon = (TSezon *)malloc(sizeof(TSezon));
            if (!sezon)
            {
                fprintf(outputFile, "Eroare alocare sezon\n");
                return 0;
            }

            sezon->coada_ep = InitQ(sizeof(int));
            if (!sezon->coada_ep)
            {
                fprintf(outputFile, "Eroare alocare coada episoade\n");
                return 0;
            }

            char *nume = strtok(NULL, " ");

            sezon->nr_ep = atoi(strtok(NULL, " "));
            sezon->durata_sezon = 0;

            for (j = 0; j < sezon->nr_ep; j++)
            {
                int durata_ep = atoi(strtok(NULL, " "));

                sezon->durata_sezon += durata_ep;

                InsQ(sezon->coada_ep, &durata_ep);
            }

            TSerial *serial = (TSerial *)CautareElemLG(tendinte, nume, CompNumeSerial);
            if (serial == NULL)
                serial = (TSerial *)CautareElemLG(documentare, nume, CompNumeSerial);
            if (serial == NULL)
                serial = (TSerial *)CautareElemLG(tutoriale, nume, CompNumeSerial);
            if (serial == NULL)
                serial = (TSerial *)CautareElemLG(top10, nume, CompNumeSerial);
            if (serial == NULL)
                serial = (TSerial *)CautareElemQ(later, nume, CompNumeSerial);
            if (serial == NULL)
                serial = (TSerial *)CautareElemS(watching, nume, CompNumeSerial);

            serial->durata_serial += sezon->durata_sezon;
            InsQ(serial->coada_sez, sezon);

            fprintf(outputFile, "Serialul %s are un sezon nou.\n", nume);
        }

        if (strcmp(command, "add_top") == 0) /* ADD_TOP */ 
        {
            TSerial *serial = (TSerial *)malloc(sizeof(TSerial));
            if (!serial)
            {
                fprintf(outputFile, "Eroare alocare serial\n");
                return 0;
            }
            serial->nume = malloc(len_nume);
            if (!serial->nume)
            {
                fprintf(outputFile, "Eroare alocare nume serial\n");
                return 0;
            }
            serial->coada_sez = InitQ(sizeof(TSezon));
            if (!serial->coada_sez)
            {
                fprintf(outputFile, "Eroare alocare coada sezoane\n");
                return 0;
            }

            int pozitie_top10 = atoi(strtok(NULL, " "));

            strcpy(serial->nume, strtok(NULL, " "));
            serial->rating = atof(strtok(NULL, " "));
            serial->nr_sez = atoi(strtok(NULL, " "));
            serial->durata_serial = 0;

            for (i = 0; i < serial->nr_sez; i++)
            {
                TSezon *sezon = (TSezon *)malloc(sizeof(TSezon));
                if (!sezon)
                {
                    fprintf(outputFile, "Eroare alocare sezon\n");
                    return 0;
                }

                sezon->coada_ep = InitQ(sizeof(int));
                if (!sezon->coada_ep)
                {
                    fprintf(outputFile, "Eroare alocare coada episoade\n");
                    return 0;
                }

                sezon->nr_ep = atoi(strtok(NULL, " "));

                for (j = 0; j < sezon->nr_ep; j++)
                {
                    int durata_ep = atoi(strtok(NULL, " "));

                    serial->durata_serial += durata_ep;
                    InsQ(sezon->coada_ep, &durata_ep);
                }

                InsQ(serial->coada_sez, sezon);
            }

            InsLG_top10(&top10, (void *)serial, pozitie_top10);

            while (LungimeLG(top10) > 10)
                EliminareLG_top10(top10, FreeSerial);

            fprintf(outputFile, "Categoria top10: ");
            AfisareLG(top10, AfisareElement, outputFile);
        }

        if (strcmp(command, "later") == 0)  /*  LATER   */
        {
            char *token = strtok(NULL, " ");
            token[strlen(token) - 1] = '\0';

            TSerial *serial = (TSerial *)EliminareLG(&tendinte, token, CompNumeSerial);

            if (serial == NULL)
                serial = (TSerial *)EliminareLG(&documentare, token, CompNumeSerial);
            if (serial == NULL)
                serial = (TSerial *)EliminareLG(&tutoriale, token, CompNumeSerial);
            if (serial == NULL)
                serial = (TSerial *)EliminareLG(&top10, token, CompNumeSerial);

            InsQ(later, serial);
            int poz = LungimeQ(later);

            fprintf(outputFile, "Serialul %s se afla in coada de asteptare pe pozitia %d.\n", serial->nume, poz);
        }

        if (strcmp(command, "watch") == 0) /*   WATCH   */
        {
            char *nume = strtok(NULL, " ");
            int durata = atoi(strtok(NULL, " "));

            TSerial *serial = (TSerial *)CautareElemS(watching, nume, CompNumeSerial);
            if (serial != NULL)
            {
                if (serial->durata_serial <= durata)
                {
                    Push(history, (void *)serial);
                    EliminareS(watching, nume, CompNumeSerial);
                    serial->durata_serial = -1;
                    fprintf(outputFile, "Serialul %s a fost vizionat integral.\n", nume);
                }
                else
                {
                    EliminareS(watching, nume, CompNumeSerial);
                    serial->durata_serial -= durata;
                    Push(watching, (void *)serial);
                }
            }
            else
            {
                serial = (TSerial *)EliminareLG(&tendinte, nume, CompNumeSerial);
                if (serial == NULL)
                    serial = (TSerial *)EliminareLG(&documentare, nume, CompNumeSerial);
                if (serial == NULL)
                    serial = (TSerial *)EliminareLG(&tutoriale, nume, CompNumeSerial);
                if (serial == NULL)
                    serial = (TSerial *)EliminareLG(&top10, nume, CompNumeSerial);
                if (serial == NULL)
                {
                    serial = (TSerial *)CautareElemQ(later, nume, CompNumeSerial);
                    EliminareQ(later, nume, CompNumeSerial);
                }

                if (serial->durata_serial <= durata)
                {
                    Push(history, (void *)serial);
                    serial->durata_serial = -1;
                    fprintf(outputFile, "Serialul %s a fost vizionat integral.\n", nume);
                }
                else
                {
                    Push(watching, (void *)serial);
                    serial->durata_serial -= durata;
                }
            }
        }
    }

    DistrugeLG(&tendinte, FreeSerial);
    DistrugeLG(&documentare, FreeSerial);
    DistrugeLG(&tutoriale, FreeSerial);
    DistrugeLG(&top10, FreeSerial);

    DistrQ(&later, FreeSerial);
    DistrS(&watching, FreeSerial);
    DistrS(&history, FreeSerial);

    free(inputFileName);
    free(outputFileName);
    fclose(inputFile);
    fclose(outputFile);
    free(line);

    return 0;
}