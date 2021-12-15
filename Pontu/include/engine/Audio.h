/**
 * \file Audio.h
 * \brief Audio management
 * \author Théotime Maillarbaux
 * \date 13/12/2021
 */

#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_thread>

/**
 * \brief Fades out a music and plays another one.
 * \param[in]	music	A pointer to the Mix_Music struct used to play the current track
 * \param[in]	path	The path to the new track to be played
 * \warning The program won't know if it failed.
 *
 * This function creates a thread that will detach on its own completion.
 */
void switchMusic(Mix_Music* music, char[] path);

#endif // AUDIO_H
