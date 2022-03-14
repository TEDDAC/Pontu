#include "view/GameCreationMenu.h"

#include <SDL2/SDL_ttf.h>

void freeCreateMenuLine(CreateMenuLine* line);
CreateMenuLine createCreateMenuLine(SDL_Renderer* renderer, int xmin, int y, int xmax, TTF_Font* font, InputProcessor* inproc);
void createPlayersLines(SDL_Renderer* renderer, TTF_Font* font, int minx, int maxx, int miny,int nbPlayer, CreateMenuLine* lines, InputProcessor* inproc);
bool drawGameCreationMenu(SDL_Renderer* renderer, TextLabel* labels, int nbLabels, P_Button* buttons, int nbButtons, CreateMenuLine* lines, int nbPlayer, const SDL_Color* bg);
bool drawCreateMenuLine(SDL_Renderer* renderer, CreateMenuLine* line);
bool initializeComponentsViewCreation(SDL_Renderer* renderer, GeneralState* gs, int width, int height, TTF_Font* font, struct array_TextLabel* labels, P_Button** buttons, int* minx, int* maxx, int* minLineY, TextLabel* nbPlayerLabel, IncrementParams* iparams, DecrementParams* dparams);
void changePlayerColor(P_Button* caller);
void decrementNbPlayer(P_Button* caller);
void incrementNbPlayer(P_Button* caller);
void validateCreation(P_Button* caller);
void cancelCreation(P_Button* caller);




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
  *params->viewChanged = true;
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
	--(*nbPlayers);
  *params->viewChanged = true;
}

void changePlayerColor(P_Button* caller)
{
	ChangeColorParams* params = (ChangeColorParams*)caller->arg;
	params->p->color = params->color;
	printf("change color %d\n", params->p->color);
	fflush(stdout);
}


bool initializeComponentsViewCreation(SDL_Renderer* renderer, GeneralState* gs, int width, int height, TTF_Font* font, struct array_TextLabel* labels, P_Button** buttons, int* minx, int* maxx, int* minLineY, TextLabel* nbPlayerLabel, IncrementParams* iparams, DecrementParams* dparams)
{
	SDL_Color white = {225, 255, 255, 255};
  // TextLabel  for "Nombre de joueur.euse.s" creation
	SDL_Point titleLabelPos = {.x=width*0.05, .y=height*0.05};
	TextLabel titleLabel = createTextLabel(
		"Nombre de joueur.euse.s",
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
	}
	decrementBtn.texture = btnTexture;
	decrementBtn.hoverTexture = btnHoveredTexture;




	// Incrementation Btn creation
	P_Button incrementBtn = createButton(NULL, NULL, nbPlayerLabel->textZone.x + nbPlayerLabel->textZone.w + 8, titleLabelPos.y, 0, 0, &incrementNbPlayer);
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
	}
	incrementBtn.texture = btnTexture;
	incrementBtn.hoverTexture = btnHoveredTexture;


		P_Button cancelBtn = createButton(NULL, NULL, titleLabelPos.x, height-64, 0, 0, cancelCreation);
		btnTexture = createGenericButtonTexture("Anuler", font, 8,COLOR_GENERIC_BUTTON_BACKGROUND, COLOR_GENERIC_BUTTON_BORDER, 4, 8, &(cancelBtn.rect.w), &(cancelBtn.rect.h), renderer);
		if(btnTexture == NULL)
		{
			fprintf(stderr, "WARNING: Can't create texture: %s\n", SDL_GetError());
			return false;
		}
		btnHoveredTexture = createGenericButtonTexture("Anuler", font, 8, COLOR_GENERIC_BUTTON_BORDER, COLOR_GENERIC_BUTTON_BACKGROUND, 4, 8, &(cancelBtn.rect.w), &(cancelBtn.rect.h), renderer);
		if(btnHoveredTexture == NULL)
		{
			fprintf(stderr, "WARNING: Can't create hover texture: %s\n", SDL_GetError());
		}
		cancelBtn.texture = btnTexture;
		cancelBtn.hoverTexture = btnHoveredTexture;
		cancelBtn.arg = gs;

		P_Button validateBtn = createButton(NULL, NULL, incrementBtn.rect.x+incrementBtn.rect.w-calculateStringPixelLenght(font, "Jouer"), height-64, 0, 0, validateCreation);
		btnTexture = createGenericButtonTexture("Jouer", font, 8,COLOR_GENERIC_BUTTON_BACKGROUND, COLOR_GENERIC_BUTTON_BORDER, 4, 8, &(validateBtn.rect.w), &(validateBtn.rect.h), renderer);
		if(btnTexture == NULL)
		{
			fprintf(stderr, "WARNING: Can't create texture: %s\n", SDL_GetError());
			return false;
		}
		btnHoveredTexture = createGenericButtonTexture("Jouer", font, 8, COLOR_GENERIC_BUTTON_BORDER, COLOR_GENERIC_BUTTON_BACKGROUND, 4, 8, &(validateBtn.rect.w), &(validateBtn.rect.h), renderer);
		if(btnHoveredTexture == NULL)
		{
			fprintf(stderr, "WARNING: Can't create hover texture: %s\n", SDL_GetError());
		}
		validateBtn.texture = btnTexture;
		validateBtn.hoverTexture = btnHoveredTexture;
		validateBtn.arg = gs;
	
    // TextLabel for the number of players creation
	SDL_Point nbPlayerLabelPos = {.x=decrementBtn.rect.x+decrementBtn.rect.w+8, .y=decrementBtn.rect.y*1.5};
	  *nbPlayerLabel = createTextLabel(
		"",
		&nbPlayerLabelPos,
		1,
		&white,
		font,
		renderer,
		POSX_LEFT,
		POSY_CENTER
	);

	// AI label
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

	// Color label
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

	// Pseudo Label
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


  decrementBtn.arg = dparams;
  incrementBtn.arg = iparams;

	// Filling arrays
  array_TextLabel_AddElement(*labels, titleLabel);
  array_TextLabel_AddElement(*labels, aiLabel);
  array_TextLabel_AddElement(*labels, pseudoLabel);
  array_TextLabel_AddElement(*labels, colorLabel);
  array_TextLabel_AddElement(*labels, *nbPlayerLabel);

  *buttons[0] = decrementBtn;
  *buttons[1] = incrementBtn;
  *buttons[2] = validateBtn;
  *buttons[3] = cancelBtn;

  *minx=titleLabel.textZone.x;
  *maxx=incrementBtn.rect.x + incrementBtn.rect.w;
  *minLineY=colorLabel.textZone.y+colorLabel.textZone.h;
  return true;
}

bool drawGameCreationMenu(SDL_Renderer* renderer, TextLabel* labels, int nbLabels, P_Button* buttons, int nbButtons, CreateMenuLine* lines, int nbPlayer, const SDL_Color* bg)
{
	//Draw background (blue-ish)
	SDL_SetRenderDrawColor(renderer, bg->r, bg->g, bg->b, bg->a);
	SDL_RenderClear(renderer);

	// Buttons
	for(int i=0; i<nbButtons; ++i)
	{
		if(!drawButtonOnRenderer(renderer, &(buttons[i])))
		{
			fprintf(stderr, "WARNING: Can't draw button\n");
			return false;
		}
	}

	// TextLabels
	for(int i=0; i<nbLabels; ++i)
	{
		drawTextLabel(renderer, &labels[i]);
	}
	// Menu lines (1 for each player)
	for(int i=0; i<nbPlayer; ++i)
	{
		drawCreateMenuLine(renderer, &lines[i]);
	}
	SDL_RenderPresent(renderer);
	return true;
}


void createPlayersLines(SDL_Renderer* renderer, TTF_Font* font, int minx, int maxx, int miny,int nbPlayer, CreateMenuLine* lines, InputProcessor* inproc)
{
	for(int i=0; i<nbPlayer; ++i)
	{
		if(i==0)
		{
			// Position of first line is absolute
			lines[i] = createCreateMenuLine(renderer, minx, miny + 16, maxx,font, inproc);
		}else{
			// Position of other lines is relative to the first one (16 px (margin) + nb_lines_already_drawn * height of AI checkbox)
			lines[i] = createCreateMenuLine(renderer, minx, miny + 16 + 16 + i* lines[i-1].aiButton.rect.h, maxx,font, inproc);
		}
	}

	return;
}

bool drawCreateMenuLine(SDL_Renderer* renderer, CreateMenuLine* line)
{
	// AI checkbox
	drawButtonOnRenderer(renderer, &line->aiButton);
	// Color chooser
  drawColorPicker(renderer, line->colorPicker);
	// TextInput
	drawTextInputOnRenderer(renderer, &line->pseudoInput);
	return true;
}

void validateCreation(P_Button* caller)
{
  GeneralState* gs = (GeneralState*) caller->arg;
  *gs = GS_Game;
}
void cancelCreation(P_Button* caller)
{
  GeneralState* gs = (GeneralState*) caller->arg;
  *gs = GS_MainMenu;
}

CreateMenuLine createCreateMenuLine(SDL_Renderer* renderer, int xmin, int y, int xmax, TTF_Font* font, InputProcessor* inproc)
{
	int const wColorBtn = 32;
	int const hColorBtn = 32;
	int const colorBtnXMargin = 8;
	SDL_Texture* btnTexture, *btnTextureHover;

	P_Button* colorsBtn = (P_Button*) malloc(sizeof(P_Button)*NB_COLORS);
	P_Button ai = createButton(NULL, NULL, xmin, y, 0, 0, NULL);

	CreateMenuLine line = {.x=xmin, y};

	// AI checkbox
	SDL_Texture* aiTexture =  createGenericButtonTexture("X", font, 16, COLOR_GENERIC_BUTTON_BACKGROUND, COLOR_GENERIC_BUTTON_BORDER, 4, 8, &(ai.rect.w), &(ai.rect.h), renderer);
	SDL_Texture* aiTextureHovered =  createGenericButtonTexture("X", font, 16, COLOR_GENERIC_BUTTON_BACKGROUND, COLOR_GENERIC_BUTTON_BACKGROUND, 4, 8, &ai.rect.w, &ai.rect.h, renderer);
	line.h = ai.rect.h;
	ai.texture = aiTexture;
	ai.hoverTexture = aiTextureHovered;

	SDL_Rect rect = {.x = xmin + ai.rect.x + ai.rect.w, .y = y, .h = TTF_FontHeight(font),.w = xmax - ai.rect.w - NB_COLORS * (wColorBtn + colorBtnXMargin*2)- 16};

	// Text input of nickname
	TextInput pseudoInput;
	initTextInput(&pseudoInput, &rect, NULL, font);

	// Color chooser
	ChangeColorParams* params;
  ColorPicker picker;

	for(int i=0; i<NB_COLORS; ++i)
	{
		params = (ChangeColorParams*) malloc(sizeof(ChangeColorParams));
	  params->color=playersColors[i];
    picker.colorButtons[i] = createButton(NULL, NULL, xmax-wColorBtn*(i+1), y, wColorBtn, hColorBtn, changePlayerColor);
		picker.colorButtons[i].arg = params;
		btnTexture = createGenericButtonTexture("", font, 0, COLOR_GENERIC_BUTTON_BORDER, PLAYER_SDL_COLORS[i], 4, 8, NULL, NULL, renderer);
		btnTextureHover = createGenericButtonTexture("", font, 0, COLOR_GENERIC_BUTTON_BACKGROUND, PLAYER_SDL_COLORS[i], 4, 8, NULL, NULL, renderer);
		picker.colorButtons[i].texture = btnTexture;
		picker.colorButtons[i].hoverTexture = btnTextureHover;
		array_P_Button_AddElement(&inproc->tabButton, picker.colorButtons[i]);

	}

	// Filling struct
	line.w = picker.colorButtons[0].rect.x + picker.colorButtons[0].rect.w;
	line.aiButton=ai;
  line.colorPicker=picker;
	line.pseudoInput=pseudoInput;
	array_TextInput_AddElement(&inproc->tabTextInput, pseudoInput);
	return line;
}

void freeCreateMenuLine(CreateMenuLine* line)
{
	destroyTextInput(&line->pseudoInput);
	freeButton(&line->aiButton);
	for(int i=0; i<NB_COLORS; ++i)
	{
		free(line->colorPicker.colorButtons[i].arg);
		freeButton(&line->colorPicker.colorButtons[i]);
		// free(&line->colorButtons[i]);
	}
}

bool gameCreationMenu(SDL_Renderer* renderer, GeneralState* generalState, AudioHandler* ah, TTF_Font* font, int width, int height, Player players[], int* nbPlayers)
{
	*nbPlayers = 2;
	int nbLabel=5, nbButton=4;
  struct array_TextLabel labels = array_TextLabel_Create();
	// TextLabel labels[nbLabel];
	P_Button buttons[nbButton];
	SDL_Color bg = {55, 120, 175, 255};
	bool viewChanged = false;
	CreateMenuLine lines[NB_PLAYER_MAX];
  int minx, maxx, minLineY;
  TextLabel nbPlayerLabel;
  DecrementParams dparams= {.nbPlayers=nbPlayers, .viewChanged=&viewChanged};
  IncrementParams iparams= {.nbPlayers=nbPlayers, .viewChanged=&viewChanged};

	initializeComponentsViewCreation(renderer, generalState, width, height, font, &labels, &buttons, &minx, &maxx, &minLineY, &nbPlayerLabel, &iparams, &dparams);
	
		// Initializing InputProcessor
		InputProcessor inputProcessor = createInputProcessor();

		// Creating 2 player lines (lines with a AI checkbox, a text input for the nickname, and a color chooser)
		createPlayersLines(renderer, font, minx, maxx, minLineY , NB_PLAYER_MAX, lines, &inputProcessor);
  char nbPlayerStr[2];
	if(*nbPlayers < 0 || *nbPlayers > NB_PLAYER_MAX)
	{
		fprintf(stderr, "WARNING: The number of players has to be between 0 and %d\n", NB_PLAYER_MAX);
		return false;
	}
	nbPlayerStr[0] = *nbPlayers + 48; // ASCII code of '0' is 48 and ASSCI code of '9' is 57 (48+9)
	nbPlayerStr[1] = '\0';
  copyTextIntoTextLabel(&nbPlayerLabel, nbPlayerStr);



    for(int i=0; i<nbButton; ++i)
    {
      array_P_Button_AddElement(&inputProcessor.tabButton, buttons[i]);
    }

		// Displaying menu
		drawGameCreationMenu(renderer, labels, nbLabel, buttons, nbButton, lines, *nbPlayers, &bg);
		while(*generalState == GS_GameCreationMenu)
		{
			InputElement inputElement;
			while (InputType_None != (inputElement = proccessInput(&inputProcessor)).type)
			{
				switch (inputElement.type)
				{
					case InputType_ActivateUI:
					switch (inputElement.data.uiAction)
					{
						case UIAction_Quit:
						*generalState = GS_Quit;
						break;
						case UIAction_Validate:
						break;
						case UIAction_Cancel:
						break;
						default:
						break;
					}
					break;
					default:
					break;
				}
			}
			/*	nbPlayerLabel.text[0] = *nbPlayers+48;
			for (int i = 0; i < *nbPlayers; i++) {
			drawTextInputOnRenderer(renderer, &inputProcessor.tabTextInput.elems[i]);
		}
		*/
		if(viewChanged)
		{
			drawGameCreationMenu(renderer, labels, nbLabel, buttons, nbButton, lines, *nbPlayers, &bg);
			viewChanged=false;
		}
		SDL_Delay(20);
	}


	//free
	freeInputProcessor(&inputProcessor);
	free(buttons);
	array_TextLabel_Free(labels);


	for (size_t i=0; i<*nbPlayers; ++i) {
		freeCreateMenuLine(&lines[i]);
	}
	return true;
}
