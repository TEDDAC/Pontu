/**
 * \file TextureLoader.h
 * \brief Define functions to load textures
 * \author Allan Point
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/*
 * \brief Create a texture with an image
 * \param[in]	renderer	The renderer which will draw the image
 * \param[in]	path	Image's path on the computer
 * \return Return texture created on success. Else return NULL and print the error on STDERR.
*/
SDL_Texture* createTextureFromPath(SDL_Renderer* renderer, char* path);

/*
 * \brief Create a generic button texture
 * \param[in]	text	The text you want to draw in on the texture
 * \param[in]	font	The font you want to apply to the text
 * \param[in]	fontSize  The size of the font
 * \param[in]	border_color  The color of the border of the button. This color is also used for the text
 * \param[in]	background_color  The color of the background
 * \param[in]	thickness The thickness of the texture
 * \param[in]	padding   The padding around the text in the button
 * \param[in]	sizex The width of the texture. You have to apply to the width of the button
 * \param[in]	sizey The height of the texture. You have to apply to the height of the button
 * \param[in]	renderer	The renderer you want the texture to be associated
 * \return Return texture created on success. Else return NULL and print the error on STDERR.
*/
SDL_Texture* createGenericButtonTexture(char* text, TTF_Font* font, int fontSize, SDL_Color border_color, SDL_Color background_color,int thickness, int padding, int* sizex, int* sizey, SDL_Renderer* renderer);
