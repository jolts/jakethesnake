#include "Menu_State.h"

Menu_State::Menu_State() {
	choice = 1;
	choice_y = 176; // initial y coordinate for the choice

}

Menu_State::~Menu_State() {
	Snake_Engine::free_memory(menu_screen);
	Snake_Engine::free_memory(apple);
}

void Menu_State::draw(SDL_Surface* surface) {
	menu_screen
			= Snake_Engine::load_image("./img/background_and_wall_menu.bmp");
	apple = Snake_Engine::load_image("./img/apple_menu.bmp");
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	SDL_BlitSurface(menu_screen, NULL, surface, &rect);
	rect.x = 168;
	rect.y = choice_y;
	SDL_BlitSurface(apple, NULL, surface, &rect);
}

void Menu_State::key_pressed(SDLKey key) {
	if (key == SDLK_RETURN) {
		switch (choice) {
		case 1:
			get_engine()->set_state(new Single_State()); // One player and ghost enemy
			break;
		case 2:
			get_engine()->set_state(new Multi_State()); // Two players
			break;
		case 3:
			get_engine()->set_state(new Highscore_State()); // High Score
			break;
		case 4:
			Snake_Engine::done = true; //exiting game and the main sdl loop
			break;
		default:
			break;
		}
	}
	if (key == SDLK_DOWN && choice < 4) {
		choice++;
		choice_y += 64;
	}
	if (key == SDLK_UP && choice > 1) {
		choice--;
		choice_y -= 64;
	}
}
