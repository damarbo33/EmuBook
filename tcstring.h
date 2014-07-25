#ifndef TCString_H
#define TCString_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "traza.h"

class TCString
{
    private:
        char *string;

    public:
        TCString();
        ~TCString();
        void add(char *);
        int size();
        char * get(int);
        void clear();
        char * get();
        void trim(char *);
        void trim();
        void toLowerCase (char *);
        void toLowerCase ();
        void filtrarLetras (char *varDato);
        void filtrarLetras ();
};

#endif // TCString_H
