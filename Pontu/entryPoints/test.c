// #include "../test/testTextureLoader.c"
// #include "../test/testFontLoader.c"
//#include "../test/testAudioHandler.c"
// #include "../test/testGenerateurTexture.c"
//#include "../test/testGameInterface.c"
//#include "../test/testConnectionMenu.c"
//#include "../test/testDrawMainMenu.c
//#include "../test/testSettingsView.c"
//#include "../test/testCreationMenu.c"
//#include "../test/testGameInterface.c"
//#include "../test/testConnectionMenu.c"
//#include "../test/testDrawMainMenu.c"
//#include "../test/testSettingsView.c"
#include "../test/testTextInputWithProcessor.c"
//#include "../test/oldMain__ThisCanBeGameMain.c"
/*
    This file is meant to be modified (used only to called other tests functions)
*/

int main(int argc, char *argv[]) {
	//testTextureLoader();
	//testAudioHandler();
	//testFontLoader();
	//testGenerateurTexture();
	testTextInputProcessor();
	//testButtonTextureLoader();
	//testConnectionMenu();
	//testMenuEndGame();
	//testButton();
	//testGameInterface();
	//testConnectionMenu();
	//testDrawMainMenu();
	//testCreationMenu();
	// testSettingsView();

	return 0;
}
