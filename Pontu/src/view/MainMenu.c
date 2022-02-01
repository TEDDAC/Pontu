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

P_Button* drawMainMenu(SDL_Renderer* renderer,const FontHandler fontHandler, unsigned int* nb, const SDL_Rect* windowSize)
{
    P_Button* buttons = (P_Button*)malloc(sizeof(P_Button)*3);
    *nb = 0;
    SDL_Color lightBlue = {.r = 0,.g = 195,.b = 255,.a = 0}; //0, 195, 255
    SDL_Color darkBlue = {.r = 0,.g = 123,.b = 161,.a = 0}; //0, 123, 161
    char* path = "../rsrc/img/Lenna.png";

    SDL_SetRenderTarget(renderer, NULL);
    TTF_Font* font = fontHandler.fonts[FONT_retro];

    int fontSize = 80;

    *nb = 3;
    buttons = (P_Button*)malloc(sizeof(P_Button)*(*nb));

    buttons[0] = createButton(NULL,NULL,20, 20, 20, 20, NULL);

    SDL_Texture* newGameButtonTexture = createGenericButtonTexture("Nouvelle Partie",font,fontSize,darkBlue,lightBlue,5, 10,&(buttons[0].rect.w),&(buttons[0].rect.h),renderer);
    SDL_Texture* newGameButtonTextureHover = createGenericButtonTexture("Nouvelle Partie",font,fontSize,lightBlue,darkBlue,5, 10,NULL,NULL,renderer);

    buttons[0].texture = newGameButtonTexture;
    buttons[0].hoverTexture = newGameButtonTextureHover;

    buttons[0].rect.x = (windowSize->w/2)-(buttons[0].rect.w/2);

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


    SDL_SetRenderTarget(renderer,NULL);
    SDL_Texture* picture = createTextureFromPath(renderer, path);
    SDL_RenderCopy(renderer, picture, NULL, NULL);
    SDL_RenderPresent(renderer);
	return buttons;
}

int mainMenu(SDL_Renderer * renderer,SDL_Window * window, GeneralState * generalState,FontHandler fontHandler){
    int statut = EXIT_FAILURE;
    char* path = "../rsrc/img/Lenna.png";
    //Initialisation

    P_Button* buttons = NULL;
    unsigned int nb = 0;

    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderClear(renderer);

    SDL_Rect rect = {.x = 0, .y = 0, .w = 0, .h = 0};
    SDL_GetWindowSize(window,&(rect.w),&(rect.h));
    if(!(buttons = drawMainMenu(renderer,fontHandler,&nb,&rect))){
        fprintf(stderr, "Le menu principale ne s'est pas déssiné correctement\n");
        return statut;
    }
    SDL_Event event;
    buttons[2].arg = generalState;
    while(*generalState != GS_Quit)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                *generalState = GS_Quit;
                break;
            case SDL_MOUSEBUTTONUP:
                if(isHover(buttons,event.button.x,event.button.y))
                    printf("Nouvelle partie\n");
                if(isHover(&(buttons[2]),event.motion.x,event.motion.y)){
                    buttons[2].onClick(&(buttons[2]));
                    break;
                }
                break;
            case SDL_MOUSEMOTION:
                isHover(&(buttons[0]),event.motion.x,event.motion.y);
                isHover(&(buttons[1]),event.motion.x,event.motion.y);
                isHover(&(buttons[2]),event.motion.x,event.motion.y);
                break;
            default:
                break;
            }
        }
        drawButtonOnRenderer(renderer,&(buttons[0]));
        drawButtonOnRenderer(renderer,&(buttons[1]));
        drawButtonOnRenderer(renderer,&(buttons[2]));
        SDL_RenderPresent(renderer);

        SDL_Delay(20);
    }

    return 0;
}
