// Class automatically generated by Dev-C++ New Class wizard

#ifndef TIMER_H
#define TIMER_H

#include "SDL/SDL.h"

class TTimer
{
	public:
        TTimer(int var_periodo);
        ~TTimer();
        void setTimer(int var_periodo);
        int getTimer();
        void start();
        void stop();
        void eventTimer();

    private:
        unsigned int periodo; //Ha de estar en milisegundos
        unsigned long lastTick;
        bool salir;

};

#endif // TIMER_H
