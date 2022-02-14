#include "view/Settings.h"
#include "engine/UIElementUtils.h"

#define NB_TEXT_LABEL 7
#define NB_TEXTURES 2
#define NB_BUTTONS 7 

struct volModifStruct {
	AudioHandler* ah;
	int currentVol;
	int (*changeVol) (AudioHandler* ah, int newVol);
	SDL_Renderer* renderer;
	TextLabel* volLabel;
	float sizeFactor;
	SDL_Point pos;
	TTF_Font* font;
	PositionX_Type posXType;
	PositionY_Type posYType;
};

// Local functions

void reduceVol(P_Button* buttonCaller) {
	struct volModifStruct* args = buttonCaller->arg;
	char tmp_str[4];
	SDL_Color white = {255,255,255,255};

	args->currentVol = args->changeVol(args->ah, args->currentVol - 1);

	sprintf(tmp_str, "%d", args->currentVol);
	TextLabel tmp = createTextLabel(tmp_str, &args->pos, args->sizeFactor, &args->volLabel->color,
					args->font, args->renderer, args->posXType, args->posYType);
	clearTextLabel(args->renderer, args->volLabel, args->volLabel->color);
	freeTextLabel(args->volLabel);
	drawTextLabel(args->renderer, &tmp);
	args->volLabel = &tmp;
}

void onClick(P_Button* buttonCaller) {
	printf("j'ai perdu %d\n",buttonCaller->rect.x);
}

// Global functions

RetValues drawSettingsView(SDL_Renderer* renderer, AudioHandler* ah, const FontHandler* fh) {
	RetValues retValues = { .arr_textLabel = NULL};	
	struct array_P_Button arr_buttons = array_P_Button_Create();
	SDL_Point title_point = {150,25};
	SDL_Point masterVolTitle_point = {150,75};
	SDL_Color blue = {52,158,235,255};
	SDL_Color black = {0,0,0,255};
	int hMinus, wMinus, hPlus, wPlus, wBack, hBack, tmp_posX, tmp_posY;
	TextLabel* arr_textLabel;
	struct volModifStruct* volModifTmp;

	if (NULL == (arr_textLabel = (TextLabel*)malloc(NB_TEXT_LABEL*sizeof(TextLabel)))) {
		fprintf(stderr, "Malloc error with TextLabel\n");
		return retValues;
	}
	SDL_Texture** arr_textures;
	if (NULL == (arr_textures = (SDL_Texture**)malloc(NB_TEXTURES*sizeof(SDL_Texture*)))) {
		fprintf(stderr, "Malloc error with Textures\n");
		return retValues;
	}
	char tmp_str[4];

	array_P_Button_Reserve(&arr_buttons, NB_BUTTONS);

	arr_textLabel[0] = createTextLabel("Parametres", &title_point, 2.0, &black,
                                           fh->fonts[FONT_retro], renderer, POSX_CENTER, POSY_CENTER);

	arr_textures[0] = createGenericButtonTexture("-",fh->fonts[FONT_retro],32,black,blue, 0, 5, &wMinus, &hMinus, renderer);
	arr_textures[1] = createGenericButtonTexture("+",fh->fonts[FONT_retro],32,black,blue, 0, 5, &wPlus, &hPlus, renderer);
	arr_textures[2] = createGenericButtonTexture("Retour", fh->fonts[FONT_retro],32,black,blue,0,20,&wBack,&hBack,renderer);
	
	/* Master volume */
	// Title
	arr_textLabel[1] = createTextLabel("Volume principal", &masterVolTitle_point, 1.25, &black,
                                           fh->fonts[FONT_retro], renderer, POSX_CENTER, POSY_CENTER);

	// - button
	array_P_Button_AddElement(&arr_buttons, createButton(arr_textures[0], NULL, 0, arr_textLabel[1].textZone.y+arr_textLabel[1].textZone.h+20, wMinus, hMinus, onClick));

	// + button
	array_P_Button_AddElement(&arr_buttons, createButton(arr_textures[1], NULL, 270, arr_textLabel[1].textZone.y+arr_textLabel[1].textZone.h+20, wPlus, hPlus, onClick));

	// Current value
	sprintf(tmp_str, "%d", ah->masterVol);
	tmp_posX = 150;
	tmp_posY = arr_buttons.elems[1].rect.y + arr_buttons.elems[1].rect.h/2;
	arr_textLabel[2] = createTextLabel(tmp_str, &((SDL_Point) {tmp_posX, tmp_posY}), 1.5, &black, fh->fonts[FONT_retro], renderer, POSX_CENTER, POSY_CENTER);

	// Adding actual onClick functions
	arr_buttons.elems[0].onClick = reduceVol;
	arr_buttons.elems[0].arg = &(struct volModifStruct) {
		.ah = ah,
		.currentVol = ah->masterVol,
		.changeVol = changeMasterVol,
		.renderer = renderer,
		.volLabel = &arr_textLabel[2],
		.sizeFactor = 1.5,
		.pos = (SDL_Point) {tmp_posX, tmp_posY},
		.font = fh->fonts[FONT_retro],
		.posXType = POSX_CENTER,
		.posYType = POSY_CENTER
	};
	arr_buttons.elems[1].onClick = reduceVol;
	arr_buttons.elems[1].arg = &(struct volModifStruct) {
		.ah = ah,
		.currentVol = ah->masterVol,
		.changeVol = changeMasterVol,
		.renderer = renderer,
		.volLabel = &arr_textLabel[2],
		.sizeFactor = 1.5,
		.pos = (SDL_Point) {tmp_posX, tmp_posY},
		.font = fh->fonts[FONT_retro],
		.posXType = POSX_CENTER,
		.posYType = POSY_CENTER
	};

	/* Music volume */
	// Title
	arr_textLabel[3] = createTextLabel("Volume musique", &((SDL_Point) {150, arr_buttons.elems[1].rect.y+arr_buttons.elems[1].rect.h+20}), 1.5, &black,
					   fh->fonts[FONT_retro], renderer, POSX_CENTER, POSY_CENTER);

	// - button
	array_P_Button_AddElement(&arr_buttons, createButton(arr_textures[0], NULL, 0, arr_textLabel[3].textZone.y+arr_textLabel[3].textZone.h+20, wMinus, hMinus, onClick));

	// + button
	array_P_Button_AddElement(&arr_buttons, createButton(arr_textures[1], NULL, 270, arr_textLabel[3].textZone.y+arr_textLabel[3].textZone.h+20, wPlus, hPlus, onClick));

	// Current value
	sprintf(tmp_str, "%d", ah->volMusic);
	arr_textLabel[4] = createTextLabel(tmp_str, &((SDL_Point) {150, arr_buttons.elems[3].rect.y+arr_buttons.elems[3].rect.h/2}), 1.5, &black, fh->fonts[FONT_retro], renderer, POSX_CENTER, POSY_CENTER);

	/* SFX Volume */
	// Title
	arr_textLabel[5] = createTextLabel("Volume sons", &((SDL_Point) {150, arr_buttons.elems[3].rect.y+arr_buttons.elems[3].rect.h + 20}), 1.5, &black,
					   fh->fonts[FONT_retro], renderer, POSX_CENTER, POSY_CENTER);

	// - button
	array_P_Button_AddElement(&arr_buttons, createButton(arr_textures[0], NULL, 0, arr_textLabel[5].textZone.y+arr_textLabel[5].textZone.h+20, wMinus, hMinus, onClick));

	// + button
	array_P_Button_AddElement(&arr_buttons, createButton(arr_textures[1], NULL, 270, arr_textLabel[5].textZone.y+arr_textLabel[5].textZone.h+20, wPlus, hPlus, onClick));

	// Current value
	sprintf(tmp_str, "%d", ah->volSFX);
	arr_textLabel[6] = createTextLabel(tmp_str, &((SDL_Point) {150, arr_buttons.elems[5].rect.y+arr_buttons.elems[5].rect.h/2}), 1.5, &black, fh->fonts[FONT_retro], renderer, POSX_CENTER, POSY_CENTER);

	/* Return button */
	array_P_Button_AddElement(&arr_buttons, createButton(arr_textures[2], NULL, 150 - wBack/2, arr_buttons.elems[5].rect.y+arr_buttons.elems[5].rect.h + 20, wBack, hBack, onClick));

	retValues.arr_buttons = arr_buttons;
	retValues.arr_textLabel = arr_textLabel;

	return retValues;
	
}

void settingsView(SDL_Window* parent, AudioHandler* ah, const FontHandler* fh) {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Color white = {255,255,255,255};
	SDL_Color blue = {52,158,235,255};
	SDL_Rect title_area = {0,0,300,50};
	RetValues retValues;
	struct array_P_Button array_buttons;
	bool stayInLoop = true;
	SDL_Event event;

	if (0 != SDL_CreateWindowAndRenderer(300,600,SDL_WINDOW_SHOWN, &window, &renderer)) {
		fprintf(stderr,"Error when trying to create window or renderer: %s\n", SDL_GetError());
		return;
	}

	if (0!=SDL_SetWindowModalFor(window, parent)) {
		fprintf(stderr,"Warning: Can't set window as modal: %s\n",SDL_GetError());
	}

	SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, blue.r, blue.g, blue.b, blue.a);
	SDL_RenderFillRect(renderer,&title_area);

	retValues = drawSettingsView(renderer,ah,fh);

	for (size_t i = 0; i < retValues.arr_buttons.size; i++) {
		drawButtonOnRenderer(renderer, &(retValues.arr_buttons.elems[i]));
	}
	
	for (size_t i = 0; i < NB_TEXT_LABEL; i++) {
		drawTextLabel(renderer, &retValues.arr_textLabel[i]);
	}

	while (stayInLoop) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_WINDOWEVENT:
					switch (event.window.event) {
						case SDL_WINDOWEVENT_CLOSE:
							stayInLoop = false;
							printf("Quit\n");
							fflush(stdout);
							break;
						default:
						break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					printf("MOUSEBUTTONUP\n");
					for (int i = 0; i < NB_BUTTONS; i++) {
						printf("%d\n",i);
						if (isButtonInteractWithCursor(&(retValues.arr_buttons.elems[i]),event.button.x,event.button.y)) {
							printf("isHover\n");
							retValues.arr_buttons.elems[i].onClick(&(retValues.arr_buttons.elems[i]));
							fflush(stdout);
							break;
						}
					}
					break;
				default:
				break;	
			}

		}

		SDL_RenderPresent(renderer);
		SDL_Delay(20);
	}
}

