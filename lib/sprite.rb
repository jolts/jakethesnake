#!/usr/bin/env ruby
require 'sdl'

module JakeTheSnake
  class Sprite
    attr_accessor :direction

    def initalize
      @@direction = 0
      @@snake_part = Struct.new
      @@snake_part.x = 0
      @@snake_part.y = 0
      @@snake_part.head = true
      @@x = 0
      @@y = 0
      image_buffer = Hash.new
    end

    def apply_surface(x, y, image, screen)
      offset = SDL::SDL_Rect
      offset.x = x
      offset.y = y
      SDL::SDL_BlitSurface(image, nil, screen, offset)
    end

    def load_image(filename)
      if(image_buffer[filename])
        # If the image already has been loaded, just return
        image_buffer[filename]
      end
      loaded_image = SDL::Surface = nil
      optimized_imae = SDL::Surface = nil
      loaded_image = SDL::LoadBMP(filename)

      if loaded_image != 0
        optimized_image = SDL::DisplayFormat(loaded_image)
        SDL::SDL_FreeSurface(loaded_image)
      end
      image_buffer[filename] = optimized_image
      optimized_image
    end

    def move(direction)
    end

    def key_pressed(key)
    end
  end
end
