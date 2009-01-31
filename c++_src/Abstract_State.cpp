#include "Abstract_State.h"

/* ------------- Abstract_State Methods ------------- */

Abstract_State::Abstract_State()
{
    this->engine = 0;
}

Abstract_State::~Abstract_State() {
	if (engine != 0) {
		engine = 0;
	}
}
void Abstract_State::set_engine(Snake_Engine* engine)
{
	this->engine=0;
    this->engine = engine;
}

Snake_Engine* Abstract_State::get_engine() const {
    return engine;
}

void Abstract_State::draw(SDL_Surface* surface)
{
}

void Abstract_State::clock_tick()
{
}

void Abstract_State::key_pressed(SDLKey key)
{
}
