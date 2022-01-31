#include "view/MainMenu.h"

void quit(struct P_button* buttonCaller){
    *((bool*)(buttonCaller->arg)) = true;
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
