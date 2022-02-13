#include "model/PlayersColors.h"


const PlayersColors playersColors[] = {
	MACRO_FOR_EACH_PLAYER_COLOR(MACRO_GEN_ENUM_PLAYER_COLOR)
};
