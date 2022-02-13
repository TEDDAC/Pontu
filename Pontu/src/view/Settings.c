#include "view/Settings.h"

#define NB_TEXT_LABEL 7
#define NB_TEXTURES 2
#define NB_BUTTONS 7 

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
	int hMinus, wMinus, hPlus, wPlus, wBack, hBack;
	TextLabel* arr_textLabel;
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
	arr_textLabel[2] = createTextLabel(tmp_str, &((SDL_Point) {150, arr_buttons.elems[1].rect.y+arr_buttons.elems[1].rect.h/2}), 1.5, &black, fh->fonts[FONT_retro], renderer, POSX_CENTER, POSY_CENTER);

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

	retValues = drawSettingsView(renderer,ah,fh, &textLabels);

	for (size_t i = 0; i < retValues.arr_buttons.size; i++) {
		drawButtonOnRenderer(renderer, &(retValues.arr_buttons.elems[i]));
	}
	
	for (size_t i = 0; i < NB_TEXT_LABEL; i++) {
		drawTextLabel(renderer, &retValues.arr_extLabels[i]);
	}


	SDL_RenderPresent(renderer);
}

