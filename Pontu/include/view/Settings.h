/**
 * \file Settings.h 
 * \brief Settings view
 * \author Théotime Maillarbaux
 * \date 24/01/2022
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "engine/AudioHandler.h"
#include "engine/Button.h"
#include <stdbool.h>
#include "engine/TextureLoader.h"
#include <SDL2/SDL_ttf.h>
#include "engine/TextLabel.h"
#include "engine/FontLoader.h"
#include "engine/arrayButton.h"

typedef struct {
	struct array_P_Button arr_buttons;
	TextLabel* arr_textLabel;
} RetValues;

/**
 * \brief Generates a settings view
 * \param[in] renderer The used SDL_Renderer
 * \param[in] ah The AudioHandler in use
 * \return true if the view could be generated, else false
 */
RetValues drawSettingsView(SDL_Renderer* renderer, AudioHandler* ah, FontHandler* fh);

void settingsView(SDL_Window* parent, AudioHandler* ah, const FontHandler* fh);

#endif // SETTINGS_H
