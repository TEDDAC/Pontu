#include "view/Settings.h"
#include "engine/InputProcessor.h"
#include "engine/InputElement.h"
#include "engine/arrayTextLabel.h"
#include <SDL2/SDL.h>

// Global functions

enum nameTextLabel {TITRE, MUSIC_VOLUME, SFX_VOLUME, MASTER_VOLUME};

void createSettingsView(SDL_Window * window, SDL_Renderer* renderer, AudioHandler* ah, const FontHandler* fh, const InputProcessor * inputProcessor, struct array_TextLabel * arrayTextLabel, SDL_Texture * numberTexture) {
	TTF_Font* font = fh->fonts[FONT_PublicPixel];
	SDL_Color white = {.r = 255, .g = 255, .b = 255, .a = 255};
	int windowWidth, windowHeight;
	SDL_GetWindowSize(window, &windowWidth,&windowHeight);
	SDL_Color lightBlue = {.r = 0,.g = 195,.b = 255,.a = 0}; //0, 195, 255
	SDL_Color darkBlue = {.r = 0,.g = 123,.b = 161,.a = 0}; //0, 123, 161


	//titre;
	SDL_Point titre_point = {.x = windowWidth/2, .y = 30};
	TextLabel titre = createTextLabel("Options", &titre_point, 4,&white, font, renderer, POSX_CENTER, POSY_CENTER);
	array_TextLabel_AddElement(arrayTextLabel, titre);



	int padding_Label_Left = 20;
	//Music volume label
	SDL_Point musicVolumeLabelPoint = {.x = padding_Label_Left, .y = titre.textZone.h + 50 + titre.textZone.y};
	TextLabel musicVolumeLabel = createTextLabel("Music Volume", &musicVolumeLabelPoint, 1.5,&white, font, renderer, POSX_LEFT, POSY_CENTER);
	array_TextLabel_AddElement(arrayTextLabel, musicVolumeLabel);


	//SFX volume label
	SDL_Point sfxVolumeLabelPoint = {.x = padding_Label_Left, .y = musicVolumeLabel.textZone.h + 50 + musicVolumeLabel.textZone.y};
	TextLabel sfxVolumeLabel = createTextLabel("Effect Volume", &sfxVolumeLabelPoint, 1.5,&white, font, renderer, POSX_LEFT, POSY_CENTER);
	array_TextLabel_AddElement(arrayTextLabel, sfxVolumeLabel);


	//SFX volume label
	SDL_Point masterVolumeLabelPoint = {.x = padding_Label_Left, .y = sfxVolumeLabel.textZone.h + 50 + sfxVolumeLabel.textZone.y};
	TextLabel masterVolumeLabel = createTextLabel("Master Volume", &masterVolumeLabelPoint, 1.5,&white, font, renderer, POSX_LEFT, POSY_CENTER);
	array_TextLabel_AddElement(arrayTextLabel, masterVolumeLabel);



	//quit button
	P_Button quitButton = createButton(NULL,NULL,0, 0, 20, 20, NULL);
    quitButton.texture = createGenericButtonTexture("Quitter",font,50,darkBlue,lightBlue,5, 10,&(quitButton.rect.w),&(quitButton.rect.h),renderer);
    quitButton.hoverTexture =  createGenericButtonTexture("Quitter",font,50,lightBlue,darkBlue,5, 10,NULL,NULL,renderer);
	quitButton.rect.y = windowHeight - quitButton.rect.h - 50;
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
	drawButtonOnRenderer(renderer,&inputProcessor.tabButton.elems[0]);


	SDL_Event event;
	bool etat = true;
	while (etat) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_WINDOWEVENT:
					switch (event.window.event) {
						case SDL_WINDOWEVENT_CLOSE:
							etat = false;
							printf("Quit\n");
							fflush(stdout);
							break;
						default:
						break;
					}
					break;
			}

		}

		SDL_RenderPresent(renderer);
		SDL_Delay(20);
	}

quit:
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}
