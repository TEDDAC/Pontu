#include "model/Player.h"

Player newPlayer(const char pseudo[PSEUDO_LENMAX], const PlayersColors color) {
	Player player;
	strcpy(player.pseudo, pseudo);
	player.color = color;
	player.rank = 0;
	player.eliminationTurn = 0;

	return player;
}

