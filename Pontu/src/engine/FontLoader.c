#include "engine/FontLoader.h"

#define MACRO_TO_FONT_NAME(N) #N".TTF",

const char* fontNames[] = {
        MACRO_FOR_ALL_FONTS(MACRO_TO_FONT_NAME)
};

FontHandler loadFonts(void)
{
	const char fontPath[] = "rsrc/font/";
	FontHandler fontHandler;
	char* fontPathFile = NULL;
	for(int i=0; i<NB_FONTS_DEFINED; ++i)
	{
		fontPathFile = (char*) malloc(strlen(fontPath)+strlen(fontNames[i]));
		if(fontPathFile == NULL)
		{
			fprintf(stderr, "Error: Internal memory error for font file name\n");
			continue;
		}
		strcpy(fontPathFile, fontPath);
		strcat(fontPathFile, fontNames[i]);
		fontHandler.fonts[i] = TTF_OpenFont(fontPathFile, 16);
		if(fontHandler.fonts[i] == NULL)
		{
			fprintf(stderr, "Warning: Can't load %s: %s\n", fontPathFile, TTF_GetError());
		}
		else
		{
			printf("Note: %s%s loaded\n", fontPath, fontNames[i]);
		}
		free(fontPathFile);
	}
	return fontHandler;
}

bool freeFonts(FontHandler fontHandler)
{
	for(int i=0; i<NB_FONTS_DEFINED; ++i)
	{
		TTF_CloseFont(fontHandler.fonts[i]);
		fontHandler.fonts[i] = NULL;
		printf("Note: Free font n°%d\n", i);
	}
	return true;
}
