#include "Sprite.h"

std::map<std::string, SDL_Surface*> Sprite::image_buffer;

Sprite::Sprite() {
}

Sprite::~Sprite() {;
}

void Sprite::apply_surface(int x, int y, SDL_Surface* image, SDL_Surface* screen) {
	SDL_Rect offset;
	// Applies the sprite to a temporary rectangular with x and y
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(image, NULL, screen, &offset);
}

SDL_Surface* Sprite::load_image(const std::string& filename) {
	if(image_buffer.find(filename) != image_buffer.end())
		// If the image already has been loaded, just return.
		return image_buffer[filename];
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;
	loadedImage = SDL_LoadBMP(filename.c_str());
	if (loadedImage != 0) {
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	image_buffer.insert(make_pair(filename, optimizedImage));
	return optimizedImage;
}

void Sprite::move(const int direction) {
}

int Sprite::get_direction() {
	return 0;
}

void Sprite::KeyPressed(SDLKey key)
{
}
