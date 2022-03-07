#include "engine/TextInput.h"

bool addStringToInputTextValue(TextInput* textInput, const char* strToAdd) {
	if(textInput == NULL)
	{
		fprintf(stderr, "WARNING: Can't add text to NULL textInput\n");
		return false;
	}

	const size_t lenText = strlen(textInput->value);
	const size_t lenStrToAdd = strlen(strToAdd);

	textInput->value = (char*) realloc(textInput->value, sizeof(char) * (lenText+lenStrToAdd+1));
	strcat(textInput->value, strToAdd);
	textInput->cursorPosition += lenStrToAdd;
	return true;
}

bool addStringToInputTextValueAtCursor(TextInput* textInput, const char* strToAdd)
{
	if(textInput == NULL)
	{
		fprintf(stderr, "WARNING: Can't add text to NULL textInput\n");
		return false;
	}
	const size_t lenText = strlen(textInput->value);
	if(textInput->cursorPosition > lenText)
	{
		textInput->cursorPosition = lenText;
	}
	const size_t lenStrToAdd = strlen(strToAdd);
	char newValue[lenText+lenStrToAdd+1];

	strcpy(newValue, "");
	strncpy(newValue, textInput->value, textInput->cursorPosition);
	strcat(newValue, strToAdd);
	strcat(newValue, textInput->value+textInput->cursorPosition);

	textInput->value = (char*) realloc(textInput->value, strlen(newValue)*sizeof(char));
	if(textInput->value == NULL)
	{
		fprintf(stderr, "WARNING: Can't allocate memory space to TextInput\n");
		return false;
	}
	strcpy(textInput->value, newValue);
	textInput->cursorPosition += lenStrToAdd;

	return true;
}

bool removeCharacterToInputTextValueAtCursor(TextInput* textInput)
{
	size_t removeSize = 0;
	size_t lenText = strlen(textInput->value);
	while (lenText>removeSize && textInput->value[textInput->cursorPosition - removeSize-1] < -64) {
		removeSize++;
	}
	if (lenText>removeSize) {
		removeSize++;
	}


	int textLen = 0;
	if(textInput == NULL)
	{
		return false;
	}
	if(textInput->value == NULL)
	{
		return true;
	}
	if(textInput->cursorPosition <= 0)
	{
		return true;
	}

	char tmp[lenText];

	if(textInput->cursorPosition-1 > lenText)
	{
		return false;
	}
	if(lenText == 0)
	{
		return true;
	}

	strcpy(tmp, textInput->value);
	strcpy(textInput->value, "");
	strncpy(textInput->value, tmp, textInput->cursorPosition-removeSize);
	strcat(textInput->value, tmp+textInput->cursorPosition+1);
	textInput->cursorPosition -= 1;
	return true;
}

bool drawTextInputOnRenderer(SDL_Renderer* renderer, const TextInput* textInput)
{
	if(textInput == NULL)
	{
		fprintf(stderr, "WARNING: TextInput mustn't be NULL\n");
		return false;
	}
	SDL_Surface* textRendered = NULL;
	SDL_Texture* textTexture = NULL;
	SDL_Color black = {0, 0, 0, 255};
	SDL_Color white = {200, 200, 200, 255};

	SDL_Texture* inputTexture = SDL_CreateTexture(renderer,
		      	SDL_PIXELFORMAT_RGBA8888,
		       	SDL_TEXTUREACCESS_TARGET,
		       	(textInput->size).w,
		       	(textInput->size).h);
	if(inputTexture == NULL)
	{
		fprintf(stderr, "WARNING: Can't create TextInput texture: %s\n", SDL_GetError());
		return false;
	}
	char textValue[strlen(textInput->value)+2];
	SDL_Rect size = {.x=0, .y=0, .w=textInput->size.w, .h=textInput->size.h};
	if(textInput->textFont == NULL)
	{
		fprintf(stderr, "WARNING: Can't use a null font\n");
		return false;
	}
	SDL_Rect textZone = {.x=textInput->size.x, .y=textInput->size.y, .h=TTF_FontHeight(textInput->textFont)};
	if(SDL_SetRenderTarget(renderer, inputTexture) < 0)
	{
		fprintf(stderr, "WARNING: Can't set TextInput's texture as target: %s\n", SDL_GetError());
		return false;
	}
	if(SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a) != 0)
	{
		fprintf(stderr, "WARNING: Can't change color: %s\n", SDL_GetError());
		return false;
	}
	if(SDL_RenderFillRect(renderer, &size) < 0)
	{
		fprintf(stderr, "WARNING: Can't fill TextInput: %s\n", SDL_GetError());
		return false;
	}
	if(SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a) != 0)
	{
		fprintf(stderr, "WARNING: Can't change color: %s\n", SDL_GetError());
		return false;
	}
	if(SDL_RenderDrawRect(renderer, &size) < 0)
	{
		fprintf(stderr, "WARNING: Can't draw TextInput's border: %s\n", SDL_GetError());
		return false;
	}
	if(textInput->isActive)
	{
		strcpy(textValue, "");
		strncat(textValue, textInput->value, textInput->cursorPosition);
		strcat(textValue, "|");
		strcat(textValue, textInput->value+textInput->cursorPosition);
	}else
	{
		strcpy(textValue, strcmp(textInput->value, "") != 0 ? textInput->value : " ");
	}
	textRendered = TTF_RenderText_Solid(textInput->textFont, textValue, textInput->textColor);
	if(textRendered == NULL)
	{
		fprintf(stderr, "WARNING: Can't write on TextInput\n");
		return false;
	}
	textTexture = SDL_CreateTextureFromSurface(renderer, textRendered);
	SDL_FreeSurface(textRendered);
	if(textTexture == NULL)
	{
		fprintf(stderr, "WARNING: Can't create texture from surface: %s\n", SDL_GetError());
		return false;
	}
	if(SDL_SetRenderTarget(renderer, NULL) < 0)
	{
		fprintf(stderr, "WARNING: Can't unset TextInput's texture as target: %s\n", SDL_GetError());
		return false;
	}
	if(SDL_RenderCopy(renderer, inputTexture, NULL, &textInput->size) != 0)
	{
		fprintf(stderr, "WARNING: Can't copy the inputTexure on renderer");
		return false;
	}
	textZone.w = calculateStringPixelLenght(textInput->textFont, textValue);
	if(SDL_RenderCopy(renderer, textTexture, NULL, &textZone) != 0)
	{
		fprintf(stderr, "WARNING: Can't copy the text on renderer");
		return false;
	}
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(inputTexture);
	return true;
}

bool initTextInput(TextInput* textInput, const SDL_Rect* size, const SDL_Color* textColor, TTF_Font* font)
{
	if(textInput == NULL)
	{
		fprintf(stderr, "WARNING: Can't assign value to NULL to create TextInput\n");
		return false;
	}

	textInput->value = (char*) malloc(sizeof(char));
	if(textInput->value == NULL)
	{
		fprintf(stderr, "WARNING: Can't allocate memory space to TextInput\n");
		return false;
	}
	strcpy(textInput->value, "");
	textInput->cursorPosition = 0;
	if(size == NULL)
	{
		fprintf(stderr, "WARNING: Can't create a TextInput with a NULL size");
		return false;
	}

	textInput->size = *size;

	if(textColor == NULL)
	{
		SDL_Color defautlColor = {0,0,0,0};
		textInput->textColor = defautlColor;
	}
	else
	{
		textInput->textColor = *textColor;
	}

	if(font == NULL)
	{
		fprintf(stderr, "WARNING: Can't create a TextIntput with a NULL font\n");
		return false;
	}
	textInput->textFont = font;
	return true;

}

bool destroyTextInput(TextInput* textInput)
{
	SDL_Rect initRect = { .x=0, .y=0, .w=0, .h=0};
	SDL_Color initColor = {0,0,0,0};

	free(textInput->value);
	textInput->cursorPosition = 0;
	textInput->size = initRect;
	textInput->isActive = false;
	textInput->textColor = initColor;
	textInput->textFont = NULL;

	return true;
}
