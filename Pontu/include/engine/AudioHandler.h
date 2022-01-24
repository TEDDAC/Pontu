/**
 * \file AudioHandler.h
 * \brief Audio management (music and sound effects)
 * \author Théotime Maillarbaux
 * \date 13/12/2021
 */

#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_thread.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * Macro used to generate enums elements and paths for musics.
 * It should take either #MACRO_MUSIC_ENUM_GEN(E) or #MACRO_TO_MUSIC_PATH(P)
 * as parameter.
 *
 * If new audios are added to the program, they should be added here.
 * \sa #MACRO_FOR_ALL_SFX(E)
 */
#define MACRO_FOR_ALL_MUSICS(M)		\
	M(base_tardi)			\
	M(testMus)

/**
 * Macro used to generate enums elements and paths for sound effects.
 * It works the same way as #MACRO_FOR_ALL_MUSICS(M).
 * \sa #MACRO_FOR_ALL_MUSICS(M)
 */
#define MACRO_FOR_ALL_SFX(M)		\
	M(testClick)

/**
 * Macro used to generate the entries for the musics in #EnumAudios.
 * It should be used in #MACRO_FOR_ALL_MUSICS(M) as a parameter.
 * Each entry of #MACRO_FOR_ALL_MUSICS(M) will be converted as MUSIC_name.
 * \sa #MACRO_SFX_ENUM_GEN(E)
 */
#define MACRO_MUSIC_ENUM_GEN(E) MUSIC_##E,

/**
 * Macro used to generate the entries for the SFX in #EnumAudios.
 * It works the same way as #MACRO_MUSIC_ENUM_GEN(E), except the entries start with SFX_
 * instead of MUSIC_.
 * \sa #MACRO_MUSIC_ENUM_GEN(E).
 */
#define MACRO_SFX_ENUM_GEN(E) SFX_##E,

/**
 * Macro used to generate the paths to the musics.
 * It should be used in #MACRO_FOR_ALL_MUSICS(M) as a parameter.
 * Each entry of #MACRO_FOR_ALL_MUSICS(M) will be converted as rsrc/music/name.mp3.
 * \sa #MACRO_TO_SFX_PATH(P)
 */
#define MACRO_TO_MUSIC_PATH(P) "rsrc/music/"#P".mp3",

/**
 * Macro used to generate the paths to the SFX.
 * It works the same way as #MACRO_TO_MUSIC_PATH(P),
 * except the entries are converted to rsrc/sfx/name.wav.
 * \sa MACRO_TO_MUSIC_PATH(P)
 */
#define MACRO_TO_SFX_PATH(P) "rsrc/sfx/"#P".wav",

/**
 * \enum EnumAudios
 * \brief Lists audios used in the program.
 */
typedef enum {
	MACRO_FOR_ALL_MUSICS(MACRO_MUSIC_ENUM_GEN)
	NB_MUSIC_DEFINED, ///< Index of this entry == number of musics
	MACRO_FOR_ALL_SFX(MACRO_SFX_ENUM_GEN)
	NB_AUDIO_DEFINED ///< Index of this entry == number of audios + 1
} EnumAudios;

/**
 * \struct AudioHandler
 * \brief A struct to store and handle all audios.
 */
typedef struct {
	bool canPlayAudio; ///< true if audio could be initialized, else false. It shouldn't be changed manually.
	Mix_Music* musics[NB_MUSIC_DEFINED]; ///< Paths to the musics
	Mix_Chunk* sfx[NB_AUDIO_DEFINED - NB_MUSIC_DEFINED - 1]; ///< Paths to the SFX
	int musicVol; ///< The current volume of the music
	int sfxVol; ///< The current volume of the SFX
	int masterVol;
} AudioHandler;

/**
 * \brief Initializes the audio and creates a new AudioHandler.
 * \param[in]	volMusic	Volume of the music
 * \param[in]	volSFX		Volume of the sound effects.
 * \return A new AudioHandler.
 * \warning The program won't know if opening the audio device and the files failed.
 */
AudioHandler newAudioHandler(int volMusic, int volSFX);

/**
 * \brief Changes volume for the SFX.
 * \param[in]	volSFX	The new volume for the SFX.
 */
void changeSFXVol(AudioHandler* ah, int volSFX);

void changeMusicVol(AudioHandler* ah, int volMusic);

void changeMasterVol(AudioHandler* ah, int masterVol);

/**
 * \brief Frees the music and SFX, and un-initializes the audio.
 * \param[in,out]	audioHandler	A pointer to the AudioHandler to be freed.
 */
void freeAudioHandler(AudioHandler* audioHandler);

/**
 * \brief Plays a music. If another music is currently playing, the previous one will fade out.
 * \param[in]	music		The music to be played. Should be a value of #EnumAudios starting with MUSIC_.
 * \param[in]	audioHandler	The AudioHandler used to store the musics.
 */
void playMusic(EnumAudios music, AudioHandler audioHandler);

/**
 * \brief Plays a sound effect.
 * \param[in]	sfx		The SFX to be played. Should be a value of #EnumAudios starting with SFX_.
 * \param[in]	audioHandler	The AudioHandler used to store the SFX.
 */
void playSFX(EnumAudios sfx, AudioHandler audioHandler);


#endif // AUDIO_H
