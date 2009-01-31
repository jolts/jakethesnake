#include "Obstacles.h"


/* ------------- Obstacles Methods ------------- */

Obstacles::Obstacles(SDL_Surface* image) {
	this->image = image;
}

Obstacles::~Obstacles() {
	// Everytime we load a image, we check if its already been loaded
	// so theres no need for freeing it, since all images are used until we close a state
	// then we free the images.
}

void Obstacles::draw(SDL_Surface* screen) {
	apply_surface(x, y, this->image, screen);
}
