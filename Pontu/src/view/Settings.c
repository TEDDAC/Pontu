#include "view/Settings.h"

// Local functions

typedef struct {
	TTF_Font* font;
	SDL_Texture* textures[4];
	TextLabel* labels[4];
} Components;

void reduceMasterVol(P_Button* caller) {
	AudioHandler* ah = (AudioHandler*) caller->args;
	if (ah->masterVol > 0) {
		changeMasterVol(ah,ah->masterVol - 1);
	}
}

void increaseMasterVol(P_Button* caller) {
	AudioHandler* ah = (AudioHandler*) caller->args;
	if (ah->masterVol < 10) {
		changeMasterVol(ah,ah->masterVol + 1);
	}
}

void reduceMusicVol(P_Button* caller) {
	AudioHandler* ah = (AudioHandler*) caller->args;
	if (ah->musicVol > 0) {
		changeMusicVol(ah,ah->musicVol - 10);
	}
}

void increaseMusicVol(P_Button* caller) {
	AudioHandler* ah = (AudioHandler*) caller->args;
	if (ah->musicVol < 100) {
		changeMusicVol(ah,ah->musicVol + 10);
	}
}

void reduceSFXVol(P_Button* caller) {
	AudioHandler* ah = (AudioHandler*) caller->args;
	if (ah->sfxVol > 0) {
		changeSFXVol(ah,ah->musicVol - 10);
	}
}

void increaseSFXVol(P_Button* caller) {
	AudioHandler* ah = (AudioHandler*) caller->args;
	if (ah->sfxVol < 100) {
		changeSFXVol(ah,ah->sfxVol + 10);
	}
}

void destroyView(P_Button* caller) {
	Components components = (Components) caller->args;
	TTF_CloseFont(components->font);

	for (int i = 3; i >= 0; i--) {
		if (components->textures[i] != NULL) {
			SDL_DestroyTexture(components->textures[i]);
		}
		if (components->labels[i] != NULL) {
			freeTextLabel(components->labels[i]);
		}
	}
}	

// Global functions

bool settingsView(const SDL_Renderer* renderer, AudioHandler* ah) {
	SDL_Color white = {255,255,255,255};
	SDl_Texture* textures[4];
	TextLabel* labels[4];
	SDL_Rect bg = {150,0,450,600};
	SDL_Rect title = {150,0,450,50}
	SDL_Rect masterVol = {150,50,450,100};
	SDL_Rect musicVol = {150,150,450,200};
	SDl_Rect sfxVol = {150,250,450,300};
	SDL_Point titlePoint = {150,50};
	SDL_Point masterVolPoint = {150,100};
	SDL_Point musicVolPoint = {150,200};
	SDL_Point sfxVolPoint = {150,300};
	int font_size = 50;
	int size = font_size*100/88;
	TTF_Font* font = TTF_OpenFont("../../rsrc/font/retro/retro.TTF", size);
	SDL_Color cyan = {24, 174, 219, 255};
	SDL_Color black = {0,0,0,255};
	P_Button button;
	int sizex[3];
	int sizey[3];

	textures[0] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,300,600);
	textures[1] = createGenericButtonTexture("-",font,fontSize,black,cyan,0,3,*sizex[0],*sizey[0],renderer);
	textures[2] = createGenericButtonTexture("+",font,fontSize,black,cyan,0,3,*sizex[1],*sizey[1],renderer);

	textures[3] = createGenericButtonTexture("Retour",font,fontSize,black,cyan,0,3,*sizex[2],*sizey[2],renderer);

	if (0 != SDL_SetRenderTarget(renderer,textures[0])) {
		// TODO destroyTexture
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
	SDL_RenderFillRect(renderer,&bg);

	SDL_SetRenderDrawColor(renderer, cyan.r, cyan.g, cyan.b, cyan.a); // cyan
	SDL_RenderFillRect(renderer,&title);
	SDL_RenderFillRect(renderer,&masterVol);
	SDL_RenderFillRect(renderer,&musicVol);
	SDL_RenderFillRect(renderer,&sfxVol);
	
	*labels[0] = createTextLabel("Volume",titlePoint,black,font,renderer,POSX_CENTER,POSY_CENTER);
	*labels[1] = createTextLabel("Principal",masterVolPoint,black,font,renderer,POSX_CENTER,POSY_CENTER);
	*labels[2] = createTextLabel("Musique",musicVolPoint,black,font,renderer,POSX_CENTER,POSY_CENTER);
	*labels[3] = createTextLabel("Effets spéciaux",sfxVolPoint,black,fonot,renderer,POSX_CENTER,POSY_CENTER);
	for (int i = 0; i < 3; i++) {
		drawTextLabel(renderer,labels[i],font);
	}

	button = createButton(textures[1],textures[1],150,100,sizex[0],sizey[0],&reduceMasterVol);
	button.args = (void*) ah;
	if (!drawButtonOnRenderer(button,renderer)) {
		return false;
	}
	button = createButton(textures[2],textures[2],400,100,sizex[1],sizey[1],&increaseMasterVol);
	button.args = (void*) ah;
	if (!drawButtonOnRenderer(button,renderer)) {
		return false;
	}
	button = createButton(textures[1],textures[1],150,200,sizex[0],sizey[0],&reduceMusicVol);
	button.args = (void*) ah;
	if (!drawButtonOnRenderer(button,renderer)) {
		return false;
	}
	button = createButton(textures[2],textures[2],400,200,sizex[1],sizey[1],&increaseMusicVol);
	button.args = (void*) ah;
	if (!drawButtonOnRenderer(button,renderer)) {
		return false;
	}
	button = createButton(textures[1],textures[1],150,300,sizex[0],sizey[0],&reduceSFXVol);
	button.args = (void*) ah;
	if (!drawButtonOnRenderer(button,renderer)) {
		return false;
	}
	button = createButton(textures[2],textures[2],400,300,sizex[1],sizey[1],&increaseSFXVol);
	button.args = (void*) ah;
	if (!drawButtonOnRenderer(button,renderer)) {
		return false;
	}
	button = createButton(textures[3],textures[3],150,500,sizex[2],sizey[2],&destroyView);
	Components components = {
		.font = fonts,
		.textures = textures,
		.labels = labels
	};
	button.args = (*void) components;
	if (!drawButtonOnRenderer(button,renderer)) {
		return false;
	}

	return true;
}


