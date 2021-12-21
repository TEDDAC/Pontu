#include "view/PiecesDrawer.h"
#include "model/Island.h"


//Don't put this in model
SDL_Rect islandToRect(const SDL_Rect* boardRect, const Island island) {
	const int w = boardRect->w/9;
	const int h = boardRect->h/9;
	SDL_Rect r = {
		.x = boardRect->x + w*(island.x*2),
		.y = boardRect->y + h*(island.y*2),
		.w = w,
		.h = h
	};

	return r;
}

void drawPieces(SDL_Renderer* renderer, const SDL_Rect* boardRect, const Piece arrPieces[], const size_t nbPieces, SDL_Texture* piece) {

	for (size_t i = 0; i < nbPieces; ++i)
	{
		const SDL_Rect rDest = islandToRect(boardRect, arrPieces[i].island);
		SDL_RenderCopy(renderer, piece, NULL, &rDest);
	}
}
