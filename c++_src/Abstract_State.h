/* -----------------------------
 File: Collision_Handler.h
 Author: Johan Nordström and Sebastian Thörn
 Updated: 2008-12-06
 Description: Handles messages to all states and our game engine.
------------------------------ */
#ifndef ABSTRACT_STATE_H_
#define ABSTRACT_STATE_H_

#include <SDL/SDL.h>
#include <iostream>

class Snake_Engine;

/** \brief Super Class which handles all states
 * Handles messages to all states and our game engine.*/
class Abstract_State {

public:
	Abstract_State();
	~Abstract_State();

	/** \brief Sets the current game engine
	* \param engine The game engine to use for the state
	*/
	void set_engine(Snake_Engine* engine);

	/** \brief Retrieves the current game engine */
	Snake_Engine* get_engine() const;

	/** \brief Applies image(s) to an SDL surface, is pure virtual
	 * \param surface a SDL_Surface pointer
	 * \return SDL_Surface with the image(s) applied */
	virtual void draw(SDL_Surface* surface);

	/** \brief Defines action that the state should do every tick */
	virtual void clock_tick();

	/* \brief When user presses down a key this function
	 * is called from the game loop.
	 * \param key Takes a key in form of a SDLKey */
	virtual void key_pressed(SDLKey key);
private:
	/* \brief Defines a pointer for a specific game engine */
	Snake_Engine* engine;
};
#endif /* ABSTRACT_STATE_H_ */
