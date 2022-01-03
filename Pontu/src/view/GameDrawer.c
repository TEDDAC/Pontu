#include "view/GameDrawer.h"
#include "view/BoardDrawer.h"
#include "view/PiecesDrawer.h"

bool drawGame(SDL_Renderer* renderer, const SDL_Rect* windowSize, const SDL_Rect* boardRect, const Game* game,TextureHandler* textureHandler)
{
	//SDL_Texture* menuTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 50, 70);
	
	/*SDL_SetRenderTarget(renderer, menuTexture);
	SDL_SetRenderDrawColor(renderer, 150, 243, 59, 255);
	SDL_Rect buttonRect = {.x = 0,.y = 0,.w = 50,.h = 70};
	SDL_RenderFillRect(renderer, &buttonRect);
	SDL_SetRenderTarget(renderer, NULL);*/

	//P_Button menu = createButton(menuTexture, NULL, (windowSize->w*5)/100,  (windowSize->h*5)/100, 50, 70, NULL);
	//P_Button menu = createButton(menuTexture, NULL, 10, 10, 50, 70, NULL);


	drawBoard(renderer, boardRect, &(game->board), textureHandler->textures[TEXTURE_Island],  textureHandler->textures[TEXTURE_Bridge], textureHandler->textures[TEXTURE_Water]);
	drawPieces(renderer, boardRect, game->board.arrPieces, game->board.nbPieces, textureHandler->textures[TEXTURE_Piece]);

	return true;
}
