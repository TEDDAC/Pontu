#include "view/PiecesDrawer.h"
#include "view/ToRect.h"


void drawPiecesPlayer(SDL_Renderer* renderer, const SDL_Rect* boardRect, const Piece arrPieces[], const size_t nbPieces, const size_t numPlayer, const TextureHandler* textureHandler, const PlayersColors color) {
	SDL_Texture* pieceTexture = textureHandler->textures[TEXTURE_PieceRed+color];
	for (size_t i = 0; i < nbPieces; ++i)
	{
		if (arrPieces[i].idJ == numPlayer) {
			Coord c = islandToCoord(&arrPieces[i].island);
			const SDL_Rect rDest = coordToRect(boardRect, &c);
			SDL_RenderCopy(renderer, pieceTexture, NULL, &rDest);		
		}
	}
}

void drawMovePiece(SDL_Renderer* renderer, const SDL_Rect* boardRect, const Coord* startMove, const Coord* endMove, const TextureHandler* textureHandler, const PlayersColors color) {
	SDL_Texture* pieceTexture = textureHandler->textures[TEXTURE_PieceRed+color];
	
	SDL_Rect rDest = coordToRect(boardRect, startMove);
	SDL_RenderCopy(renderer, textureHandler->textures[TEXTURE_Island], NULL, &rDest);
	
	rDest = coordToRect(boardRect, endMove);
	SDL_RenderCopy(renderer, pieceTexture, NULL, &rDest);	
}


void drawPlacePiece(SDL_Renderer* renderer, const SDL_Rect* boardRect, const TextureHandler* textureHandler, const PlayersColors color, const Coord* coordPlace) {
	SDL_Texture* pieceTexture = textureHandler->textures[TEXTURE_PieceRed+color];
	
	SDL_Rect rDest = coordToRect(boardRect, coordPlace);
	SDL_RenderCopy(renderer, pieceTexture, NULL, &rDest);
}


