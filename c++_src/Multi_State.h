/* -----------------------------
 File: Menu_State.h
 Author: Johan Nordström and Sebastian Thörn
 Updated: 2008-12-06
 Description: The state handles multi player mode
 where the player can play against a friend
 with WASD and arrow keys.
 ------------------------------ */
#ifndef MULTI_STATE_H_
#define MULTI_STATE_H_
#include <vector>
#include "Abstract_State.h"
#include "Snake_Engine.h"
#include "Collision_Handler.h"
#include "Snake.h"
#include "Obstacles.h"

/** \brief A state which handles multi player mode in the game
 * two snakes are spawned, so the player can play against someone else. */
class Multi_State: public Abstract_State {
public:
	/** \brief Handles key presses from the user in the menu
	 * \param key Takes a keypress from the keyboard and performs a action */
	void key_pressed(SDLKey key);

	/** \brief In this function we describe what we'll happen each tick. */
	void clock_tick();
	Multi_State();
	virtual ~Multi_State();
private:
	Obstacles apple;
	Obstacles carrot;

	/** \brief A container containing all our carrots */
	std::vector<Obstacles> rotten_carrots;
	Collision_Handler collision_handler;

	/** \brief Creates a instance of player1 */
	Snake player1;

	/** \brief Creates a instance of player1 */
	Snake player2;

	/** \brief Defines a temporary coordinate for a sprite */
	int sprite_x, sprite_y;

	/** \brief Checks whether there is a free coordinate for the sprite */
	bool is_free(int x, int y);

	/** \brief This SDL_Rect handles the inner rectangle, * inside our wall. */
	SDL_Rect green_background;

	/** brief Sets variables for both players direction and points */
	int p1dir, p2dir, p1points, p2points;

	/** Defines how often the first carrot should move */
	int carrot_tick;

	/** Is used to determine which player lost/won when the game has ended */
	int finished;

	/** Defines which player won */
	int player_won;

	/** Defines how many parts should be added to player1 */
	int p1parts_to_add;

	/** Defines how many parts should be added to player2 */
	int p2parts_to_add;

	/** \brief Applies menu image to a SDL surface
	 * \param surface takes a SDL surface, like *screen */
	void draw(SDL_Surface* surface);

	/** \brief This function interacts with our collision handler
	 * and handles all events when the snake(s) collides with another object */
	void check_collisions();
};

#endif
