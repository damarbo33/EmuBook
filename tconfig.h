#ifndef TCONFIG_H
#define TCONFIG_H


#include <SDL/SDL_ttf.h>
#include "abrir_fichero.h" // inheriting class's header file
#include <SDL/SDL.h>
#include <stdio.h>
#include "traza.h"

/*
 * No description
 */
class TConfig : public abrir_fichero
{
	public:
		// class constructor
		TConfig();
		// class destructor
		~TConfig();
		void obtenClaves();
		char * getClave(char *dato);
        bool setClave(char *dato, char *valor);
		void setClave(char *dato, int valor);
	protected:
        bool esRetorno(char dato);
        void separarValores(char *dato);
        traza *objTraza;

        struct my_struct_clave {
          char nombre[255];
          char valor[255];
        };

        struct my_struct_arrayClaves {
            my_struct_clave *clave;
            int numClaves;
        } arrayClaves ;           //Se permiten 20 valores


};

#endif // MENU_H
