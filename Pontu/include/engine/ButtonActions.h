#ifndef BUTTON_ACTION_INCLUDED
#define BUTTON_ACTION_INCLUDED

#include "engine/Button.h"


void action_none(P_Button* caller);

void action_print(P_Button* caller);

/**
 * @brief Button handle which set a generalState to GS_MainMenu
 *
 * @param caller The button clicked
 */
void action_setStateToMainMenu(P_Button* caller);

#endif //BUTTON_ACTION_INCLUDED