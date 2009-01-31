/* -----------------------------
 File: Sprite.h
 Author: Johan Nordström and Sebastian Thörn
 Updated: 2008-12-06
 Description: This is our abstract superclass for
 all of our sprites.
 --------------------------------- */
#ifndef SPRITE_H_
#define SPRITE_H_
#include <iostream>
#include <SDL/SDL.h>
#include <map>
#include <string>

/** \brief The abstract superclass, which all our sprites inherit from. */
class Sprite {
public:
	Sprite();
	virtual ~Sprite();
	/** \brief The snake contains a struct for each his part (16x16 pixels).
	 * is accessed by several classes, since its added to a vector.
	 * \param x defines x coordinate of a part.
	 * \param y defines y coordinate of a part.
	 * \param is_head defines whether the part is a head part or not. */
	struct Snake_Part {
		int x;
		int y;
		bool is_head;
	};
	/** \brief Defines x coordinate for sprite, which is access by various
	 * objects.*/
	int x;

	/** \brief Defines y coordinate for sprite, which is accessed by various
	 * objects */
	int y;


	/** \brief Applies menu image to a SDL surface
	 * \param surface takes a SDL surface, like *screen */
	virtual void draw(SDL_Surface* screen) = 0;

	/** \brief This function is only used in Snake class, moves sprite.
	 * \param current_direction takes a direction the sprite should be moved.
	 * 1 for UP, 2 for LEFT, 3 for DOWN, 4 for RIGHT. */
	virtual void move(const int direction);

	/** \brief Returns the direction sprite is having. */
	virtual int get_direction();

	/** \brief Takes a surface and applies it to our screen surface.
	 *\param x x coordinate where surface should be applied.
	 *\param y y coordinate where surface should be applied.
	 *\param image the image which should be applied to screen
	 *\param screen takes the screen surface which is applied to. */
	void apply_surface(int x, int y, SDL_Surface* image, SDL_Surface* screen);

	/** \brief Loads a image to our surface (like screen).
	 * \param filename takes the filename of a image.
	 * \return Returns a SDL Surface with the image appplied. */
	static SDL_Surface* load_image(const std::string& filename);

	/** \brief Handles key presses from the user in the menu
	 * \param key Takes a keypress from the keyboard and performs a action */
	void KeyPressed(SDLKey key);
private:
	/** \brief Saves the filename and the surface when its been loaded to
	 * cause a image not be loaded twice. */
	static std::map<std::string, SDL_Surface*> image_buffer;
};

#endif /* SPRITE_H_ */
