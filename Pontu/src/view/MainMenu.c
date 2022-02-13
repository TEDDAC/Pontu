#include "view/MainMenu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "engine/Button.h"
#include "engine/FontLoader.h"
#include "view/MainMenu.h"
#include "engine/GeneralState.h"

void quit(P_Button* buttonCaller) {
    *((GeneralState*)(buttonCaller->arg)) = GS_Quit;
}

void generalStateToNewGame(P_Button* buttonCaller) {
    *((GeneralState*)(buttonCaller->arg)) = GS_GameCreationMenu;
}

P_Button* drawMainMenu(SDL_Renderer* renderer,const FontHandler fontHandler, unsigned int* nb, const SDL_Rect* windowSize, GeneralState* generalState)
{
    P_Button* buttons = (P_Button*)malloc(sizeof(P_Button)*3);
    *nb = 0;
    SDL_Color lightBlue = {.r = 0,.g = 195,.b = 255,.a = 0}; //0, 195, 255
    SDL_Color darkBlue = {.r = 0,.g = 123,.b = 161,.a = 0}; //0, 123, 161

    SDL_SetRenderTarget(renderer, NULL);
    TTF_Font* font = fontHandler.fonts[FONT_retro];

    int fontSize = 80;

    *nb = 3;
    buttons = (P_Button*)malloc(sizeof(P_Button)*(*nb));

    buttons[0] = createButton(NULL,NULL,20, 20, 20, 20, generalStateToNewGame);

    SDL_Texture* newGameButtonTexture = createGenericButtonTexture("Nouvelle Partie",font,fontSize,darkBlue,lightBlue,5, 10,&(buttons[0].rect.w),&(buttons[0].rect.h),renderer);
    SDL_Texture* newGameButtonTextureHover = createGenericButtonTexture("Nouvelle Partie",font,fontSize,lightBlue,darkBlue,5, 10,NULL,NULL,renderer);

    buttons[0].texture = newGameButtonTexture;
    buttons[0].hoverTexture = newGameButtonTextureHover;

    buttons[0].rect.x = (windowSize->w/2)-(buttons[0].rect.w/2);
    buttons[0].arg = generalState;

    buttons[1] = createButton(NULL,NULL,20, buttons[0].rect.y+buttons[0].rect.h+20, 20, 20, NULL);

    SDL_Texture* optionButtonTexture = createGenericButtonTexture("Options",font,fontSize,darkBlue,lightBlue,5, 10,&(buttons[1].rect.w),&(buttons[1].rect.h),renderer);
    SDL_Texture* optionButtonTextureHover = createGenericButtonTexture("Options",font,fontSize,lightBlue,darkBlue,5, 10,NULL,NULL,renderer);

    buttons[1].texture = optionButtonTexture;
    buttons[1].hoverTexture = optionButtonTextureHover;
    buttons[1].rect.x = (windowSize->w/2)-(buttons[1].rect.w/2);

    buttons[2] = createButton(NULL,NULL,20, buttons[1].rect.y+buttons[1].rect.h+20, 20, 20, quit);

    SDL_Texture* quitButtonTexture = createGenericButtonTexture("Quitter",font,fontSize,darkBlue,lightBlue,5, 10,&(buttons[2].rect.w),&(buttons[2].rect.h),renderer);
    SDL_Texture* quitButtonTextureHover = createGenericButtonTexture("Quitter",font,fontSize,lightBlue,darkBlue,5, 10,NULL,NULL,renderer);

    buttons[2].texture = quitButtonTexture;
    buttons[2].hoverTexture = quitButtonTextureHover;
    buttons[2].rect.x = (windowSize->w/2)-(buttons[2].rect.w/2);
    buttons[2].arg = generalState;


    SDL_SetRenderTarget(renderer,NULL);
    SDL_RenderPresent(renderer);
	return buttons;
}

int mainMenu(SDL_Renderer * renderer,SDL_Window * window, GeneralState * generalState,FontHandler fontHandler, AudioHandler audioHandler){
    int statut = EXIT_FAILURE;

    char* path = "../rsrc/img/Lenna.png";
    SDL_SetRenderTarget(renderer,NULL);
    SDL_Texture* picture = createTextureFromPath(renderer, path);
    //Initialisation

    P_Button* buttons = NULL;
    unsigned int nb = 0;

    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, picture, NULL, NULL);

    SDL_Rect windowSize = {.x = 0, .y = 0, .w = 0, .h = 0};
    SDL_GetWindowSize(window,&(windowSize.w),&(windowSize.h));
    if(!(buttons = drawMainMenu(renderer,fontHandler,&nb,&windowSize, generalState))){
        fprintf(stderr, "Le menu principale ne s'est pas déssiné correctement\n");
        return statut;
    }
    SDL_Event event;

    drawButtonOnRenderer(renderer,&(buttons[0]));
    drawButtonOnRenderer(renderer,&(buttons[1]));
    drawButtonOnRenderer(renderer,&(buttons[2]));

    while(*generalState == GS_MainMenu)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                *generalState = GS_Quit;
                break;
            case SDL_MOUSEBUTTONUP:
                if(isHover(&(buttons[2]))){
                    buttons[2].onClick(&(buttons[2]));
                    break;
                }
                if(isHover(&(buttons[0]))){
                    buttons[0].onClick(&(buttons[0]));
                    break;
                }
                break;
            case SDL_MOUSEMOTION:
                switch (isButtonInteractWithCursor(&(buttons[0]),event.motion.x,event.motion.y)) {
                    case 1:
                        drawButtonOnRenderer(renderer,&(buttons[0]));
                        playSFX(SFX_menu_sound_effect, audioHandler);
                        break;
                    case 2:
                        drawButtonOnRenderer(renderer,&(buttons[0]));
                        break;
                }
                switch (isButtonInteractWithCursor(&(buttons[1]),event.motion.x,event.motion.y)) {
                    case 1:
                        drawButtonOnRenderer(renderer,&(buttons[1]));
                        playSFX(SFX_menu_sound_effect, audioHandler);
                        break;
                    case 2:
                        drawButtonOnRenderer(renderer,&(buttons[1]));
                        break;
                }
                switch (isButtonInteractWithCursor(&(buttons[2]),event.motion.x,event.motion.y)) {
                    case 1:
                        drawButtonOnRenderer(renderer,&(buttons[2]));
                        playSFX(SFX_menu_sound_effect, audioHandler);
                        break;
                    case 2:
                        drawButtonOnRenderer(renderer,&(buttons[2]));
                        break;
                }
                break;
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_RESIZED){
                    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, picture, NULL, NULL);
                    printf("Window %d resized to %dx%d\n",
                        event.window.windowID, event.window.data1,
                        event.window.data2);
                    windowSize.w = event.window.data1;
                    windowSize.h = event.window.data2;
                    buttons[0].rect.x = (windowSize.w/2)-(buttons[0].rect.w/2);
                    buttons[1].rect.x = (windowSize.w/2)-(buttons[1].rect.w/2);
                    buttons[2].rect.x = (windowSize.w/2)-(buttons[2].rect.w/2);
                }
            break;
            default:
                break;
            }
        }
        SDL_RenderPresent(renderer);

        SDL_Delay(20);
    }

Quit:
    for(int i=0;i<nb;i++){
        freeButton(&(buttons[i]));
    }
    free(buttons);

    return 0;
}
