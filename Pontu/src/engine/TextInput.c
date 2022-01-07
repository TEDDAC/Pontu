#include "engine/TextInput.h"

bool addCharacterToInputTextValueAtCursor(TextInput* textInput, const char charToAdd)
{
	if(textInput == NULL)
	{
		return false;
	}
	if(textInput->cursorPosition >= strlen(textInput->value))
	{
		return false;
	}
	char newValue[strlen(textInput->value)+1];

	strncpy(newValue, textInput->value, textInput->cursorPosition);
	strcat(newValue, &charToAdd);
	strcat(newValue, textInput->value+textInput->cursorPosition+1);

	free(textInput->value);
	textInput->value = (char*) malloc(strlen(newValue));
	if(textInput->value == NULL)
	{
		fprintf(stderr, "WARNING: Can't allocate memory space to TextInput\n");
		return false;
	}
	strcpy(textInput->value, newValue);
	textInput->cursorPosition -= 1;

	return true;
}

bool removeCharacterToInputTextValueAtCursor(TextInput* textInput)
{
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

	textLen = strlen(textInput->value);
	char tmp[textLen];
	
	if(textInput->cursorPosition > textLen)
	{
		return false;
	}
	if(textLen == 0)
	{
		return true;
	}
	
	strcpy(tmp, textInput->value);
	strncpy(textInput->value, tmp, textInput->cursorPosition-1);
	strcat(textInput->value, tmp+textInput->cursorPosition);
	textInput->cursorPosition -= 1;
	return true;
}

bool drawTextInputOnRenderer(SDL_Renderer* renderer, const TextInput* textInput)
{
	SDL_Surface* textRendered = NULL;
	SDL_Texture* inputTexture = SDL_CreateTexture(renderer,
		      	SDL_PIXELFORMAT_RGBA8888,
		       	SDL_TEXTUREACCESS_TARGET,
		       	(textInput->size).w,
		       	(textInput->size).h);
	SDL_Color black = {0, 0, 0, 255};
	SDL_Color white = {200, 200, 200, 255};
	char textValue[strlen(textInput->value)+1];
	SDL_Rect size = {.x=0, .y=0, .w=textInput->size.w, .h=textInput->size.h};

	if(inputTexture == NULL)
	{
		fprintf(stderr, "WARNING: Can't create TextInput texture: %s\n", SDL_GetError());
		return false;
	}
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
	if(SDL_RenderFillRect(renderer, &(textInput->size)) < 0)
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
		strncpy(textValue, textInput->value, textInput->cursorPosition);
		strcat(textValue, "|");
		strcat(textValue, textInput->value+textInput->cursorPosition+1);
	}else
	{
		strcpy(textValue, textInput->value);
	}
	textRendered = TTF_RenderUTF8_Solid(textInput->textFont, textValue, textInput->textColor);
	if(textRendered == NULL)
	{
		fprintf(stderr, "WARNING: Can't write on TextInput\n");
		return false;
	}
	if(SDL_SetRenderTarget(renderer, NULL) < 0)
	{
		fprintf(stderr, "WARNING: Can't unset TextInput's texture as target: %s\n", SDL_GetError());
		return false;
	}
	return SDL_RenderCopy(renderer, inputTexture, NULL, &textInput->size) == 0;
}

bool initTextInput(TextInput* textInput, const SDL_Rect* size, const SDL_Color* textColor, const TTF_Font* font)
{
	if(textInput == NULL)
	{
		fprintf(stderr, "WARNING: Can't assign value to NULL to create TextInput\n");
		return false;
	}

	textInput->value = (char*) malloc(strlen("TEST"));
	if(textInput->value == NULL)
	{
		fprintf(stderr, "WARNING: Can't allocate memory space to TextInput\n");
		return false;
	}
	strcpy(textInput->value, "TEST");
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
