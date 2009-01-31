/* ---------------------------------
 File: Collision_Handler.h
 Author: Johan Nordström and Sebastian Thörn
 Updated: 2008-12-06
 Description:
 All collisions in the game is handled inside here and is
 called from our Game Engine (Snake_Engine).
 If a collision occurs the method returns true (>0).
------------------------------------ */
#ifndef COLLISION_HANDLER_H_
#define COLLISION_HANDLER_H_
#include <vector>
#include <SDL/SDL.h>
#include "Sprite.h"
#include <iostream>
#include "Snake.h"


/** \brief This class handles all collisions in the game */
class Collision_Handler {
public:
	Collision_Handler();
	virtual ~Collision_Handler();

	/** \brief Checks if the snake has collided with a wall
	 * \param snake_head Takes a vector containing all parts of the snake
	 * \param wall Takes a whole SDL_Rect object, which is our wall */
	bool is_wall_collision(const Snake::Snake_Part& snake_head, const SDL_Rect* wall) const;

	/** \brief Checks if a obstacle, like an apple has collided with the snake
	 * \param jake_body Takes an vector containing snake parts
	 * \param obstacles Takes a obstacles Sprite object */
	bool is_obstacles_collision(const std::vector<Snake::Snake_Part>& jake_body, const Sprite& obstacles) const;

	/** \brief Checks whether the snake has collided with any parts of itself
	 * \param snake Takes a vector containing snake parts */
	bool is_self_snake_collision(const std::vector<Snake::Snake_Part>& snake) const;

	/** \brief In multiplayer mode this function checks if two snakes has collided
	 * \param player1, takes a vector of player1's snake parts
	 * \param player2, takes a vector of player2's snake parts
	 * \return 1 if player1 lost, 2 if player2 lost and 3 if their heads collided (a draw) */
	int is_player1_player2_collision(const std::vector<Snake::Snake_Part>& player1,
	const std::vector<Snake::Snake_Part>& player2) const;
};
#endif /* COLLISION_HANDLER_H_ */
