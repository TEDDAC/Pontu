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

typedef enum {BUTTON_NOTHING, BUTTON_ENTRY, BUTTON_EXIT} ButtonEvent;

/**
 * \struct P_Button
 * \brief Represents a button
 */
typedef struct P_button
{
	SDL_Texture* texture;  ///> background sprite or texture
	SDL_Texture* hoverTexture; ///> texture to draw when the button is hovered
	SDL_Rect rect;		   ///> defines coordinates and size for hitbox and display
	void (*onClick)(struct P_button* buttonCaller); ///> action done on click
	bool enable;	///> is the button enable and drawable
	bool hover;	///> is the button hovered
	void* arg;
} P_Button;

/**
 * \brief Creates a brand new button with specs
 * \param[in]   texture texture for the button
 * \param[in]   hoverTexture texture for the button when it's hover (can be NULL)
 * \param[in]   coordx  placement in width (NOT NULL)
 * \param[in]   coordy  placement in height (NOT NULL)
 * \param[in]   sizex   button's width (NOT NULL)
 * \param[in]   sizey   button's height (NOT NULL)
 * \param[in]   onClick action to do when the button is clicked
 * \pre At least text or texture must be defined, or an error will be printed in STDERR.
 * \return a button created with the specs passed as params, or NULL if there was an error.
 */
P_Button createButton(SDL_Texture* texture, SDL_Texture* hoverTexture ,const int coordx, const int coordy, const int sizex, const int sizey, void (*onClick)(P_Button* buttonCaller));

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
 * \return true if the cursor is on the button
 */
bool isHover(P_Button* button);// dit si le bouton est survolé en donnant les coordonnées x,y

/**
 * \brief Test if the cursor has just entered the button.
 * \param[in]   button	the button target
 * \param[in]   x	x of the point
 * \param[in]   y	y of the point
 * \return 1 if the cursor has just entry in the button, 2 if it has just exit, else 0
 */
int isButtonInteractWithCursor(P_Button * button,const int x,const int y);

/**
 * \brief Free the texture of a button.
 * \param[in]   button	the button you want to destroy the texture
 */
void freeButton(P_Button * button);

#endif
