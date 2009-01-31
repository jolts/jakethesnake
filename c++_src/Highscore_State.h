/* -----------------------------
 File: Highscore_State.h
 Author: Johan Nordström and Sebastian Thörn
 Updated: 2008-12-06
 Description: This state is called in Single Player mode
 when the snakes have collided or died.
------------------------------ */
#ifndef HIGHSCORE_STATE_H_
#define HIGHSCORE_STATE_H_

#include <iostream>
#include <SDL/SDL.h>
#include "Snake_Engine.h"
#include "Single_State.h"

/** \brief This state is called in single player mode when the snake has
 * collided or died.  */
class Highscore_State: public Abstract_State {
public:
	Highscore_State();
	~Highscore_State();

	/** \brief Applies Highscore image to screen.
	 * \param surface Takes a SDL_Surface, like *screen.
	 * \return a SDL_Surface with the highscore screen. */
	void draw(SDL_Surface* surface);

	/** \brief Handles events through key presses during highscore screen.
	/* \param key Takes a keyboard event. */
	void key_pressed(SDLKey key);
private:
	void draw_highscreen();

	/** \brief the SDL Surface containing high score image. */
	SDL_Surface* highscore_screen;

	/** \brief Each number in high score is a sdl surface being written up. */
	SDL_Surface* number;

	/** \brief A list container which contains the top 5 scores. */
	std::list<std::string> high_score_list;

	/** \brief Returns a list containing top 5 scores from a file on disk. */
	std::list<std::string>read_and_evaluate();

	/** \brief The row which corresponds to the players recent score. */
	unsigned int player_row;
};

#endif /* HIGHSCORE_STATE_H_ */
