#include "tconfig.h" // class's header file


// class constructor
TConfig::TConfig()
{
    objTraza = new traza();
    arrayClaves.numClaves=0;

    arrayClaves.clave = (struct my_struct_clave *) malloc(sizeof(struct my_struct_clave));
    memset(arrayClaves.clave[arrayClaves.numClaves].nombre, '\0', 255);
    memset(arrayClaves.clave[arrayClaves.numClaves].valor, '\0', 255);
    //separarValores("PosicionTexto=0");
}

// class destructor
TConfig::~TConfig()
{
    free(arrayClaves.clave);
    arrayClaves.numClaves=0;
}

//Obtenemos los valores de las claves y los almacenamos en variables
void TConfig::obtenClaves()
{
      if (texto != NULL)
      {
          char linea[255];
          memset(linea, '\0', 255);
          char leido[2] = {' ','\0'};
          unsigned long int posString = 0;
          unsigned long int posLinea = 0;
          unsigned int tam = strlen(texto);

          while (posString <= tam)
          {
                leido[0]=texto[posString];
                if (!esRetorno(leido[0]) && posString != tam)
                {
                      linea[posLinea]=leido[0];
                      posLinea++;
                }
                else
                {
                      separarValores(linea);
                      memset(linea, '\0', 255);
                      posLinea=0;
                }
                posString++;
          }
      }
}

bool TConfig::esRetorno(char dato)
{
     char carControl[] = "\r\n";
     Uint8 tam = strlen(carControl);
     bool salir = false;
     Uint8 pos = 0;

     while (!salir && pos < tam)
     {
         if (dato == carControl[pos])
         {
             salir = true;
         }
         pos++;
     }
     return salir;
}

void TConfig::separarValores(char *dato)
{

     char *p;
     char datoTemp[255];
     memset(datoTemp, '\0', 255);

     objTraza->print("TConfig::separarValores Separamos",dato);
     if (dato != NULL)
     {
        strcpy(datoTemp,dato);

        p = strtok(datoTemp, "=");
        if (p != NULL)
        {
           if (arrayClaves.numClaves != 0)
           {
                arrayClaves.clave = (struct my_struct_clave *) realloc(arrayClaves.clave,(arrayClaves.numClaves+1)*sizeof(struct my_struct_clave));
           }

           strcpy(arrayClaves.clave[arrayClaves.numClaves].nombre,p);
           if((p = strtok(NULL, "="))!=NULL)
           {
                 strcpy(arrayClaves.clave[arrayClaves.numClaves].valor,p);
                 arrayClaves.numClaves++;
           }
        }
     }
}

char * TConfig::getClave(char *dato)
{
     int i=0;
     char *valor = NULL;
     bool encontrado = false;

     if (dato != NULL)
     {
             while (i < arrayClaves.numClaves && !encontrado)
             {
                 if (arrayClaves.clave[i].nombre != NULL)
                 {
                    if (strcmp(dato,arrayClaves.clave[i].nombre)==0)
                    {
                       valor = new char[strlen(arrayClaves.clave[i].valor)+1];
                       strcpy(valor,arrayClaves.clave[i].valor);
                       valor[strlen(arrayClaves.clave[i].valor)] = '\0';
                       encontrado = true;
                    }
                 }
                 i++;
             }
     }

     if (!encontrado)
     {
        valor = new char[2];
        strcpy(valor,"0");
        valor[1] = '\0';
     }
     return valor;
}

bool TConfig::setClave(char *dato, char *valor)
{
     int i=0;
     bool encontrado = false;

     while (i < arrayClaves.numClaves)
     {
           if (strcmp(dato,arrayClaves.clave[i].nombre)==0)
           {
              strcpy(arrayClaves.clave[i].valor,valor);
              encontrado = true;
           }
           i++;
     }

     //Si no hemos encontrado el elemento, lo damos de alta
     if (encontrado == false)
     {
        arrayClaves.clave = (struct my_struct_clave *) realloc(arrayClaves.clave,(arrayClaves.numClaves+1)*sizeof(struct my_struct_clave));
        strcpy(arrayClaves.clave[i].valor,valor);
        strcpy(arrayClaves.clave[i].nombre,dato);
        arrayClaves.numClaves++;
     }
     return encontrado;
}

void TConfig::setClave(char *dato, int valor)
{
     char temp[255];
     memset(temp, '\0', 255);

     sprintf(temp,"%d",valor);
     this->setClave(dato,temp);
}
