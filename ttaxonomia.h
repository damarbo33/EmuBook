
#ifndef TTaxonomia_H
#define TTaxonomia_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "traza.h"
#include <SDL/SDL.h>

//Es necesario que la lista est� ordenada
const char temp_adverbios[][14] = {"a","a menudo","abierto","absolutamente","acaso","adem�s","ahora","al","algo","alguna vez","all�","all�","alrededor","ante","ante todo","antes","aquel","aquella","aquellas","aquellos","aqu�","as�","aunque","a�n","bajo","bien","cabe","cada","casi","cerrado","como","con","contra","cuando","c�mo","de","del","dem�s","dentro","desde","despu�s","dijo","donde","durante","e","el","ella","ellas","ellos","en","entonces","entre","era","eran","es","esa","esas","ese","eso","esos","esta","estaba","estas","este","esto","estos","est�","exactamente","fue","fuera","ha","haber","hab�a","hab�an","hacer","hacia","hac�a","hasta","hay","he","hubiera","hubo","i","iba","juntos","la","las","le","les","lo","los","luego","mal","mas","me","mejor","menos","mi","mientras","mis","mismo","modo","mucho","muy","m�s","m�","m�a","m�as","m�o","m�os","nada","nadie","ni","no","nos","nosotras","nosotros","nuestra","nuestras","nuestro","nuestros","nunca","o","otra","otro","para","peor","pero","poco","pod�a","por","porque","pues","que","quien","quiz�","quiz�s","qu�","se","segun","ser","se�or","se�ora","si","sido","siempre","sin","sin embargo","so","sobra","sobre","su","sus","suya","suyas","suyo","suyos","s�","s�","s�lo","tal","tal vez","tambi�n","tampoco","tan","tanto","te","tendremos","tendr�","tendr�n","tendr�s","tendr�","tendr�is","tenemos","tengo","ten�is","ten�a","tiene","tienen","tienes","toda","todas","todo","todos","tras","tu","tus","tuve","tuvieron","tuvimos","tuviste","tuvo","tuv�steis","tuya","tuyas","tuyo","tuyos","t�","u","un","una","unas","uno","unos","usted","vez","vosotras","vosotros","vuestra","vuestras","vuestro","vuestros","y","ya","yo","�l","�ltimamente"};

class TTaxonomia
{
    private:
        int numPalabras;
        struct t_taxonomia
        {
            char *palabra;
        } *taxoList;

        struct t_taxonomiaRepeats
        {
            char *palabra;
            int ocurrencias;
        } *finalTaxoList;

        void QuickSort(t_taxonomia *A, int AHigh, int iLo, int iHi);
        void filtrar (char *varDato);
        void stringTrim(char *dato);
        int strcompare (char *s1, char *s2);
        int numAdv;
        int maxPalabras;
        int numPalabrasRecuento;
        void QuickSortRecuento(t_taxonomiaRepeats *A, int AHigh, int iLo, int iHi);
        int buscarAdv(char *palabra);
        int BuscarBin(int izq, int der, char *n);
        void clearPrimeraOrdenacion();
        void clearSegundaOrdenacion();
        int stadisticData;
        int BuscarBin(t_taxonomia *datos, int izq, int der, char *n);


    public:
        TTaxonomia();
        ~TTaxonomia();
        void add(char *varDato);
        int size();
        char * get(int var_pos);
        void Sort();
        void clear();
        void recuento();
        //int sizeRecuento();
        void SortRecuento();
        int getReps(int var_pos);
        void Sort(int n_palabras);
        int getTotalPalabras ();
        int find(char *palabra);

};

#endif // TTaxonomia_H
