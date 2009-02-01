#!/usr/bin/env ruby
require 'sdl'
require 'abstract_state'
require 'gameover_state'
require 'highscore_state'
require 'multi_state'
require 'single_state'

module JakeTheSnake
  class Snake_Engine
    attr_accessor :tick_interval, screen

    def initalize(width, height, fullscreen)
      done = false
      $image_buffer = Hash.new
      state = Abstract_State.new
      if(SDL::Init(SDL::INIT_VIDEO) == -1)
        puts "Can't init SDL: #{SDL::SDL_GetError}"
        exit 1
      end

      if fullscreen
        flags = SDL::SDL_SWSURFACE or SDL::SDL_FULLSCREEN
      else
        flags = SDL::SDL_SWSURFACE
      end

      if screen == nil
        puts "Can't set video mode: #{SDL::SDL_GetError}"
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

      def loop
        event = SDL::SDL_event

        if state == nil
          return
        end

        while not done
          next_tick = SDL::SDL_GetTicks.to_i + tick_interval

          while SDL::SDL_PollEvent(event)
            case event.type
            when SDL::SDL_Quit
              quit
              break
            when SDL::SDL_KEYDOWN
              state.key_pressed(event.key.keysym.sym)
              break
            end
          end
          state.clock_tick
          state.draw(screen)

          SDL::SDL_Flip(screen)

          if SDL::SDL_GetTicks < next_tick
            SDL::SDL_Delay(next_tick - SDL_GetTicks)
          end
          SDL::SDL_Quit
        end

        def quit
          done = true
        end

        def load_image(filename)
          if image_buffer.find(filename) != image_buffer.end
            # If the image already has been loaded, just return.
            exit 1
          end

          loaded_image = SDL::Surface = 0
          optimized_image = SDL::Surface = 0
          loaded_image = SDL::SDL_LoadBMP(filename)

          if loaded_image
            optimized_image = SDL_DisplayFormat(loaded_image)
            SDL::SDL_FreeSurface(loaded_image)
          end
          optimized_image
        end
      end
    end
  end
end
