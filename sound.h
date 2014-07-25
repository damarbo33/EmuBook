#ifndef TSound_H
#define TSound_H

#include "SDL\SDL_mixer.h"

class TSound
{
	public:
		// class constructor
		TSound();
		// class destructor
		~TSound();
		void play(int);
		void setSound(bool);

    private:
        //Mix_Music *music;
        void cargar();
        void freeMusic();
        struct my_struct_music {
          Mix_Music *Music[4];
          int numMusic;
        } arrayMusic;
        bool SActivo;
};
#endif // TSound_H
