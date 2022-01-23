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

	printf("Playing SFX\n");

	playSFX(SFX_testClick, ah);

	SDL_Delay(2000);

	printf("Trying to play a music as SFX (playSFX(MUSIC_base_tardi))\n");

	playSFX(MUSIC_base_tardi, ah);

	printf("Trying to play -1 as SFX\n");

	playSFX(-1, ah);

	printf("Trying to play 9999 as SFX\n");

	playSFX(9999, ah);

	printf("Trying to play a SFX as music (playMusic(SFX_testClick))\n");

	playMusic(SFX_testClick, ah);

	printf("Trying to play -1 as music\n");

	playMusic(-1, ah);

	printf("Trying to play 9999 as music\n");

	playMusic(9999, ah);

	printf("Playing louder (vol = 128) the SFX, testing with SFX_testClick\n");

	changeSFXVol(128);
	playSFX(SFX_testClick, ah);
	SDL_Delay(2000);

	printf("Playing quieter (vol = 10) the SFX, testing with SFX_testClick\n");

	changeSFXVol(10);
	playSFX(SFX_testClick, ah);
	SDL_Delay(2000);

	printf("Waiting another 30 seconds to test loop...\n");

	SDL_Delay(30000);

	printf("Freeing AudioHandler\n");
	freeAudioHandler(&ah);

	if (ah.canPlayAudio == true) {
		printf("Failed to free AudioHandler!\n");
	}

	SDL_Quit();
}


