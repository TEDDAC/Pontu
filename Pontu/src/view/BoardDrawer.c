#include "view/BoardDrawer.h"
#include "view/ToRect.h"

void drawRemoveBridge(SDL_Renderer* renderer, const SDL_Rect* boardRect, SDL_Texture* water, const Coord* coordBridge) {
	const SDL_Rect destRect = coordToRect(boardRect, coordBridge);
	SDL_RenderCopy(renderer, water, NULL, &destRect);
}

bool drawFullBoard(SDL_Renderer* renderer, const SDL_Rect* boardRect, const Board* board, SDL_Texture* island, SDL_Texture* bridge, SDL_Texture* water)
{
	int h = boardRect->h / 9;
	int w = boardRect->w / 9;

	//Water (Possible to optimize)
	for (size_t y = 0; y < 9; ++y)
	{
		for (size_t x = 0; x < 9; ++x)
		{
			const SDL_Rect destRect = {
				.x = boardRect->x+x*w,
				.y = boardRect->y+y*h,
				.w = w, 
				.h = h,
			}; 
			SDL_RenderCopy(renderer, water, NULL, &destRect);
		}
	}
	

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
