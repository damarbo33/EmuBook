#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include "traza.h"
#include "sound.h"


//#include "abrir_fichero.h"
//#include "pantalla.h"
#include "ttext.h"
#include "tmenuprincipal.h"


/* The screen surface, joystick device */
SDL_Surface *screen = NULL;
SDL_Joystick *joy = NULL;


//abrir_fichero *fichero;
//TPantalla *pantalla;

//TText *Lector;
TMenuPrincipal *menu;

void funcAhorro(TMenuPrincipal *var_menu)
{
    bool done = false;
    while (!done)
    {
        SDL_Event event;
        /* Check for events */
        if (SDL_WaitEvent (&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                if ( (event.key.keysym.sym == SDLK_c) && (event.key.keysym.mod & (KMOD_LCTRL | KMOD_RCTRL)) )
                    done = 1;
                else
                {
                    done = var_menu->procesarTeclas(event.key.keysym.sym);
                }
                break;
            case SDL_JOYBUTTONDOWN:
                done = menu->procesarJoystick(event);
                break;
            case SDL_QUIT:
                done = 1;
                break;
            case SDL_VIDEORESIZE:

                printf("Redimensionamos: %d, %d\n",event.resize.w,event.resize.h);
                screen = SDL_SetVideoMode (event.resize.w, event.resize.h, 16, SDL_SWSURFACE|SDL_RESIZABLE);
                menu->maxWidth = event.resize.w-menu->margenI-menu->margenD;
                menu->maxHeight = event.resize.h-menu->margenF-menu->margenS;
                menu->Lector->maxWidth = menu->maxWidth;
                menu->Lector->maxHeight = menu->maxHeight;

                if (var_menu->visible)
                {
                    menu->reset_marcador();
                    menu->MostrarMenu(menu->menusD->posMenu);
                }
                else
                {
                    menu->refrescarTexto();
                    menu->Lector->pintarPagina(true);
                    menu->visible = false;
                    SDL_UpdateRect(screen, 0, 0, 0, 0);
                }
                //SDL_UpdateRect(screen, 0, 0, 0, 0);

                break;

            default:
                break;
            }
        }
    }
}

void Terminate(void)
{
    Mix_CloseAudio();
    SDL_Quit();
#ifdef GP2X
    chdir("/usr/gp2x");
    execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
#endif
}

int main (int argc, char *argv[])
{

    int done;
    if(TTF_Init()==-1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    traza *objTraza = new traza();

    objTraza->print("Main");

    // Initialize SDL
    if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) < 0)
    {
        fprintf (stderr, "Couldn't initialize SDL: %s\n", SDL_GetError ());
        objTraza->print("Main No SDL");
        exit (1);
    }

    atexit (Terminate);
    //SDL_ShowCursor(SDL_DISABLE);


    #ifdef GP2X
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16, MIX_DEFAULT_CHANNELS, 128);			// Initialize SDL_mixer for GP2X, buffer is set lower than PC
	#endif

	#ifndef GP2X
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16, MIX_DEFAULT_CHANNELS, 1024);		// Initialize SDL_mixer for PC, buffer is set higher
	#endif


    /* Set 320x240 16-bits video mode */
    #ifdef GP2X
		screen = SDL_SetVideoMode (320, 240, 16, SDL_SWSURFACE);
	#endif

	#ifndef GP2X
		//screen = SDL_SetVideoMode (0, 0, 16, SDL_SWSURFACE|SDL_FULLSCREEN);
		screen = SDL_SetVideoMode (640, 480, 16, SDL_SWSURFACE|SDL_RESIZABLE);
	#endif

    if (screen == NULL)
    {
        fprintf (stderr, "Couldn't set 320x240x16 video mode: %s\n", SDL_GetError ());
        objTraza->print("Main No Video");

        exit (2);
    }

    /* Check and open joystick device */
    if (SDL_NumJoysticks() > 0)
    {
        joy = SDL_JoystickOpen(0);
        if (!joy)
        {
            fprintf (stderr, "Couldn't open joystick 0: %s\n", SDL_GetError ());
            objTraza->print("Main No Joystick");
        }
    }

    int procesarTeclas (SDLKey sym);
    int procesarJoystick (Uint8 sym);


    SDL_ShowCursor(SDL_DISABLE);
    //fichero = new abrir_fichero();
    //pantalla = new TPantalla(screen);

    objTraza->print("Main antes de crear el objeto menu");
    menu = new TMenuPrincipal(screen);
    //Lector = new TText(screen);
    objTraza->print("Main Despues de crear el objeto menu");


#ifdef win
    //SDL_EnableKeyRepeat(200, 50);
#endif

    done = 0;

	objTraza->print("Main antes de MostrarMenuPrincipal");
    menu->MostrarMenuPrincipal();
    printf("Main despues de MostrarMenuPrincipal\n");
    bool pressed = false;
    bool first_press = true;
    unsigned int last_press = 0;

    bool modoAhorro = false;
	TConfig *fichConf = new TConfig();
    if (fichConf->procesar_fichero("lector.ini"))
    {
        fichConf->obtenClaves();
        char dato[5];
        strcpy(dato,fichConf->getClave("waitMode"));

        if (strcmp(dato,"1") == 0)
        {
           //modoAhorro
           modoAhorro = true;
        }
    }
    else
    {
        objTraza->print("Error al abrir el fihcheros");
    }

    if (modoAhorro)
    {
        funcAhorro(menu);
    }
    else
    {
        while (!done)
        {
            SDL_Event event;
            /* Check for events */
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_KEYDOWN:
                    if ( (event.key.keysym.sym == SDLK_c) && (event.key.keysym.mod & (KMOD_LCTRL | KMOD_RCTRL)) )
                        done = 1;
                    else
                    {
                        //done = menu->procesarTeclas(event.key.keysym.sym);
                        pressed = true;
                        last_press = SDL_GetTicks();
                    }
                    break;
                case SDL_KEYUP:
                    pressed = false;
                    first_press = true;

                    break;
                case SDL_JOYBUTTONDOWN:
                    //done = menu->procesarJoystick(event);
                    pressed = true;
                    last_press = SDL_GetTicks();
                    break;
                case SDL_JOYBUTTONUP:
                    pressed = false;
                    first_press = true;
                    break;
                case SDL_QUIT:
                    done = 1;
                    break;
                case SDL_VIDEORESIZE:

                printf("Redimensionamos: %d, %d\n",event.resize.w,event.resize.h);
                screen = SDL_SetVideoMode (event.resize.w, event.resize.h, 16, SDL_SWSURFACE|SDL_RESIZABLE);
                menu->maxWidth = event.resize.w-menu->margenI-menu->margenD;
                menu->maxHeight = event.resize.h-menu->margenF-menu->margenS;
                menu->Lector->maxWidth = menu->maxWidth;
                menu->Lector->maxHeight = menu->maxHeight;
                if (menu->visible)
                {
                    menu->reset_marcador();
                    menu->MostrarMenu(menu->menusD->posMenu);
                }
                else
                {
                    menu->refrescarTexto();
                    menu->Lector->pintarPagina(true);
                    menu->visible = false;
                    SDL_UpdateRect(screen, 0, 0, 0, 0);
                }

                break;

                default:
                    break;
                }
            }

           /* Processing */

            if (pressed)
            {
                if (last_press < (SDL_GetTicks() - menu->getInitKeyDelay()) || first_press)
                {
                    first_press = false;
    #ifdef GP2X
                    if (event.jbutton.button == GP2X_BUTTON_B || event.jbutton.button == GP2X_BUTTON_START)
                        pressed = false;
                    //done = menu->procesarJoystick(event.jbutton.button);
                    done = menu->procesarJoystick(event);
    #else
                    if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_RETURN)
                        pressed = false;
                    done = menu->procesarTeclas(event.key.keysym.sym);
    #endif
                }
            }


        }
    }
    return 0;
}
