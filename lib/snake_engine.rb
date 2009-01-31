#!/usr/bin/env ruby

require 'sdl'

module JakeTheSnake
  class Snake_Engine
    attr_accessor :tick_interval, screen

    def initalize(width, height, fullscreen)
      $image_buffer = Hash.new
      state = Abstract_State.new
      if(SDL::Init(SDL::INIT_VIDEO) == -1)
        print ("Can't init SDL: #{SDL::SDL_GetError}")
        exit 1
      end

      if fullscreen
        flags = SDL::SDL_SWSURFACE or SDL::SDL_FULLSCREEN
      else
        flags = SDL::SDL_SWSURFANCE
      end

      if screen == nil
        print ("Can't set video mode: #{SDL::SDL_GetError}")
        SDL::SDL_Quit
        exit 1
        state = nil
        tick_interval = 50
      end

      def set_state(state)
        self.state = nil
        self.state = state
        self.state.set_engine(self)
      end
    end
  end
end
