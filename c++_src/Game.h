#ifndef GAME_H_
#define GAME_H_

#include <SDL/SDL.h>
#include "Snake_Engine.h"
#include "Abstract_State.h"
#include "Menu_State.h"

/** \brief This is a simple class which handles execution of the game. */
class Game {
public:
	Game();
	virtual ~Game();

	/* \brief Initalizes the game */
	void run();
private:
	/** \brief Defines a pointer to the current state */
	Abstract_State* state;

	/** \brief Defines a pointer to the current engine */
	Snake_Engine* engine;
};

#endif /* GAME_H_ */
