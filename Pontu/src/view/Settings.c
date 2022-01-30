#include "view/Settings.h"

// Global functions

bool settingsView(SDL_Renderer* renderer, AudioHandler* ah) {
    SDL_Rect bg_area = {150,0,300,600};
    SDL_Rect title_area = {150,0,300,50};
    SDL_Color white = {255,255,255,255};
    SDL_Color blue = {52,158,235,255};
    SDL_Color black = {0,0,0,255};
    SDL_Texture* bg = NULL;
    TextLabel tmp_textLabel;

    SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, 300,600);
    SDL_SetRenderTarget(renderer, bg);
    SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
    SDL_RenderFillRect(renderer,&bg_area);

    SDL_SetRenderDrawColor(renderer, blue.r, blue.g, blue.b, blue.a);
    SDL_RenderFillRect(renderer,&title_area);
    tmp_textLabel = createTextLabel("Paramètres", &((SDL_Point) {150,50}), &black,
                                    FONT_Curvilingus, renderer, POSX_CENTER, POSY_CENTER);



    SDL_RenderCopy(renderer, bg, NULL, &bg_area);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderPresent(renderer);

	return true;
}
