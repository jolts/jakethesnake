#!/usr/bin/env ruby
require 'sdl'
require 'snake_engine'
require 'single_state'

module JakeTheSnake
  class Highscore_State < Abstract_State
    attr_accessor :high_score_list

    def initialize
      @@highscore_screen = SDL::Surface
      @@number = SDL::Surface
      @@high_score_list = Array.new
      # Assign the highscore file to a list variable
      high_score_list = read_and_evaluate
      draw_highscreen
    end

    def draw(surface)
      rect = SDL::SDL_rect
      rect.x = 0
      rect.y = 0
      SDL::SDL_BlitSurface(highscore_screen, nil, surface, rect)
    end

    def key_pressed(key)
      # Manipulate the row player_row
      # remove the last two chars in the list
      # save the file. Is only run when pressing enter.
      if (key == SDL::SDLK_RETURN)
        output = File.open('highscore_txt', a)
        i = 1
        high_score_list.each do |element|
          if player_row == i # If the current player row is found
            player_line = element.to_s
            player_line = player_line[0..player_line.length-2]
            output.write(player_line.to_s + '\n')
          else
            output.write(element.to_s + '\n')
          end
          i += 1
        end
        output.close
        get_engine.set_state(Menu_State.new)
      end
    end

    def read_and_evaluate
      filename = "high_score.txt"
      high_score_list = Array.new
      input = File.open(filename, "a+")
      
      input.each_line do |line|
        high_score_list << line
      end
      input.close
      high_score_list
    end

    def draw_highscreen
      highscore_screen = engine.load_image("./img/background_and_wall_high.bmp")
      rect = SDL::SDL_Rect
      rect.x = 0
      rect.y = 0
      current_row = 0 # The row its reading at
      rect.y = 59

      high_score_list.each do |element|
        rect.y += 64
        rect.x = 224
        s = element.to_s
        current_row +=1 # Goes to next line
        element.each do |char|
          case char
          when char == '.'
            temp_x = rect.x
            temp_y = rect.y
            player_row = current_row # If the player scores this row
            number = engine.load_image("./img/apple_menu.bmp")
            rect.x = 224
            rect.y += 13
            SDL::SDL_BlitSurface(number, nil, highscore_screen, rect)
            rect.x = temp_x
            rect.y = temp_y
            rect.x -= 32
            # For every number we apply the image and blit the surface
          when char == '1'
            number = engine.load_image("./img/high_1.bmp")
            SDL::SDL_BlitSurface(number, nil, highscore_screen, rect)
          when char == '2'
            number = engine.load_image("./img/high_2.bmp")
            SDL::SDL_BlitSurface(number, nil, highscore_screen, rect)
          when char == '3'
            number = engine.load_image("./img/high_3.bmp")
            SDL::SDL_BlitSurface(number, nil, highscore_screen, rect) 
          when char == '4'
            number = engine.load_image("./img/high_4.bmp")
            SDL::SDL_BlitSurface(number, nil, highscore_screen, rect)
          when char == '5'
            number = engine.load_image("./img/high_5.bmp")
            SDL::SDL_BlitSurface(number, nil, highscore_screen, rect)
          when char == '6'
            number = engine.load_image("./img/high_6.bmp")
            SDL::SDL_BlitSurface(number, nil, highscore_screen, rect)
          when char == '7'
            number = engine.load_image("./img/high_7.bmp")
            SDL::SDL_BlitSurface(number, nil, highscore_screen, rect)
          when char == '8'
            number = engine.load_image("./img/high_8.bmp")
            SDL::SDL_BlitSurface(number, nil, highscore_screen, rect)
          when char == '9'
            number = engine.load_image("./img/high_9.bmp")
            SDL::SDL_BlitSurface(number, nil, highscore_screen, rect)
          when char == '0'
            number = engine.load_image("./img/high_0.bmp")
            SDL::SDL_BlitSurface(number, nil, highscore_screen, rect)
          end
          rect.x += 32
          number = engine.load_image("./img/high_p.bmp")
          SDL::SDL_BlitSurface(number, nil, highscore_screen, rect)
        end
      end
    end
