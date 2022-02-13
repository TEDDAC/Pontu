#include "view/GameCreationMenu.h"

#include <SDL2/SDL_ttf.h>

bool gameCreationMenu(SDL_Renderer* renderer, GeneralState* generalState,TTF_Font* font, int width, int height);
void freeCreateMenuLine(CreateMenuLine* line);
CreateMenuLine createCreateMenuLine(SDL_Renderer* renderer, int xmin, int y, int xmax, TTF_Font* font, Player* player);
void createPlayersLines(SDL_Renderer* renderer, TTF_Font* font, int minx, int maxx, int miny,int nbPlayer, CreateMenuLine* lines);
bool drawGameCreationMenu(SDL_Renderer* renderer, TextLabel** labels, int nbLabels, P_Button* buttons, int nbButtons, CreateMenuLine* lines, int nbPlayer);
bool drawCreateMenuLine(SDL_Renderer* renderer, CreateMenuLine* line);
void changePlayerColor(P_Button* caller);
void decrementNbPlayer(P_Button* caller);
void incrementNbPlayer(P_Button* caller);




void incrementNbPlayer(P_Button* caller)
{
	IncrementParams* params = (IncrementParams*) caller->arg;
	int* nbPlayers = params->nbPlayers;
	if(*nbPlayers == 4)
	{
		fprintf(stderr, "WARNING: Can't increment up to 5 and more\n");
		return;
	}
	++(*nbPlayers);
	createPlayersLines(params->renderer, params->font, params->minx, params->maxx, params->miny, *params->nbPlayers, params->lines);
	drawCreateMenuLine(params->renderer, params->lines+*params->nbPlayers-1);
}
void decrementNbPlayer(P_Button* caller)
{
	DecrementParams* params = (DecrementParams*)caller->arg;
	int* nbPlayers = params->nbPlayers;
	if(*nbPlayers == 2)
	{
		fprintf(stderr, "WARNING: Can't decrement down to 1 and less\n");
		return;
	}
	freeCreateMenuLine(&params->lines[*nbPlayers-1]);
	*nbPlayers -= 1;
}

void changePlayerColor(P_Button* caller)
{
	ChangeColorParams* params = (ChangeColorParams*)caller->arg;
	params->p->color = params->color;
}

bool drawGameCreationMenu(SDL_Renderer* renderer, TextLabel** labels, int nbLabels, P_Button* buttons, int nbButtons, CreateMenuLine* lines, int nbPlayer)
{
	//Draw everything
	
	for(int i=0; i<nbButtons; ++i)
	{
		if(!drawButtonOnRenderer(renderer, &(buttons[i])))
		{
			fprintf(stderr, "WARNING: Can't draw button\n");
			return false;
		}
	}

	for(int i=0; i<nbLabels; ++i)
	{
		drawTextLabel(renderer, labels[i]);
	}
	for(int i=0; i<nbPlayer; ++i)
	{
		drawCreateMenuLine(renderer, &lines[i]);
	}
	SDL_RenderPresent(renderer);
	return true;
}


void createPlayersLines(SDL_Renderer* renderer, TTF_Font* font, int minx, int maxx, int miny,int nbPlayer, CreateMenuLine* lines)
{
	
	Player players[nbPlayer];
	for(int i=0; i<nbPlayer; ++i)
	{
		if(i==0)
		{
			lines[i] = createCreateMenuLine(renderer, minx, miny + 16, maxx,font, &players[i]);
		}else{
			lines[i] = createCreateMenuLine(renderer, minx, miny + 16 + 16 + i* lines[i-1].aiButton.rect.h, maxx,font, &players[i]);
		}
	}

	return;
}

bool drawCreateMenuLine(SDL_Renderer* renderer, CreateMenuLine* line)
{
	drawButtonOnRenderer(renderer, &line->aiButton);
	for(int i=0; i<NB_COLORS; ++i)
	{
		drawButtonOnRenderer(renderer, &line->colorButtons[i]);
	}
	drawTextInputOnRenderer(renderer, &line->pseudoInput);
	return true;
}

CreateMenuLine createCreateMenuLine(SDL_Renderer* renderer, int xmin, int y, int xmax, TTF_Font* font, Player* player)
{
	int const wColorBtn = 32;
	int const hColorBtn = 32;
	int const colorBtnXMargin = 8;
	SDL_Texture* btnTexture, *btnTextureHover;
	
	P_Button* colorsBtn = (P_Button*) malloc(sizeof(P_Button)*NB_COLORS);
	P_Button ai = createButton(NULL, NULL, xmin, y, 0, 0, NULL);

	CreateMenuLine line;

	SDL_Texture* aiTexture =  createGenericButtonTexture("X", font, 16, COLOR_GENERIC_BUTTON_BACKGROUND, COLOR_GENERIC_BUTTON_BORDER, 4, 8, &(ai.rect.w), &(ai.rect.h), renderer);
	SDL_Texture* aiTextureHovered =  createGenericButtonTexture("X", font, 16, COLOR_GENERIC_BUTTON_BACKGROUND, COLOR_GENERIC_BUTTON_BACKGROUND, 4, 8, &ai.rect.w, &ai.rect.h, renderer);
	ai.texture = aiTexture;
	ai.hoverTexture = aiTextureHovered;

	SDL_Rect rect = {.x = xmin + ai.rect.x + ai.rect.w, .y = y, .h = TTF_FontHeight(font),.w = xmax - ai.rect.w - NB_COLORS * (wColorBtn + colorBtnXMargin*2)- 16};

	TextInput pseudoInput;
	initTextInput(&pseudoInput, &rect, NULL, font);

	ChangeColorParams* params;

	for(int i=0; i<NB_COLORS; ++i)
	{
		params = (ChangeColorParams*) malloc(sizeof(ChangeColorParams));
		params->p = player;
	        params->color=playersColors[i];
		colorsBtn[i] = createButton(NULL, NULL, xmax-wColorBtn*(i+1), y, wColorBtn, hColorBtn, changePlayerColor);
		colorsBtn[i].arg = params;
		btnTexture = createGenericButtonTexture("", font, 0, COLOR_GENERIC_BUTTON_BORDER, PLAYER_SDL_COLORS[i], 4, 8, NULL, NULL, renderer);
		btnTextureHover = createGenericButtonTexture("", font, 0, COLOR_GENERIC_BUTTON_BACKGROUND, PLAYER_SDL_COLORS[i], 4, 8, NULL, NULL, renderer);
		colorsBtn[i].texture = btnTexture;
		colorsBtn[i].hoverTexture = btnTextureHover;

	}
	line.aiButton=ai;
        line.colorButtons=colorsBtn;
	line.player=player;
	line.pseudoInput=pseudoInput;
	return line;
}

void freeCreateMenuLine(CreateMenuLine* line)
{
	destroyTextInput(&line->pseudoInput);
	freeButton(&line->aiButton);
	for(int i=0; i<NB_COLORS; ++i)
	{
		free(line->colorButtons[i].arg);
		freeButton(&line->colorButtons[i]);
		// free(&line->colorButtons[i]);
	}
}
bool gameCreationMenu(SDL_Renderer* renderer, GeneralState* generalState,TTF_Font* font, int width, int height)
{
	int nbPlayers = 2;
	int const nbLabels = 5;
	int nbButtons = 2;
	TextLabel *labels[nbLabels];
	P_Button* buttons = (P_Button*) malloc(sizeof(P_Button)*nbButtons);


	// TextLabel  for "Nombre de joueur.euse.s" creation
	SDL_Point titleLabelPos = {.x=width*0.05, .y=height*0.05};
	SDL_Color white = {225, 255, 255, 255};
	CreateMenuLine lines[NB_PLAYER_MAX];
	TextLabel titleLabel = createTextLabel(
		"Nombre de joueur·euse·s", 
		&titleLabelPos,
		1, 
		&white,
		font,
		renderer,
		POSX_LEFT,
		POSY_TOP
	);

	// Decrementation Btn creation
	P_Button decrementBtn = createButton(NULL, NULL, titleLabelPos.x+calculateStringPixelLenght(font, titleLabel.text)+32, titleLabelPos.y, 0, 0, &decrementNbPlayer);
	SDL_Texture* btnTexture = createGenericButtonTexture("-", font, 8,COLOR_GENERIC_BUTTON_BACKGROUND, COLOR_GENERIC_BUTTON_BORDER, 4, 8, &(decrementBtn.rect.w), &(decrementBtn.rect.h), renderer);
	if(btnTexture == NULL)
	{
		fprintf(stderr, "WARNING: Can't create texture: %s\n", SDL_GetError());
		return false;
	}
	SDL_Texture* btnHoveredTexture = createGenericButtonTexture("-", font, 8, COLOR_GENERIC_BUTTON_BORDER, COLOR_GENERIC_BUTTON_BACKGROUND, 4, 8, &(decrementBtn.rect.w), &(decrementBtn.rect.h), renderer);

	if(btnHoveredTexture == NULL)
	{
		fprintf(stderr, "WARNING: Can't create hover texture: %s\n", SDL_GetError());
		return false;
	}
	decrementBtn.texture = btnTexture;
	decrementBtn.hoverTexture = btnHoveredTexture;

	// TextLabel for the number of players creation
	SDL_Point nbPlayerLabelPos = {.x=decrementBtn.rect.x+decrementBtn.rect.w+8, .y=decrementBtn.rect.y*1.5};
	char nbPlayerStr[2];
	if(nbPlayers < 0 || nbPlayers > 9)
	{
		fprintf(stderr, "WARNING: The number of players has to be between 0 and 9\n");
		return false;
	}
	nbPlayerStr[0] = nbPlayers + 48; // ASCII code of '0' is 48 and ASSCI code of '9' is 57 (48+9)
	nbPlayerStr[1] = '\0';
	TextLabel nbPlayerLabel = createTextLabel(
		nbPlayerStr, 
		&nbPlayerLabelPos,
		1, 
		&white,
		font,
		renderer,
		POSX_LEFT,
		POSY_CENTER
	);




	// Incrementation Btn creation
	P_Button incrementBtn = createButton(NULL, NULL, nbPlayerLabel.textZone.x + nbPlayerLabel.textZone.w + 8, titleLabelPos.y, 0, 0, &incrementNbPlayer);
	btnTexture = createGenericButtonTexture("+", font, 8,COLOR_GENERIC_BUTTON_BACKGROUND, COLOR_GENERIC_BUTTON_BORDER, 4, 8, &(incrementBtn.rect.w), &(incrementBtn.rect.h), renderer);
	if(btnTexture == NULL)
	{
		fprintf(stderr, "WARNING: Can't create texture: %s\n", SDL_GetError());
		return false;
	}
	btnHoveredTexture = createGenericButtonTexture("+", font, 8, COLOR_GENERIC_BUTTON_BORDER, COLOR_GENERIC_BUTTON_BACKGROUND, 4, 8, &(incrementBtn.rect.w), &(incrementBtn.rect.h), renderer);

	if(btnHoveredTexture == NULL)
	{
		fprintf(stderr, "WARNING: Can't create hover texture: %s\n", SDL_GetError());
		return false;
	}
	incrementBtn.texture = btnTexture;
	incrementBtn.hoverTexture = btnHoveredTexture;


	SDL_Point aiLabelPos = {.x=titleLabel.textZone.x, .y=decrementBtn.rect.y+ decrementBtn.rect.h + 16};
	TextLabel aiLabel = createTextLabel(
		"IA", 
		&aiLabelPos,
		1, 
		&white,
		font,
		renderer,
		POSX_LEFT,
		POSY_TOP
	);

	SDL_Point colorLabelPos = {
		.x=incrementBtn.rect.x+incrementBtn.rect.w,
		decrementBtn.rect.y+ decrementBtn.rect.h + 16
	};
	TextLabel colorLabel = createTextLabel(
		"Couleur", 
		&colorLabelPos,
		1, 
		&white,
		font,
		renderer,
		POSX_RIGHT,
		POSY_TOP
	);

	SDL_Point pseudoLabelPos = {
		.x=	(titleLabel.textZone.x+
			aiLabel.textZone.w+
			colorLabelPos.x)
			/2,
		.y=decrementBtn.rect.y+ decrementBtn.rect.h + 16
	};
	TextLabel pseudoLabel = createTextLabel(
		"Pseudonyme", 
		&pseudoLabelPos,
		1, 
		&white,
		font,
		renderer,
		POSX_CENTER,
		POSY_TOP
	);


	createPlayersLines(renderer, font, titleLabelPos.x, incrementBtn.rect.x+incrementBtn.rect.w, colorLabel.textZone.y+colorLabel.textZone.h , nbPlayers, lines);
	
	labels[0] = &titleLabel;
	labels[1] = &nbPlayerLabel;
	labels[2] = &aiLabel;
	labels[3] = &pseudoLabel;
	labels[4] = &colorLabel;
	DecrementParams dparams= {.nbPlayers=&nbPlayers, .lines=lines, .renderer=renderer};
	decrementBtn.arg = &dparams;

	IncrementParams iparams= {.nbPlayers=&nbPlayers, .lines=lines, .minx=titleLabelPos.x, .maxx=incrementBtn.rect.x+incrementBtn.rect.w, .miny=colorLabelPos.y+colorLabel.textZone.h + 16, .font=font, .renderer=renderer};
	incrementBtn.arg = &iparams;

	buttons[0] = decrementBtn;
	buttons[1] = incrementBtn;

	InputProcessor inputProcessor = createInputProcessor();
	array_P_Button_AddElement(&inputProcessor.tabButton, incrementBtn);
	array_P_Button_AddElement(&inputProcessor.tabButton, decrementBtn);
	
	while(*generalState == GS_GameCreationMenu)
	{
		printf("%d\n", nbPlayers);
		SDL_SetRenderDrawColor(renderer, 55, 120, 175, 255);
		SDL_RenderClear(renderer);
		InputElement inputElement;
		while (InputType_None != (inputElement = proccessInput(&inputProcessor)).type) 
		{
			switch (inputElement.type)
			{
			case InputType_ActivateUI:
				switch (inputElement.data.uiAction)
				{
				case UIAction_Quit:
					*generalState = GS_MainMenu;
					break;
				case UIAction_Validate:
					break;
				case UIAction_Cancel:
					break;
				default:
					break;
				}
				break;
			case InputType_MoveGame:

				break;
			case InputType_ClickGame:

				break;
			case InputType_None:
			default:
				break;
			}
		}
		nbPlayerLabel.text[0] = nbPlayers+48;
		drawGameCreationMenu(renderer, labels, nbLabels, buttons, nbButtons, lines, nbPlayers);
		SDL_RenderPresent(renderer);
		SDL_Delay(25);	
	}

	
	
	
	//free
	freeInputProcessor(&inputProcessor);
	freeTextLabel(&titleLabel);
	freeButton(&incrementBtn);
	freeButton(&decrementBtn);
	return true;
}
