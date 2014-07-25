#include "ttaxonomia.h" // class's header file

// class constructor
TTaxonomia::TTaxonomia()
{
    numPalabras = 0;
    maxPalabras = 20;
    numAdv = sizeof(temp_adverbios)/(sizeof(char)*14);
    numPalabrasRecuento = 0;
    stadisticData = 0; //Servirá para saber el numero de palabras que hay en total sin tener en cuenta que sean duplicados o esten en la lista de adverbios
    //printf("adverbios %s\n",temp_adverbios[1]);
}

// class destructor
TTaxonomia::~TTaxonomia()
{
    clear();
}

void TTaxonomia::clear()
{
    clearPrimeraOrdenacion();
    clearSegundaOrdenacion();
}

//Elimina todos los registros del array ordenado por la secuencia de caracteres
void TTaxonomia::clearPrimeraOrdenacion()
{
    for (int i = 0; i < numPalabras;i++)
    {
        free(taxoList[i].palabra);
    }
    if (numPalabras > 0) free(taxoList);
    numPalabras = 0;
}

//Elimina todos los registros del array ordenado por número de ocurrencias
void TTaxonomia::clearSegundaOrdenacion()
{
    for (int i = 0; i < numPalabrasRecuento;i++)
    {
        free(finalTaxoList[i].palabra);
    }
    if (numPalabrasRecuento > 0) free(finalTaxoList);
    numPalabrasRecuento = 0;
}

//Da valor al array finalTaxoList que contendrá el array de palabras ordenadas según
//el número de ocurrencias de cada palabra
void TTaxonomia::recuento()
{
     char temp_palabra[255] ={""};

     if (numPalabras > 0)
     {
         strcpy(temp_palabra,taxoList[0].palabra);
         finalTaxoList = (struct t_taxonomiaRepeats *)malloc(sizeof(struct t_taxonomiaRepeats));
         finalTaxoList[0].palabra = (char *)malloc((strlen(temp_palabra)+1)*sizeof(char));
         strcpy(finalTaxoList[0].palabra,temp_palabra);
         finalTaxoList[0].ocurrencias = 1;
         int j = 0; //Contara las ocurrencias

         for (int i=1;i<numPalabras;i++)
         {
            if (strcmp(taxoList[i].palabra,temp_palabra) == 0 && i < numPalabras - 1)
            {
                finalTaxoList[j].ocurrencias++;
            }
            else
            {
                if (i == numPalabras - 1) finalTaxoList[j].ocurrencias++;
                j++;
                strcpy(temp_palabra,taxoList[i].palabra);
                finalTaxoList = (struct t_taxonomiaRepeats *)realloc(finalTaxoList,(j+1) * sizeof(struct t_taxonomiaRepeats));
                finalTaxoList[j].palabra = (char *)malloc((strlen(temp_palabra)+1)*sizeof(char));
                strcpy(finalTaxoList[j].palabra,temp_palabra);
                finalTaxoList[j].ocurrencias = 1;
            }
         }
         numPalabrasRecuento = j+1;
         SortRecuento();
     }
}

//Algoritmo de búsqueda binaria para buscar las palabras que no se tienen que tener en cuenta
//para generar la lista de palabras más comunes
int TTaxonomia::BuscarBin(int izq, int der, char *n)
{
 bool encontrado=false;
 int centro=0,i=0;

 while ( (!encontrado) &  (izq <= der) )
 {
 i++;
        centro=(izq+der)/2;
        if (strcmp(temp_adverbios[centro],n) == 0)
            encontrado=true;
        else
            if (strcmp(temp_adverbios[centro], n) < 0)
                izq=centro+1;
            else
                der=centro-1;
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


int TTaxonomia::BuscarBin(t_taxonomia *datos, int izq, int der, char *n)
{
 bool encontrado=false;
 int centro=0,i=0;

 printf("En 9443: %s\n",datos[9443].palabra);

 while ( (!encontrado) && (izq <= der) )
 {
 i++;
        centro=(izq+der)/2;
//        printf("centro: %d, i: %d, d: %d, %s, total: %d\n",centro,izq,der,datos[centro].palabra,getTotalPalabras());

/*        if (izq == der-2)
        {
            if (strcmp(datos[centro].palabra,n) == 0)
            {
                return centro;
            }
            else if (getTotalPalabras() > 0)
            {
                if (strcmp(datos[centro+1].palabra,n) == 0)
                {
                    return centro+1;
                }
            }
        }
        else */


        if (strcmp(datos[centro].palabra,n) == 0)
        {
            encontrado=true;
            printf("finded: %s %d\n",datos[centro].palabra,centro);

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


//Metodo para buscar una palabra en una lista
int TTaxonomia::buscarAdv(char *palabra)
{

    //int numAdv = sizeof(temp_adverbios)/(sizeof(char)*14);
    return BuscarBin(0, numAdv-1,palabra);
}

int TTaxonomia::find(char *palabra)
{

    //int numAdv = sizeof(temp_adverbios)/(sizeof(char)*14);
    return BuscarBin(taxoList,0, getTotalPalabras()-1,palabra);
}


//Metodo para añadir todas las palabras de un texto. En base a estas palabras, se obtendrán
//las mas comunes
void TTaxonomia::add(char *varDato)
{
    if (varDato != NULL)
    {
        filtrar(varDato);
        if (varDato[0] !=  ' ')
        {
            if (numPalabras == 0)
            {
                taxoList = (struct t_taxonomia *)malloc(sizeof(struct t_taxonomia));
                taxoList[numPalabras].palabra = (char *)malloc((strlen(varDato)+1)*sizeof(char));
            }
            else
            {
                taxoList = (struct t_taxonomia *)realloc(taxoList,(numPalabras+1) * sizeof(struct t_taxonomia));
                taxoList[numPalabras].palabra = (char *)malloc((strlen(varDato)+1)*sizeof(char));
            }
            strcpy(taxoList[numPalabras].palabra,varDato);
            numPalabras++;
        }
    }
}


//Se obtiene el numero de palabras que existen despues de hacer el recuento
int TTaxonomia::size()
{
    return numPalabrasRecuento;
}

//Se obtiene el número de todas las palabras que han habido
/*int TTaxonomia::size()
{
    return numPalabras;
}
*/

char * TTaxonomia::get(int var_pos)
{
    if (numPalabrasRecuento > 0 && var_pos < numPalabrasRecuento) return finalTaxoList[var_pos].palabra;
    else return "";
}

int TTaxonomia::getReps(int var_pos)
{
    if (numPalabrasRecuento > 0 && var_pos < numPalabrasRecuento) return finalTaxoList[var_pos].ocurrencias;
    else return 0;
}

void TTaxonomia::filtrar (char *varDato)
{
    int tam = strlen(varDato);
    unsigned char leido = ' ';


    for (int i=0;i<tam;i++)
    {

        leido = varDato[i];
        //Los caracteres que no pueden ser letras, seran eliminados con un espacio
        if ((int)leido < 65 || ( (int)leido > 90 && (int)leido < 97) || ((int)leido > 122 && (int)leido < 192) )
        {
            varDato[i] = ' ';
        }
        else
        //Hacemos que todas las palabras esten en minusculas
        if ((int)leido >= 65 && (int)leido <= 90 || (int)leido >= 192 && (int)leido <= 221)
        {
            varDato[i] = (int)leido+32;
        }
    }

    this->stringTrim(varDato);
    if (varDato[0] !=  ' ') stadisticData++;

    if (buscarAdv(varDato) != -1)
        strcpy(varDato," ");
}

void TTaxonomia::stringTrim(char *dato)
{
    Uint8 tam = strlen(dato);
    int i = tam - 1;
    bool salir = false;

    int j=0;

    while (!salir && tam > 1 && j < tam)
    {
        if (dato[0] == ' ')
        {
            //printf("Encontramos un espacio en %d\n",j);
            for (int k=1;k<tam;k++)
            {
                dato[k-1] = dato[k];
            }
            if (tam > 1) dato[tam-1] = ' ';
        }
        else
        {
            salir = true;
        }
        j++;
    }

/*
    bool salir2 = false;
    if (i > 0)
    {
        while (i >= 0 && !salir2)
        {
            printf("bucle: %d, %d\n",i,dato[i]);
            if (dato[i] != ' ' && i < tam-2 && dato[i] != '\0')
            {
                printf("salimos en: %d\n",i);
                if (dato[i+1] == ' ')
                    dato[i+1] = '\0';
                salir2 = true;
            }
            i--;
        }
*/

    if (i > 0)
    {
        //temp[0] = dato[i];
        while (i > 0 && dato[i] == ' ' )
        {
            dato[i] = '\0';
            i--;
        }
    }
}


void TTaxonomia::SortRecuento()
{
    if (numPalabrasRecuento > 0)
    {
        QuickSortRecuento(finalTaxoList, numPalabrasRecuento-1, 0, numPalabrasRecuento-1);
    }
}

void TTaxonomia::QuickSortRecuento(t_taxonomiaRepeats *A, int AHigh, int iLo, int iHi)
{
  int Lo, Hi;
  int Mid;
  t_taxonomiaRepeats T;

  Lo = iLo;
  Hi = iHi;
  Mid = A[(Lo+Hi)/2].ocurrencias;

  do
  {
    while (A[Lo].ocurrencias <  Mid)
        Lo++;
    while (A[Hi].ocurrencias > Mid)
        Hi--;

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
    QuickSortRecuento(A, AHigh, iLo, Hi);
  if (Lo < iHi)
    QuickSortRecuento(A, AHigh, Lo, iHi);
}



void TTaxonomia::Sort()
{
    int inicio = SDL_GetTicks();
    if (numPalabras > 0)
    {
        QuickSort(taxoList, numPalabras-1, 0, numPalabras-1);
        printf("Objetos ordenados en: %d\n",(SDL_GetTicks()-inicio));
        inicio = SDL_GetTicks();
        this->recuento();
        printf("Objetos reordenados en: %d\n",(SDL_GetTicks()-inicio));
    }
}

void TTaxonomia::Sort(int n_palabras)
{
    t_taxonomiaRepeats *T;
    int contador = n_palabras;

    if (numPalabras > 0)
    {
        Sort();

        if (n_palabras > numPalabrasRecuento) n_palabras = numPalabrasRecuento;
        for (int i=0;(i<(numPalabrasRecuento)/2) && contador > 0;i++)
        {
            T = new (t_taxonomiaRepeats);
            *T = finalTaxoList[i];
            finalTaxoList[i] = finalTaxoList[numPalabrasRecuento-1-i];
            finalTaxoList[numPalabrasRecuento-1-i] = *T;
            contador--;
            delete (T);
        }

        for (int i=n_palabras;i<numPalabrasRecuento;i++)
        {
            free(finalTaxoList[i].palabra);
        }

        finalTaxoList = (struct t_taxonomiaRepeats *)realloc(finalTaxoList,(numPalabrasRecuento) * sizeof(struct t_taxonomiaRepeats));
        numPalabrasRecuento = n_palabras;

    }
}


void TTaxonomia::QuickSort(t_taxonomia *A, int AHigh, int iLo, int iHi)
{
  int Lo, Hi;
  char Mid[255];

  t_taxonomia T;

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

int TTaxonomia::strcompare (char *s1, char *s2)
{

    int len_s1=0, len_s2=0; //Tamanyos de los strings
    int j=0;  //para recorrer s2
    int i=0;  //para recorrer s1
    unsigned char leido1 = ' ';
    unsigned char leido2 = ' ';
    bool leido1IsMayor = false;

    if (s1 != NULL && s2 != NULL)
    {
        len_s1 = strlen(s1);
        len_s2 = strlen(s2);

        for (i = 0; i < len_s1; i++)
        {
            leido1 = s1[i];
            leido2 = s2[j];

            if (leido1 == leido2)
                j++;
            else if ( (int)leido1 > (int)leido2 && (int)leido1 - 32 == (int)leido2)
            {
                //leido1 esta en minusculas y leido2 en mayusculas
                j++;
                leido1IsMayor = true;
            }
            else if ( (int)leido2 > (int)leido1 && (int)leido2 - 32 == (int)leido1)
                //leido2 esta en minusculas y leido1 en mayusculas
                j++;
        }
    }

    if (j == len_s2 && j != 0)
    {
        if (i-j != 0)
        {
            if (leido1IsMayor) return -1;
            else return 1;
        }
        else return (i-j);
    }
    else
    {
       if (leido1IsMayor) return -1;
            else return 1;
    }
}

int TTaxonomia::getTotalPalabras ()
{
    return stadisticData;
}
