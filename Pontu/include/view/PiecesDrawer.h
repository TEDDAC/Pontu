#ifndef PIECES_DRAWER_INCLUDED
#define PIECES_DRAWER_INCLUDED

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "model/Piece.h"

void drawPiecesPlayer(SDL_Renderer* renderer, const SDL_Rect* boardRect, const Piece arrPieces[], const size_t nbPieces, const size_t numPlayer, SDL_Texture* piece);

void drawMovePiece(SDL_Renderer* renderer, const SDL_Rect* boardRect, const Island* startMove, const Island* endMove, SDL_Texture* pieceTexture, SDL_Texture* islandTexture);

#endif //PIECES_DRAWER_INCLUDED

