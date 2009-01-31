#include "Multi_State.h"

Multi_State::Multi_State() {
	// Initalises player1 with number one sprite
	// which gives shows us 'player1' in the head of the sprite.
	player1.init(1);
	player2.init(2);

	// Assigns the objects, and sends a SDL_Surface* which is returned
	// from load_image as a argument.
	apple = Obstacles(Snake_Engine::load_image("./img/apple.bmp"));
	carrot = Obstacles(Snake_Engine::load_image("./img/carrot.bmp"));

	// Get a random position until we find a free one.
	do {
		sprite_x = get_engine()->rand_x();
		sprite_y = get_engine()->rand_y();
	} while (!is_free(sprite_x, sprite_y));
	apple.x = sprite_x;
	apple.y = sprite_y;

	// Does the same thing but spawns 35 carrots.
	for (int i = 0; i != 35; i++) {
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

	// Direction is initalized to right in the beginning
	p1dir = 2;
	p2dir = 2;
	p1points = 0;
	p2points = 0;
	p1parts_to_add = 0;
	p2parts_to_add = 0;
}

Multi_State::~Multi_State() {
	// No dynamic allocation so nothing to free.
}

void Multi_State::key_pressed(SDLKey key) {
	// Checks whether direction is not opposite
	// for exampel if snake is moving down it cant move up.
	switch (key) {
	case SDLK_UP:
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
	case SDLK_w:
		if (player2.get_direction() != 3) {
			p2dir = 1;
		}
		break;
	case SDLK_d:
		if (player2.get_direction() != 4) {
			p2dir = 2;
		}
		break;
	case SDLK_s:
		if (player2.get_direction() != 1) {
			p2dir = 3;
		}
		break;
	case SDLK_a:
		if (player2.get_direction() != 2) {
			p2dir = 4;
		}
		break;
	default:
		break;
	}
}

void Multi_State::clock_tick() {
	// Defines what will happen each tick.
	player1.move(p1dir);
	player2.move(p2dir);

	check_collisions();

	if (p1parts_to_add != 0) {
		// If theres body to add, add one
		player1.add_parts(1);
		p1parts_to_add--;
	}

	if (p2parts_to_add != 0) {
		player2.add_parts(1);
		p2parts_to_add--;
	}

	carrot_tick++; // Is added every tick
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
		// After we've removed the carrot we add it to the first position
		rotten_carrots.insert(it, carrot);
		carrot_tick = 0;
	}
}

void Multi_State::draw(SDL_Surface* surface) {
	// Draws up all our sprite in our multi player mode
	green_background.x = 16;
	green_background.y = 16;
	green_background.w = 608;
	green_background.h = 448;
	SDL_FillRect(surface, &green_background, SDL_MapRGB(surface->format, 0x61,
			0xAD, 0x2F));

	player1.draw(surface);
	player2.draw(surface);

	apple.draw(surface);

	for (std::vector<Obstacles>::iterator it = rotten_carrots.begin(); it != rotten_carrots.end(); it++) {
		(*it).draw(surface);
	}

	// If we lose the game we get thrown to game_over_state
	if (finished) {
		SDL_Delay(2000);
		std::string img_str;

		switch (player_won) {
		case 0:
			img_str = "./img/player_even.bmp";
			break;
		case 1:
			img_str = "./img/player1_won.bmp";
			break;
		case 2:
			img_str = "./img/player2_won.bmp";
			break;
		default:
			break;
		}
		SDL_Surface* game_over_image = Snake_Engine::load_image(img_str);
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		SDL_BlitSurface(game_over_image, NULL, surface, &rect);
		get_engine()->set_state(new Gameover_State());
	}
}

void Multi_State::check_collisions() {
	if (collision_handler.is_wall_collision(player1.snake_body[0],
			&green_background)) {
		player_won = 2;
		finished = true;
	}

	if (collision_handler.is_wall_collision(player2.snake_body[0],
			&green_background)) {
		player_won = 1;
		finished = true;
	}

	if (collision_handler.is_self_snake_collision(player1.snake_body)) {
		player_won = 2;
		finished = true;
	}

	if (collision_handler.is_self_snake_collision(player2.snake_body)) {
		player_won = 1;
		finished = true;
	}

	if (collision_handler.is_obstacles_collision(player1.snake_body, apple)) {
		// When the player collides with a apple, try to get a random position
		// which doesnt collide with a coordinate.
		p1points += 5;
		p1parts_to_add += 3;
		do {
			sprite_x = get_engine()->rand_x();
			sprite_y = get_engine()->rand_y();
		} while (!is_free(sprite_x, sprite_y));
		apple.x = sprite_x;
		apple.y = sprite_y;
	}

	if (collision_handler.is_obstacles_collision(player2.snake_body, apple)) {
		p2points += 5;
		p2parts_to_add += 3;
		do {
			sprite_x = get_engine()->rand_x();
			sprite_y = get_engine()->rand_y();
		} while (!is_free(sprite_x, sprite_y));
		apple.x = sprite_x;
		apple.y = sprite_y;
	}

	// Handles carrot collision with the snake.
	for (std::vector<Obstacles>::iterator it = rotten_carrots.begin();
	it != rotten_carrots.end(); it++) {
		if (collision_handler.is_obstacles_collision(player1.snake_body, (*it))) {
			if (player1.snake_body.size() == 2) {
				player_won = 2;
				finished = true;
			}
			p1points -= 10;
			player1.remove_parts((player1.snake_body.size() / 3));
			do {
				sprite_x = get_engine()->rand_x();
				sprite_y = get_engine()->rand_y();
			} while (!is_free(sprite_x, sprite_y));
			(*it).x = sprite_x;
			(*it).y = sprite_y;

		}
	}

	for (std::vector<Obstacles>::iterator it = rotten_carrots.begin();
	it != rotten_carrots.end(); it++) {
		if (collision_handler.is_obstacles_collision(player2.snake_body, (*it))) {

			if (player2.snake_body.size() == 2) {
				player_won = 1;
				finished = true;
			}
			p2points -= 10;
			player2.remove_parts((player2.snake_body.size() / 3));
			do {
				sprite_x = get_engine()->rand_x();
				sprite_y = get_engine()->rand_y();
			} while (!is_free(sprite_x, sprite_y));
			(*it).x = sprite_x;
			(*it).y = sprite_y;
		}
	}

	// Gets the value of which player has lost.
	int multi_collision = collision_handler.is_player1_player2_collision(
			player1.snake_body, player2.snake_body);

	switch (multi_collision) {
	case 1:
		player_won = 2;
		finished = true;
		break;
	case 2:
		player_won = 1;
		finished = true;
		break;
	case 3:
		player_won = 0;
		finished = true;
		break;
	default:
		break;
	}
}

bool Multi_State::is_free(int x, int y) {
	std::vector<Obstacles>::iterator o_it;
	if (x == apple.x && y == apple.y) {
		return false;
	}

	for (o_it = rotten_carrots.begin(); o_it != rotten_carrots.end(); o_it++) {
		if ((*o_it).x == x && (*o_it).y == y) {
			return false;
		}

	}

	for (std::vector<Snake::Snake_Part>::iterator s_it = player1.snake_body.begin(); s_it != player1.snake_body.end(); s_it++) {
		if ((*s_it).x == x && (*s_it).y == y) {
			return false;
		}
	}
	return true;
}
