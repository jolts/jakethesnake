#include "Snake.h"

Snake::Snake() {
}

Snake::~Snake() {
	// Frees our snakes surface
	if (snake_surface != 0) {
		SDL_FreeSurface(snake_surface);
		snake_surface = 0;
	}
}

int Snake::get_direction() const {
	return direction;
}

void Snake::init(int m_player) {
	rainbow = false;
	direction = 2;
	length = 3;
	x = 128;
	y = 0 + 160 * m_player; // Gives us different coordinates for our players.
	instance = m_player;
	head = true; // First part gets initalized to a head.
	for (int i = 0; i != length; i++) {
		Snake_Part snake_part;
		snake_part.is_head = head;
		snake_part.x = x;
		snake_part.y = y;
		snake_body.push_back(snake_part);
		x -= 16;
		head = false;
	}
}

void Snake::draw(SDL_Surface* screen) {
	for (unsigned int i = 0; i != snake_body.size(); i++) {
		if (snake_body[i].is_head) {
			// Loads different head pictures depending on whether its player1
			// or player2.
			if (instance == 1) {
				snake_surface = load_image("./img/player1_head.bmp");
			} else {
				snake_surface = load_image("./img/player2_head.bmp");
			}
		} else {
			if (!rainbow) {
				snake_surface = load_image("./img/player_body.bmp");
			} else {
				snake_surface = load_image("./img/player_rainbow.bmp");
			}
		}
		apply_surface(snake_body[i].x, snake_body[i].y, snake_surface, screen);
	}
}

void Snake::move(const int current_direction) {
	direction = current_direction;
	std::vector<Snake_Part*>::reverse_iterator it;
	switch (direction) {
	case 1:
		// size - 1, otherwise we'll go out of range
		for (int i = snake_body.size() - 1; i != 0; i--) {
			snake_body[i].x = snake_body[i - 1].x;
			snake_body[i].y = snake_body[i - 1].y;
		}
		snake_body[0].y -= 16; // Move the snake upwards 16 pixels
		break;
	case 2:
		for (int i = snake_body.size() - 1; i != 0; i--) {
			snake_body[i].x = snake_body[i - 1].x;
			snake_body[i].y = snake_body[i - 1].y;
		}
		snake_body[0].x += 16; // Move the snake left 16 pixels
		break;
	case 3:
		for (int i = snake_body.size() - 1; i != 0; i--) {
			snake_body[i].x = snake_body[i - 1].x;
			snake_body[i].y = snake_body[i - 1].y;
		}
		snake_body[0].y += 16; // Move the snake down 16 pixels
		break;
	case 4:
		for (int i = snake_body.size() - 1; i != 0; i--) {
			snake_body[i].x = snake_body[i - 1].x;
			snake_body[i].y = snake_body[i - 1].y;
		}
		snake_body[0].x -= 16; // Move the snake right 16 pixels
		break;
	default:
		break;
	}
}

void Snake::add_parts(const int& n) {
	for (int i = 0; i != n; i++) {
		Snake_Part snake_part;
		snake_part.is_head = false;
		// Adds any part to the back of snake
		snake_part.x = snake_body.back().x;
		snake_part.y = snake_body.back().y;
		snake_body.push_back(snake_part);
	}
}

int Snake::get_length() const {
	return length;
}

void Snake::remove_parts(const int& n) {
	for (int i = 0; i != n; i++) {
		snake_body.pop_back();
	}
}

void Snake::set_rainbow(bool flag) {
	rainbow = flag;
}

bool Snake::get_rainbow() {
	return rainbow;
}
