// Class automatically generated by Dev-C++ New Class wizard

#include "menu.h" // class's header file

// class constructor
TMenu::TMenu(SDL_Surface* screen) : TPantalla(screen)
{
    menusD = new TMenuData();
    this->setFondo(clNegro);
    this->setColor(clBlanco);
    justificar = false;
    tamFuente = 16;
//    this->LoadFont(tamFuente);	//load font size 12
    separacion = saltoLinea + tamFuente;
    left = 0;
    top = 0;
    menusD->numMenus = 0;
    menusD->posMenuScreenIni = 0;
    menusD->posMenuScreenFin = (this->maxHeight - this->top) / (tamFuente + saltoLinea);
    visible = false;
    menusD->posCampo = 0;
    menusD->posAntCampo = 0;
    menusD->posMenu = 0;

    tiempoInicioLectura = 0;
    this->miImagen = new TImagen(screen);
    printf("TMenu: Antes de cargar iconos\n");
    this->miImagen->cargarIconos();

    fichLang = new TConfig();
    objTraza->print("fichero lenguaje creado");
    if (!fichLang->procesar_fichero("lang.ini"))
    {
        objTraza->print("Error al abrir el fichero lenguaje");
    }
    objTraza->print("fichero lenguaje procesado");
    fichLang->obtenClaves();
    objTraza->print("claves lenguaje creadas");
    iniciarMensajesMenus();
}

// class destructor
TMenu::~TMenu()
{
    // insert your code here
    printf("TMenu::~TMenu()\n");
}

void TMenu::iniciarMensajesMenus()
{
    this->menusD->mensajes_menus.menus = 9;

    strcpy(this->menusD->mensajes_menus.mensajes[0].textoMensaje,"Emubook");
    strcpy(this->menusD->mensajes_menus.mensajes[1].textoMensaje,fichLang->getClave("mOpen"));
    strcpy(this->menusD->mensajes_menus.mensajes[2].textoMensaje,fichLang->getClave("mOpt"));
    strcpy(this->menusD->mensajes_menus.mensajes[3].textoMensaje,fichLang->getClave("mFontType"));
    strcpy(this->menusD->mensajes_menus.mensajes[4].textoMensaje,fichLang->getClave("mGoto"));
    strcpy(this->menusD->mensajes_menus.mensajes[5].textoMensaje,fichLang->getClave("mRecent"));
    strcpy(this->menusD->mensajes_menus.mensajes[6].textoMensaje,"");
    strcpy(this->menusD->mensajes_menus.mensajes[7].textoMensaje,fichLang->getClave("mEstat"));
    strcpy(this->menusD->mensajes_menus.mensajes[8].textoMensaje,fichLang->getClave("mAltern"));

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
    //drawText(nuevaRuta,0,10);
    strcpy(this->menusD->mensajes_menus.mensajes[6].textoMensaje,nuevaRuta);
    //SDL_UpdateRect(screen, 0, 0, 0, 0);

}

void TMenu::verTiempoLectura ()
{
    if (strcmp("",nombreFicheroAbierto) != 0 && nombreFicheroAbierto != NULL)
    {
        //int lineas_pantalla = (this->maxHeight - this->top) / (tamFuente + saltoLinea);
        int posX;
        int horas=0,minutos=0,segundos=0;
        int alto = screen->h - (tamFuente + saltoLinea) - 5;
        int centroFuente = this->tamFuente+2;
        char sTiempo[255] = {"Tiempo - "};
        char temp_time[255];
        int posTitulo = 0;



        segundos = tiempoLectura % 60;
        minutos = (tiempoLectura / 60)%60;
        horas = (tiempoLectura / 60) / 60;

        sprintf(temp_time,"%d",horas);
        strcat(sTiempo,temp_time);
        strcat(sTiempo,":");
        if (minutos < 10)
        strcat(sTiempo,"0");
        sprintf(temp_time,"%d",minutos);
        strcat(sTiempo,temp_time);
        strcat(sTiempo,":");
        if (segundos < 10)
        strcat(sTiempo,"0");
        sprintf(temp_time,"%d",segundos);
        strcat(sTiempo,temp_time);



        TTF_SizeText(font,sTiempo,&posX,NULL);
        posTitulo = (screen->w - posX)/2;
        this->miImagen->pintarCirculo(posTitulo, alto + margenS + centroFuente/2 , centroFuente/2,clBlanco);
        this->miImagen->pintarCirculo(posTitulo + posX, alto + margenS + centroFuente/2 , centroFuente/2,clBlanco);
        SDL_Rect rectTitulo = { posTitulo,alto + margenS+1, posX, centroFuente-1};
        //Pintamos el texto sobresaltado en color rojo ClRojo
        SDL_FillRect(screen, &rectTitulo, SDL_MapRGB(screen->format,255,255,255));
        this->setColor(clNegro);
        drawText(sTiempo,posTitulo,alto + margenS);
        this->setColor(clBlanco);
    }
}

void TMenu::setTiempoLectura(int timer)
{
    tiempoLectura = (timer - tiempoInicioLectura)/1000;
}

int TMenu::getTiempoLectura()
{
    return tiempoLectura;
}


// No description
void TMenu::sangrado(int numMenu)
{
    switch (numMenu)
    {
    case 0 :
    case 2 :
        left = 50;
        top = 35;
        menusD->posMenuScreenFin = (this->maxHeight - this->top) / (tamFuente + saltoLinea);
        break;
    case 1 :
    case 5 :
        left = 23;
        top = 20;
        menusD->posMenuScreenFin = (this->maxHeight - this->top) / (tamFuente + saltoLinea);
        break;
    case 4 :
        left = 40;
        top = 40;
        menusD->posMenuScreenFin = (this->maxHeight - this->top) / (tamFuente + saltoLinea);
        break;
    case 6 :
        left = 20;
        top = 60;
        menusD->posMenuScreenFin = (this->maxHeight - this->top) / (tamFuente + saltoLinea);
        break;
    case 7 :
        left = 20;
        top = 20;
        menusD->posMenuScreenFin = (this->maxHeight - this->top) / (tamFuente + saltoLinea);
        break;

    default :
        left = 20;
        top = 30;
        menusD->posMenuScreenFin = (this->maxHeight - this->top) / (tamFuente + saltoLinea);
        break;
    }
}

void TMenu::IconosMenu(int var_numMenu, int var_posCampo, int var_topCampo)
{

    if ( var_numMenu < menusD->numMenus)
    {
//        printf("menu: %d props: %s\n",var_numMenu,menusD->menus[var_numMenu].campo[var_posCampo].props);
        if (menusD->menus[var_numMenu].campo[var_posCampo].props != NULL && menusD->menus[var_numMenu].tieneProps == true)
        {
            //Este caso se usa para el explorador de archivos
            //Para directorios
            if (var_posCampo < menusD->menus[var_numMenu].numCampos)
            {
                if (menusD->menus[var_numMenu].campo[var_posCampo].props[0] == 'd')
                {
                    this->miImagen->pintarIcono(1,this->left,var_topCampo);
                }
                //Para menus especiales
                else if (menusD->menus[var_numMenu].campo[var_posCampo].props[0] == 's')
                {
                    //if (menusD->menus[var_numMenu].props[var_posCampo].nombre[1] == 'v')
                    //{
                        //this->miImagen->pintarIcono(3,0,var_topCampo);
                    //}
                    char dato[3] = {' ',' ','\0'};
                    int tam = strlen(menusD->menus[var_numMenu].campo[var_posCampo].props);

                    for (int i=0;i<tam && i<2;i++)
                    {
                        dato[i] = menusD->menus[var_numMenu].campo[var_posCampo].props[i+1];
                    }

                    dato[0] = menusD->menus[var_numMenu].campo[var_posCampo].props[1];
                    this->miImagen->pintarIcono(atoi(dato),this->left,var_topCampo);
                }
                //Si ses un fichero
                else if (menusD->menus[var_numMenu].campo[var_posCampo].props[0] == 'f')
                {
                    //Si es un fichero de texto
                    if (menusD->menus[var_numMenu].campo[var_posCampo].props[1] == 't')
                    {
                        this->miImagen->pintarIcono(0,this->left,var_topCampo);
                    }
                    else if (menusD->menus[var_numMenu].campo[var_posCampo].props[1] == 'g')
                    {
                        this->miImagen->pintarIcono(21,this->left,var_topCampo);
                    }
                    else if (menusD->menus[var_numMenu].campo[var_posCampo].props[1] == 'z')
                    {
                        this->miImagen->pintarIcono(22,this->left,var_topCampo);
                    }
                    else if (menusD->menus[var_numMenu].campo[var_posCampo].props[1] == 'p')
                    {
                        this->miImagen->pintarIcono(23,this->left,var_topCampo);
                    }
                    else if (menusD->menus[var_numMenu].campo[var_posCampo].props[1] == 'c')
                    {
                        this->miImagen->pintarIcono(24,this->left,var_topCampo);
                    }
                    else if (menusD->menus[var_numMenu].campo[var_posCampo].props[1] == 'h')
                    {
                        this->miImagen->pintarIcono(25,this->left,var_topCampo);
                    }
                    else if (menusD->menus[var_numMenu].campo[var_posCampo].props[1] == 'f')
                    {
                        this->miImagen->pintarIcono(13,this->left,var_topCampo);
                    }
                    else if (menusD->menus[var_numMenu].campo[var_posCampo].props[1] == 'i')
                    {
                        this->miImagen->pintarIcono(26,this->left,var_topCampo);
                    }
                    //Para cualquier otro tipo de contenido
                    else
                    {
                        this->miImagen->pintarIcono(2,this->left,var_topCampo);
                    }
                }
            }
        }
        else
        {
            if (menusD->menus[var_numMenu].numCampos == var_posCampo+1 && var_numMenu != 0 && var_numMenu != 6 && menusD->menus[var_numMenu].campo[var_posCampo].props != NULL )
            {
                this->miImagen->pintarIcono(3,this->left,var_topCampo);
            }
            else if (var_numMenu == 5)
            {
                this->miImagen->pintarIcono(0,this->left,var_topCampo);
            }
        }
    }

}

//Metodo que sirve para resaltar un elemento en el menu y actualizar los elementos
//que se van mostrando
void TMenu::MostrarMenu(int numMenu)
{
    Clear();
    //Hay que mover fondo circulos a otro lugar
    this->miImagen->fondoCirculos();

    int contador2 = 0;

    int lineas_pantalla = (this->maxHeight -this->top) / (tamFuente + saltoLinea);
    bool pantallaMovida = false;

    if (menusD->posCampo >= menusD->posMenuScreenFin)
    {
        menusD->posMenuScreenIni++;
        menusD->posMenuScreenFin++;
        pantallaMovida = true;
    }
    else if (menusD->posCampo < menusD->posMenuScreenIni)
    {
        menusD->posMenuScreenIni--;
        menusD->posMenuScreenFin--;
        pantallaMovida = true;
    }

    int inicio=menusD->posMenuScreenIni, fin=menusD->posMenuScreenFin;

    if (menusD->menus[numMenu].numCampos < lineas_pantalla)
        fin = menusD->menus[numMenu].numCampos;

    //this->sangrado(numMenu);

    if (menusD->posMenuScreenIni > 0)
    {
        this->miImagen->pintarTriangulo (5,1,10,9,true,clBlanco);
    }

    if (menusD->posMenuScreenIni < menusD->menus[numMenu].numCampos - lineas_pantalla )
    {
        this->miImagen->pintarTriangulo (5,screen->h - 1,10,9,false,clBlanco);
    }
    int posX=0;
    //Lo mismo que se hace aqui para pintar los menus, debe hacerse
    //en TMenuPrincipal::MostrarMenuPrincipal()
    for (int i = inicio; i < fin;i++)
    {
        if (i == menusD->posCampo)
        {
            TTF_SizeText(font,menusD->menus[numMenu].campo[i].nombre,&posX,NULL);
            this->miImagen->pintarCirculo(margenI + left + 3,margenS + top + contador2*separacion + separacion/2, separacion/2,clRojo);
            this->miImagen->pintarCirculo(margenI + left + 3 + posX, margenS + top + contador2*separacion+separacion/2, separacion/2,clRojo);
            this->setColor(clNegro);
            SDL_Rect pantalla = { margenI + left + 3,margenS + top + contador2*separacion +1, posX, separacion-2};
            //Pintamos el texto sobresaltado en color rojo ClRojo
            SDL_FillRect(screen, &pantalla, SDL_MapRGB(screen->format,255,0,0));
            IconosMenu(numMenu,i,margenS + top + contador2*separacion +1);
        }
        else
        {
                this->setColor(clBlanco);
                IconosMenu(numMenu,i,margenS + top + contador2*separacion +1);
        }

        drawText(menusD->menus[numMenu].campo[i].nombre,left, margenS + top + contador2*separacion);
        contador2++;
    }
    if (numMenu <= this->menusD->mensajes_menus.menus-1)
    {
        this->setColor(clBlanco);
        if (numMenu == 6)
        {
            objTraza->print("Antes de asignar los menus recientes",fichLang->getClave("mBorra"));
            //this->miImagen->pintarTitulo("Borrar ficheros recientes de la ruta:");
            this->miImagen->pintarTitulo(fichLang->getClave("mBorra"));
            //drawText("Borrar de la ruta:",0,0);
            drawText(this->menusD->mensajes_menus.mensajes[numMenu].textoMensaje,0,25);
        }
        else
        {
            this->miImagen->pintarTitulo(this->menusD->mensajes_menus.mensajes[numMenu].textoMensaje);
        }



/*        else
        {
            drawText(this->mensajes_menus.mensajes[numMenu].textoMensaje,0,0);
        }
*/
    }

    if (numMenu == 0)
    {
        //Se hace lo mismo en TMenuPrincipal::MostrarMenuPrincipal
        this->miImagen->pintarTitulo(this->nombreFicheroAbierto);
        this->verTiempoLectura();
    }
/*    else if (numMenu == 2)
    {
        this->pintarTitulo("Opciones");
    }
    else if (numMenu == 3)
    {
        this->pintarTitulo("Tipos de fuente");
    }
    else if (numMenu == 4)
    {
        this->pintarTitulo("Ir a la p�gina");
    }
*/

    SDL_UpdateRect(screen, 0, 0, 0, 0);
    visible = true;
}

// No description
void TMenu::siguienteCampo()
{

    //Actualizamos el menu anterior al fondo de pantalla
    if (visible)
    {
        if (menusD->posCampo < menusD->menus[menusD->posMenu].numCampos - 1)
        {
            menusD->posAntCampo = menusD->posCampo;
            menusD->posCampo++;
            MostrarMenu(menusD->posMenu);
        }
    }
}

// No description
void TMenu::anteriorCampo()
{
    if (visible)
    {
        if (menusD->posCampo > 0)
        {
            menusD->posAntCampo = menusD->posCampo;
            menusD->posCampo--;
            MostrarMenu(menusD->posMenu);
        }
    }
}

void TMenu::siguientePaginaCampo()
{
    //Actualizamos el menu anterior al fondo de pantalla
    int lineas_pantalla = (this->maxHeight -this->top) / (tamFuente + saltoLinea);

    if (visible)
    {
        if (menusD->posCampo < menusD->menus[menusD->posMenu].numCampos - 1 && menusD->menus[menusD->posMenu].numCampos > lineas_pantalla)
        {
            menusD->posCampo+=lineas_pantalla;
            menusD->posMenuScreenIni+=lineas_pantalla;
            menusD->posMenuScreenFin+=lineas_pantalla;

            if (menusD->posMenuScreenFin > menusD->menus[menusD->posMenu].numCampos+1)
            {
                menusD->posMenuScreenFin =  menusD->menus[menusD->posMenu].numCampos;
                menusD->posMenuScreenIni = menusD->posMenuScreenFin - lineas_pantalla;
                menusD->posCampo=menusD->posMenuScreenFin-1;
            }

            MostrarMenu(menusD->posMenu);
        }
    }
}

void TMenu::anteriorPaginaCampo()
{
    //Actualizamos el menu anterior al fondo de pantalla
    int lineas_pantalla = (this->maxHeight -this->top) / (tamFuente + saltoLinea);

    if (visible)
    {
        menusD->posCampo-=lineas_pantalla;
        menusD->posMenuScreenIni-=lineas_pantalla;
        menusD->posMenuScreenFin-=lineas_pantalla;

        if (menusD->posCampo < lineas_pantalla)
        {
            menusD->posCampo = 0;
            menusD->posMenuScreenFin =  lineas_pantalla;
            menusD->posMenuScreenIni = 0;
        }

        MostrarMenu(menusD->posMenu);
    }
}




//Resetea el marcador del elemento seleccionado en el menu
void TMenu::reset_marcador()
{
    menusD->posMenuScreenIni = 0;
    menusD->posMenuScreenFin = (this->maxHeight -this->top) / (tamFuente + saltoLinea);
    this->menusD->posCampo = 0;
}

//Vuelve al menu principal con los valores por defecto
void TMenu::ResetMenus()
{
    this->menusD->posMenu = 0;
    this->menusD->posCampo = 0;
    this->menusD->posMenuScreenFin = (this->maxHeight -this->top) / (tamFuente + saltoLinea);
    this->menusD->posMenuScreenIni = 0;
}

