
set(SOURCES 
	Board.c
	Coord.c
	Game.c
	Island.c
	IslandOrBridge.c
	Piece.c
	Player.c
	PlayersColors.c
)

target_sources(
	${PROJECT_NAME}
	PUBLIC
	${SOURCES}
)

target_sources(
	Test
	PUBLIC
	${SOURCES}
)
