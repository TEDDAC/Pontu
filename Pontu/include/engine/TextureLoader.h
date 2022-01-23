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

SDL_Texture* createGenericButtonTexture(char* text, TTF_Font* font, int fontSize, SDL_Color border_color, SDL_Color background_color,int thickness, int padding, int* sizex, int* sizey, SDL_Renderer* renderer);
