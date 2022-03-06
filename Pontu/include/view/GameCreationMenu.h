#include <SDL2/SDL.h>
#include <stdbool.h>
#include "engine/TextLabel.h"
#include "engine/Button.h"
#include "engine/TextureLoader.h"
#include "engine/Colors.h"
#include "engine/ColorPicker.h"
#include "engine/FontUtils.h"
#include "engine/GeneralState.h"
#include "engine/InputProcessor.h"
#include "model/Player.h"
#include "engine/TextInput.h"
#include "engine/AudioHandler.h"

#define NB_COLORS 4
#define NB_PLAYER_MAX 4


/*
bool drawGameCreationMenu(SDL_Renderer* renderer, P_Button* incrementBtn, P_Button* decrementBtn, TextLabel* nbJoueurTxtLabel, TextLabel* nbPlayerLabel);
*/

typedef struct
{
	P_Button aiButton;
	TextInput pseudoInput;
  ColorPicker colorPicker;
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
  bool* viewChanged;
}IncrementParams;

typedef struct
{
	int* nbPlayers;
  bool* viewChanged;
}DecrementParams;

bool gameCreationMenu(SDL_Renderer* renderer, GeneralState* generalState, AudioHandler* ah, TTF_Font* font, int width, int height, Player players[], int* nbPlayers);
