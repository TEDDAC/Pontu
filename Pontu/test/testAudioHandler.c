#include "engine/AudioHandler.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>

void testAudioHandler(void) {
	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		perror("SDL");
		exit(errno);
	}

	AudioHandler ah = newAudioHandler(100, 100);
	if (ah.canPlayAudio == false) {
		perror("AudioHandler");
		SDL_Quit();
		exit(1);
	}

	printf("AudioHandler created!\n");

	printf("Now (normally) playing base_tardi...\n");
	playMusic(MUSIC_base_tardi, ah);
	
	SDL_Delay(2000);

	printf("Switching to testMus\n");
	playMusic(MUSIC_testMus, ah);

	SDL_Delay(5000);

	printf("Playing SFX");

	playSFX(SFX_testClick, ah);

	SDL_Delay(1000);

	printf("Freeing AudioHandler\n");
	freeAudioHandler(&ah);

	if (ah.canPlayAudio == true) {
		printf("Failed to free AudioHandler!\n");
	}

	SDL_Quit();
}


