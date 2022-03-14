#include "engine/ButtonActions.h"
#include "engine/GeneralState.h"
#include "engine/AudioHandler.h"
#include "engine/TextureLoader.h"

int soundMuted=0;

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
	argsSoundButton argsSoundB = *(argsSoundButton*)caller->arg;
	AudioHandler* audioHandler = argsSoundB.audio;

	//fprintf(stderr,"Sound muted = %d\n",soundMuted);

	if(!soundMuted)
	{
		changeMasterVol(audioHandler,0);
		soundMuted=1;
	}
	else
	{
		changeMasterVol(audioHandler,10);
		soundMuted=0; 
	}

	//Change Icon -> Mute icon
	SDL_DestroyTexture(caller->texture);
	caller->texture = createTextureFromPath(argsSoundB.renderer,"rsrc/img/MuteResized.png");

}
