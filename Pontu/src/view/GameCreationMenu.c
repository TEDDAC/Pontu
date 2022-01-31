#include "view/GameCreationMenu.h"

bool drawGameCreationMenu(SDL_Renderer* renderer, TTF_Font* font, int width, int height)
{
	// TextLabel  for "Nombre de joueur.euse.s" creation
	SDL_Point nbJoueurLabelPos = {.x=width*0.05, .y=height*0.05};
	SDL_Color black = {0,0,0,255};
	SDL_Color white = {225, 255, 255, 255};
	TextLabel nbJoueurLabel = createTextLabel(
		"Nombre de joueur.euse.s", 
		&nbJoueurLabelPos,
		1, 
		&white,
		font,
		renderer,
		POSX_LEFT,
		POSY_TOP
	);

	// Incrementation Btn creation
	
	P_Button incrementBtn = createButton(NULL, NULL, nbJoueurLabelPos.x+calculateStringPixelLenght(font, nbJoueurLabel.text)+32, nbJoueurLabelPos.y, 0, 0, NULL);
	SDL_Texture* btnTexture = createGenericButtonTexture("+", font, 8,COLOR_GENERIC_BUTTON_BACKGROUND, COLOR_GENERIC_BUTTON_BORDER, 4, 8, &(incrementBtn.rect.w), &(incrementBtn.rect.h), renderer);
	if(btnTexture == NULL)
	{
		fprintf(stderr, "WARNING: Can't create texture: %s\n", SDL_GetError());
		return false;
	}
	SDL_Texture* btnHoveredTexture = createGenericButtonTexture("+", font, 8, COLOR_GENERIC_BUTTON_BORDER, COLOR_GENERIC_BUTTON_BACKGROUND, 4, 8, &(incrementBtn.rect.w), &(incrementBtn.rect.h), renderer);

	if(btnHoveredTexture == NULL)
	{
		fprintf(stderr, "WARNING: Can't create hover texture: %s\n", SDL_GetError());
		return false;
	}
	incrementBtn.texture = btnTexture;
	incrementBtn.hoverTexture = btnHoveredTexture;

	// Decrementation Btn creation
	
	P_Button decrementBtn = createButton(NULL, NULL, nbJoueurLabelPos.x+calculateStringPixelLenght(font, nbJoueurLabel.text)+32, nbJoueurLabelPos.y, 0, 0, NULL);
	btnTexture = createGenericButtonTexture("-", font, 8,COLOR_GENERIC_BUTTON_BACKGROUND, COLOR_GENERIC_BUTTON_BORDER, 4, 8, &(decrementBtn.rect.w), &(decrementBtn.rect.h), renderer);
	if(btnTexture == NULL)
	{
		fprintf(stderr, "WARNING: Can't create texture: %s\n", SDL_GetError());
		return false;
	}
	btnHoveredTexture = createGenericButtonTexture("-", font, 8, COLOR_GENERIC_BUTTON_BORDER, COLOR_GENERIC_BUTTON_BACKGROUND, 4, 8, &(decrementBtn.rect.w), &(decrementBtn.rect.h), renderer);

	if(btnHoveredTexture == NULL)
	{
		fprintf(stderr, "WARNING: Can't create hover texture: %s\n", SDL_GetError());
		return false;
	}
	decrementBtn.texture = btnTexture;
	decrementBtn.hoverTexture = btnHoveredTexture;

	//Draw everything
	drawButtonOnRenderer(renderer, &incrementBtn);
	drawButtonOnRenderer(renderer, &decrementBtn);
	drawTextLabel(renderer, &nbJoueurLabel);

	//free
	freeTextLabel(&nbJoueurLabel);
	freeButton(&incrementBtn);

	return true;
}
