#include "engine/FontUtils.h"
#include <string.h>

int calculateStringPixelLenght(TTF_Font* font, char* str)
{
	int length = 0;
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

	while(i < textLenght)
	{
		TTF_GlyphMetrics(font, str[i], &minx, &maxx, NULL, NULL, NULL);
		length += maxx-minx;
		++i;
	}
	return length;
}
