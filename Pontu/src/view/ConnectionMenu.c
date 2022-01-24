#include "view/ConnectionMenu.h"

bool drawMenuConnection(const SDL_Renderer* renderer, TTF_Font* font,  int w, int h)
{
	if(font == NULL)
	{
		fprintf(stderr, "WARNING: Font can't be null\n");
		return false;
	}

	TextInput pseudoInput;
	P_Button connectionButton;

	SDL_Color black = {255,255,255,255};
	SDL_Rect pseudoInputRect = {50, h*0.35, 50, 20};

	char title[] = "Connexion";
	SDL_Point titlePos = {.x=w*0.05, .y=h*0.1};
	TextLabel titleLabel = createTextLabel(title, &titlePos, &black, font, renderer);

	char pseudoText[] = "Pseudonyme: ";
	SDL_Point pseudoPos = {.x=w*0.05, .y=h*0.35};
	TextLabel pseudoLabel = createTextLabel(pseudoText, &pseudoPos, &black, font, renderer);

	char colorText[] = "Couleur: ";
	SDL_Point colorPos = {.x=w*0.05, .y=h*0.55};
	TextLabel colorLabel = createTextLabel(colorText, &colorPos, &black, font, renderer);
	
	if(!initTextInput(&pseudoInput, &pseudoInputRect, NULL, font))
	{
		fprintf(stderr, "WARNING: Can't init TextInput\n");
		return false;
	}

	drawTextLabel(renderer, &titleLabel);
	drawTextLabel(renderer, &pseudoLabel);
	drawTextLabel(renderer, &colorLabel);


	return true;
}
