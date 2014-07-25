#ifndef TClist_H
#define TClist_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "traza.h"
#include <SDL/SDL.h>

class TClist
{
    private:
        int numPalabras;
        struct t_clist
        {
            char *palabra;
            int ocurrencias;
        } *CList;
        int BuscarBin(t_clist *datos, int izq, int der, char *n);
        void QuickSort(t_clist *A, int AHigh, int iLo, int iHi);
        int BuscarBinAprox(t_clist *, int, int, char *,TClist *);
        int contiene (char *, char *);

    public:
        TClist();
        ~TClist();
        void add(char *);
        int size();
        char * get(int);
        void Sort();
        void clear();
        int find(char *);
        int findAprox(char *,TClist *);

};

#endif // TClist_H
