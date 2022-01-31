#include "engine/FontUtils.h"
#include <string.h>

int calculateStringPixelLenght(TTF_Font* font, char* str)
{
	char curentChar;
	int lenght = 0;
	int minx, maxx;
	int i=0;

	if(str == NULL || font == NULL)
	{
		return -1;
	}

	int textLenght=strlen(str);
	if(textLenght == 0)
	{
		return 0;
	}

	curentChar = *str;
	while(i < textLenght)
	{
		TTF_GlyphMetrics(font, curentChar, &minx, &maxx, NULL, NULL, NULL);
		lenght += maxx-minx;
		++i;
	}
	return lenght;
}
