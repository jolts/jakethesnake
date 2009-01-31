#include "Collision_Handler.h"

/* ------------- Collision_Handler Methods ------------- */

Collision_Handler::Collision_Handler() {
}

Collision_Handler::~Collision_Handler() {
}

bool Collision_Handler::is_wall_collision(const Snake::Snake_Part& snake_head,
		const SDL_Rect* wall) const {
	// When snakehead collides with any wall coordinate, return True.
	if (snake_head.x < wall->x || snake_head.y < wall-> y || snake_head.x
			+ 16 > wall->x + wall->w || snake_head.y + 16 > wall->y + wall->h) {
		return true;
	}
	return false;
}

bool Collision_Handler::is_obstacles_collision (
	const std::vector<Snake::Snake_Part>& jake_body, const Sprite &obstacles) const {
	std::vector<Snake::Snake_Part>::const_iterator it;
	for (it = jake_body.begin(); it != jake_body.end(); it++) {
		if ((*it).x == obstacles.x && (*it).y == obstacles.y) {
			return true;
		}
	}
	return false;
}

bool Collision_Handler::is_self_snake_collision(
	const std::vector<Snake::Snake_Part>& snake) const {
	std::vector<Snake::Snake_Part>::const_iterator it;

	// Nested for loop to check whether one part of the Snake
	// collides with another part.
	for (it = snake.begin(); it != snake.end(); it++) {
		std::vector<Snake::Snake_Part>::const_iterator sit;
		for (sit = it + 1; sit != snake.end(); sit++) {
			if ((*it).x == (*sit).x && (*it).y == (*sit).y) {
				return true;
			}
		}
	}
	return false;
}

int Collision_Handler::is_player1_player2_collision(const std::vector<
	Snake::Snake_Part>& player1, const std::vector<Snake::Snake_Part>& player2) const {

	if (player1[0].x == player2[0].x && player1[0].y == player2[0].y) {
				return 3; // Head to head collision
			}
	std::vector<Snake::Snake_Part>::const_iterator it;

	for (it = player1.begin(); it != player1.end(); it++) {
		if ((*it).x == player2[0].x && (*it).y == player2[0].y) {
			return 2; // Player 2 loose
		}
	}

	for (it = player2.begin(); it != player2.end(); it++) {
			if ((*it).x == player1[0].x && (*it).y == player1[0].y) {
				return 1; // Player 1 loose
			}
		}
	return 0; // No collision
}
