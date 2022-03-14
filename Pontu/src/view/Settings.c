#include "view/Settings.h"
#include "engine/InputProcessor.h"
#include "engine/InputElement.h"
#include "engine/arrayTextLabel.h"
#include <SDL2/SDL.h>

// Global functions

enum nameTextLabel {TITRE, MUSIC_VOLUME, SFX_VOLUME, MASTER_VOLUME};
enum nameButton {MOINSVOLUME,PLUSVOLUME,MOINSSFX,PLUSSFX,MOINSMASTER,PLUSMASTER,QUIT};

void quitSettings(P_Button * caller){
	*((bool*)(caller->arg)) = false;
}

void createSettingsView(SDL_Window * window, SDL_Renderer* renderer, AudioHandler* ah, const FontHandler* fh, InputProcessor * inputProcessor, struct array_TextLabel * arrayTextLabel, SDL_Texture * numberTexture) {
	TTF_Font* font = fh->fonts[FONT_PublicPixel];
	SDL_Color white = {.r = 255, .g = 255, .b = 255, .a = 255};
	int windowWidth, windowHeight;
	SDL_GetWindowSize(window, &windowWidth,&windowHeight);
	SDL_Color lightBlue = {.r = 0,.g = 195,.b = 255,.a = 0}; //0, 195, 255
	SDL_Color darkBlue = {.r = 0,.g = 123,.b = 161,.a = 0}; //0, 123, 161

	int elementSpacing = 40;

	//titre;
	SDL_Point titre_point = {.x = windowWidth/2, .y = 30};
	TextLabel titre = createTextLabel("Options", &titre_point, 4,&white, font, renderer, POSX_CENTER, POSY_CENTER);
	array_TextLabel_AddElement(arrayTextLabel, titre);


	//+ textures
	int plusHeight, plusWidth;
	SDL_Texture * plusTexture = createGenericButtonTexture("+",font,20,darkBlue,lightBlue,3,3,&plusWidth,&plusHeight,renderer);
	SDL_Texture * plusTextureHover = createGenericButtonTexture("+",font,20,lightBlue,darkBlue,3,3,&plusWidth,&plusHeight,renderer);


	//- textures
	int moinsHeight, moinsWidth;
	SDL_Texture * moinsTexture = createGenericButtonTexture("-",font,20,darkBlue,lightBlue,3,3,&moinsWidth,&moinsHeight,renderer);
	SDL_Texture * moinsTextureHover = createGenericButtonTexture("-",font,20,lightBlue,darkBlue,3,3,&moinsWidth,&moinsHeight,renderer);


	int padding_Label_Left = 20;
	//Music volume label
	SDL_Point musicVolumeLabelPoint = {.x = padding_Label_Left, .y = titre.textZone.h + elementSpacing + titre.textZone.y};
	TextLabel musicVolumeLabel = createTextLabel("Music Volume", &musicVolumeLabelPoint, 1.5,&white, font, renderer, POSX_LEFT, POSY_CENTER);
	array_TextLabel_AddElement(arrayTextLabel, musicVolumeLabel);

	//- volume button
	P_Button moinsVolumeButton = createButton(moinsTexture,moinsTextureHover,windowWidth/2 + 100,musicVolumeLabelPoint.y - moinsHeight/2,moinsWidth,moinsHeight, NULL);
	array_P_Button_AddElement(&inputProcessor->tabButton,moinsVolumeButton);

	//+ volume button
	P_Button plusVolumeButton = createButton(plusTexture,plusTextureHover,moinsVolumeButton.rect.x + moinsVolumeButton.rect.w + 25,moinsVolumeButton.rect.y,plusWidth,plusHeight, NULL);
	array_P_Button_AddElement(&inputProcessor->tabButton,plusVolumeButton);



	//SFX volume label
	SDL_Point sfxVolumeLabelPoint = {.x = padding_Label_Left, .y = musicVolumeLabel.textZone.h + musicVolumeLabel.textZone.y + elementSpacing};
	TextLabel sfxVolumeLabel = createTextLabel("Effect Volume", &sfxVolumeLabelPoint, 1.5,&white, font, renderer, POSX_LEFT, POSY_CENTER);
	array_TextLabel_AddElement(arrayTextLabel, sfxVolumeLabel);

	//- SFX button
	P_Button moinsSFXButton = createButton(moinsTexture,moinsTextureHover,windowWidth/2 + 100,sfxVolumeLabelPoint.y - moinsHeight/2,moinsWidth,moinsHeight, NULL);
	array_P_Button_AddElement(&inputProcessor->tabButton,moinsSFXButton);

	//+ SFX button
	P_Button plusSFXButton = createButton(plusTexture,plusTextureHover,moinsSFXButton.rect.x + moinsSFXButton.rect.w + 25,sfxVolumeLabelPoint.y - moinsHeight/2,plusWidth,plusHeight, NULL);
	array_P_Button_AddElement(&inputProcessor->tabButton,plusSFXButton);




	//Master volume label
	SDL_Point masterVolumeLabelPoint = {.x = padding_Label_Left, .y = sfxVolumeLabel.textZone.h + elementSpacing + sfxVolumeLabel.textZone.y};
	TextLabel masterVolumeLabel = createTextLabel("Master Volume", &masterVolumeLabelPoint, 1.5,&white, font, renderer, POSX_LEFT, POSY_CENTER);
	array_TextLabel_AddElement(arrayTextLabel, masterVolumeLabel);

	//- master button
	P_Button moinsMasterButton = createButton(moinsTexture,moinsTextureHover,windowWidth/2 + 100,masterVolumeLabelPoint.y - moinsHeight/2,moinsWidth,moinsHeight, NULL);
	array_P_Button_AddElement(&inputProcessor->tabButton,moinsMasterButton);

	//+ master button
	P_Button plusMasterButton = createButton(plusTexture,plusTextureHover,moinsMasterButton.rect.x + moinsMasterButton.rect.w + 25,masterVolumeLabelPoint.y - moinsHeight/2,plusWidth,plusHeight, NULL);
	array_P_Button_AddElement(&inputProcessor->tabButton,plusMasterButton);




	//quit button
	P_Button quitButton = createButton(NULL,NULL,0, 0, 20, 20, quitSettings);
    quitButton.texture = createGenericButtonTexture("Quitter",font,50,darkBlue,lightBlue,5, 10,&(quitButton.rect.w),&(quitButton.rect.h),renderer);
    quitButton.hoverTexture =  createGenericButtonTexture("Quitter",font,50,lightBlue,darkBlue,5, 10,NULL,NULL,renderer);
	quitButton.rect.y = windowHeight - quitButton.rect.h - elementSpacing;
	quitButton.rect.x = windowWidth/2 - quitButton.rect.w/2;
	array_P_Button_AddElement(&inputProcessor->tabButton,quitButton);
}

void settingsView(SDL_Window* parent, AudioHandler* ah, const FontHandler* fh) {
	SDL_Window* window;
	SDL_Renderer* renderer;
	struct array_P_Button array_buttons;

	if (0 != SDL_CreateWindowAndRenderer(500,600,SDL_WINDOW_SHOWN, &window, &renderer)) {
		fprintf(stderr,"Error when trying to create window or renderer: %s\n", SDL_GetError());
		return;
	}

	if (0!=SDL_SetWindowModalFor(window, parent)) {
		fprintf(stderr,"Warning: Can't set window as modal: %s\n",SDL_GetError());
	}

	SDL_Color bg = {55, 120, 175, 255};

    SDL_SetRenderDrawColor(renderer, bg.r,bg.g,bg.b,bg.a);
	SDL_RenderClear(renderer);

	InputProcessor inputProcessor = createInputProcessor();
	struct array_TextLabel arrayTextLabel = array_TextLabel_Create();
	SDL_Texture * numberTexture[11];
	createSettingsView(window, renderer, ah, fh, &inputProcessor, &arrayTextLabel, numberTexture);


	//Title position and drawing
	drawTextLabel(renderer,&arrayTextLabel.elems[TITRE]);
	drawTextLabel(renderer,&arrayTextLabel.elems[MUSIC_VOLUME]);
	drawTextLabel(renderer,&arrayTextLabel.elems[SFX_VOLUME]);
	drawTextLabel(renderer,&arrayTextLabel.elems[MASTER_VOLUME]);


	bool etat = true;
	InputElement inputElement;

	for(int i = 0; i < inputProcessor.tabButton.size; i++){
		drawButtonOnRenderer(renderer,&inputProcessor.tabButton.elems[i]);
	}

	//arg for quit button
	inputProcessor.tabButton.elems[QUIT].arg = &etat;

	bool hasToPresent = true;

	while (etat) {
		while (InputType_None != (inputElement = proccessInput(&inputProcessor)).type) {
		 	switch (inputElement.type){
				case InputType_ButtonChanged:
					drawButtonOnRenderer(renderer,inputElement.data.buttonEvent.button);
					hasToPresent = true;
					break;
				case InputType_Window_Close:
					etat = false;
					break;
				default:
					break;
			}
			SDL_Delay(20);
		}

		if(hasToPresent){
			SDL_RenderPresent(renderer);
			hasToPresent = false;
		}
	}

quit:
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}
