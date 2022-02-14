#ifndef FONT_LOADER_INCLUDED
#define FONT_LOADER_INCLUDED

#define FONT_PATH rsrc/font/

#define MACRO_FOR_ALL_FONTS(M)       \
        M(retro)\
        M(PublicPixel)\
        M(Curvilingus)
#define MACRO_FONT_ENUM_GEN(E) FONT_##E,

#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>




typedef enum
{
        MACRO_FOR_ALL_FONTS(MACRO_FONT_ENUM_GEN)
        NB_FONTS_DEFINED ///< Contains the number of fonts
} EnumFont;

typedef struct
{
        TTF_Font* fonts[NB_FONTS_DEFINED]; ///< An array of texture (indexed with EnumTextures)
} FontHandler;

/*
 * \brief Allows to load fonts located in rsrc/font/. Pleas note that all fonts must be in TTF format.
 * \author Allan Point
 * \date 03/01/22
 * \return A FontHandler filled with all fonts
 * \copyright CECIL
 */
FontHandler loadFonts(void);

/*
 * \brief Allows to free all fonts from a FontHandler.
 * \author Allan Point
 * \date 03/01/22
 * \return True on success. Else false. Normaly, this function will always retrun true.
 * \copyright CECIL
 */
bool freeFonts(FontHandler fontHandler);


#endif
