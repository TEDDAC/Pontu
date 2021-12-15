#include "test/testAudio.h"

void testAudio(void) {
	char path1[] = "../rsrc/music/testMus.mp3";
	char path2[] = "../rsrc/music/base_tardi.mp3";
	Mix_Music* music;

	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		perror("SDL");
		exit(errno);
	}

	if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNEL,1024) != 0) {
		SDL_Quit();
		perror("SDL Mixer");
		exit(errno);
	}

	switchMusic(music,path1);
	SDL_Delay(5000);
	switchMusic(music,path2);
	SDL_Delay(5000);

	SDL_FreeMusic(music);
	SDL_Quit();
}


