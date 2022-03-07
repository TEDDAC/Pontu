
set(SOURCES 
	BoardDrawer.c
	GameCreationMenu.c
	GameInterface.c
	GameMain.c
	MainMenu.c
	MenuEndGame.c
	PiecesDrawer.c
	Settings.c
	ToRect.c
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
