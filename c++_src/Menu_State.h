/* -----------------------------
 File: Menu_State.h
 Author: Johan Nordström and Sebastian Thörn
 Updated: 2008-12-06
 Description: The state handles the first screen
 the player is presented by and also handles input
 for the players choice.
------------------------------ */
#ifndef MENU_STATE_H_
#define MENU_STATE_H_
#include "Abstract_State.h"
#include "Snake_Engine.h"

class Snake_Engine;
/** \brief The state presents user with a menu, whenever the state
 * is set. */
class Menu_State: public Abstract_State {
public:
	Menu_State();
	~Menu_State();

	/** \brief Applies menu image to a SDL surface.
	 * \param surface takes a SDL surface, like *screen */
	void draw(SDL_Surface* surface);

	/** \brief Handles key presses from the user in the menu
	 * \param key Takes a keypress from the keyboard and performs a action. */
	void key_pressed(SDLKey key);
private:
	/** \brief Is the choice user is markign in the menu */
	int choice;

	/** \brief Is the y coordinate of the choice. */
	int choice_y;

	/** \brief Defines a pointer holding the menu image/surface. */
	SDL_Surface* menu_screen;

	/** \brief Defines a pointer holding the menu image/surface. */
	SDL_Surface* apple;
};

#endif
