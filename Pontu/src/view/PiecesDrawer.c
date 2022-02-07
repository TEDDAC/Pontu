#include "view/PiecesDrawer.h"
#include "model/Island.h"


//Don't put this in model
SDL_Rect islandToRect(const SDL_Rect* boardRect, const Island* island) {
	const int w = boardRect->w/9;
	const int h = boardRect->h/9;
	SDL_Rect r = {
		.x = boardRect->x + w*(island->x*2),
		.y = boardRect->y + h*(island->y*2),
		.w = w,
		.h = h
	};

	return r;
}

void drawPiecesPlayer(SDL_Renderer* renderer, const SDL_Rect* boardRect, const Piece arrPieces[], const size_t nbPieces, const size_t numPlayer,  SDL_Texture* piece) {

	for (size_t i = 0; i < nbPieces; ++i)
	{
		if (arrPieces[i].idJ == numPlayer) {
			const SDL_Rect rDest = islandToRect(boardRect, &arrPieces[i].island);
			SDL_RenderCopy(renderer, piece, NULL, &rDest);		
		}
	}
}

void drawMovePiece(SDL_Renderer* renderer, const SDL_Rect* boardRect, const Island* startMove, const Island* endMove, SDL_Texture* pieceTexture, SDL_Texture* islandTexture) {
	
	SDL_Rect rDest = islandToRect(boardRect, startMove);
	SDL_RenderCopy(renderer, islandTexture, NULL, &rDest);
	
	rDest = islandToRect(boardRect, endMove);
	SDL_RenderCopy(renderer, pieceTexture, NULL, &rDest);	
}
