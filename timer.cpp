#include "timer.h" // class's header file

// class constructor
TTimer::TTimer(int var_periodo)
{
    this->periodo = var_periodo;
    this->lastTick = 0;
    this->salir = false;

}

TTimer::~TTimer()
{

}

void TTimer::start()
{
    this->salir = false;
}

void TTimer::stop()
{
    this->salir = true;
}

void TTimer::eventTimer()
{
    lastTick = SDL_GetTicks();
    while (SDL_GetTicks() - lastTick < periodo && !this->salir)
    {
        //No hacemos nada hasta que pase el tiempo
    }
    lastTick = SDL_GetTicks();
}


void TTimer::setTimer(int var_periodo)
{
    this->periodo = var_periodo;
}

int TTimer::getTimer()
{
    return this->periodo;
}
