#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	int statut = EXIT_FAILURE;

	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Error : %s\n", SDL_GetError());
		goto Quit;
	}

	window = SDL_CreateWindow("Pontu",10,10,600,600,SDL_WINDOW_SHOWN);
	if (!window)
	{
		fprintf(stderr, "Error : %s\n", SDL_GetError());
		goto Quit;   
	}

	renderer = SDL_CreateRenderer(window,-1,0);
	if(!renderer)
	{
		fprintf(stderr, "Erreur : %s", SDL_GetError());
		goto Quit;
	}

	SDL_bool quit = SDL_FALSE;
	while(!quit)
	{
		// Event handling
		SDL_Event event;
		while(SDL_PollEvent(&event)) 
		{
			switch (event.type) 
			{
				case SDL_QUIT:
					quit = SDL_TRUE;
					break;
				
			}
		}
		

		// Drawing
		

		SDL_RenderPresent(renderer);

		SDL_Delay(20);
	}

	statut = EXIT_SUCCESS;

Quit:
	if(renderer != NULL) {
		SDL_DestroyRenderer(renderer);
	}
	if(window != NULL) {
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
	return statut;
}