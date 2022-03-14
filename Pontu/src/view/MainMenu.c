#include "view/MainMenu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "engine/Button.h"
#include "engine/FontLoader.h"
#include "view/MainMenu.h"
#include "engine/GeneralState.h"
#include "engine/Colors.h"

enum {NEWGAME, OPTION, QUIT};

void quit(P_Button* buttonCaller) {
    *((GeneralState*)(buttonCaller->arg)) = GS_Quit;
}

void generalStateToNewGame(P_Button* buttonCaller) {
    *((GeneralState*)(buttonCaller->arg)) = GS_GameCreationMenu;
}

P_Button* createMainMenu(SDL_Renderer* renderer,const FontHandler fontHandler, unsigned int* nb, const SDL_Rect* windowSize, GeneralState* generalState)
{
    P_Button* buttons = (P_Button*)malloc(sizeof(P_Button)*3);
    *nb = 0;
    SDL_Color lightBlue = {.r = 0,.g = 195,.b = 255,.a = 0}; //0, 195, 255
    SDL_Color darkBlue = {.r = 0,.g = 123,.b = 161,.a = 0}; //0, 123, 161

    TTF_Font* font = fontHandler.fonts[FONT_PublicPixel];

    int fontSize = 80;

    *nb = 3;
    buttons = (P_Button*)malloc(sizeof(P_Button)*(*nb));

    buttons[NEWGAME] = createButton(NULL,NULL,20, 20, 20, 20, generalStateToNewGame);

    SDL_Texture* newGameButtonTexture = createGenericButtonTexture("Nouvelle Partie",font,fontSize,darkBlue,lightBlue,5, 10,&(buttons[NEWGAME].rect.w),&(buttons[NEWGAME].rect.h),renderer);
    SDL_Texture* newGameButtonTextureHover = createGenericButtonTexture("Nouvelle Partie",font,fontSize,lightBlue,darkBlue,5, 10,NULL,NULL,renderer);

    buttons[NEWGAME].texture = newGameButtonTexture;
    buttons[NEWGAME].hoverTexture = newGameButtonTextureHover;

    buttons[NEWGAME].rect.x = (windowSize->w/2)-(buttons[NEWGAME].rect.w/2);
    buttons[NEWGAME].arg = generalState;

    buttons[OPTION] = createButton(NULL,NULL,20, buttons[NEWGAME].rect.y+buttons[NEWGAME].rect.h+20, 20, 20, NULL);

    SDL_Texture* optionButtonTexture = createGenericButtonTexture("Options",font,fontSize,darkBlue,lightBlue,5, 10,&(buttons[OPTION].rect.w),&(buttons[OPTION].rect.h),renderer);
    SDL_Texture* optionButtonTextureHover = createGenericButtonTexture("Options",font,fontSize,lightBlue,darkBlue,5, 10,NULL,NULL,renderer);

    buttons[OPTION].texture = optionButtonTexture;
    buttons[OPTION].hoverTexture = optionButtonTextureHover;
    buttons[OPTION].rect.x = (windowSize->w/2)-(buttons[OPTION].rect.w/2);

    buttons[QUIT] = createButton(NULL,NULL,20, buttons[OPTION].rect.y+buttons[OPTION].rect.h+20, 20, 20, quit);

    SDL_Texture* quitButtonTexture = createGenericButtonTexture("Quitter",font,fontSize,darkBlue,lightBlue,5, 10,&(buttons[QUIT].rect.w),&(buttons[QUIT].rect.h),renderer);
    SDL_Texture* quitButtonTextureHover = createGenericButtonTexture("Quitter",font,fontSize,lightBlue,darkBlue,5, 10,NULL,NULL,renderer);

    buttons[QUIT].texture = quitButtonTexture;
    buttons[QUIT].hoverTexture = quitButtonTextureHover;
    buttons[QUIT].rect.x = (windowSize->w/2)-(buttons[QUIT].rect.w/2);
    buttons[QUIT].arg = generalState;

	return buttons;
}

int mainMenu(SDL_Renderer * renderer,SDL_Window * window, GeneralState * generalState,FontHandler fontHandler, AudioHandler audioHandler){
    int statut = EXIT_FAILURE;


    SDL_SetRenderTarget(renderer,NULL);

    //Initialisation

    P_Button* buttons = NULL;
    unsigned int nb = 0;

    SDL_Color bg = {55, 120, 175, 255};

    SDL_SetRenderDrawColor(renderer, bg.r,bg.g,bg.b,bg.a);
    SDL_RenderClear(renderer);


    SDL_Rect windowSize = {.x = 0, .y = 0, .w = 0, .h = 0};
    SDL_GetWindowSize(window,&(windowSize.w),&(windowSize.h));
    if(!(buttons = createMainMenu(renderer,fontHandler,&nb,&windowSize, generalState))){
        fprintf(stderr, "Le menu principale ne s'est pas instancié correctement\n");
        return statut;
    }
    SDL_Event event;

    drawButtonOnRenderer(renderer,&(buttons[NEWGAME]));
    drawButtonOnRenderer(renderer,&(buttons[OPTION]));
    drawButtonOnRenderer(renderer,&(buttons[QUIT]));

    bool drawSomething = true;
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
                for (size_t i = 0; i < nb; i++) {
                    if(isHover(&(buttons[i]))){
                        buttons[i].onClick(&(buttons[i]));
                        break;
                    }
                }
                break;
            case SDL_MOUSEMOTION:
                for (size_t i = 0; i < nb; i++) {
                    switch (isButtonInteractWithCursor(&(buttons[i]),event.motion.x,event.motion.y)) {
                        case 1:
                            drawButtonOnRenderer(renderer,&(buttons[i]));
                            playSFX(SFX_menu_sound_effect, &audioHandler);
                            drawSomething = true;
                            break;
                        case 2:
                            drawButtonOnRenderer(renderer,&(buttons[i]));
                            drawSomething = true;
                            break;
                    }
                }
                break;
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_RESIZED){
                    SDL_SetRenderDrawColor(renderer, bg.r,bg.g,bg.b,bg.a);
                    SDL_RenderClear(renderer);
                    printf("Window %d resized to %dx%d\n",
                        event.window.windowID, event.window.data1,
                        event.window.data2);
                    windowSize.w = event.window.data1;
                    windowSize.h = event.window.data2;
                    for (size_t i = 0; i < nb; i++) {
                        buttons[i].rect.x = (windowSize.w/2)-(buttons[i].rect.w/2);
                        drawButtonOnRenderer(renderer,&(buttons[i]));
                    }
                    drawSomething = true;
                }
            break;
            default:
            break;
            }
        }
        if (drawSomething) {
            SDL_RenderPresent(renderer);
            drawSomething = false;
        }

        SDL_Delay(20);
    }

Quit:
    for(int i=0;i<nb;i++){
        freeButton(&(buttons[i]));
    }
    free(buttons);

    return 0;
}
