#include "Gameover_State.h"

Gameover_State::Gameover_State() {

}

Gameover_State::~Gameover_State() {
}

void Gameover_State::key_pressed(SDLKey key) {
	if (key == SDLK_RETURN) { // When user presses return, we go back to menu
		get_engine()->set_state(new Menu_State());
	}
}

