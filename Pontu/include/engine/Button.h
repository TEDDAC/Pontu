/**
 * \file Button.h
 * \brief Basic button
 * \author Allan Point
 * \date 29/11/2021
 */

#ifndef BUTTON_INCLUDED
#define BUTTON_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/**
 * \struct P_Button
 * \brief Represents a button
 */
typedef struct
{
	SDL_Texture* texture;  ///> background sprite or texture
	SDL_Rect rect;		   ///> defines coordinates and size for hitbox and display
	void (*onClick)(void); ///> action done on click
} P_Button;

/**
 * \brief Creates a brand new button with specs
 * \param[in]   texture background image for the button (can be NULL)
 * \param[in]   coordx  placement in width
 * \param[in]   coordy  placement in height
 * \param[in]   sizex   button's width
 * \param[in]   sizey   button's height
 * \param[in]   onClick action to do when the button is clicked
 * \pre At least text or texture must be defined, or an error will be printed in STDERR.
 * \return a button created with the specs passed as params, or NULL if there was an error.
 */
P_Button createButton(const SDL_Texture* texture, const int coordx, const int coordy, const int sizex, const int sizey, void (*onClick)(void));
// texture: design du bouton, si rien n'est passer, le bouton sera générer dans la fonction.

//SDL_bool putButtonOnRenderer(SDL_Renderer* renderer, TTF_Font* police, P_Button* button);
// function isHover(int x,int y) : bool, dit si le bouton est survolé en donnant les coordonnées x,y
// function isClicked(int x,int y) : void (appel isHover et éxecute button.onClick())

#endif
