/**
 * \file Button.h
 * \brief Basic button
 * \author Allan Point, Mathis Ribémont
 * \date 29/11/2021
 */

#ifndef BUTTON_INCLUDED
#define BUTTON_INCLUDED

#include <SDL2/SDL.h>
#include <stdbool.h>

struct P_buttonArg;

/**
 * \struct P_Button
 * \brief Represents a button
 */
typedef struct
{
	SDL_Texture* texture;  ///> background sprite or texture
	SDL_Texture* hoverTexture; ///> texture to draw when the button is hovered
	SDL_Rect rect;		   ///> defines coordinates and size for hitbox and display
	void (*onClick)(struct P_buttonArg* arg); ///> action done on click
	bool drawn;	///> is the button drawn
	bool hover;	///> is the button hovered
} P_Button;

/**
 * \struct P_Button
 * \brief Structure of arguments to pass to onClick function
 */
typedef struct P_buttonArg
{
	P_Button* buttonCaller;	///> button who call the one click
	SDL_Texture* texture;	///> texture to putt on the button if we want to change his default texture;
} P_ButtonArg;

/**
 * \brief Creates a brand new button with specs
 * \param[in]   texture texture for the button (NOT NULL)
 * \param[in]   hoverTexture texture for the button when it's hover (can be NULL)
 * \param[in]   coordx  placement in width
 * \param[in]   coordy  placement in height
 * \param[in]   sizex   button's width
 * \param[in]   sizey   button's height
 * \param[in]   onClick action to do when the button is clicked
 * \pre At least text or texture must be defined, or an error will be printed in STDERR.
 * \return a button created with the specs passed as params, or NULL if there was an error.
 */
P_Button createButton(SDL_Texture* texture, SDL_Texture* hoverTexture ,const int coordx, const int coordy, const int sizex, const int sizey, void (*onClick)(P_ButtonArg* arg));

/**
 * \brief draw a button on a renderer with his texture according if it hover or not
 * \param[in]   renderer	the renderer you want to draw the button on
 * \param[in]   button	the button you want to draw
 * \pre At least text or texture must be defined, or an error will be printed in STDERR.
 * \return false if the texture is null
 */
bool drawButtonOnRenderer(SDL_Renderer* renderer, P_Button* button);

/**
 * \brief Test if a point is on a button
 * \param[in]   button	the button target
 * \param[in]   x	x of the point
 * \param[in]   y	y of the point
 * \return SDL_TRUE if the point is on the button
 */
bool isHover(P_Button* button, int x,int y);// dit si le bouton est survolé en donnant les coordonnées x,y

/**
 * \brief Change the texture of the button
 * \param[in]   button	the button target
 * \param[in]   texture	the texture you want to apply to the button
 * \return false	if the texture is NULL
 */
bool changeButtonTexture(P_Button* button, SDL_Texture* texture);

/**
 * \brief Change the texture to use when the button is hovered
 * \param[in]   button	the button target
 * \param[in]   texture	the texture you want to apply to the button
 * \return false	if the texture is NULL
 */
bool changeButtonHoverTexture(P_Button* button, SDL_Texture* texture);

#endif
