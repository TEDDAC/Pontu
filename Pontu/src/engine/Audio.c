#include "engine/Audio.h"

struct params {
	Mix_Music* music; // AA pointer to the Mix_Music struct used for the current track
	char[] path; // The pparh to the new track to be played
};

static int fadeOut(void* args) {
	if (args->music != NULL) {
		Mix_FadeOutMusic(1000);
		Mix_FreeMusic(args->music);
	}
	args->music = Mix_LoadMUS(args->path);
	return Mix_PlayMusic(args->music,-1);
}		

void switchMusic(Mix_Music* music, char[] path) {
	struct params args = {
		.music = music,
		.path = path;
	};

	SDL_Thread *thread;

	thread = SDL_CreateThread(fadeOut, "Fade out", args);
	SDL_DetachThread(thread); // Won't wait until thread is done to continue
}

