#include "engine/ButtonActions.h"
#include "engine/GeneralState.h"
#include "engine/AudioHandler.h"


void action_none(P_Button* caller) {
	//return nothing
}


void action_print(P_Button* caller) {
	printf("Button pressed\n");
}

void action_setStateToMainMenu(P_Button* caller)
{
	*((GeneralState*)caller->arg) = GS_MainMenu;
}

void action_muteSound(P_Button* caller)
{
	//Mute sound -> Master Volume = 0
	AudioHandler audioHandler = *((AudioHandler*)caller->arg);
	changeMasterVol(&audioHandler,0);

	//Change Icon -> Mute icon
	//caller->texture = createTextureFromPath(renderer,"rsrc/img/MuteResized.png");
}
