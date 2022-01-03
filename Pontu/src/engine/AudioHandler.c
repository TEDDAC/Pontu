#include "engine/AudioHandler.h"

// A channel represents the number of SFX we can play at the same time.
// We normally should use only 1 channel, and we add one for safety.
#define NBCHANNELS 2

// Local functions

/*
 * Used in a thread. Fades out the currently played music,
 * then plays the music passed in as parameter.
 * args should be passed as a pointer to void,
 * but should actually be a pointer to Mix_Music.
 * It is the music we want to play next;
 */
int fadeOut(void* args) {
	// Since args is a pointer to void
	// (the way C handles undefined types),
	// casting args to a pointer to Mix_Music
	Mix_Music* = (Mix_Music*)args;
	int ret;
	
	if(Mix_FadeOutMusic(500) == 0) { // Starting the fadeout
		while (Mix_PlayingMusic()) {
			; // Waiting until it's done
		}
	} else {
		fprintf(stderr,"WARNING: couldn't fade out");
		Mix_HaltMusic();
	}

	ret = Mix_PlayMusic(argsCast->music,-1);
	if (ret != 0) {
		fprintf(stderr,"WARNING: %s\n",Mix_GetError());
	}

	// We're supposed to return an int to use SDL_thread.
	// We're not using the return value though.
	return ret;
}

// Global functions

AudioHandler newAudioHandler(int volMusic, int volSFX) {
	AudioHandler audioHandler;
	int nb_SFX = NB_AUDIO_DEFINED - NB_MUSC_DEFINED - 1;

	// Generating paths to musics and SFX files using macros
	char* musicsPaths[] = {MACRO_FOR_ALL_MUSICS(MACRO_TO_MUSIC_PATH)};
	char* sfxPaths[]    = {MACRO_FOR_ALL_SFX(MACRO_TO_SFX_PATH)};
	audioHandler.canPlayAudio = true;

	// Initialize + verify opening audio device
	if (0 != Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)) {
		fprintf(stderr,"Error when initializing audio.\n");
		return audioHandler;
	}

	audioHandler.canPlayAudio = true;

	fprintf(stderr,"Musics: %d\nSFX: %d\n",NB_MUSIC_DEFINED,nb_SFX);
	
	// Loading musics
	for (size_t i = 0; i < NB_MUSIC_DEFINED; i++) {
		if ((audioHandler.musics[i] = LoadMUS(musicPaths[i]) == NULL)) {
			fprintf(stderr,"WARNING: %s\n",Mix_GetError());
		} else {
			fprintf(stderr,"Loaded %s\n",musicPaths[i]);
		}
	}

	Mix_VolumeMusic(volMusic);

	// Initializing SFX
	Mix_AllocateChannels(NBCHANNELS);

	// Loading SFX
	for (size_t i = 0; i < nb_SFX; i++) {
		if ((audioHandler.sfx[i] = Mix_LoadWAV(sfxPaths[i])) == NULL) {
			fprintf(stderr,"WARNING: %s\n",Mix_GetError());
		} else {
			fprintf(stderr,"Loaded %s\n",sfxPaths[i]);
		}
	}

	changeSFXVol(volSFX);
	return audioHandler;
}

void changeSFXVol(int volSFX) {
	for (size_t i = 0; i < NBCHANNELS; i++) {
		Mix_Volume(i, volSFX);
	}
}

void freeAudioHandler(AudioHandler* audioHandler) {
	// Freeing the music
	Mix_HaltMusic();
	for (size_t i = 0; i < NB_MUSIC_DEFINED; i++) {
		if (audioHandler->musics[i] != NULL) {
			Mix_FreeMusic(audioHandler->musics[i]);
			audioHandler->musics[i] = NULL; // "to be safe...", says the docs
		}
	}

	// Freeing the SFX
	Mix_HaltChannel(-1); // Stopping playback on ALL channels
	for (size_t i = 0; i < NB_AUDIO_DEFINED - NB_MUSIC_DEFINED - 1; i++) {
		if (audioHandler->sfx[i] != NULL) {
			Mix_FreeChunk(audioHandler->sfx[i]);
			audioHandler->sfx[i] = NULL; // "to be safe...", says the docs
		}
	}
	Mix_AllocateChannels(0); // Unallocating all channels

	// Un-initializing the audio
	Mix_CloseAudio();

	audioHandler->canPlayAudio = false;
}

void playMusic(EnumAudios music, AudioHandler audioHandler) {
	// music should be a value of EnumAudios that starts by MUSIC_
	// In other words, it should be an enumerator before NB_MUSIC_DEFINED.
	if (music >= NB_MUSIC_DEFINED) {
		fprintf(stderr,"WARNING: tried to play an arbitrary value as a music\n");
		return;
	}
	
	// Checking if audio has been opened.
	if (!(audioHandler.canPlayAudio)) {
		fprintf(stderr,"WARNING: tried to play a music with an unusable AudioHandler\n");
		return;
	}
	
	// If another music is playing, fading the previous one out
	if (Mix_PlayingMusic()) {
		// Creating the thread, passing the music as parameter
		SDL_Thread* thread = SDL_CreateThread(&fadeOut, "Fade out", (void*)audioHandler.musics[music]);
		if (thread == NULL) {
			fprintf(stderr,"WARNING: couldn't create thread to fade out music\n");
		}
		// playMusic won't wait until the thread is finished to end
		SDL_DetachThread(thread);
	// No other music is playing: starting a music normally.
	} else {
		if (Mix_PlayMusic(audioHandler.musics[music],-1) != 0) {
			fprintf("WARNING: %s\n",Mix_GetError());
		}
	}
}

void playSFX(EnumAudios sfx, AudioHandler audioHandler) {
	int nb_SFX = NB_AUDIO_DEFINED - NB_MUSIC_DEFINED - 1;
	int channel;
	Mix_Chunk* chunkSFX;

	// sfx should be a value of EnumAudios that starts by SFX_.
	// In other words, it should be an enumerator after NB_MUSIC_DEFINED but before NB_AUDIO_DEFINED.
	if (sfx <= NB_MUSIC_DEFINED || sfx >= NB_AUDIO_DEFINED) {
		fprintf(stderr,"WARNING: tried to play an arbitrary value as a SFX\n");
		return;
	}

	// Checking if SFX has been opened.
	if (!(audioHandler.canPlayAudio)) {
		fprintf(stderr,"WARNING: tried to play an SFX with an unusable AudioHandler\n");
		return;
	}
	
	// Getting actual chunk
	chunkSFX = audioHandler.sfx[sfx - NB_MUSIC_DEFINED - 1];
	// Getting first available channel
	channel = Mix_GroupAvailable(-1);
	if (channel == -1) {
		fprintf(stderr,"WARNING: cannot play SFX because all channels are used\n");
		return;
	}

	// Playing the SFX once (0 repetitions)
	if (Mix_PlayChannel(channel,chunkSFX,0) != 0) {
		fprintf(stderr,"WARNING: %s\n",Mix_GetError());
		return;
	}
}

