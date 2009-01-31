#include "Game.h"

Game::Game() {

}

Game::~Game() {
	if (engine != 0) {
		delete engine;
		engine = 0;
		}
	if (state != 0) {

		delete state;
		state = 0;
	}
}

void Game::run() {
	srand(time(NULL));
    engine = new Snake_Engine(640, 480, false);
    state = new Menu_State();
    engine->set_state(state);
    engine->set_tick_interval(100);
    engine->loop();
    delete engine;
    delete state;
}

int main(int argc, char* argv[]) {
	Game game;
	game.run();

    return 0;
}
