/**
 * \file Button.h
 * \brief Basic button
 * \author Allan Point
 * \date 29/11/2021
 */

#ifndef BUTTON_INCLUDED
#define BUTTON_INCLUDED

#include <SDL2/SDL.h>
#include <stdbool.h>

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
 * \param[in]   texture background image for the button (NOT NULL)
 * \param[in]   coordx  placement in width
 * \param[in]   coordy  placement in height
 * \param[in]   sizex   button's width
 * \param[in]   sizey   button's height
 * \param[in]   onClick action to do when the button is clicked
 * \pre At least text or texture must be defined, or an error will be printed in STDERR.
 * \return a button created with the specs passed as params, or NULL if there was an error.
 */
P_Button createButton(SDL_Texture* texture, const int coordx, const int coordy, const int sizex, const int sizey, void (*onClick)(void));

/**
 * \brief draw a button on a renderer
 * \param[in]   renderer	the renderer you want to draw the button on
 * \param[in]   button	the button you want to draw
 * \pre At least text or texture must be defined, or an error will be printed in STDERR.
 */
void drawButtonOnRenderer(SDL_Renderer* renderer, const P_Button* button);

/**
 * \brief Test if a point is on a button
 * \param[in]   button	the button target
 * \param[in]   x	x of the point
 * \param[in]   y	y of the point
 * \return SDL_TRUE if the point is on the button
 */
SDL_bool isHover(P_Button button, int x,int y);// dit si le bouton est survolé en donnant les coordonnées x,y
//void changeButtonTexture(P_Button* button, const SDL_Texture* texture);

#endif
