#include "tcstring.h" // class's header file

// class constructor
TCString::TCString()
{
    string = NULL;
    clear();
}

// class destructor
TCString::~TCString()
{
    if (string != NULL) free(string);
}

void TCString::clear()
{
    if (string != NULL) free(string);
    //string = (char *)malloc(2*sizeof(char));
    string = (char *)calloc( 2, sizeof(char) );
    memset (string,'\0',2);
}

void TCString::add(char *dato)
{
    if (dato != NULL)
    {
        //printf("string: %d\n",strlen(string));
        //printf("dato: %d\n",strlen(dato));
        //dato
        string = (char *) realloc(string,(strlen(string)+1+strlen(dato))* sizeof(char));
        strcat(string, dato);
        //printf("ss: %s\n",string);
    }
}

char * TCString::get ()
{
   return string;
}

void TCString::trim()
{
    trim(string);
}

void TCString::trim(char *dato)
{
    int tam = strlen(dato);
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

void TCString::toLowerCase ()
{
    toLowerCase(string);
}

void TCString::filtrarLetras ()
{
    filtrarLetras (string);
}

void TCString::filtrarLetras (char *varDato)
{
    if (varDato != NULL)
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
        }
    }
}

void TCString::toLowerCase (char *varDato)
{
    if (varDato != NULL)
    {
        int tam = strlen(varDato);
        unsigned char leido = ' ';

        //char *temp = new char[tam+1];
        //strcpy(temp,varDato);

        for (int i=0;i<tam;i++)
        {

            leido = varDato[i];
            //Hacemos que todas las palabras esten en minusculas
            if ((int)leido >= 65 && (int)leido <= 90 || (int)leido >= 192 && (int)leido <= 221)
            {
                varDato[i] = (int)leido+32;
            }
        }
    }
    //strcpy(varDato,temp);
}



