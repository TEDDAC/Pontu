#include "model/Player.h"

Player newPlayer(const char pseudo[PSEUDO_LENMAX], const SDL_Color color) {
	Player player;
	strcpy(player.pseudo, pseudo);
	player.color = color;
	player.rank = 0;

	return player;
}

