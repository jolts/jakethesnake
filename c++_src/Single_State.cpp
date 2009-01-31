#include "Single_State.h"

Single_State::Single_State() {

	pacman_is_alive = true;

	player1.init(1);

	apple = Obstacles(Snake_Engine::load_image("./img/apple.bmp"));
	carrot = Obstacles(Snake_Engine::load_image("./img/carrot.bmp"));
	pacman = Obstacles(Snake_Engine::load_image("./img/pac.bmp"));
	ghost = Obstacles(Snake_Engine::load_image("./img/ghost.bmp"));

	// Spawns 10 apples.
	// Get a random position until we find a free one.
	for (int i = 0; i != 10; i++) {
		do {
			sprite_x = get_engine()->rand_x();
			sprite_y = get_engine()->rand_y();
		} while (!is_free(sprite_x, sprite_y));
		apple.x = sprite_x;
		apple.y = sprite_y;
		apples.push_back(apple);
	}
	apple_tick = 0;

	// Tries to find a free coordinate for the ghost sprite.
	do {
		sprite_x = get_engine()->rand_x();
		sprite_y = get_engine()->rand_y();
	} while (!is_free(sprite_x, sprite_y));
	ghost.x = sprite_x;
	ghost.y = sprite_y;
	ghost_tick = 0;

	// Tries to find a free coordinate for the pacman sprite.
	do {
		sprite_x = get_engine()->rand_x();
		sprite_y = get_engine()->rand_y();
	} while (!is_free(sprite_x, sprite_y));
	pacman.x = sprite_x;
	pacman.y = sprite_y;
	pacman_tick = 0;

	// Spawns 10 carrots and get a random coordinate for them.
	for (int i = 0; i != 25; i++) {
		do {
			sprite_x = get_engine()->rand_x();
			sprite_y = get_engine()->rand_y();
		} while (!is_free(sprite_x, sprite_y));
		carrot.x = sprite_x;
		carrot.y = sprite_y;
		rotten_carrots.push_back(carrot);
	}
	carrot_tick = 0;

	green_background.x = 16;
	green_background.y = 16;
	green_background.w = 608;
	green_background.h = 448;

	finished = false;

	// Sets the initial direction to right
	p1dir = 2;

	p1points = 0;

	// Everytime a event happens that increases size, 3 parts are added.
	p1parts_to_add = 3;
}

Single_State::~Single_State() {
}

void Single_State::key_pressed(SDLKey key) {
	switch (key) {
	case SDLK_UP:
		// The != handles that there isnt a opposite direction
		// that for ex, if he's going up he cant go down.
		if (player1.get_direction() != 3) {
			p1dir = 1;
		}
		break;
	case SDLK_RIGHT:
		if (player1.get_direction() != 4) {
			p1dir = 2;
		}
		break;
	case SDLK_DOWN:
		if (player1.get_direction() != 1) {
			p1dir = 3;
		}
		break;
	case SDLK_LEFT:
		if (player1.get_direction() != 2) {
			p1dir = 4;
		}
		break;
	default:
		break;
	}
}

void Single_State::clock_tick() {
	player1.move(p1dir);

	check_collisions();

	if (p1parts_to_add != 0) {
		// If theres body to add, add one
		player1.add_parts(1);
		p1parts_to_add--;
	}

	move_carrot();
	move_apple();
	move_ghost();
	move_pacman();
}

void Single_State::draw(SDL_Surface* surface) {
	// Draws all the sprites for single player.
	Snake_Engine::free_memory(surface);
	SDL_FillRect(surface, &green_background, SDL_MapRGB(surface->format, 0x61,
			0xAD, 0x2F));

	player1.draw(surface);

	// Draw carrots
	std::vector<Obstacles>::iterator it;
	for (it = rotten_carrots.begin(); it != rotten_carrots.end(); it++) {
		(*it).draw(surface);
	}

	// Draw apples
	for (std::vector<Obstacles>::iterator it = apples.begin(); it
			!= apples.end(); it++) {
		(*it).draw(surface);
	}

	ghost.draw(surface);

	if (pacman_is_alive) {
		pacman.draw(surface);
	}

	if (finished) {
		SDL_Delay(2000);
		high_score(p1points);
		get_engine()->set_state(new Highscore_State());
	}
}

void Single_State::check_collisions() {
	// Defines temporary sprite x,y coordinates.
	int sprite_x, sprite_y;

	if (collision_handler.is_wall_collision(player1.snake_body[0],
			&green_background)) {
		finished = true;
	}

	if (collision_handler.is_self_snake_collision(player1.snake_body)) {
		finished = true;
	}

	if (collision_handler.is_obstacles_collision(player1.snake_body, ghost)) {
		if (player1.snake_body.size() == 2) {
			finished = true;
		} else {
			player1.remove_parts((player1.snake_body.size() / 2));
			do {
				sprite_x = get_engine()->rand_x();
				sprite_y = get_engine()->rand_y();
			} while (!is_free_ghost(sprite_x, sprite_y));
			ghost.x = sprite_x;
			ghost.y = sprite_y;
		}
		player1.set_rainbow(false);
		p1points -= 15;
	}

	for (std::vector<Obstacles>::iterator it = rotten_carrots.begin(); it
			!= rotten_carrots.end(); it++) {
		if (collision_handler.is_obstacles_collision(player1.snake_body, (*it))) {
			if (player1.snake_body.size() == 2) {
				finished = true;
			} else {
				player1.remove_parts((player1.snake_body.size() / 3));
				do {
					sprite_x = get_engine()->rand_x();
					sprite_y = get_engine()->rand_y();
				} while (!is_free(sprite_x, sprite_y));
				(*it).x = sprite_x;
				(*it).y = sprite_y;
			}
			player1.set_rainbow(false);
			p1points -= 10;
		}
	}

	for (std::vector<Obstacles>::iterator it = apples.begin(); it
			!= apples.end(); it++) {
		if (collision_handler.is_obstacles_collision(player1.snake_body, (*it))) {
			if (player1.get_rainbow() == true) {
				p1points += 10;
			} else {
				p1points += 5;
			}
			p1parts_to_add += 3;
			do {
				sprite_x = get_engine()->rand_x();
				sprite_y = get_engine()->rand_y();
			} while (!is_free(sprite_x, sprite_y));
			(*it).x = sprite_x;
			(*it).y = sprite_y;
		}
	}

	for (std::vector<Obstacles>::iterator it = apples.begin(); it
			!= apples.end(); it++) {
		if ((*it).x == ghost.x && (*it).y == ghost.y) {
			do {
				sprite_x = get_engine()->rand_x();
				sprite_y = get_engine()->rand_y();
			} while (!is_free(sprite_x, sprite_y));
			(*it).x = sprite_x;
			(*it).y = sprite_y;
		}
	}

	for (std::vector<Obstacles>::iterator it = rotten_carrots.begin(); it
			!= rotten_carrots.end(); it++) {
		if ((*it).x == ghost.x && (*it).y == ghost.y) {
			do {
				sprite_x = get_engine()->rand_x();
				sprite_y = get_engine()->rand_y();
			} while (!is_free(sprite_x, sprite_y));
			(*it).x = sprite_x;
			(*it).y = sprite_y;
		}
	}

	if (collision_handler.is_obstacles_collision(player1.snake_body, pacman)) {
		player1.set_rainbow(true);
		p1points += 25;
		pacman.x = -16;
		pacman.y = -16;
		pacman_is_alive = false;
	}
}
bool Single_State::is_free(int x, int y) {
	std::vector<Obstacles>::iterator o_it;
	for (o_it = apples.begin(); o_it != apples.end(); o_it++) {
		if ((*o_it).x == x && (*o_it).y == y) {
			return false;
		}
	}

	for (std::vector<Obstacles>::iterator it = rotten_carrots.begin(); it
			!= rotten_carrots.end(); it++) {
		if ((*it).x == x && (*it).y == y) {
			return false;
		}
	}

	std::vector<Snake::Snake_Part>::iterator s_it;
	for (s_it = player1.snake_body.begin(); s_it != player1.snake_body.end(); s_it++) {
		if ((*s_it).x == x && (*s_it).y == y) {
			return false;
		}
	}

	if (ghost.x == x && ghost.y == y) {
		return false;
	}
	return true;
}

void Single_State::high_score(int score) {
	// We use float to determine which row is the recent player's.
	int scores;
	float in_score = 0.1 + score;
	std::string filename = "high_score.txt";
	std::ifstream input;
	std::list<float> high_score_list;
	input.open(filename.c_str(), std::ifstream::in);

	while (input >> scores) {
		high_score_list.push_back(scores);
	}

	high_score_list.push_back(in_score);
	high_score_list.sort();
	high_score_list.reverse(); // highest score on top
	input.close();

	std::ofstream output;
	output.open(filename.c_str());
	unsigned int i = 0;
	for (std::list<float>::iterator it = high_score_list.begin(); it
			!= high_score_list.end(); it++) {
		if (i < 5) {
			output << *it << std::endl;
			i++;
		}
	}
	output.close();
}

bool Single_State::is_free_ghost(int x, int y) {
	// Checks if theres a free position for the ghost to spawn at.
	std::vector<Obstacles>::iterator o_it;
	for (o_it = apples.begin(); o_it != apples.end(); o_it++) {
		if ((*o_it).x == x && (*o_it).y == y) {
			return false;
		}
	}

	for (std::vector<Obstacles>::iterator it = rotten_carrots.begin(); it
			!= rotten_carrots.end(); it++) {
		if ((*it).x == x && (*it).y == y) {
			return false;
		}
	}

	std::vector<Snake::Snake_Part>::iterator s_it;
	for (s_it = player1.snake_body.begin(); s_it != player1.snake_body.end(); s_it++) {
		if ((*s_it).x == x && (*s_it).y == y) {
			;
			return false;
		}
	}
	return true;
}

void Single_State::move_carrot() {
	carrot_tick++;// Is added every tick
	if (carrot_tick == 10) { // When it updates every 10th tick
		carrot = rotten_carrots.at(rotten_carrots.size() - 1);
		rotten_carrots.pop_back();
		do {
			sprite_x = get_engine()->rand_x();
			sprite_y = get_engine()->rand_y();
		} while (!is_free(sprite_x, sprite_y));
		carrot.x = sprite_x;
		carrot.y = sprite_y;
		std::vector<Obstacles>::iterator it;
		it = rotten_carrots.begin();
		rotten_carrots.insert(it, carrot);
		carrot_tick = 0;
	}
}

void Single_State::move_apple() {
	apple_tick++;
	if (apple_tick == 20) {
		apple = apples.at(apples.size() - 1);
		apples.pop_back();
		do {
			sprite_x = get_engine()->rand_x();
			sprite_y = get_engine()->rand_y();
		} while (!is_free(sprite_x, sprite_y));
		apple.x = sprite_x;
		apple.y = sprite_y;
		std::vector<Obstacles>::iterator it;
		it = apples.begin();
		apples.insert(it, apple);
		apple_tick = 0;
	}
}

void Single_State::move_ghost() {
	ghost_tick++;
	if (ghost_tick == 5) {
		if (player1.snake_body[0].x < ghost.x) {
			ghost.x -= 16;
		} else if (player1.snake_body[0].x > ghost.x) {
			ghost.x += 16;
		}
		if (player1.snake_body[0].y < ghost.y) {
			ghost.y -= 16;
		} else if (player1.snake_body[0].y > ghost.y) {
			ghost.y += 16;
		}
		ghost_tick = 0;
	}
}

void Single_State::move_pacman() {
	if (pacman_is_alive) { // When pacman hasnt been taken by the snake
		pacman_tick++;
		// Pacman tries to run away from the snake
		if (pacman_tick == 1) {
			if (player1.snake_body[0].x < pacman.x && pacman.x
					< green_background.w) {
				pacman.x += 16;
			} else if (player1.snake_body[0].x > pacman.x && pacman.x
					> green_background.x) {
				pacman.x -= 16;
			}
			if (player1.snake_body[0].y < pacman.y && pacman.y
					< green_background.h) {
				pacman.y += 16;
			} else if (player1.snake_body[0].y > pacman.y && pacman.y
					> green_background.y) {
				pacman.y -= 16;
			}
			if (pacman.x == green_background.x && pacman.y
					== green_background.y) {
				if (pacman.x == player1.snake_body[0].x) {
					pacman.x += 16;
				}
				if (pacman.y == player1.snake_body[0].y) {
					pacman.y += 16;
				}
			} else if (pacman.x == green_background.w && pacman.y
					== green_background.y) {
				if (pacman.x == player1.snake_body[0].x) {
					pacman.x -= 16;
				}
				if (pacman.y == player1.snake_body[0].y) {
					pacman.y += 16;
				}
			} else if (pacman.x == green_background.x && pacman.y
					== green_background.h) {
				if (pacman.x == player1.snake_body[0].x) {
					pacman.x += 16;
				}
				if (pacman.y == player1.snake_body[0].y) {
					pacman.y -= 16;
				}
			} else if (pacman.x == green_background.w && pacman.y
					== green_background.h) {
				if (pacman.x == player1.snake_body[0].x) {
					pacman.x -= 16;
				}
				if (pacman.y == player1.snake_body[0].y) {
					pacman.y -= 16;
				}
			}
			pacman_tick = 0;
		}
	}
}
