#include "engine/Audio.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <errno.h>

void testAudio(void) {
	char path1[] = "../rsrc/music/testMus.mp3";
	char path2[] = "../rsrc/music/base_tardi.mp3";
	Mix_Music* music = NULL;

	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		perror("SDL");
		exit(errno);
	}

	if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024) != 0) {
		SDL_Quit();
		perror("SDL Mixer");
		exit(errno);
	}

	switchMusic(music,path1);
	SDL_Delay(5000);
	switchMusic(music,path2);
	SDL_Delay(5000);

	Mix_FreeMusic(music);
	SDL_Quit();
}


