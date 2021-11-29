#include "model/Player.h"

Player newPlayer(char      pseudo[PSEUDO_LENMAX],
                 SDL_Color color) {
	Player player;
	strcpy(player.pseudo, pseudo);
	player.color = color;
	player.rank = 0;
}

