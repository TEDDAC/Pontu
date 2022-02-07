#include "view/PiecesDrawer.h"
#include "view/ToRect.h"

void drawPiecesPlayer(SDL_Renderer* renderer, const SDL_Rect* boardRect, const Piece arrPieces[], const size_t nbPieces, const size_t numPlayer,  SDL_Texture* piece) {

	for (size_t i = 0; i < nbPieces; ++i)
	{
		if (arrPieces[i].idJ == numPlayer) {
			Coord c = islandToCoord(&arrPieces[i].island);
			const SDL_Rect rDest = coordToRect(boardRect, &c);
			SDL_RenderCopy(renderer, piece, NULL, &rDest);		
		}
	}
}

void drawMovePiece(SDL_Renderer* renderer, const SDL_Rect* boardRect, const Coord* startMove, const Coord* endMove, SDL_Texture* pieceTexture, SDL_Texture* islandTexture) {
	
	SDL_Rect rDest = coordToRect(boardRect, startMove);
	SDL_RenderCopy(renderer, islandTexture, NULL, &rDest);
	
	rDest = coordToRect(boardRect, endMove);
	SDL_RenderCopy(renderer, pieceTexture, NULL, &rDest);	
}
