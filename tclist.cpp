#include "tclist.h" // class's header file

// class constructor
TClist::TClist()
{
    numPalabras = 0;
}

// class destructor
TClist::~TClist()
{
    clear();
}

int TClist::findAprox(char *palabra,TClist *datosSalida)
{
    //int numAdv = sizeof(temp_adverbios)/(sizeof(char)*14);
    return BuscarBinAprox(CList,0, size()-1,palabra,datosSalida);
}

int TClist::BuscarBinAprox(t_clist *datos, int izq, int der, char *n, TClist *aproxList)
{
 bool encontrado=false;
 int centro=0,i=0;

 while ( (!encontrado) && (izq <= der) )
 {
 i++;
        centro=(izq+der)/2;
//        printf("centro: %d, i: %d, d: %d, %s, total: %d\n",centro,izq,der,datos[centro].palabra,size());

        if (strcmp(datos[centro].palabra,n) == 0)
        {
            encontrado=true;
            //printf("ENCONTRADO: %s %d\n",datos[centro].palabra,centro);

        }
        else
        {
            if (strcmp(datos[centro].palabra, n) < 0)
                izq=centro+1;
            else
                der=centro-1;
        }
 }

 int numCoincidencias = 0;
 //No encontramos la palabra pero es parte de una palabra más larga
 if (!encontrado && centro > 0)
 {
     int len_s1 = strlen(n);
     int len_s2 = strlen(datos[centro].palabra);
     char *stringCoincidente = NULL;
     //printf("Tamaño: %d, %d\n",len_s1,len_s2);

     int max_len = 0;
     if (len_s1 > len_s2)
     {
        max_len = len_s2;
     }
     else
     {
        max_len = len_s1;
     }

     //Buscamos que por lo menos hayan las dos primeras palabras iguales, sino pueden salir muchos resultados
     if (max_len > 3)
     {
        int len_coincidencia = 0;
        int contador = 0;
        bool salir = false;
        //for (int i=0;i<len_s2;i++)
        while (!salir && contador < max_len)
        {
            if (datos[centro].palabra[contador] == n[contador])
            {
                len_coincidencia++;
            }
            else
            {
                salir = true;
            }
            contador ++;
        }

        stringCoincidente = new char[len_coincidencia+1];
        stringCoincidente[len_coincidencia] = '\0';
        //printf("Tamaño: %d\n",len_coincidencia);
        for (int i=0;i<len_coincidencia;i++)
        {
            stringCoincidente[i] = n[i];
        }

        //printf("Coincidencia: %s\n",stringCoincidente);
     }

     //Vamos hacia atras para ver si hubiera más coincidencias
     if (centro > 0 && max_len > 3)
     {
         if (contiene(datos[centro-1].palabra,stringCoincidente) != -1 )
         {
             do
             {
                centro--;
             }while (contiene(datos[centro].palabra,stringCoincidente) != -1 && centro > 0);
             centro++;
         }
     }

     do
     {
        aproxList->add(datos[centro].palabra);
        //printf("añadimos palabra: %s %d\n",datos[centro].palabra,centro);
        centro++;
        numCoincidencias++;

     }while (contiene(datos[centro].palabra,stringCoincidente) != -1 && centro < numPalabras && numCoincidencias < 50);

 }

 // El algoritmo de búsqueda binaria encuentra el número, pero no
// asegura que sea el primero si hay repeticiones de números. Por eso
// retrocedemos hasta el primer elemento
// if (encontrado)
// while(strcmp(temp_adverbios[centro-1],n) == 0)
//       centro--;
 if (encontrado) return (centro);
 else return(-1);
}

int TClist::contiene (char *s1, char *s2)
{
    int len_s1=0, len_s2=0; //Tamanyos de los strings
    int j=0;  //para recorrer s2
    int i=0;  //para recorrer s1

    if (s1 != NULL && s2 != NULL)
    {
        len_s1 = strlen(s1);
        len_s2 = strlen(s2);

        for (i = 0; i < len_s1; i++)
        {
            if (s1[i] == s2[j])
            {
                j++;
            }
            else if (j != len_s2)
            {
                j = 0;
                if (s1[i] == s2[j])
                {
                    j++;
                }
            }
        }
    }

    if (j == len_s2 && j != 0)
    {
        return (i-j);
    }
    else
    {
        return -1;
    }
}



int TClist::find(char *palabra)
{

    //int numAdv = sizeof(temp_adverbios)/(sizeof(char)*14);
    return BuscarBin(CList,0, size()-1,palabra);
}


int TClist::BuscarBin(t_clist *datos, int izq, int der, char *n)
{
 bool encontrado=false;
 int centro=0,i=0;


 while ( (!encontrado) && (izq <= der) )
 {
 i++;
        centro=(izq+der)/2;
//        printf("centro: %d, i: %d, d: %d, %s, total: %d\n",centro,izq,der,datos[centro].palabra,size());

        if (strcmp(datos[centro].palabra,n) == 0)
        {
            encontrado=true;
            //printf("finded: %s %d\n",datos[centro].palabra,centro);

        }
        else
        {
            if (strcmp(datos[centro].palabra, n) < 0)
                izq=centro+1;
            else
                der=centro-1;
        }
 }
// El algoritmo de búsqueda binaria encuentra el número, pero no
// asegura que sea el primero si hay repeticiones de números. Por eso
// retrocedemos hasta el primer elemento
// if (encontrado)
// while(strcmp(temp_adverbios[centro-1],n) == 0)
//       centro--;
 if (encontrado) return (centro);
 else return(-1);
}


int TClist::size()
{
    return numPalabras;
}

void TClist::add(char *varDato)
{
    if (varDato != NULL)
    {
            if (numPalabras == 0)
            {
                CList = (struct t_clist *)malloc(sizeof(struct t_clist));
                CList[numPalabras].palabra = (char *)malloc((strlen(varDato)+1)*sizeof(char));
            }
            else
            {
                CList = (struct t_clist *)realloc(CList,(numPalabras+1) * sizeof(struct t_clist));
                CList[numPalabras].palabra = (char *)malloc((strlen(varDato)+1)*sizeof(char));
            }
            strcpy(CList[numPalabras].palabra,varDato);
            numPalabras++;
    }
}


void TClist::Sort()
{
    int inicio = SDL_GetTicks();
    if (numPalabras > 0)
    {
        QuickSort(CList, numPalabras-1, 0, numPalabras-1);
        printf("Objetos ordenados en: %d\n",(SDL_GetTicks()-inicio));
    }
}

void TClist::QuickSort(t_clist *A, int AHigh, int iLo, int iHi)
{
  int Lo, Hi;
  char Mid[255];

  t_clist T;

  Lo = iLo;
  Hi = iHi;

  //char *Mid = (char *)malloc((strlen(A[(Lo+Hi)/2].palabra)+1)*sizeof(char));
  strcpy(Mid, A[(Lo+Hi)/2].palabra);

  do
  {
    while (strcmp(A[Lo].palabra , Mid) < 0)
        Lo++;
    while (strcmp(A[Hi].palabra , Mid) > 0)
        Hi--;
    //free(Mid);
    if (Lo <= Hi)
    {
      T=A[Lo];
      A[Lo] = A[Hi];
      A[Hi]=T;
      Lo++;
      Hi--;
    }
  }
  while (Lo <= Hi);

  if (Hi > iLo)
    QuickSort(A, AHigh, iLo, Hi);
  if (Lo < iHi)
    QuickSort(A, AHigh, Lo, iHi);
}

char * TClist::get(int var_pos)
{
    if (numPalabras > 0 && var_pos < numPalabras) return CList[var_pos].palabra;
    else return "";
}

void TClist::clear()
{
    for (int i = 0; i < numPalabras;i++)
    {
        free(CList[i].palabra);
    }
    if (numPalabras > 0) free(CList);
    numPalabras = 0;
}
