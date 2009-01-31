/* -----------------------------
 File: Gameover_State.h
 Author: Johan Nordström and Sebastian Thörn
 Updated: 2008-12-06
 Description: This state is called in Multi Player mode
 when the snakes have collided or died.
------------------------------ */
#ifndef GAMEOVER_STATE_H_
#define GAMEOVER_STATE_H_
#include "Abstract_State.h"
#include "Snake_Engine.h"
#include "Menu_State.h"

/** \brief Shows who won the current round in multiplayer mode */
class Gameover_State: public Abstract_State {
public:
	Gameover_State();
	virtual ~Gameover_State();

	/** \brief Handles key events during game over state
	 * \param key Takes a key in form of a SDLKey */
	void key_pressed(SDLKey key);
};

#endif /* GAMEOVER_STATE_H_ */
