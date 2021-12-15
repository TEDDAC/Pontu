#include "engine/Audio.h"

struct params {
	Mix_Music* music; // AA pointer to the Mix_Music struct used for the current track
	char* path; // The path to the new track to be played
};

int fadeOut(void* args) {
	struct params* argsCast = (struct params*)args;
	if (argsCast->music != NULL) {
		Mix_FadeOutMusic(1000);
		Mix_FreeMusic(argsCast->music);
	}
	argsCast->music = Mix_LoadMUS(argsCast->path);
	return Mix_PlayMusic(argsCast->music,-1);
}		

void switchMusic(Mix_Music* music, char path[]) {
	struct params args = {
		.music = music,
		.path = path
	};
SDL_Thread* thread = SDL_CreateThread(&fadeOut, "Fade out", (void*)&args);


	SDL_DetachThread(thread); // Won't wait until thread is done to continue
}

