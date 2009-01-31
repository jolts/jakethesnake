/* -----------------------------
 File: Snake_Engine.h
 Author: Johan Nordström and Sebastian Thörn
 Updated: 2008-12-06
 Description: This is our Game Engine, and core of the game
 the main SDL Loop is defined here which handles messages to all
 states.
 --------------------------------- */
#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <SDL/SDL.h>
#include <string>
#include <map>
#include "Abstract_State.h"
#include "Gameover_State.h"
#include "Highscore_State.h"
#include "Multi_State.h"
#include "Single_State.h"

/** \brief The game engine which handles messages to all the states. */
class Snake_Engine {
public:
	Snake_Engine(int with, int height, bool fullscreen);
	~Snake_Engine();

	/** \brief Sets the current state.
	 * \param state Takes a state object to be set*/
	void set_state(Abstract_State* state);

	/** \brief Returns the current SDL Surface */
	SDL_Surface* get_screen() const;

	/** \brief Sets how often the screen should be updated.
	 * \param interval Takes a integer in form of milliseconds. */
	void set_tick_interval(int interval);

	/** \brief This is where all the action happens and all interactions
	 * are sent to our current state. */
	void loop();

	/** \brief Whenever the game has to be ended, we call this function. */
	void quit();

	/** \brief Gives a random x coordinate. Is used by other classes
	 * to get random x coordinates for their sprites */
	int rand_x();

	/** \brief Gives a random y coordinate. Is used by other classes
	 * to get random y coordinates for their sprites */
	int rand_y();

	/** \brief Loads a image to our surface (like screen).
	 * \param filename takes the filename of a image.
	 * \return Returns a SDL Surface with the image appplied. */
	static SDL_Surface* load_image(const std::string& filename);

	/** \brief When this variable is true the sdl loop continues */
	static bool done;

	/** Simplified function which free's a surface and sets the pointer to 0. */
	static void free_memory(SDL_Surface* surface);
private:
	/** \brief This is the main underlying SDL_Surface which everything
	 * is "based on".*/
	SDL_Surface* screen;

	/** \brief A pointer to the state handling class */
	Abstract_State* state;

	/** \brief Saves the filename and the surface when its been loaded to
	 * cause a image not be loaded twice. */
	static std::map<std::string, SDL_Surface*> image_buffer;

	/** \brief Defines how often SDL should draw */
	int tick_interval;
};

#endif
