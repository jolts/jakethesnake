#include "Snake_Engine.h"

bool Snake_Engine::done = false;
std::map<std::string, SDL_Surface*> Snake_Engine::image_buffer;

/* ------------- Class Snake_Engine ------------- */

Snake_Engine::Snake_Engine(int width, int height, bool fullscreen) {
	Uint32 flags;
	if (-1 == SDL_Init(SDL_INIT_VIDEO)) {
		printf("Can't init SDL:  %s\n", SDL_GetError());
		exit(1);
	}
	if (fullscreen) {
		flags = SDL_SWSURFACE | SDL_FULLSCREEN;

	} else {
		flags = SDL_SWSURFACE;
	}
	screen = SDL_SetVideoMode(width, height, 32, flags);
	if (NULL == screen) {
		printf("Can't set video mode: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}
	state = NULL;
	tick_interval = 50; // 20 FPS
}

Snake_Engine::~Snake_Engine() {
	// No need to delete state as this object is always active
	// Deleting object casues segmentation fault due to this.
	// We dont have any deallocation here because this object is
	// always alive and memory is taken back by other classes.
}

void Snake_Engine::set_state(Abstract_State* state) {
	delete this->state;
	this->state = 0;
	this->state = state;
	this->state->set_engine(this);
}

void Snake_Engine::set_tick_interval(int interval) {
	tick_interval = interval;
}

SDL_Surface* Snake_Engine::get_screen() const {
	return screen;
}

void Snake_Engine::loop() {
	SDL_Event event;
	Uint32 next_tick;

	if (NULL == state) {
		return;
	}
	while (!done) {
		next_tick = SDL_GetTicks() + tick_interval;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit();
				break;
			case SDL_KEYDOWN:
				state->key_pressed(event.key.keysym.sym);
				break;
			}
		}
		state->clock_tick();
		state->draw(screen);

		SDL_Flip(screen);

		if (SDL_GetTicks() < next_tick) {
			SDL_Delay(next_tick - SDL_GetTicks());
		}
	}
	SDL_Quit();
}

void Snake_Engine::quit() {
	done = true;
}

SDL_Surface* Snake_Engine::load_image(const std::string& filename)  {
	if(image_buffer.find(filename) != image_buffer.end())
		// If the image already has been loaded, just return.
		return image_buffer[filename];
	SDL_Surface* loaded_image = 0;
	SDL_Surface* optimized_image = 0;
	loaded_image = SDL_LoadBMP(filename.c_str());
	if (loaded_image != 0) {
		optimized_image = SDL_DisplayFormat(loaded_image);
		SDL_FreeSurface(loaded_image);
	}
	image_buffer.insert(make_pair(filename, optimized_image));
	return optimized_image;
}

int Snake_Engine::rand_x() {
	// Randoms out a x coordinate within the green background.
	return (rand() % 38 * 16 + 16);
}

int Snake_Engine::rand_y() {
	// Randoms out a y coordinate within the green background.
	return (rand() % 28 * 16 + 16);
}

void Snake_Engine::free_memory(SDL_Surface* surface) {
	if (surface !=0) {
		SDL_FreeSurface(surface);
		surface = 0;
	}
}
