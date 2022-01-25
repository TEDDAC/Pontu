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

/**
 * \brief Generates a settings view
 * \param[in] renderer The used SDL_Renderer
 * \param[in] ah The AudioHandler in use
 * \return true if the view could be generated, else false
 */
bool settingsView(SDL_Renderer* renderer, AudioHandler* ah);


#endif // SETTINGS_H
