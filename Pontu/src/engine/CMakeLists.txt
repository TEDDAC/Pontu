
set(SOURCES 
	AudioHandler.c
	Button.c
	ButtonActions.c
	ColorPicker.c
	Colors.c
	FontLoader.c
	FontUtils.c
	GameInputProcessor.c
	InputElement.c
	InputProcessor.c
	TextInput.c
	TextLabel.c
	TextureHandler.c
	TextureLoader.c
	UIElementUtils.c
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
