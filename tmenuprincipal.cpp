#include "tmenuprincipal.h" // class's header file
// class constructor
TMenuPrincipal::TMenuPrincipal(SDL_Surface* screen) : TMenu(screen)
{
    objTraza->print("Fin TMenuPrincipal: Inicio");
    sonido = new TSound();
    crearColores();
    fichConf = new TConfig();
    this->b_diccionario = false;

    objTraza->print("TMENUPRINCIPAL Antes de procesar el lector.ini");
    if (!fichConf->procesar_fichero("lector.ini"))
    {
        objTraza->print("TMENUPRINCIPAL HA FALLADO LA LECTURA DEL FICHERO");
        //Damos valores por defecto cuando fallamos al abrir el fichero
        fichConf->setClave("font_size","16");
        fichConf->setClave("font_type","Vera.ttf");
        fichConf->setClave("font_color","7");
        fichConf->setClave("font_bkgd","6");
        fichConf->setClave("font_just","1");
        fichConf->setClave("barra","1");
        fichConf->setClave("sonido","1");
        fichConf->setClave("waitMode","1");
    }
    objTraza->print("TMENUPRINCIPAL antes de mostrar claves");
    fichConf->obtenClaves();
    objTraza->print("Fin TMenuPrincipal: Antes de crear campos");
    this->CrearCampos();
    objTraza->print("Fin TMenuPrincipal: Campos creados");
    Lector = new TText(screen);
    objTraza->print("Fin TMenuPrincipal: Lector creado");
    this->cargaConfiguracion(Lector);
    objTraza->print("Fin TMenuPrincipal: config cargada");
    strcpy(this->ficheroSeleccionado,"");
    SetArchivoAbierto(false,"");
    this->key_delay = 100;
    this->key_init_delay = 700;
    this->fuenteCambiada = false;
    this->tecladoPantalla = new TTecladoPantalla(screen);
    LectorDiccionario = new TText(screen);
    objTraza->print("Fin TMenuPrincipal: Fin Constructor");

}


// class destructor
TMenuPrincipal::~TMenuPrincipal()
{
    printf("TMenuPrincipal::~TMenuPrincipal()\n");
    // insert your code here
//    printf("despues de guardar la configuracion");
    for (int i = 0; i < menusD->numMenus;i++)
    {
        free(menusD->menus[i].campo);
    }
    free(menusD->menus);
    delete [] Lector;
    delete fichConf;
    delete tecladoPantalla;
    delete sonido;
}

int TMenuPrincipal::getKeyDelay()
{
    return this->key_delay;
}

void TMenuPrincipal::setKeyDelay(int iDelay)
{
    this->key_delay = iDelay;
}

unsigned int TMenuPrincipal::getInitKeyDelay()
{
    return this->key_init_delay;
}

void TMenuPrincipal::setInitKeyDelay(unsigned int iDelay)
{
    this->key_init_delay = iDelay;
}


void TMenuPrincipal::cargaConfiguracion(TText *lectorTexto)
{
    char tamFuente[4];

    printf("Cargamos config del lector\n");

    strcpy(tamFuente,fichConf->getClave("font_size"));

    if (tamFuente != NULL)
    {
        Lector->setTamFuente(atoi(tamFuente));
    }

    int conf_justicado = atoi(fichConf->getClave("font_just"));
    if (conf_justicado == 0)
    {
        Lector->setJustificar(false);
    }
    else
    {
        Lector->setJustificar(true);
    }

    int conf_barra = atoi(fichConf->getClave("barra"));
    if (conf_barra == 0)
    {
        printf("No activamos la barra\n");
        Lector->setBarra(false);
    }
    else
    {
        printf("Activamos la barra\n");
        Lector->setBarra(true);
    }

    int conf_sound = atoi(fichConf->getClave("sonido"));
    if (conf_sound == 0)
    {
        printf("No activamos el sonido\n");
        this->sonido->setSound(false);
        //Lector->setBarra(false);
    }
    else
    {
        printf("Activamos el sonido\n");
        this->sonido->setSound(true);
    }

    printf("antes de obtener la fuente %s\n",fichConf->getClave("font_type"));


 	char TipoFuente[100];
    strcpy(TipoFuente,fichConf->getClave("font_type"));

    /*char TipoFuente[255];
    memset(TipoFuente, '\0', 255);
    printf("Antes de copiar\n");*/


    strcpy(TipoFuente,fichConf->getClave("font_type"));

    if (TipoFuente != NULL)
    {
        char directorio[MAXPATH];
        strcpy(directorio,this->rutaSeleccion);

#ifdef GP2X
        strcat(directorio,"/fonts/");
#endif

#ifdef WIN32
        strcat(directorio,"\\fonts\\");
#endif

        strcat(directorio,TipoFuente);

        this->Lector->setColor(atoi(fichConf->getClave("font_color")));
        this->Lector->setFondo(atoi(fichConf->getClave("font_bkgd")));

        printf("TamFuenteLector: %d, %s\n",this->Lector->getTamFuente(), directorio);
        if (!this->Lector->LoadFont(directorio,this->Lector->getTamFuente()))
        {
            printf("Iniciamos el lector\n");
            this->Lector->LoadFont(this->Lector->getTamFuente()) ;
            this->LoadFont(this->tamFuente);
        }
        else
        {
            printf("Solo iniciamos los menus\n");
            this->LoadFont(directorio,this->tamFuente);
        }
    }

}

void TMenuPrincipal::guardaConfiguracion(void)
{
    char tamFuente[4];
    char tipoFuente[100];
    char colorFuente[10];
    char fondoFuente[10];
    char posTexto[20];
    char justificadoTexto[20];
    char sTiempo[20];
    char barra[20];
    char modoAhorro[20];
    char posLinea[20];
    char sonido_c[20];

    sprintf(posLinea,"%d",this->Lector->posLinea);
    strcpy(tamFuente,fichConf->getClave("font_size"));
    strcpy(tipoFuente,fichConf->getClave("font_type"));
    strcpy(colorFuente,fichConf->getClave("font_color"));
    strcpy(fondoFuente,fichConf->getClave("font_bkgd"));
    strcpy(justificadoTexto,fichConf->getClave("font_just"));
    strcpy(barra,fichConf->getClave("barra"));
    strcpy(modoAhorro,fichConf->getClave("waitMode"));
    strcpy(sonido_c,fichConf->getClave("sonido"));

    strcpy(posTexto,posLinea);

    //printf("Posicion texto es: %d\n",this->Lector->posLinea);


//    delete fichConf;

    FILE* fout;
    //FILE* fout2;

    char directorioINI[MAXPATH];
    char directorioCFG[MAXPATH];


    strcpy(directorioINI,this->rutaSeleccion);
    strcpy(directorioCFG,this->rutaSeleccion);

#ifdef GP2X
    strcat(directorioINI,"/lector.ini");
    strcat(directorioCFG,"/cfg/");
    strcat(directorioCFG,this->ficheroSeleccionado);
    strcat(directorioCFG,".cfg");
#endif

#ifdef WIN32
    strcat(directorioINI,"\\lector.ini");
    strcat(directorioCFG,"\\cfg\\");
    strcat(directorioCFG,this->ficheroSeleccionado);
    strcat(directorioCFG,".cfg");
#endif

    char buffer[1000];
    memset(buffer, '\0', 1000);

    strcpy(buffer,"");
    if (tamFuente != NULL)
    {
        strcat(buffer,"font_size=");
        strcat(buffer,tamFuente);
        addreturn(buffer);
    }
    if (tipoFuente != NULL)
    {
        strcat(buffer,"font_type=");
        strcat(buffer,tipoFuente);
        addreturn(buffer);
    }
    if (tipoFuente != NULL)
    {
        strcat(buffer,"font_color=");
        strcat(buffer,colorFuente);
        addreturn(buffer);
    }
    if (tipoFuente != NULL)
    {
        strcat(buffer,"font_bkgd=");
        strcat(buffer,fondoFuente);
        addreturn(buffer);
    }
    if (justificadoTexto != NULL)
    {
        strcat(buffer,"font_just=");
        strcat(buffer,justificadoTexto);
        addreturn(buffer);
    }

    if (barra != NULL)
    {
        strcat(buffer,"barra=");
        strcat(buffer,barra);
        addreturn(buffer);
    }

    if (sonido_c != NULL)
    {
        strcat(buffer,"sonido=");
        strcat(buffer,sonido_c);
        addreturn(buffer);
    }

    if (modoAhorro != NULL)
    {
        strcat(buffer,"waitMode=");
        strcat(buffer,modoAhorro);
    }

    addreturn(buffer);


    if ( (fout = fopen(directorioINI,"wt")) != NULL)
    {
        fwrite(buffer, sizeof(char) , strlen(buffer), fout);
        fclose(fout);
    }

    if (strcmp(this->ficheroSeleccionado,"") != 0)
    {
        memset(buffer, '\0', 1000);
        strcpy(buffer,"");
        if (posTexto != NULL)
        {
            strcat(buffer,"PosicionTexto=");
            strcat(buffer,posTexto);
            addreturn(buffer);
        }

        if (this->ficheroSeleccionado != NULL)
        {
            strcat(buffer,"ruta=");
            char rutaActual[MAXPATH+1]; //Ruta Actual en la que nos encontramos
            char nuevaRuta[MAXPATH+1];  //Ruta nueva con el directorio seleccionado

            getDirActual(rutaActual);

            //Concatenamos la ruta actual con el directorio seleccionado
            strcpy(nuevaRuta,rutaActual);
        #ifdef GP2X
            strcat(nuevaRuta,"/");
        #endif

        #ifdef WIN32
            strcat(nuevaRuta,"\\");
        #endif



            strcat(buffer,nuevaRuta);
            addreturn(buffer);
            strcat(buffer,"nombre=");
            strcat(buffer,this->ficheroSeleccionado);
            addreturn(buffer);

            strcat(buffer,"bookmarks=");
            char str_bookmarks[1];

            for (int i=0;i<this->Lector->arrayBookmarks.n_bookmarks;i++)
            {
                sprintf(str_bookmarks,"%d",this->Lector->arrayBookmarks.booklist[i]);
                strcat(buffer,str_bookmarks);
                if (i < this->Lector->arrayBookmarks.n_bookmarks - 1) strcat(buffer,",");
            }
            addreturn(buffer);

            sprintf(sTiempo,"%d",this->getTiempoLectura());
            strcat(buffer,"tiempo=");
            strcat(buffer,sTiempo);
            addreturn(buffer);

        }

        if ( (fout = fopen(directorioCFG,"wt")) != NULL)
        {
            fwrite(buffer, sizeof(char) , strlen(buffer), fout);
            fclose(fout);
        }
    }

#ifdef GP2X
    sync();
#endif
}

void TMenuPrincipal::CrearCampos()
{

    menusD->AddMenu("Menu Principal");
    menusD->AddCampoMenu(fichLang->getClave("mOpen"),"s8");
    menusD->AddCampoMenu(fichLang->getClave("mOpt"),"s5");
    menusD->AddCampoMenu(fichLang->getClave("mGoto"),"s7");
    menusD->AddCampoMenu(fichLang->getClave("mRecent"),"s6");
    menusD->AddCampoMenu(fichLang->getClave("mSearch"),"s9");
    menusD->AddCampoMenu(fichLang->getClave("mEstat"),"s10");
    menusD->AddCampoMenu(fichLang->getClave("mReturn"),"s3");
    menusD->AddCampoMenu(fichLang->getClave("mExit"),"s4");


    printf("Antes del explorador\n");
    menusD->AddMenu("Explorador");
    this->explorar(".");

    printf("Antes de opciones\n");
    menusD->AddMenu("Opciones");
    menusD->AddCampoMenu("","s14");
    menusD->AddCampoMenu("","s13");
    menusD->AddCampoMenu("","s15");
    menusD->AddCampoMenu("","s15");
    menusD->AddCampoMenu("","s16");
    menusD->AddCampoMenu("","s17");
    menusD->AddCampoMenu("","s18");
    menusD->AddCampoMenu("","s30");
    menusD->AddCampoMenu("","s29");
    menusD->AddCampoMenu("","s3");
    this->opciones();

    menusD->AddMenu("Tipos de fuente");

    menusD->AddMenu("Ir A");
    menusD->AddCampoMenu("","s19");
    menusD->AddCampoMenu(fichLang->getClave("mReturn"),"s3");
    //this->irA();

    menusD->AddMenu("Archivos recientes");

    menusD->AddMenu("Borrar recientes");
    menusD->AddCampoMenu(fichLang->getClave("mYes"),"s12");
    menusD->AddCampoMenu(fichLang->getClave("mNo"),"s11");

    menusD->AddMenu("Estadísticas");
    menusD->AddCampoMenu("","");

    menusD->AddMenu("Quizás quiso buscar...");

/*
    menusD->numMenus = 1;
    menusD->menus = (struct TMenuData::my_struct_menu *) malloc(menusD->numMenus * sizeof(struct TMenuData::my_struct_menu));
    //campo = (struct TMenuData::TMenuData::my_struct_campo *) malloc(numCampos * sizeof(struct TMenuData::TMenuData::my_struct_campo));

    //El menú 0 representa la pantalla inicial
    menusD->menus[0].numCampos = 8;
    menusD->menus[0].campo = (struct TMenuData::TMenuData::my_struct_campo *) malloc((menusD->menus[0].numCampos+1) * sizeof(struct TMenuData::TMenuData::my_struct_campo));
    menusD->menus[0].tieneProps = true;
    strcpy(menusD->menus[0].campo[0].nombre,"Abrirme la puerta");
    strcpy(menusD->menus[0].campo[1].nombre,"Opciones");
    strcpy(menusD->menus[0].campo[2].nombre,"Ir a");
    strcpy(menusD->menus[0].campo[3].nombre,"Archivos recientes");
    strcpy(menusD->menus[0].campo[4].nombre,"Buscar");
    strcpy(menusD->menus[0].campo[5].nombre,"Estadísticas");
    strcpy(menusD->menus[0].campo[6].nombre,"Volver");
    strcpy(menusD->menus[0].campo[7].nombre,"Salir");

    strcpy(menusD->menus[0].campo[0].props,"s8");
    strcpy(menusD->menus[0].campo[1].props,"s5");
    strcpy(menusD->menus[0].campo[2].props,"s7");
    strcpy(menusD->menus[0].campo[3].props,"s6");
    strcpy(menusD->menus[0].campo[4].props,"s9");
    strcpy(menusD->menus[0].campo[5].props,"s10");
    strcpy(menusD->menus[0].campo[6].props,"s3");
    strcpy(menusD->menus[0].campo[7].props,"s4");


    //El menu 1 Será el de el explorador de archivos
    this->explorar(".");
    menusD->menus[1].tieneProps = true;

    //El menu 2 será el de opciones
    menusD->menus[2].numCampos = 8;
    menusD->menus[2].campo = (struct TMenuData::TMenuData::my_struct_campo *) malloc(menusD->menus[2].numCampos * sizeof(struct TMenuData::TMenuData::my_struct_campo));
    menusD->menus[2].tieneProps = false;
    this->opciones();

    //El menu 3 será el de la seleccion de tipos de fuentes dentro del menu opciones
    menusD->menus[3].campo = (struct TMenuData::TMenuData::my_struct_campo *) malloc(sizeof(struct TMenuData::TMenuData::my_struct_campo));
    menusD->menus[3].tieneProps = false;

    //El menu 4 será el de ir a la pagina indicada
    menusD->menus[4].numCampos = 2;
    menusD->menus[4].campo = (struct TMenuData::TMenuData::my_struct_campo *) malloc(menusD->menus[4].numCampos * sizeof(struct TMenuData::TMenuData::my_struct_campo));
    menusD->menus[4].tieneProps = false;
    this->irA();

    //El menu 5 será el de seleccionar archivos recientes
    menusD->menus[5].campo = (struct TMenuData::TMenuData::my_struct_campo *) malloc(sizeof(struct TMenuData::TMenuData::my_struct_campo));
    menusD->menus[5].tieneProps = false;
    //El menu 6 es el de borrar los archivos recientes
    menusD->menus[6].numCampos = 2;
    menusD->menus[6].campo = (struct TMenuData::TMenuData::my_struct_campo *) malloc(menusD->menus[6].numCampos * sizeof(struct TMenuData::TMenuData::my_struct_campo));
    menusD->menus[6].tieneProps = false;

    strcpy(menusD->menus[6].campo[0].nombre,"Si");
    strcpy(menusD->menus[6].campo[1].nombre,"No");

    //El menu 7 será el menú de las estadísticas que se rellenará cuando pulsemos sobre el botón y hallamos cargado un fichero antes
    menusD->menus[7].campo = (struct TMenuData::TMenuData::my_struct_campo *) malloc(sizeof(struct TMenuData::TMenuData::my_struct_campo));
    menusD->menus[7].tieneProps = false;
*/
}

void TMenuPrincipal::MostrarMenuPrincipal()
{
    if (!visible)
    {
        Clear();
        this->miImagen->fondoCirculos();
        reset_marcador();
        ResetMenus();
        int lineas_pantalla = (this->maxHeight - this->top) / (tamFuente + saltoLinea);
        sangrado(menusD->posMenu);
        int posX=0;
        TTF_SizeText(font,menusD->menus[0].campo[0].nombre,&posX,NULL);

        /*
        pintarCirculo(left + 3,top + 2*saltoLinea + tamFuente/2,tamFuente/2,clRojo);
        pintarCirculo(left + 3 + posX,top+ 2*saltoLinea + tamFuente/2,tamFuente/2,clRojo);

        SDL_Rect pantalla = { left + 3,top + 2*saltoLinea + menusD->posCampo*separacion + 1, posX, tamFuente - 1};
        //Pintamos el texto sobresaltado en color rojo ClRojo
        SDL_FillRect(screen, &pantalla, SDL_MapRGB(screen->format,255,0,0));
        */

        this->miImagen->pintarCirculo(margenI + left + 3,margenS + top + menusD->posCampo*separacion + separacion/2, separacion/2,clRojo);
        this->miImagen->pintarCirculo(margenI + left + 3 + posX, margenS + top + menusD->posCampo*separacion+separacion/2, separacion/2,clRojo);
        SDL_Rect pantalla = {margenI + left + 3,margenS + top + menusD->posCampo*separacion +1, posX, separacion-2};
        //Pintamos el texto sobresaltado en color rojo ClRojo
        SDL_FillRect(screen, &pantalla, SDL_MapRGB(screen->format,255,0,0));

        if (menusD->posMenuScreenIni > 0)
        {
            this->miImagen->pintarTriangulo (5,1,10,9,true,clBlanco);
        }

        if (menusD->posMenuScreenIni < menusD->menus[0].numCampos - lineas_pantalla )
        {
            this->miImagen->pintarTriangulo (5,screen->h - 1,10,9,false,clBlanco);
        }


        for (int contador = 0;contador < menusD->menus[0].numCampos;contador++)
        {
            if (contador == 0) this->setColor(clNegro);
            else this->setColor(clBlanco);
            drawText(menusD->menus[0].campo[contador].nombre,left,margenS + top + contador*separacion);
            IconosMenu(0,contador,margenS + top + contador*separacion +1);
        }

        if (menusD->posMenu == 0)
        {
            //Se hace lo mismo en TMenu::MostrarMenu(int numMenu)
            if (strcmp("",this->nombreFicheroAbierto) != 0 && this->nombreFicheroAbierto != NULL) this->miImagen->pintarTitulo(this->nombreFicheroAbierto);
            else this->miImagen->pintarTitulo(this->menusD->mensajes_menus.mensajes[0].textoMensaje);
            this->setTiempoLectura(SDL_GetTicks() + atoi(this->fichConf->getClave("tiempo")));
            this->verTiempoLectura();
        }

        SDL_UpdateRect(screen, 0, 0, 0, 0);
        visible = true;
        this->guardaConfiguracion();
    }
    else if (b_diccionario)
    {
            //this->LectorDiccionario->anterior_linea();
            //this->fichConf->setClave("PosicionTexto",this->Lector->posLinea);
            this->LectorDiccionario->pintarPagina(true);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
            visible = false;
    }
    else
    {
        menusD->posMenu = 0;
        if (this->fuenteCambiada == true)
        {
            this->refrescarTexto();
        }
        Lector->pintarPagina(true);
        visible = false;
        SDL_UpdateRect(screen, 0, 0, 0, 0);
    }
    this->Lector->setForzarTextoRemarcar(NULL);

}

void TMenuPrincipal::refrescarTexto()
{
        int posicionLinea = Lector->posLinea;
        int paginasAntes = Lector->lineas.n_lineas;
        int repaginado = posicionLinea;
        Lector->buscar_paginas();
        //this->fichConf->setClave("PosicionTexto",this->Lector->posLinea);
        int paginasDespues = Lector->lineas.n_lineas;

        if (paginasAntes > 0)
        {
            float relacion = paginasDespues/(float)paginasAntes;
            repaginado = (int)ceil(posicionLinea * relacion);
            if (repaginado < 1) repaginado = 1;
            Lector->repaginarFavoritos(relacion);
        }
        Lector->posLinea = repaginado;
        this->fuenteCambiada = false;
}


int TMenuPrincipal::ejecutarMenu(Uint8 sym)
{
    int done = 0;

    //Este es el caso del menu principal. Incluimos las acciones a realizar
    //dentro de este menu

    if (visible)
    {
        if (menusD->posMenu == 0 && sym == VK_FB)
        {
            //reseteamos la ruta del explorador de archivos
            //setRutaSeleccion(".");
            //getDirActual(rutaSeleccion);
            //Acciones del menú
            switch (menusD->posCampo)
            {
            case 0 :
                //Introducimos el codigo para pintar la pantalla "explorador de archivos"
                menusD->posMenu = 1;
                this->reset_marcador();
                this->sangrado(menusD->posMenu);
                this->MostrarMenu(menusD->posMenu);
                break;
            case 1 :
                //Introducimos el codigo para pintar la pantalla "opciones"
                menusD->posMenu = 2;
                this->reset_marcador();
                this->sangrado(menusD->posMenu);
                this->MostrarMenu(menusD->posMenu);
                break;
            case 2 :
                if (this->GetArchivoAbierto())
                {
                    //Introducimos el codigo para pintar la pantalla "ir a"
                    menusD->posMenu = 4;
                    this->reset_marcador();
                    this->sangrado(menusD->posMenu);
                    this->irA();
                }
                break;
            case 3 :
                    //Introducimos el codigo para pintar la pantalla de "archivos recientes"
                    menusD->posMenu = 5;
                    this->reset_marcador();
                    this->sangrado(menusD->posMenu);
                    this->MostrarFicherosRecientes();
                    this->MostrarMenu(menusD->posMenu);
                break;

            case 4 :
                    //Introducimos el codigo para pintar la pantalla de "Buscar"
                    this->MenuBuscar();
                break;
            case 5 :
                    //Introducimos el codigo para pintar la pantalla de "Estadísticas"
                    if (this->GetArchivoAbierto())
                    {
                        menusD->posMenu = 7;
                        this->reset_marcador();
                        this->sangrado(menusD->posMenu);
                        this->MostrarEstadisticas();
                        this->MostrarMenu(menusD->posMenu);
                    }
                break;

            case 6 :
                //Introducimos el codigo para pintar la pantalla de "Volver"
                if (this->GetArchivoAbierto())
                {
                    this->MostrarMenuPrincipal();
                }
                break;

            case 7 :
                //Introducimos el codigo para pintar la pantalla de "Salir"
                this->guardaConfiguracion();
                SDL_Quit();
#ifdef GP2X
                chdir("/usr/gp2x");
                execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
#endif
                done = 1;
                break;
            default :
                break;
            }
        }
        //Aqui metemos las ordenes para el menu del explorador de archivos
        else if (menusD->posMenu == 1 && sym == VK_FB)
        {
            //Para el caso en el que se desea salir al menu. Se selecciona la opción de volver.
            if (menusD->posCampo == menusD->menus[1].numCampos - 1 )
            {
                this->ResetMenus();
                this->sangrado(menusD->posMenu);
                this->MostrarMenu(menusD->posMenu);
            }
            else
            {
//                printf("ejecutarMenu::AccionesMenuAbrir\n");
                this->AccionesMenuAbrir();
            }
        }
        //Aqui metemos las ordenes para el menu de las opciones del programa
        else if (menusD->posMenu == 2)
        {
            //Para el caso en el que se desea salir al menu. Se selecciona la opción de volver.
            if (menusD->posCampo == menusD->menus[2].numCampos - 1 && sym == VK_FB)
            {
                this->ResetMenus();
                this->sangrado(menusD->posMenu);
                this->MostrarMenu(menusD->posMenu);
            }
            else
            {
                this->AccionesMenuOpciones(sym);
            }
        }
        //Aqui metemos las ordenes para el menu de la seleccion de fuentes
        else if (menusD->posMenu == 3  && sym == VK_FB)
        {
            //Para el caso en el que se desea salir al menu. Se selecciona la opción de volver.
            if (menusD->posCampo == menusD->menus[3].numCampos - 1)
            {
                this->ResetMenus();

                menusD->posMenu=2;
                this->sangrado(menusD->posMenu);
                this->MostrarMenu(menusD->posMenu);
            }
            else
            {
                this->AccionesMenuFuentes();
            }
        }
        //Aqui metemos las opciones del menu irA
        else if (menusD->posMenu == 4)
        {
            if (menusD->posCampo == menusD->menus[4].numCampos - 1 && sym == VK_FB)
            {
//                printf("Antes del reset de menus para ir\n");
                this->ResetMenus();
                menusD->posMenu=0;
                this->sangrado(menusD->posMenu);
                this->MostrarMenu(menusD->posMenu);
            }
            else if (sym != VK_FB)
            {
//                printf("Antes delas acciones de ir\n");
                this->AccionesMenuIrA(sym);
            }

        }
        //Aqui metemos las ordenes para el menu de los archivos recientes
        else if (menusD->posMenu == 5 && sym == VK_FB)
        {
            //Para el caso en el que se desea salir al menu. Se selecciona la opción de volver.
            if (menusD->posCampo == menusD->menus[5].numCampos - 1 )
            {
                this->ResetMenus();
                this->sangrado(menusD->posMenu);
                this->MostrarMenu(menusD->posMenu);
            }
            else
            {
                this->AccionesMenuRecientes();
            }
        }
        //Aqui metemos las ordenes para el menu de borrar los archivos recientes
        else if (menusD->posMenu == 6 && sym == VK_FB)
        {
            //Para el caso en el que se desea salir al menu. Se selecciona la opción de volver.
            if (menusD->posCampo == menusD->menus[6].numCampos - 1 )
            {
                this->ResetMenus();
                this->sangrado(menusD->posMenu);
                this->MostrarMenu(menusD->posMenu);
            }
            else
            {
                this->AccionesBorradoRecientes();
            }
        }
        //Aqui metemos las ordenes para el menu de borrar los archivos recientes
        else if (menusD->posMenu == 7 && sym == VK_FB)
        {
            //Para el caso en el que se desea salir al menu. Se selecciona la opción de volver.
            if (menusD->posCampo == menusD->menus[7].numCampos - 1 )
            {
                this->ResetMenus();
                this->sangrado(menusD->posMenu);
                this->MostrarMenu(menusD->posMenu);
            }
            //else
            //{
            //    this->AccionesBorradoRecientes();
            //}
        }
        //Aqui metemos las ordenes para el menu de la seleccion de quizas quiso buscar
        else if (menusD->posMenu == 8  && sym == VK_FB)
        {
            //Para el caso en el que se desea salir al menu. Se selecciona la opción de volver.
            if (menusD->posCampo == menusD->menus[8].numCampos - 1)
            {
                //this->ResetMenus();
                //this->sangrado(menusD->posMenu);
                //this->MostrarMenuPrincipal();
                this->visible = true;
                this->b_diccionario = false;
                this->MostrarMenuPrincipal();
            }
            else
            {
                this->AccionesQuizasQuisoBuscar();
            }
        }

    }
    return done;
}

void TMenuPrincipal::MenuBuscar()
{
    if (this->GetArchivoAbierto())
    {
        char palabraBuscar[16];
        //memset(palabraBuscar,' ',16);
        //palabraBuscar[15] = '\0';
        //strcpy(palabraBuscar,"");
        this->miImagen->pintarTitulo("Buscar palabra");

        //if (tecladoPantalla->gestionTeclado(palabraBuscar) == true)
        if (tecladoPantalla->gestionTeclado() == true)
        {
            this->MostrarMenuPrincipal();
            strcpy(palabraBuscar,tecladoPantalla->getTextoBusqueda());
            this->Lector->buscarTexto(palabraBuscar,0,1);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        else
        {
            this->MostrarMenu(0);
        }
    }
}

// No description
void TMenuPrincipal::explorar(char *filename)
{
    DIR *dir;
    struct dirent *ent;
    //int contador = 0;
//   char *datos;


    if ((dir = opendir(filename)) != NULL)
    {

        //reseteamos el marcador del elemento seleccionado
        this->reset_marcador();
        this->menusD->posCampo = 0;
        this->menusD->clearCamposMenu(1);
        //Hacemos dos pases. Uno para leer en primer lugar los directorios y otro para leer
        //los archivos
        for (int i=0;i<2;i++)
        {
            while ((ent = readdir(dir)) != NULL)
            {
                if (!get_file_attrib(ent->d_name) && i==1)
                {
                    //El fichero recogido es un fichero
//                    if (contador == 0)
//                    {
//                        this->menusD->clearCamposMenu(1);
//                    }

                    //Definimos si estamos pintando una imagen o cualquier otro fichero
                    if (miImagen->isImagen(ent->d_name))
                    {
                        menusD->AddCampoMenu(1,ent->d_name,"fi");
                    }
                    else if (this->contiene(ent->d_name, "txt") >= 0 || this->contiene(ent->d_name, "TXT") >= 0)
                    {
                        menusD->AddCampoMenu(1,ent->d_name,"ft");
                    }
                    else if (this->contiene(ent->d_name, ".gpu") >= 0 || this->contiene(ent->d_name, ".GPU") >= 0
                    || this->contiene(ent->d_name, ".gpe") >= 0 || this->contiene(ent->d_name, ".GPE") >= 0
                    || this->contiene(ent->d_name, ".exe") >= 0 || this->contiene(ent->d_name, ".EXE") >= 0
                    || this->contiene(ent->d_name, ".bat") >= 0 || this->contiene(ent->d_name, ".BAT") >= 0
                    || this->contiene(ent->d_name, ".com") >= 0 || this->contiene(ent->d_name, ".COM") >= 0)
                    {
                        menusD->AddCampoMenu(1,ent->d_name,"fg");
                    }
                    else if (this->contiene(ent->d_name, ".gz") >= 0 || this->contiene(ent->d_name, ".GZ") >= 0
                    || this->contiene(ent->d_name, ".z") >= 0 || this->contiene(ent->d_name, ".Z") >= 0
                    || this->contiene(ent->d_name, ".tar") >= 0 || this->contiene(ent->d_name, ".TAR") >= 0
                    || this->contiene(ent->d_name, ".zip") >= 0 || this->contiene(ent->d_name, ".ZIP") >= 0
                    || this->contiene(ent->d_name, ".rar") >= 0 || this->contiene(ent->d_name, ".RAR") >= 0)
                    {
                        menusD->AddCampoMenu(1,ent->d_name,"fz");
                    }
                    else if (this->contiene(ent->d_name, ".pdf") >= 0 || this->contiene(ent->d_name, ".PDF") >= 0
                    || this->contiene(ent->d_name, ".ps") >= 0 || this->contiene(ent->d_name, ".PS") >= 0)
                    {
                        menusD->AddCampoMenu(1,ent->d_name,"fp");
                    }
                    else if (this->contiene(ent->d_name, ".c") >= 0 || this->contiene(ent->d_name, ".C") >= 0
                    || this->contiene(ent->d_name, ".cpp") >= 0 || this->contiene(ent->d_name, ".CPP") >= 0)
                    {
                        menusD->AddCampoMenu(1,ent->d_name,"fc");
                    }
                    else if (this->contiene(ent->d_name, ".h") >= 0 || this->contiene(ent->d_name, ".H") >= 0)
                    {
                        menusD->AddCampoMenu(1,ent->d_name,"fh");
                    }
                    else if (this->contiene(ent->d_name, ".ttf") >= 0 || this->contiene(ent->d_name, ".TTF") >= 0)
                    {
                        menusD->AddCampoMenu(1,ent->d_name,"ff");
                    }
                    else
                    {
                        menusD->AddCampoMenu(1,ent->d_name,"f.");
                    }

                }
                else if (get_file_attrib(ent->d_name) && i==0 && strcmp(ent->d_name,".") != 0)
                {
                    //Pintamos los directorios
//                    if (contador == 0)
//                    {
//                        this->menusD->clearCamposMenu(1);
//                    }
                    menusD->AddCampoMenu(1,ent->d_name,"d.");
                }
            }
            rewinddir(dir);
        }
        menusD->AddCampoMenu(1,fichLang->getClave("mReturn"),"s3");
//        contador++;
    }
}

/**
*Con este metodo comprobamos que el directorio al que tengo que ir es el adecuado
*Convertiremos C:\\Archivos de programa\\.. en
* C:\\
*
*/
char * TMenuPrincipal::comprobarDirPadre(char * dirDestino)
{
    char file[FILENAME_MAX];
    strcpy(file,dirDestino);
    //memset(file, '\0',FILENAME_MAX);


    if (dirDestino != NULL)
    {
        memset(file, '\0',FILENAME_MAX);
        //strcpy(file,dirDestino);
        #ifdef GP2X
        int pos = contiene(dirDestino,"/..");
        #else
        int pos = contiene(dirDestino,"\\..");
        #endif

        if (pos > 0)
        {
            int i = pos;
            char letra = 0;
            bool encontrado = false;

            do
            {
                i--;
                letra = dirDestino[i];
                #ifdef GP2X
                if (letra == '/') encontrado = true;
                #else
                if (letra == '\\') encontrado = true;
                #endif
            }while (i > 0 && !encontrado);

            for (int j=0;j<=i;j++)
            {
                file[j] = dirDestino[j];
            }

            return file;
        }
    }
    return file;

}


void TMenuPrincipal::AccionesCampoVolver(void)
{

  if (!this->visible && this->b_diccionario)
  {
    if (menusD->menus[8].numCampos > 0)
    {
        menusD->posMenu = 8;
        this->reset_marcador();
        this->sangrado(menusD->posMenu);
        this->MostrarMenu(menusD->posMenu);
    }
    else
    {
        this->visible = true;
        this->b_diccionario = false;
        this->MostrarMenuPrincipal();
    }
  }
  else if (this->menusD->posMenu != 0)
  {
    this->menusD->posCampo = menusD->menus[this->menusD->posMenu].numCampos - 1;
    this->ejecutarMenu(VK_FB);
  }
  else if ( this->visible && this->GetArchivoAbierto())
  {
       this->MostrarMenuPrincipal();
  }


}


void TMenuPrincipal::opciones(void)
{

//    printf("reconstruimos los menus\n");

    char fila[255];

    strcpy(fila,fichLang->getClave("mFontSize"));
    strcat(fila,": ");
    strcat(fila,fichConf->getClave("font_size"));
    //strcpy(menusD->menus[2].campo[0].nombre,fila);
    menusD->ModCampoMenu(2,0,fila,"");

    strcpy(fila,fichLang->getClave("mFontType"));
    strcat(fila,": ");
    strcat(fila,fichConf->getClave("font_type"));
    //strcpy(menusD->menus[2].campo[1].nombre,fila);
    menusD->ModCampoMenu(2,1,fila,"");

    strcpy(fila,fichLang->getClave("mFontColor"));
    strcat(fila,": ");
    strcat(fila, colores[atoi(fichConf->getClave("font_color"))].color  );
    //strcpy(menusD->menus[2].campo[2].nombre,fila);
    menusD->ModCampoMenu(2,2,fila,"");

    strcpy(fila,fichLang->getClave("mBkgColor"));
    strcat(fila,": ");
    strcat(fila, colores[atoi(fichConf->getClave("font_bkgd"))].color );
    //strcpy(menusD->menus[2].campo[3].nombre,fila);
    menusD->ModCampoMenu(2,3,fila,"");

    strcpy(fila,fichLang->getClave("mJustify"));
    strcat(fila,": ");

    int justificado = atoi(fichConf->getClave("font_just"));
    if (justificado == 0)
    {
        strcat(fila, "No");
    }
    else
    {
        strcat(fila, "Si");
    }

    //strcpy(menusD->menus[2].campo[4].nombre,fila);
    menusD->ModCampoMenu(2,4,fila,"");

    strcpy(fila,fichLang->getClave("mScrollBar"));
    strcat(fila,": ");

    int barra = atoi(fichConf->getClave("barra"));
    if (barra == 0)
    {
        strcat(fila, "No");
    }
    else
    {
        strcat(fila, "Si");
    }
    //strcpy(menusD->menus[2].campo[5].nombre,fila);
    menusD->ModCampoMenu(2,5,fila,"");
    //strcpy(menusD->menus[2].campo[6].nombre,"Borrar recientes");
    menusD->ModCampoMenu(2,6,fichLang->getClave("mDelRecent"),"");
    //strcpy(menusD->menus[2].campo[7].nombre,"Volver");

    strcpy(fila,fichLang->getClave("mWait"));
    strcat(fila,": ");
    int ahorro = atoi(fichConf->getClave("waitMode"));
    if (ahorro == 0)
    {
        strcat(fila, "No");
    }
    else
    {
        strcat(fila, "Si");
    }
    //strcpy(menusD->menus[2].campo[5].nombre,fila);
    menusD->ModCampoMenu(2,7,fila,"");

    strcpy(fila,fichLang->getClave("mSound"));
    strcat(fila,": ");
    int iSonido = atoi(fichConf->getClave("sonido"));

    if (iSonido == 0)
    {
        strcat(fila, "No");
    }
    else
    {
        strcat(fila, "Si");
    }
    menusD->ModCampoMenu(2,8,fila,"");

    menusD->ModCampoMenu(2,9,fichLang->getClave("mReturn"),"");
}


void TMenuPrincipal::abrirFichero(char * x)
{

    if (Lector->fichero->procesar_fichero(x))
    {
        Lector->lineas.offset = NULL;
        objTraza->print("abrirFichero: Antes de buscar paginas");
        Lector->buscar_paginas();
        objTraza->print("abrirFichero: Paginas encontradas");
        Lector->Clear();
        //this->fichConf->setClave("PosicionTexto",this->Lector->posLinea);
        TConfig *fichCfg = new TConfig();
        char directorio[MAXPATH];
        strcpy(directorio,this->rutaSeleccion);

#ifdef GP2X
        strcat(directorio,"/cfg/");
#endif

#ifdef WIN32
        strcat(directorio,"\\cfg\\");
#endif

        strcat(directorio,x);
        strcat(directorio,".cfg");

        if (fichCfg->procesar_fichero(directorio))
        {
            fichCfg->obtenClaves();
            for (int i=0;i<atoi(fichCfg->getClave("PosicionTexto"))-1;i++)
                Lector->siguiente_linea();
            //fichConf->setClave("PosicionTexto",fichCfg->getClave("PosicionTexto"));
            Lector->setOrientacion(0);
        }

//        printf("Bookmarks: %s\n",fichCfg->getClave("bookmarks"));
        this->Lector->AsignarBookmarks(fichCfg->getClave("bookmarks"));
        this->fichConf->setClave("tiempo",atoi(fichCfg->getClave("tiempo"))*1000);
        this->tiempoInicioLectura = SDL_GetTicks();
        this->setTiempoLectura(SDL_GetTicks() + atoi(fichCfg->getClave("tiempo"))*1000);
        delete fichCfg;
        Lector->pintarPagina(true);
        SDL_UpdateRect(screen, 0, 0, 0, 0);
    }
    else
    {
//        printf("antes de pintar el mensake de error\n");
        Lector->msg_info("Error al abrir el fichero");
    }
}


void TMenuPrincipal::AccionesMenuAbrir(void)
{
    char rutaActual[MAXPATH+1]; //Ruta Actual en la que nos encontramos
    char nuevaRuta[MAXPATH+1];  //Ruta nueva con el directorio seleccionado
    getDirActual(rutaActual);

    //Concatenamos la ruta actual con el directorio seleccionado
    strcpy(nuevaRuta,rutaActual);

    int tamNuevaRuta = strlen(nuevaRuta);
    int posBarra = contiene(nuevaRuta,'\\');

    if (posBarra != tamNuevaRuta -1)
    {
        #ifdef GP2X
            strcat(nuevaRuta,"/");
        #endif

        #ifdef WIN32
            strcat(nuevaRuta,"\\");
        #endif
    }


    strcat(nuevaRuta,menusD->menus[1].campo[this->menusD->posCampo].nombre);

    //Comprobamos que el directorio seleccionado es el superior
    if (strcmp(menusD->menus[1].campo[this->menusD->posCampo].nombre,"..") == 0)
    {
#ifdef GP2X
        strcat(rutaActual,"/..");
        //strcpy(rutaActual,comprobarDirPadre(rutaActual));
#endif

#ifdef WIN32
        strcat(rutaActual,"\\..");
        //strcpy(rutaActual,comprobarDirPadre(rutaActual));
#endif
        setDirActual(rutaActual);

        this->explorar(rutaActual);
        this->MostrarMenu(menusD->posMenu);
    }
    //Comprobamos que la ruta pasada es un directorio
    else if (get_file_attrib(nuevaRuta))
    {
        setDirActual(nuevaRuta);
        this->explorar(nuevaRuta);
        this->MostrarMenu(menusD->posMenu);
    }
    //El fichero seleccionado es un archivo, por lo que debemos abrirlo
    else
    {
        this->MostrarMenuPrincipal();
        strcpy(this->ficheroSeleccionado,menusD->menus[1].campo[this->menusD->posCampo].nombre);
        this->abrirFichero(menusD->menus[1].campo[this->menusD->posCampo].nombre);
        SetArchivoAbierto(true,menusD->menus[1].campo[this->menusD->posCampo].nombre);
        setTiempoLectura(SDL_GetTicks() + atoi(this->fichConf->getClave("tiempo")));
        //this->setTiempoLectura(SDL_GetTicks() + atoi(fichConf->getClave("tiempo"))*1000 );

    }
}

void TMenuPrincipal::AccionesQuizasQuisoBuscar(void)
{
    TDiccionario *diccionario = new TDiccionario(this->rutaSeleccion);
    int res = diccionario->find(menusD->menus[8].campo[this->menusD->posCampo].nombre);

    if (res != -1)
    {
        //Hemos encontrado la palabra buscada en el diccionario
        if (LectorDiccionario->fichero->crearTexto(diccionario->get()))
        {
            LectorDiccionario->lineas.offset = NULL;
            LectorDiccionario->buscar_paginas();
            LectorDiccionario->Clear();
            LectorDiccionario->pintarPagina(true);
            b_diccionario = true;
            this->MostrarMenuPrincipal();
        }
    }
    delete diccionario;
}


void TMenuPrincipal::AccionesMenuOpciones(Uint8 sym)
{
    int resultado=0;

    switch (this->menusD->posCampo)
    {
    case 0:  //Tamaño de la fuente
        if ((resultado = modificaCampo("font_size",sym)) != -1)
        {
            this->Lector->setTamFuente(resultado);
            this->AccionesMenuTamFuentes();
            printf("Antes opciones\n");
            this->opciones();
            printf("Despues opciones\n");
            this->MostrarMenu(menusD->posMenu);
            printf("Despues mostrar menu\n");
            this->fuenteCambiada = true;
        }
        break;
    case 1:  //tipo de fuente
        this->menusD->posMenu++;
        MostrarFuentes();
        this->MostrarMenu(menusD->posMenu);
        this->fuenteCambiada = true;
        break;
    case 2:  //cOLOR DE LA FUENTE
        if (atoi(fichConf->getClave("font_color")) < 9 || sym == VK_FL)
        {
            if ( modificaCampo("font_color",sym))
            {
                this->AccionesEstiloFuentes();
                this->opciones();
                this->MostrarMenu(menusD->posMenu);
            }
        }
        break;
    case 3:  //COLOR DEL FONDO
        if (atoi(fichConf->getClave("font_bkgd")) < 9 || sym == VK_FL)
        {
            if (modificaCampo("font_bkgd",sym))
            {
                this->AccionesEstiloFuentes();
                this->opciones();
                this->MostrarMenu(menusD->posMenu);
            }
        }
        break;

    case 4:  //Justificado
        if ((resultado = modificaCampo("font_just",sym)) != -1)
        {
            this->AccionesJustificadoFuentes(resultado);
            this->opciones();
            this->MostrarMenu(menusD->posMenu);
        }
        break;


    case 5:  //Barra de desplazamiento
        if ((resultado = modificaCampo("barra",sym)) != -1)
        {
            this->AccionesBarra(resultado);
            this->opciones();
            this->MostrarMenu(menusD->posMenu);
        }
        break;

    case 6: //Borrar recientes
           this->menusD->posMenu = 6;
           this->reset_marcador();
           this->menusD->posCampo = 0;
           this->sangrado(this->menusD->posMenu);
           this->MostrarMenu(this->menusD->posMenu);
        break;

    case 7:  //Modo de ahorro
        if ((resultado = modificaCampo("waitMode",sym)) != -1)
        {
            if (atoi(fichConf->getClave("waitMode"))>1) fichConf->setClave("waitMode",1);
            this->opciones();
            this->MostrarMenu(menusD->posMenu);
        }
        break;

    case 8:  //Sonido activado
        if ((resultado = modificaCampo("sonido",sym)) != -1)
        {
            AccionesSonido(resultado);
            this->opciones();
            this->MostrarMenu(menusD->posMenu);
        }
        break;

    default:
        break;
    }
}

int TMenuPrincipal::modificaCampo(char *campo,Uint8 sym)
{

    char valor[25];
    char *dato = fichConf->getClave(campo);

//    printf("modificamos: %s, %s\n",campo,dato);

    if (sym == VK_FR)
    {
        sprintf(valor,"%d",atoi(dato)+1);
        if (fichConf->setClave(campo,valor))
        {
            //this->Lector->setTamFuente(atoi(dato)+1);
            //return true;
            return (atoi(dato)+1);
        }
        else
        {
            printf("No la hemos encontrado: %s\n",campo);
            return -1;
        }
    }
    else if (sym == VK_FL)
    {
        if (atoi(dato) > 0)
        {
            sprintf(valor,"%d",atoi(dato)-1);
            fichConf->setClave(campo,valor);
            //this->Lector->setTamFuente(atoi(dato)-1);
            return (atoi(dato)-1);
        }
    }
    return -1;
}

void TMenuPrincipal::MostrarFuentes(void)
{
    DIR *dir;
    struct dirent *ent;
    //int contador = 0;
    char directorio[MAXPATH];
    char fichero[MAXPATH];

    strcpy(directorio,this->rutaSeleccion);

#ifdef GP2X
    strcat(directorio,"/fonts/");
#endif

#ifdef WIN32
    strcat(directorio,"\\fonts\\");
#endif

    if ((dir = opendir(directorio)) != NULL)
    {
        //reseteamos el marcador del elemento seleccionado
        this->reset_marcador();
        this->menusD->posCampo = 0;

        //miTraza->print("Ruta de fuentes",directorio);
        this->menusD->clearCamposMenu(3);
        while ((ent = readdir(dir)) != NULL)
        {
            strcpy(fichero,directorio);
            strcat(fichero,ent->d_name);

            if (!get_file_attrib(fichero) && this->contiene(ent->d_name,".ttf") >= 0)
            {
                //El fichero recogido no es un directorio
                //strcpy(menusD->menus[3].campo[contador].nombre,ent->d_name);
                menusD->AddCampoMenu(3,ent->d_name,"s13");
                //contador++;
                //menusD->menus[3].campo = (struct TMenuData::TMenuData::my_struct_campo *) realloc(menusD->menus[3].campo,(contador+1)* sizeof(struct TMenuData::TMenuData::my_struct_campo));
            }
        }

        //menusD->menus[3].campo = (struct TMenuData::TMenuData::my_struct_campo *) realloc(menusD->menus[3].campo,(contador+1)* sizeof(struct TMenuData::TMenuData::my_struct_campo));
        //strcpy(menusD->menus[3].campo[contador].nombre,"Volver");
        menusD->AddCampoMenu(3,fichLang->getClave("mReturn"),"s3");
        //contador++;

        //menusD->menus[3].numCampos = contador;
    }

    closedir(dir);

}

void TMenuPrincipal::MostrarEstadisticas(void)
{
    //int contador = 0;
    //reseteamos el marcador del elemento seleccionado
    this->reset_marcador();
    this->menusD->posCampo = 0;
    menusD->clearCamposMenu(7);
    //this->Lector->crearArrayTamanyos(this->Lector->font,this->Lector->tamFuente);



    /****************************************************************/
    /*                 TAXONOMIA                                    */

    char leido[2] = {' ','\0'};
    char *texto = this->Lector->fichero->Gettexto();
    unsigned int tam = strlen(texto);
    unsigned int posString = 0;
    char palabraTaxonomia[255] ={""};
    char s_ocurrencias[20];
    char s_estPalabra[255];

    //int inicio = SDL_GetTicks();
    TTaxonomia *objTaxonomia = new TTaxonomia();

    while(posString <= tam)
    {
        leido[0] = texto[posString];

        if (leido[0] ==' ' || esRetorno(leido[0]) || posString == tam)
        {

             //stringTrim(palabraTaxonomia);
             if (strcmp(palabraTaxonomia,"") != 0)
             {
               objTaxonomia->add(palabraTaxonomia);
               strcpy(palabraTaxonomia,"");
             }
             this->Lector->msg_processing(posString, tam);
        }
        else
        {
            strcat(palabraTaxonomia,leido);
        }

        posString++;
    }

    //printf("Objetos anadidos: %d en: %d\n",objTaxonomia->size(),(SDL_GetTicks()-inicio));



    objTaxonomia->Sort(50);





    printf("Hay objTaxonomia->sizeRecuento: %d\n",objTaxonomia->size());


    for (int i=0;i<objTaxonomia->size();i++)
    {
        //#ifdef win
        //printf("%s, n: %d\n",objTaxonomia->get(i),objTaxonomia->getReps(i));
        //#endif

        /*
        if (contador == 0)
        {
            menusD->menus[7].campo = (struct TMenuData::TMenuData::my_struct_campo *) malloc(sizeof(struct TMenuData::TMenuData::my_struct_campo));
        }
        else
        {
            menusD->menus[7].campo = (struct TMenuData::TMenuData::my_struct_campo *) realloc(menusD->menus[7].campo,(contador+1)* sizeof(struct TMenuData::TMenuData::my_struct_campo));
        }
        */
        sprintf(s_ocurrencias,"%d",objTaxonomia->getReps(i));
/*        strcpy(menusD->menus[7].campo[contador].nombre,s_ocurrencias);
        strcat(menusD->menus[7].campo[contador].nombre," - ");
        strcat(menusD->menus[7].campo[contador].nombre,objTaxonomia->get(i));
*/
        strcpy(s_estPalabra,s_ocurrencias);
        strcat(s_estPalabra," - ");
        strcat(s_estPalabra,objTaxonomia->get(i));

        menusD->AddCampoMenu(7,s_estPalabra,"s20");

        //contador++;

    }

    //getTotalPalabras
    //objTaxonomia->clear();
    delete objTaxonomia;

    /****************************************************************/



    /*if (contador == 0)
    {
        menusD->menus[7].campo = (struct TMenuData::TMenuData::my_struct_campo *) malloc(sizeof(struct TMenuData::TMenuData::my_struct_campo));
    }
    else
    {
        menusD->menus[7].campo = (struct TMenuData::TMenuData::my_struct_campo *) realloc(menusD->menus[7].campo,(contador+1)* sizeof(struct TMenuData::TMenuData::my_struct_campo));
    }*/

    menusD->AddCampoMenu(7,fichLang->getClave("mReturn"),"s3");
    //strcpy(menusD->menus[7].campo[contador].nombre,"Volver");
    //contador++;

    //menusD->menus[7].numCampos = contador;




}

void TMenuPrincipal::MostrarFicherosRecientes(void)
{
    DIR *dir;
    struct dirent *ent;
    //int contador = 0;
    char directorio[MAXPATH];
    char fichero[MAXPATH];
    char ficheroPrint[MAXPATH];
    //memset(ficheroPrint,'\0',MAXPATH);


    strcpy(directorio,this->rutaSeleccion);

#ifdef GP2X
    strcat(directorio,"/cfg/");
#endif

#ifdef WIN32
    strcat(directorio,"\\cfg\\");
#endif

//    printf("La ruta es: %s\n",directorio);

    if ((dir = opendir(directorio)) != NULL)
    {
        //reseteamos el marcador del elemento seleccionado
        this->reset_marcador();
        this->menusD->posCampo = 0;
        menusD->clearCamposMenu(5);

        while ((ent = readdir(dir)) != NULL)
        {
            strcpy(fichero,directorio);
            strcat(fichero,ent->d_name);
            int puntoExtension = this->contiene(ent->d_name,".cfg");
            if (!get_file_attrib(fichero) && puntoExtension >= 0)
            {
                memset(ficheroPrint,'\0',MAXPATH);
                for (int i=0;i<puntoExtension;i++)
                {
                   ficheroPrint[i]=ent->d_name[i];
                }
                //strcpy(menusD->menus[5].campo[contador].nombre,ficheroPrint);
                menusD->AddCampoMenu(5,ficheroPrint,"s20");
                //contador++;
                //menusD->menus[5].campo = (struct TMenuData::TMenuData::my_struct_campo *) realloc(menusD->menus[5].campo,(contador+1)* sizeof(struct TMenuData::TMenuData::my_struct_campo));
            }
        }

        //menusD->menus[5].campo = (struct TMenuData::TMenuData::my_struct_campo *) realloc(menusD->menus[5].campo,(contador+1)* sizeof(struct TMenuData::TMenuData::my_struct_campo));
        //strcpy(menusD->menus[5].campo[contador].nombre,"Volver");
        menusD->AddCampoMenu(5,fichLang->getClave("mReturn"),"s3");
        //contador++;

        //menusD->menus[5].numCampos = contador;
    }

    closedir(dir);
}

void TMenuPrincipal::AccionesMenuRecientes(void)
{
//    printf("vamos a pintar la ruta\n");
    char rutaActual[MAXPATH+1]; //Ruta Actual en la que nos encontramos
    char nuevaRuta[MAXPATH+1];  //Ruta nueva con el directorio seleccionado

    getDirActual(rutaActual);

    //Concatenamos la ruta actual con el directorio seleccionado
    //strcpy(nuevaRuta,rutaActual);
    strcpy(nuevaRuta,this->rutaSeleccion);
#ifdef GP2X
    strcat(nuevaRuta,"/cfg/");
#endif

#ifdef WIN32
    strcat(nuevaRuta,"\\cfg\\");
#endif

    strcat(nuevaRuta,menusD->menus[5].campo[this->menusD->posCampo].nombre);
    strcat(nuevaRuta,".cfg");

//    printf("La ruta es: %s\n",nuevaRuta);

    TConfig *fichConfCFG = new TConfig();
    fichConfCFG->procesar_fichero(nuevaRuta);
    fichConfCFG->obtenClaves();

//    printf("Hay que abrir: %s\n",fichConfCFG->getClave("ruta"));

    this->MostrarMenuPrincipal();
    strcpy(this->ficheroSeleccionado,fichConfCFG->getClave("nombre"));
    this->setDirActual(fichConfCFG->getClave("ruta"));
    this->abrirFichero(fichConfCFG->getClave("nombre"));
    SetArchivoAbierto(true,fichConfCFG->getClave("nombre"));
    delete fichConfCFG;
}






void TMenuPrincipal::AccionesMenuFuentes(void)
{

    char directorio[MAXPATH];

    strcpy(directorio,this->rutaSeleccion);

#ifdef GP2X
    strcat(directorio,"/fonts/");
#endif

#ifdef WIN32
    strcat(directorio,"\\fonts\\");
#endif

    //miTraza->print("directorio: ");
    //miTraza->print(directorio);

    strcat(directorio,menusD->menus[3].campo[this->menusD->posCampo].nombre);
    //miTraza->print("directorio2: ");
    //miTraza->print(directorio);

//    printf("Vamos a pintar: %s\n",directorio);
    this->LoadFont(directorio,this->tamFuente);
    this->Lector->LoadFont(directorio,this->Lector->getTamFuente());

    if (fichConf->setClave("font_type",menusD->menus[3].campo[this->menusD->posCampo].nombre))
    {
        this->opciones();
    }
    this->MostrarMenu(menusD->posMenu);
}



void TMenuPrincipal::AccionesMenuTamFuentes(void)
{
    char directorio[MAXPATH];

    strcpy(directorio,this->rutaSeleccion);

#ifdef GP2X
    strcat(directorio,"/fonts/");
#endif

#ifdef WIN32
    strcat(directorio,"\\fonts\\");
#endif

    strcat(directorio,fichConf->getClave("font_type"));
    printf("Antes de cambiar el tamaño\n");
    if (this->Lector->LoadFont(directorio,atoi(fichConf->getClave("font_size"))))
        printf("Despues de cambiar el tamaño con exito\n");
    else
        printf("Despues de cambiar el tamaño con FALLO\n");

}

void TMenuPrincipal::AccionesEstiloFuentes(void)
{
    this->Lector->setColor(atoi(fichConf->getClave("font_color")));
    this->Lector->setFondo(atoi(fichConf->getClave("font_bkgd")));
}

void TMenuPrincipal::AccionesJustificadoFuentes(int entrada)
{
    if (entrada >= 1)
    {
        fichConf->setClave("font_just",1);
        this->Lector->setJustificar(true);
    }
    else
    {
        this->Lector->setJustificar(false);
    }
}


void TMenuPrincipal::AccionesBarra(int entrada)
{
    if (entrada >= 1)
    {
        fichConf->setClave("barra",1);
        this->Lector->setBarra(true);
    }
    else
    {
        fichConf->setClave("barra",0);
        this->Lector->setBarra(false);
    }
}

void TMenuPrincipal::AccionesSonido(int entrada)
{
    if (entrada >= 1)
    {
        fichConf->setClave("sonido",1);
        this->sonido->setSound(true);
    }
    else
    {
        fichConf->setClave("sonido",0);
        this->sonido->setSound(false);
    }
}


// returns the value of archivoAbierto
bool TMenuPrincipal::GetArchivoAbierto()
{
    return archivoAbierto;
}


// sets the value of archivoAbierto
void TMenuPrincipal::SetArchivoAbierto(bool x, char *nomFichero)
{
    archivoAbierto = x;
    strcpy(nombreFicheroAbierto,nomFichero);
}

void TMenuPrincipal::AccionesMenuIrA(Uint8 sym)
{

    switch (this->menusD->posCampo)
    {
    case 0:  //Tamaño de la fuente
        if (sym == VK_FR)
        {
            for (int i=0;i<10;i++)
                Lector->siguiente_pagina();
            irA();
        }
        else if (sym == VK_FL)
        {
            for (int i=0;i<10;i++)
                Lector->anterior_pagina();
            irA();
        }
        break;
    default:
        break;
    }

}

void TMenuPrincipal::irA(void)
{
    if (this->GetArchivoAbierto())
    {
        int lineas_pantalla =  Lector->maxHeight / (Lector->tamFuente + Lector->saltoLinea);
        int total =  Lector->lineas.n_lineas;
        int n_paginas = total / lineas_pantalla;

        char datos3[30];
        char datos2[30];
        char datos1[255];
        char datos4[30];

        if (total % lineas_pantalla > 0)
            n_paginas++;
        int paginaActual = Lector->posLinea / lineas_pantalla + 1;
        strcpy(datos1,fichLang->getClave("mPagina"));
        sprintf(datos3," %d ",paginaActual);
        strcat(datos1,datos3);
        strcat(datos1,"de");
        sprintf(datos2," %d",n_paginas);

        strcat(datos1,datos2);
        sprintf(datos4,"%3.2f",paginaActual/(float)n_paginas*100);
        strcat(datos1," = ");

        strcat(datos1,datos4);
        strcat(datos1,"%");
        strcpy(menusD->menus[4].campo[0].nombre,datos1);
        strcpy(menusD->menus[4].campo[1].nombre,fichLang->getClave("mReturn"));
        this->MostrarMenu(menusD->posMenu);
    }
}

void TMenuPrincipal::addreturn (char *buffer)
{
#ifdef GP2X
    strcat(buffer,"\r");
#endif

#ifdef WIN32
    strcat(buffer,"\n");
#endif
}
void TMenuPrincipal::crearColores(void)
{
    strcpy(colores[0].color,"Rojo");
    strcpy(colores[1].color,"Azul");
    strcpy(colores[2].color,"Verde");
    strcpy(colores[3].color,"Amarillo");
    strcpy(colores[4].color,"Naranja");
    strcpy(colores[5].color,"Marron");
    strcpy(colores[6].color,"Negro");
    strcpy(colores[7].color,"Blanco");
    strcpy(colores[8].color,"Lila");
    strcpy(colores[9].color,"Gris");
}

int TMenuPrincipal::procesarTeclas (SDLKey sym)
{
    int done = 0;

    int inicio = SDL_GetTicks();

    switch (sym)
    {
        case SDLK_UP :
        if (!this->visible && !b_diccionario)
        {
            this->Lector->anterior_linea();
            this->Lector->pintarPagina(true);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        else if (!this->visible && b_diccionario)
        {
            this->LectorDiccionario->anterior_linea();
            this->LectorDiccionario->pintarPagina(true);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        else
        {
            //sonido->play(2);
            this->anteriorCampo();
        }
        break;

    case SDLK_DOWN :
        if (!this->visible && !b_diccionario)
        {
            this->Lector->siguiente_linea();
            this->Lector->pintarPagina(true);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        else if (!this->visible && b_diccionario)
        {
            this->LectorDiccionario->siguiente_linea();
            this->LectorDiccionario->pintarPagina(true);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        else
        {
            //sonido->play(2);
            this->siguienteCampo();
        }
        break;

    case SDLK_RIGHT :
        if (!this->visible && !b_diccionario)
        {
            objTraza->print("Pagina texto siguiente");
            sonido->play(3);
            this->Lector->siguiente_pagina();
            //this->fichConf->setClave("PosicionTexto",this->Lector->posLinea);
            this->Lector->pintarPagina(true);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
            //this->miImagen->blur_image();
        }
        else if (!this->visible && b_diccionario)
        {
            objTraza->print("Pagina diccionario siguiente");
            sonido->play(3);
            this->LectorDiccionario->siguiente_pagina();
            this->LectorDiccionario->pintarPagina(true);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        else
        {
            //sonido->play(2);
            this->siguientePaginaCampo();
        }

        break;

    case SDLK_LEFT :
        if (!this->visible && !b_diccionario)
        {
            sonido->play(3);
            this->Lector->anterior_pagina();
            //this->fichConf->setClave("PosicionTexto",this->Lector->posLinea);
            this->Lector->pintarPagina(true);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        else if (!this->visible && b_diccionario)
        {
            sonido->play(3);
            this->LectorDiccionario->anterior_pagina();
            this->LectorDiccionario->pintarPagina(true);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        else
        {
            //sonido->play(2);
            this->anteriorPaginaCampo();
        }
        break;

    case 'q' :
        if (!this->visible)
        {
            this->Lector->desplazarPantalla();
            //this->fichConf->setClave("PosicionTexto",this->Lector->posLinea);
            this->guardaConfiguracion();
        }
        break;

    case SDLK_ESCAPE :
    {
        if (this->GetArchivoAbierto())
        {
            this->MostrarMenuPrincipal();
        }
        break;
    }

    case SDLK_RETURN :

        if (!this->visible && b_diccionario)
        {
            AccionesTeclasDiccionario();
        }
        else
        {
            if (this->visible) sonido->play(0);
            done = this->ejecutarMenu(VK_FB);
        }
        break;



    case 'a' :
        //sonido->play(2);
        done = this->ejecutarMenu(VK_FL);
        break;

    case 's' :
        //sonido->play(2);
        done = this->ejecutarMenu(VK_FR);
        break;
    case SDLK_BACKSPACE :
        if (this->visible) sonido->play(1);
        this->AccionesCampoVolver();
        break;

    case 'f' :
        if (!this->visible)
        {
            if (this->Lector->favoritos())
            {
//                printf("Mostramos el principal\n");
                this->MostrarMenuPrincipal();
            }
        }
        break;

    case 'd':
        AccionesTeclasDiccionario();
        break;

    case 'e':
        if (!this->visible)
        {
            this->Lector->buscarSiguiente();
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        break;
    case 'w':
        if (!this->visible)
        {
            this->Lector->buscarAnterior();
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        break;

    default :
        break;
    }

    int tiempo_empleado = SDL_GetTicks() - inicio;
    if ( tiempo_empleado < this->key_delay)
    {
        SDL_Delay(this->key_delay - tiempo_empleado);
    }

    return done;
}


int TMenuPrincipal::procesarJoystick (SDL_Event evento)
{
    int done = 0;
    int inicio = SDL_GetTicks();
    Uint8 sym = evento.jbutton.button;

    switch (sym)
    {

    case GP2X_BUTTON_UP :
        procesarTeclas(SDLK_UP);
        /*
        if (!this->visible)
        {
            this->Lector->anterior_linea();
            this->fichConf->setClave("PosicionTexto",this->Lector->posLinea);
            this->Lector->pintarPagina(true);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        else
        {
            this->anteriorCampo();
        }
        */
        break;
    case GP2X_BUTTON_DOWN :
        procesarTeclas(SDLK_DOWN);
        /*if (!this->visible && !b_diccionario)
        {
            this->Lector->siguiente_linea();
            this->fichConf->setClave("PosicionTexto",this->Lector->posLinea);
            this->Lector->pintarPagina(true);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        else if (!this->visible && b_diccionario)
        {
            this->LectorDiccionario->siguiente_linea();
            this->LectorDiccionario->pintarPagina(true);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        else
        {
            this->siguienteCampo();
        }*/
        break;

    case GP2X_BUTTON_LEFT :
    {
        /*if (this->visible)
        {
            this->anteriorPaginaCampo();
        }*/
        procesarTeclas(SDLK_LEFT);
        break;
    }

    case GP2X_BUTTON_RIGHT :
    {
        /*if (this->visible)
        {
            this->siguientePaginaCampo();
        }*/
        procesarTeclas(SDLK_RIGHT);
        break;
    }

    case GP2X_BUTTON_SELECT :
        AccionesTeclasDiccionario();
        break;

    case GP2X_BUTTON_START :
    {
        if (this->GetArchivoAbierto())
        {
            this->MostrarMenuPrincipal();
        }
        break;
    }
    case GP2X_BUTTON_B :
        //sonido->play(0);
        //done = this->ejecutarMenu(VK_FB);
            procesarTeclas(SDLK_z);
            break;

    case GP2X_BUTTON_Y :
        if (!this->visible && !b_diccionario)
        {
            this->Lector->desplazarPantalla();
            //this->fichConf->setClave("PosicionTexto",this->Lector->posLinea);
            this->guardaConfiguracion();
        }
        break;

    case GP2X_BUTTON_X :
         //sonido->play(1);
         //this->AccionesCampoVolver();
        procesarTeclas(SDLK_x);
         break;

    case GP2X_BUTTON_A :
        if (!this->visible && !b_diccionario)
        {
            if (this->Lector->favoritos())
            {
                this->MostrarMenuPrincipal();
            }
        }
        break;

    case GP2X_BUTTON_L :
        if (this->visible)
        {
            //sonido->play(2);
            this->ejecutarMenu(VK_FL);
        }
        else if (!this->visible && !b_diccionario)
        {
            sonido->play(3);
            this->Lector->anterior_pagina();
            //this->fichConf->setClave("PosicionTexto",this->Lector->posLinea);
            this->Lector->pintarPagina(true);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        else if (!this->visible && b_diccionario)
        {
            sonido->play(3);
            this->LectorDiccionario->anterior_pagina();
            this->LectorDiccionario->pintarPagina(true);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        break;

    case GP2X_BUTTON_R :
        if (this->visible)
        {
            //sonido->play(2);
            this->ejecutarMenu(VK_FR);
        }
        else if (!this->visible && !b_diccionario)
        {
            sonido->play(3);
            this->Lector->siguiente_pagina();
            //this->fichConf->setClave("PosicionTexto",this->Lector->posLinea);
            this->Lector->pintarPagina(true);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        else if (!this->visible && b_diccionario)
        {
            sonido->play(3);
            this->LectorDiccionario->siguiente_pagina();
            //this->fichConf->setClave("PosicionTexto",this->Lector->posLinea);
            this->LectorDiccionario->pintarPagina(true);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        break;

    case GP2X_BUTTON_VOLUP:
        if (!this->visible)
        {
            this->Lector->buscarSiguiente();
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        break;
    case GP2X_BUTTON_VOLDOWN:
        if (!this->visible)
        {
            this->Lector->buscarAnterior();
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        break;

    default :
        break;
    }

    int tiempo_empleado = SDL_GetTicks() - inicio;
    if ( tiempo_empleado < this->key_delay)
    {
        SDL_Delay(this->key_delay - tiempo_empleado);
    }

    return done;
}

void TMenuPrincipal::AccionesBorradoRecientes(void)
{
//    printf("vamos a pintar la ruta\n");
    char rutaActual[MAXPATH+1]; //Ruta Actual en la que nos encontramos
    char filename[MAXPATH+1];  //Ruta nueva con el directorio seleccionado
    char filenameContat[MAXPATH+1];  //Ruta nueva con el directorio seleccionado

    getDirActual(rutaActual);

    strcpy(filename,this->rutaSeleccion);
#ifdef GP2X
    strcat(filename,"/cfg/");
#endif

#ifdef WIN32
    strcat(filename,"\\cfg\\");
#endif

    DIR *dir;
    struct dirent *ent;
    int contador = 0;


    int resultado=0;

//    printf("recorremos: %s\n",filename);

    if ((dir = opendir(filename)) != NULL)
    {
//        traza *miTraza = new traza("salidita.txt");
        //reseteamos el marcador del elemento seleccionado
        while ((ent = readdir(dir)) != NULL)
        {
            strcpy(filenameContat,filename);
            strcat(filenameContat,ent->d_name);
//            printf("recorremos: %s\n",filenameContat);
//            miTraza->print("filenameContat: ",filenameContat);
            if (!get_file_attrib(filenameContat) && (strcmp(ent->d_name,".") != 0) && (strcmp(ent->d_name,"..") != 0))
            {

                if ( (remove(filenameContat) ) != 0)
                {
                    printf("error al borrar el fichero\n");
                    resultado = 1;
                }
                else
                {
                    printf("borramos: %s\n",ent->d_name);
                }
                contador++;
            }
        }

        if (resultado == 0 && contador > 0)
               drawText(fichLang->getClave("mBorraOK"),0,120);
        else if (contador == 0)
               drawText(fichLang->getClave("mBorraNO"),0,120);
        else
               drawText(fichLang->getClave("mBorraKO"),0,120);


        SDL_UpdateRect(screen, 0, 0, 0, 0);
    }

}

void TMenuPrincipal::menuQuizasQuisoBuscar(TClist *lista)
{
        this->reset_marcador();
        this->menusD->posCampo = 0;
        menusD->posMenu = 8;
        sangrado(menusD->posMenu);
        //this->menusD->
        this->menusD->clearCamposMenu(8);

        for (int i=0;i<lista->size();i++)
        {
            menusD->AddCampoMenu(8,lista->get(i),"s20");
        }

        menusD->AddCampoMenu(8,fichLang->getClave("mReturn"),"s3");
        this->MostrarMenu(8);

}

void TMenuPrincipal::AccionesTeclasDiccionario(void)
{
        if (!this->visible)
        {
            //Si el diccionario ya estaba habilitado salimos del diccionario y pintamos la novela
            if (b_diccionario)
            {
                objTraza->print("TMenuPrincipal::b_diccionario=true");
                b_diccionario = false;
                this->Lector->stopPosMarcaPalabra();
                this->Lector->clearPalabraRemarcada();
                this->Lector->pintarPagina(true);
                //SDL_UpdateRect(screen, 0, 0, 0, 0);
            }
            else
            //Devuelve true si se ha pulsado el return.
            if (this->Lector->definiciones())
            {
                objTraza->print("TMenuPrincipal::b_diccionario=false, definiciones");
                procesarTeclas(SDLK_RETURN);
            }
            else
            {
                objTraza->print("TMenuPrincipal::PalabraRemarcada",this->Lector->getPalabraRemarcada());
                if (this->Lector->getPalabraRemarcada() != NULL)
                if (strcmp(this->Lector->getPalabraRemarcada(),"")!=0)
                {
                    objTraza->print("TMenuPrincipal::filtramos");
                    filtrarYMinusculas(this->Lector->getPalabraRemarcada());
                    objTraza->print("TMenuPrincipal::Antes de crear el diccionario");
                    TDiccionario *diccionario = new TDiccionario(this->rutaSeleccion);
                    objTraza->print("TMenuPrincipal::Diccionario creado");
                    int res = diccionario->find(this->Lector->getPalabraRemarcada());
                    objTraza->print("TMenuPrincipal::buscamos",res);

                    if (res != -1)
                    {
                        //Hemos encontrado la palabra buscada en el diccionario
                        objTraza->print("TMenuPrincipal::creamos texto");
                        if (LectorDiccionario->fichero->crearTexto(diccionario->get()))
                        {
                            LectorDiccionario->lineas.offset = NULL;
                            LectorDiccionario->buscar_paginas();
                            LectorDiccionario->Clear();
                            objTraza->print("TMenuPrincipal::antes pintar");
                            LectorDiccionario->pintarPagina(true);
                            objTraza->print("TMenuPrincipal::pintado");
                            b_diccionario = true;
                        }
                        //printf("texto-------------\n%s",diccionario->get());
                        //printf("------------------\n");
                    }
                    else
                    {
                        //SDL_Surface *pantallazo = SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w, screen->h, 16,0, 0, 0, 0);
                        //SDL_BlitSurface(screen, NULL,pantallazo, NULL);
                        //Clear();
                        //this->Lector->msg_info("No se ha encontrado la palabra");
                        //SDL_Delay(1000);
                        objTraza->print("TMenuPrincipal::Creando la lista de posibilidades");
                        TClist *aproxList = new TClist();
                        diccionario->findAprox(this->Lector->getPalabraRemarcada(), aproxList);
                        menuQuizasQuisoBuscar(aproxList);
                        delete aproxList;
                        //this->Lector->pintarPagina(true);
                    }
                    objTraza->print("TMenuPrincipal::Eliminando diccionario");
                    delete diccionario;
                }
            }
            SDL_UpdateRect(screen, 0, 0, 0, 0);
        }
        objTraza->print("TMenuPrincipal::FIN AccionesTeclasDiccionario()");
}




