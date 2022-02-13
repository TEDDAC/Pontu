#ifndef PLAYERS_COLORS_INCLUDED
#define PLAYERS_COLORS_INCLUDED


#define MACRO_FOR_EACH_PLAYER_COLOR(M) \
	M(Red) \
	M(Violet) \
	M(Blue) \
	M(Yellow) 

#define MACRO_GEN_ENUM_PLAYER_COLOR(Elem) Player##Elem,

typedef enum {
	MACRO_FOR_EACH_PLAYER_COLOR(MACRO_GEN_ENUM_PLAYER_COLOR)
	NB_PLAYER_COLORS
} PlayersColors;

extern const PlayersColors playersColors[];

#endif //PLAYERS_COLORS_INCLUDED
