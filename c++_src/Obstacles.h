/* -----------------------------
 File: Obstacles.h
 Author: Johan Nordström and Sebastian Thörn
 Updated: 2008-11-29
 Description:
 Handles all kind of obstacles, like apples, rotten carrots
 and ghost(s).
 --------------------------------- */

#ifndef OBSTACLES_H_
#define OBSTACLES_H_
#include "Sprite.h"

/** \brief In this class, all kind of obstacles that our snake
 * can meet, is defined. */
class Obstacles: public Sprite {
public:
	/** \brief Applies menu image to a SDL surface
	 * \param surface takes a SDL surface, like *screen */
	void draw(SDL_Surface* screen);

	Obstacles(SDL_Surface* = NULL);
	virtual ~Obstacles();
private:
	/** Defines the current obstacle sprite */
	SDL_Surface* image;
};

#endif
