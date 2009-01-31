/* -----------------------------
 File: Obstacles.h
 Author: Johan Nordström and Sebastian Thörn
 Updated: 2008-12-06
 Description: This is our main state, which handles all events
 and interactions when the player choices to play
 Single player mode.
 --------------------------------- */
#ifndef SINGLE_STATE_H_
#define SINGLE_STATE_H_

#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include "Abstract_State.h"
#include "Collision_Handler.h"
#include "Obstacles.h"
#include "Snake.h"
#include "Snake_Engine.h"

/** \brief Handles all kind of events and interactions during
 * single player mode. */
class Single_State: public Abstract_State {
public:
	/** \brief Handles key presses from the user in the menu
	 * \param key Takes a keypress from the keyboard and performs a action */
	void key_pressed(SDLKey key);

	/** \brief In this function we describe what we'll happen each tick. */
	void clock_tick();

	Single_State();
	virtual ~Single_State();
private:
	int sprite_x, sprite_y;
	Obstacles apple;
	Obstacles carrot;
	Obstacles pacman;
	Obstacles ghost;

	/** \brief Contains all carrot obstacles that will be spawned
	 * throughout game. */
	std::vector<Obstacles> rotten_carrots;

	/** \brief Contains all apple obstacles that will be spawned
	 * throughout game. */
	std::vector<Obstacles> apples;

	Collision_Handler collision_handler;
	Snake player1;
	SDL_Rect green_background;
	int p1dir, p1points;

	/** \brief Is used to determine  when game has ended. */
	bool finished;

	/** \brief Defines how often apple should move. */
	int apple_tick;

	/** \brief Defines how often carrot should move. */
	int carrot_tick;

	/** \brief Defines how often ghost should move. */
	int ghost_tick;

	/** \brief Defines how often pacman should move. */
	int pacman_tick;

	/** \brief Sets how many parts should be added when a certain event should happen. */
	int p1parts_to_add;

	/** \brief Determines whether the pacman power-up has been used or not. */
	bool pacman_is_alive;

	/** \brief Applies menu image to a SDL surface
	 * \param surface takes a SDL surface, like *screen */
	void draw(SDL_Surface* surface);

	/** \brief This function interacts with our collision handler
	 * and handles all events when the snake(s) collides with another object */
	void check_collisions();

	/** \brief This function writes to filesystem whenever the player
	 * collides or dies, and gets a score. And then presents
	 * the player with the highscore screen, showing the top 5 results.
	 * \param score Takes the players score to store. */
	void high_score(int score);

	/** \brief Returns true if theres a free position to spawn at. */
	bool is_free(int x, int y);

	/** \brief Checks for a free position for the ghost to spawn at */
	bool is_free_ghost(int x, int y);

	/** \brief Handles movement of carrot in every tick */
	void move_carrot();

	/** \brief Handles movement of apple in every tick */
	void move_apple();

	/** \brief Handles movement of pacman in every tick */
	void move_pacman();

	/** \brief Handles movement of ghost in every tick */
	void move_ghost();
};

#endif
