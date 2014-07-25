
#ifndef TTaxonomia_H
#define TTaxonomia_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "traza.h"
#include <SDL/SDL.h>

//Es necesario que la lista esté ordenada
const char temp_adverbios[][14] = {"a","a menudo","abierto","absolutamente","acaso","además","ahora","al","algo","alguna vez","allá","allí","alrededor","ante","ante todo","antes","aquel","aquella","aquellas","aquellos","aquí","así","aunque","aún","bajo","bien","cabe","cada","casi","cerrado","como","con","contra","cuando","cómo","de","del","demás","dentro","desde","después","dijo","donde","durante","e","el","ella","ellas","ellos","en","entonces","entre","era","eran","es","esa","esas","ese","eso","esos","esta","estaba","estas","este","esto","estos","está","exactamente","fue","fuera","ha","haber","había","habían","hacer","hacia","hacía","hasta","hay","he","hubiera","hubo","i","iba","juntos","la","las","le","les","lo","los","luego","mal","mas","me","mejor","menos","mi","mientras","mis","mismo","modo","mucho","muy","más","mí","mía","mías","mío","míos","nada","nadie","ni","no","nos","nosotras","nosotros","nuestra","nuestras","nuestro","nuestros","nunca","o","otra","otro","para","peor","pero","poco","podía","por","porque","pues","que","quien","quizá","quizás","qué","se","segun","ser","señor","señora","si","sido","siempre","sin","sin embargo","so","sobra","sobre","su","sus","suya","suyas","suyo","suyos","sé","sí","sólo","tal","tal vez","también","tampoco","tan","tanto","te","tendremos","tendrá","tendrán","tendrás","tendré","tendréis","tenemos","tengo","tenéis","tenía","tiene","tienen","tienes","toda","todas","todo","todos","tras","tu","tus","tuve","tuvieron","tuvimos","tuviste","tuvo","tuvísteis","tuya","tuyas","tuyo","tuyos","tú","u","un","una","unas","uno","unos","usted","vez","vosotras","vosotros","vuestra","vuestras","vuestro","vuestros","y","ya","yo","él","últimamente"};

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
