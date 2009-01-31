/* -----------------------------
 File: Snake.h
 Author: Johan Nordström and Sebastian Thörn
 Updated: 2008-12-06
 Description: This is the sprite which handles the player sprite,
 our snake. All action like adding, removing parts and moving the snake
 is performed here.
 --------------------------------- */
#ifndef SNAKE_H_
#define SNAKE_H_
#include <vector>
#include <iostream>
#include "Sprite.h"

class Snake_Engine;

/** \brief The class handling our player sprite, Jake the Snake */
class Snake: public Sprite {
public:
	Snake();
	virtual ~Snake();

	/** \brief This vector contains all 16x16 parts of our snake
	 * and corresponding x,y coordinates and whether the part is a head. */
	std::vector<Snake_Part> snake_body;

	/** \brief Sets how long the snake should be .*/
	void set_jake_parts();

	/** \brief Initalizes the snake */
	void init(int m_player);

	/** \brief Applies menu image to a SDL surface
	 * \param surface takes a SDL surface, like *screen */
	void draw(SDL_Surface* screen);

	/** \brief Redraws the snake and moves him one step.
	 * \param current_direction takes a direction the snake should be moved,
	 * 1 for UP, 2 for LEFT, 3 for DOWN, 4 for RIGHT. */
	void move(const int current_direction);

	/** \brief Returns the direction snake is having. */
	int get_direction() const;

	/** \brief Returns the length of the snake */
	int get_length() const;

	/** \brief Adds parts to our snake.
	 * \param n takes number of parts to be added. */
	void add_parts(const int& n);

	/** \brief Removes parts from our snake.
	 * \param n takes number of parts to be added. */
	void remove_parts(const int& n);

	/** \brief Whenever pacman has collided with us we get rainbow powers. */
	void set_rainbow(bool flag);

	/** \brief Returns the value of rainbow. */
	bool get_rainbow();
private:
	/** \brief The direction the snake should move in. */
	int direction;

	/** \brief Keeps track of whether its player1 or player2. */
	int instance;

	/** \brief The length of the snake. */
	int length;

	/** \brief Amount of body parts (not length). */
	int body_parts;

	/** \brief Defines whether a body part is a head. */
	bool head;

	/** \brief The surface which we apply the snake to. */
	SDL_Surface* snake_surface;

	/** \brief Member variable which holds the player numebr */
	int m_player;

	/** \brief Whenever pacman has collided with us we get rainbow powers. */
	bool rainbow;
};

#endif /* SNAKE_H_ */
