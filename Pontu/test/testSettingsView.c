#include "view/Settings.h"
#include "engine/AudioHandler.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

void testSettingsView(void) {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* background = NULL;
	AudioHandler ah;
	FontHandler fh;

	if (0 != SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr,"Error when initializing SDL: %s\n",SDL_GetError());
		goto Quit;
	}

	if (0 != SDL_CreateWindowAndRenderer(600,700,SDL_WINDOW_SHOWN,&window,&renderer)) {
		fprintf(stderr,"Error when creating window and renderer: %s\n",SDL_GetError());
		goto Quit;
	}

	if (0 != TTF_Init()) {
		fprintf(stderr,"Error when initializing TTF: %s\n",TTF_GetError());
		goto Quit;
	}

	ah = newAudioHandler(10,100,100);
	fh = loadFonts();

	SDL_SetRenderDrawColor(renderer,255,140,0,255);
	printf("%s\n",SDL_GetError());
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
    playMusic(MUSIC_testMus, ah);
	settingsView(window, &ah,&fh);


	SDL_Delay(5000);


	Quit:
	if (renderer != NULL) SDL_DestroyRenderer(renderer);
	if (window != NULL) SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

}
