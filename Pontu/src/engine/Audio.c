#include "engine/Audio.h"

struct params {
	Mix_Music* music; // AA pointer to the Mix_Music struct used for the current track
	char* path; // The path to the new track to be played
};

int fadeOut(void* args) {
	struct params* argsCast = (struct params*)args;
	Mix_Music* newMusic = Mix_LoadMUS(argsCast->path);
	if (argsCast->music != NULL) {
		if(Mix_FadeOutMusic(500) == 0) {
			while (Mix_PlayingMusic()) {
				;
			}
		}
	}
	if (newMusic != NULL) {
		argsCast->music = newMusic;
		return Mix_PlayMusic(argsCast->music,-1);
	}
	else return -2;
}		

void switchMusic(Mix_Music* music, char path[]) {
	struct params args = {
		.music = music,
		.path = path
	};
	SDL_Thread* thread = SDL_CreateThread(&fadeOut, "Fade out", (void*)&args);


	SDL_DetachThread(thread); // Won't wait until thread is done to continue
}

