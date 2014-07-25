// Class automatically generated by Dev-C++ New Class wizard

#ifndef TImagen_H
#define TImagen_H


#include <SDL/SDL.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL_image.h>
#include "menuData.h"
#include "timer.h"
#include "mapeos.h"
#include "pantalla.h"

class TImagen : public TPantalla
{
	public:
		// class constructor
		TImagen(SDL_Surface *screen);
		// class destructor
		~TImagen();
        //metodos
        void Refresh(void);
        void Resize(float relacion);
		bool LoadFromFile(char *file_name, bool actualizarPantalla);
		Uint32 getpixel(SDL_Surface *surface, int x, int y);
		Uint32 getpixelbilinear(int x, int y);
		void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
		bool isImagen(char *filename);
		void RefreshAll(void);
		void moverZoomPantallaX(int varSalto);
		void moverZoomPantallaY(int varSalto);
		void Zoom(int varSalto);
        void ZoomOriginal();
        void presentacion(TMenuData *listaCampos);
        void pintarCirculo (int x, int y, int r,int r_color);
        void pintarLinea (int x1, int y1, int x2, int y2 ,int r_color);
        void fondoCirculos();
        void setRetrasoPresentacion(int var_dato);
        int getRetrasoPresentacion();
        void thumbnail(TMenuData *var_menu);
        bool thumbVisible;
        void thumbArriba();
        void thumbAbajo();
        void thumbIzquierda();
        void thumbDerecha();
        void resaltarThumb(int posicion);
        void pintarTriangulo (int x, int y, int base, int altura, bool isUP, int r_color);
        void pintarTitulo(char *titulo);
        void pintarIcono(int numIcono,int x,int y);
        bool cargarIconos();
        void blur_image();
        int blur_slow_get_rgba(int, int, int);


    private:
		void drawSprite(SDL_Surface* imageSurface, SDL_Surface* screenSurface, int srcX, int srcY, int width, int height);
		float relacion(SDL_Surface *visor, int alto, int ancho);
		void centrado(int *posicion, double imAlto, double imAncho, int alto, int ancho);
		void ResizeSurface(float relacion, SDL_Surface *varBitmap);

		//propiedades
		SDL_Surface *bitmap;    //Bitmap sin procesar
		SDL_Surface *RAWbitmap; //Bitmap procesado
		//SDL_Surface* sprite;
		SDL_Surface *screen;
		float zoomFactor;
        int moveIncFactor;
        SDL_Rect *rectPantalla;
		int top;
		int left;
		bool autosize;
		int retrasoPresentacion;
 	    int arrayColores[10];
        static int dato;


        struct my_struct_arrays {
          SDL_Surface *Icon[31];
          int numIcons;
        } arrayIcons;


        //Datos para el thumb de imagenes
         //representa la posicion del cuadrado azul dentro del thumb de imagenes
        int posicionImgThumb;
        int separacion;
        int thumb_w;
        int thumb_h;
};


#endif // TImagen_H