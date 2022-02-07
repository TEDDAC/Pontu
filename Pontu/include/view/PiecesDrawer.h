#ifndef PIECES_DRAWER_INCLUDED
#define PIECES_DRAWER_INCLUDED

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "model/Piece.h"
#include "model/Coord.h"
#include "model/PlayersColors.h"
#include "engine/TextureHandler.h"

void drawPiecesPlayer(SDL_Renderer* renderer, const SDL_Rect* boardRect, const Piece arrPieces[], const size_t nbPieces, const size_t numPlayer, const TextureHandler* textureHandler, const PlayersColors color);

void drawMovePiece(SDL_Renderer* renderer, const SDL_Rect* boardRect, const Coord* startMove, const Coord* endMove, const TextureHandler* textureHandler, const PlayersColors color);


void drawPlacePiece(SDL_Renderer* renderer, const SDL_Rect* boardRect, const TextureHandler* textureHandler, const PlayersColors color, const Coord* coordPlace);

#endif //PIECES_DRAWER_INCLUDED

