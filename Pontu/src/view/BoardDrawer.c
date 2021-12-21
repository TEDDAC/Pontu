#include "view/BoardDrawer.h"


bool drawBoard(SDL_Renderer* renderer, const SDL_Rect* boardRect, const Board* board, SDL_Texture* island, SDL_Texture* bridge, SDL_Texture* water)
{
	int h = boardRect->h / 9;
	int w = boardRect->w / 9;

	SDL_RenderCopy(renderer, water, NULL, boardRect);

	//Islands
	for (int y=0; y<9; y+=2) {
		for (int x=0; x<9; x+=2) {
			const SDL_Rect destRect = {
				.x = boardRect->x+x*w, 
				.y = boardRect->y+y*h,
				.w = w, 
				.h = h,
			}; 
			SDL_RenderCopy(renderer, island, NULL, &destRect);
		}
	}

	//HBridge
	for (int y=0; y<5; ++y) {
		for (int x=0; x<4; ++x) {
			if (board->hBridges[y][x]) {
				const SDL_Rect destRect = {
					.x = boardRect->x+w+x*w*2, 
					.y = boardRect->y+y*h*2,
					.w = w, 
					.h = h,
				}; 
				SDL_RenderCopy(renderer, bridge, NULL, &destRect);
			}
		}
	}

	//VBridge
	for (int y=0; y<4; ++y) {
		for (int x=0; x<5; ++x) {
			if (board->vBridges[y][x]) {
				const SDL_Rect destRect = {
					.x = boardRect->x+x*w*2, 
					.y = boardRect->y+h+y*h*2,
					.w = w, 
					.h = h,
				}; 
				SDL_RenderCopyEx(renderer, bridge, NULL, &destRect, 90.0, NULL, SDL_FLIP_NONE);
			}
		}
	}

	return true;
}
