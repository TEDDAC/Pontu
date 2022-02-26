#include <SDL2/SDL.h>
#include <stdbool.h>
#include "engine/TextLabel.h"
#include "engine/Button.h"
#include "engine/TextureLoader.h"
#include "engine/Colors.h"
#include "engine/FontUtils.h"
#include "engine/GeneralState.h"
#include "engine/InputProcessor.h"
#include "engine/Colors.h"
#include "model/Player.h"
#include "engine/TextInput.h"

#define NB_COLORS 4
#define NB_PLAYER_MAX 4


/*
bool drawGameCreationMenu(SDL_Renderer* renderer, P_Button* incrementBtn, P_Button* decrementBtn, TextLabel* nbJoueurTxtLabel, TextLabel* nbPlayerLabel);
*/

typedef struct
{
	P_Button aiButton;
	P_Button* colorButtons;
	TextInput pseudoInput;
	Player* player;
	int w;
	int h;
	int x;
	int y;
}CreateMenuLine;

typedef struct
{
	Player* p;
	PlayersColors color;
} ChangeColorParams;

typedef struct
{
	int* nbPlayers;
	TextLabel* nbPlayersLbl;
	TTF_Font* font;
	int minx;
	int maxx;
	int miny;
	CreateMenuLine* lines;
	SDL_Renderer* renderer;
	SDL_Color* bg;
}IncrementParams;

typedef struct
{
	int* nbPlayers;
	CreateMenuLine* lines;
	SDL_Renderer* renderer;
	TextLabel* nbPlayersLbl;
	SDL_Color* bg;
	TTF_Font* font;
}DecrementParams;

bool gameCreationMenu(SDL_Renderer* renderer, GeneralState* generalState, TTF_Font* font, int width, int height);
