#include "engine/ButtonActions.h"
#include "engine/GeneralState.h"


void action_none(P_Button* caller) {
}


void action_print(P_Button* caller) {
	printf("Button pressed\n");
}

void action_setStateToMainMenu(P_Button* caller)
{
	*((GeneralState*)caller->arg) = GS_MainMenu;
}
