#include "view/Settings.h"

void onClick(P_Button* buttonCaller) {
	printf("j'ai perdu %d\n",buttonCaller->rect.x);
}

// Global functions

bool settingsView(SDL_Window* parent, AudioHandler* ah, const FontHandler* fh) {
	SDL_Window* window;
	SDL_Renderer* renderer;
	if (0 != SDL_CreateWindowAndRenderer(300,600,SDL_WINDOW_SHOWN, &window, &renderer)) {
		fprintf(stderr,"Error when trying to create window or renderer: %s\n", SDL_GetError());
		return false;
	}
	SDL_Rect title_area = {0,0,300,50};
	SDL_Point title_point = {150,25};
	SDL_Point masterVolTitle_point = {150,75};
	SDL_Color white = {255,255,255,255};
	SDL_Color blue = {52,158,235,255};
	SDL_Color black = {0,0,0,255};
	int hMinus, wMinus, hPlus, wPlus;
	TextLabel* arr_textLabel = (TextLabel*)malloc(7*sizeof(TextLabel));
	SDL_Texture** arr_textures = (SDL_Texture**)malloc(2*sizeof(SDL_Texture*));
	P_Button tmp_button;
	char tmp_str[3];

	if (arr_textLabel == NULL) {
		fprintf(stderr, "Can't allocate memory for text labels\n");
		return false;
	}

	if (arr_textures == NULL) {
		fprintf(stderr,"Can't allocate memory for button textures");
		return false;
	}

	if (0!=SDL_SetWindowModalFor(window, parent)) {
		fprintf(stderr,"Warning: Can't set window as modal: %s\n",SDL_GetError());
	}

	SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, blue.r, blue.g, blue.b, blue.a);
	SDL_RenderFillRect(renderer,&title_area);
	arr_textLabel[0] = createTextLabel("Parametres", &title_point, &black,
                                           fh->fonts[FONT_Curvilingus], renderer, POSX_CENTER, POSY_CENTER);
	drawTextLabel(renderer, &arr_textLabel[0]);

	arr_textures[0] = createGenericButtonTexture("-",fh->fonts[FONT_Curvilingus],16,black,blue, 0, 5, &wMinus, &hMinus, renderer);
	arr_textures[1] = createGenericButtonTexture("+",fh->fonts[FONT_Curvilingus],16,black,blue, 0, 5, &wPlus, &hPlus, renderer);
	
	/* Master volume */
	// Title
	arr_textLabel[1] = createTextLabel("Volume principal", &masterVolTitle_point, &black,
                                           fh->fonts[FONT_Curvilingus], renderer, POSX_CENTER, POSY_CENTER);
	drawTextLabel(renderer,&arr_textLabel[1]);

	// - button
	tmp_button = createButton(arr_textures[0], NULL, 0, arr_textLabel[1].textZone.y+arr_textLabel[1].textZone.h+20, wMinus, hMinus, onClick);
	drawButtonOnRenderer(renderer, &tmp_button);

	// + button
	tmp_button = createButton(arr_textures[1], NULL, 280, arr_textLabel[1].textZone.y+arr_textLabel[1].textZone.h+20, wPlus, hPlus, onClick);
	drawButtonOnRenderer(renderer, &tmp_button);

	// Current value
	sprintf(tmp_str, "%d", ah->masterVol);
	arr_textLabel[2] = createTextLabel(tmp_str, &((SDL_Point) {150, tmp_button.rect.y+tmp_button.rect.h/2}), &black, fh->fonts[FONT_Curvilingus], renderer, POSX_CENTER, POSY_CENTER);
	drawTextLabel(renderer, &arr_textLabel[2]);

	/* Music volume */
	// Title
	arr_textLabel[3] = createTextLabel("Volume musique", &((SDL_Point) {150, tmp_button.rect.y+tmp_button.rect.h+20}), &black,
					   fh->fonts[FONT_Curvilingus], renderer, POSX_CENTER, POSY_CENTER);
	drawTextLabel(renderer, &arr_textLabel[3]);

	// - button
	tmp_button = createButton(arr_textures[0], NULL, 0, arr_textLabel[3].textZone.y+arr_textLabel[3].textZone.h+20, wMinus, hMinus, onClick);
	drawButtonOnRenderer(renderer, &tmp_button);

	// + button
	tmp_button = createButton(arr_textures[1], NULL, 280, arr_textLabel[3].textZone.y+arr_textLabel[3].textZone.h+20, wPlus, hPlus, onClick);
	drawButtonOnRenderer(renderer, &tmp_button);

	// Current value
	sprintf(tmp_str, "%d", ah->volMusic);
	arr_textLabel[4] = createTextLabel(tmp_str, &((SDL_Point) {150, tmp_button.rect.y+tmp_button.rect.h/2}), &black, fh->fonts[FONT_Curvilingus], renderer, POSX_CENTER, POSY_CENTER);
	drawTextLabel(renderer, &arr_textLabel[4]);

	/* SFX Volume */
	// Title
	arr_textLabel[5] = createTextLabel("Volume sons", &((SDL_Point) {150, tmp_button.rect.y+tmp_button.rect.h + 20}), &black,
					   fh->fonts[FONT_Curvilingus], renderer, POSX_CENTER, POSY_CENTER);
	drawTextLabel(renderer, &arr_textLabel[5]);

	// - button
	tmp_button = createButton(arr_textures[0], NULL, 0, arr_textLabel[5].textZone.y+arr_textLabel[5].textZone.h+20, wMinus, hMinus, onClick);
	drawButtonOnRenderer(renderer, &tmp_button);

	// + button
	tmp_button = createButton(arr_textures[1], NULL, 280, arr_textLabel[5].textZone.y+arr_textLabel[5].textZone.h+20, wPlus, hPlus, onClick);
	drawButtonOnRenderer(renderer, &tmp_button);

	// Current value
	sprintf(tmp_str, "%d", ah->volSFX);
	arr_textLabel[6] = createTextLabel(tmp_str, &((SDL_Point) {150, tmp_button.rect.y+tmp_button.rect.h/2}), &black, fh->fonts[FONT_Curvilingus], renderer, POSX_CENTER, POSY_CENTER);
	drawTextLabel(renderer, &arr_textLabel[6]);


	SDL_RenderPresent(renderer);

	return true;
}

