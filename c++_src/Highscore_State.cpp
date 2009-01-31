#include "Highscore_State.h"

Highscore_State::Highscore_State() {
	// Assign the highscore file to a list variable
	high_score_list = read_and_evaluate();
	draw_highscreen();
}

Highscore_State::~Highscore_State() {
	Snake_Engine::free_memory(highscore_screen);
	Snake_Engine::free_memory(number);
}

void Highscore_State::draw(SDL_Surface* surface) {
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	SDL_BlitSurface(highscore_screen, NULL, surface, &rect);
	Snake_Engine::free_memory(surface); //retrieve memory from surface
}
void Highscore_State::key_pressed(SDLKey key) {
	if (key == SDLK_RETURN) {
		// Manipulate the row player_row
		// remove the last two chars in the list
		// save the file. Is only run when pressing enter.
		std::ofstream output;
		output.open("high_score.txt");
		unsigned int i = 1;
		for (std::list<std::string>::iterator it = high_score_list.begin(); it
				!= high_score_list.end(); it++) {
			if (player_row == i) { // If the current player row is found
				std::string player_line = (*it);
				player_line = player_line.substr(0, player_line.length() - 2);
				output << player_line << std::endl;
			} else {
				output << *it << std::endl;
			}
			i++;
		}
		output.close();
		get_engine()->set_state(new Menu_State());
	}
}

std::list<std::string> Highscore_State::read_and_evaluate() {
	// Takes all the scores in file and outputs it to a stl list
	std::string filename = "high_score.txt";
	std::string scores;
	std::ifstream input;
	std::list<std::string> high_score_list;
	input.open(filename.c_str(), std::ifstream::in);
	while (input >> scores) {
		high_score_list.push_back(scores);
	}
	input.close();
	return high_score_list;
}

void Highscore_State::draw_highscreen() {
	highscore_screen = Snake_Engine::load_image(
			"./img/background_and_wall_high.bmp");
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	unsigned int current_row = 0; // The row its reading at
	rect.y = 59;
	for (std::list<std::string>::iterator it = high_score_list.begin(); it
			!= high_score_list.end(); it++) {
		rect.y += 64;
		rect.x = 224;
		std::string s = (*it);
		current_row++; // Goes to next line
		for (unsigned int i = 0; i != (*it).size(); i++) {
			rect.x += 32;
			if (s[i] == '.') {
				int temp_x = rect.x;
				int temp_y = rect.y;
				player_row = current_row; // If the player scores this row
				number = Snake_Engine::load_image("./img/apple_menu.bmp");
				rect.x = 224;
				rect.y += 13;
				SDL_BlitSurface(number, NULL, highscore_screen, &rect);
				rect.x = temp_x;
				rect.y = temp_y;
				rect.x -= 32;
				i++;
				// For every number we apply the image and blit the surface
			} else if (s[i] == '1') {
				number = Snake_Engine::load_image("./img/high_1.bmp");
				SDL_BlitSurface(number, NULL, highscore_screen, &rect);
			} else if (s[i] == '2') {
				number = Snake_Engine::load_image("./img/high_2.bmp");
				SDL_BlitSurface(number, NULL, highscore_screen, &rect);
			} else if (s[i] == '3') {
				number = Snake_Engine::load_image("./img/high_3.bmp");
				SDL_BlitSurface(number, NULL, highscore_screen, &rect);
			} else if (s[i] == '4') {
				number = Snake_Engine::load_image("./img/high_4.bmp");
				SDL_BlitSurface(number, NULL, highscore_screen, &rect);
			} else if (s[i] == '5') {
				number = Snake_Engine::load_image("./img/high_5.bmp");
				SDL_BlitSurface(number, NULL, highscore_screen, &rect);
			} else if (s[i] == '6') {
				number = Snake_Engine::load_image("./img/high_6.bmp");
				SDL_BlitSurface(number, NULL, highscore_screen, &rect);
			} else if (s[i] == '7') {
				number = Snake_Engine::load_image("./img/high_7.bmp");
				SDL_BlitSurface(number, NULL, highscore_screen, &rect);
			} else if (s[i] == '8') {
				number = Snake_Engine::load_image("./img/high_8.bmp");
				SDL_BlitSurface(number, NULL, highscore_screen, &rect);
			} else if (s[i] == '9') {
				number = Snake_Engine::load_image("./img/high_9.bmp");
				SDL_BlitSurface(number, NULL, highscore_screen, &rect);
			} else if (s[i] == '0') {
				number = Snake_Engine::load_image("./img/high_0.bmp");
				SDL_BlitSurface(number, NULL, highscore_screen, &rect);
			}
		}
		rect.x += 32;
		number = Snake_Engine::load_image("./img/high_p.bmp");
		SDL_BlitSurface(number, NULL, highscore_screen, &rect);
	}
}
