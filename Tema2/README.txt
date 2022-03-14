/* ROANGHESI ANA MARIA */


In structuri.h se afla structurile folosite pentru a retine informatiile pentru serial si sezon.

In functiiLG, functiiCoada, functiiStiva se afla functiile pentru fiecare structura in parte;
acestea sunt explicate in fiecare fisier prin comentarii.

===============tema2.c===============

Functia CompSerial: compara 2 elemente si returneaza:
    -o valoare > 0 daca elementul1 > elementul2
    -o valoare < 0 daca elementul1 < elementul2

Functiile FreeSezon si FreeSerial elibereaza memoria din seria si sezon;

/*   ADD   */
-Se aloca si se citesc informatiile pentru serial
-Se aloca si se citesc informatiile pentru fiecare sezon in parte
-Se citesc duratele episoadelor si se adauga in coada de episoade a fiecarui sezon
-Se calculeaza si durata totala a serialului
-Se adauga sezonul in coada de sezoane a serialului
-In functie de ID, se adauga serialul in lista de seriale

/*  SHOW   */
-Se afiseaza elementele listei, stivei sau cozii dorite

/* ADD_SEZ */
-Se citesc duratele episoadelor si se adauga in coada de episoade a fiecarui sezon
-Se calculeaza durata totala a sezonului
-Se cauta serialul in categorii dupa nume
-Se adauga durata sezonului la durata totala a serialului;
-si se adauga sezonul in coada de sezoane a serialului

/* ADD_TOP */
-Se face citirea ca pentru comanda ADD
-Se adauga serialul in lista TOP10 pe pozitia ceruta
-In caz ca lungimea listei este mai mare decat 10, se elimina elemente de la sfarsit

/*  LATER   */
-Se cauta si se elimina elementul cu numele dat din lista in care se afla
-Se adauga la sfarsitul cozii later
-Pozitia este data de lungimea cozii, pentru ca este inserat la sfarsit

/*   WATCH   */
-Se cauta serialul in stiva watching
-Daca serialul se afla deja in stiva:
    -Daca durata vizionata este >= durata totala a serialului:
        -se adauga in history si se elimina din watching
    -Daca durata vizionata este < durata totala a serialului:
        -se actualizeaza durata totala a serialului
        -se elimina si se adauga iar serialul in watching pentru a ajunge in varful stivei
-Daca serialul nu se afla in stiva watching:
    -se cauta si se elimina serialul din lista/coada in care elibereaza
    -Daca durata vizionata este >= durata totala a serialului se adauga in history
    -Daca durata vizionata este < durata totala a serialului:
        -se actualizeaza durata totala a serialului
        -se adauga serialul in stiva watching

