#!/usr/bin/env ruby
require 'sprite'
require 'snake_engine'

module JakeTheSnake
  attr_accessor :length, :direction, :rainbow

  class Snake < Sprite
    def initalize
      snake_body = Array.new
      @@snake_surface = SDL::Surface
      @@instance = Integer.new # Keeps track of whether its player1 or player2
      @@rainbow = false
    end

    def init(m_player)
      rainbow = false
      direction = 2
      length = 3
      x = 128
      y = 0 + 160 * m_player # Gives us coordinates for our players
      instance = m_player
      head = true
      
      0.upto(length) do |part|
        snake_part.is_head = head
        snake_part.x = x
        snake_part.y = y
        snake_body << snake_part
        x -= 16
        head = false
      end
    end
    
    def draw(screen)
      snake_body.each do |body_part|
        if body_part.is_head
          # Loads differenet pictures depending on whether its player1
          # or player2.
          if instance == 1
            snake_surface = load_image("./img/player_1_head.bmp")
          else
            snake_surface = load_image("./img/player_2_head.bmp")
          end
          
        else
          if !rainbow
            snake_surface = load_image("./img/player_body.bmp")
          else
            snake_surface = load_image("./img/player_rainbow.bmp")
          end
        end
        apply_surface(body_part.x, body_part.y, snake_surface, screen)
      end
    end

    def move(direction)
      case direction
      when 1
        # size - 1, otherwise we'll go out of range
        (snake_body-1).each do |body_part|
          body_part.x = (body_part-1).x
          body_part.y = (body_part-1).y
        end
        snake_body[0].y -= 16 # Move the snake upwards 16 pixels
        break
      when 2
        (snake_body-1).each do |body_part|
          body_part.y = (body_part-1).y
          body_part.y = (body_part-1).y
        end
        snake_body[0].x += 16 # Move the snake left 16 pixels
        break
      when 3
        (snake_body-1).each do |body_part|
          body_part.y = (body_part-1).y
          body_part.y = (body_part-1).y
        end
        snake_body[0].y += 16 # Move the snake down 16 pixels
        break
      when 4
        (snake_body-1).each do |body_part|
          body_part.y = (body_part-1).y
          body_part.y = (body_part-1).y
        end
        snake_body[0].x -= 16 # Move the snake right 16 pixels
        break
      end
    end
    
    def add_part(n)
      0.upto(n) do |part|
        snake_part.is_head = false
        # Adds any part to the back of snake
        snake_part.x = snake_body[-1].x
        snake_part.y = snake_body[-1].y
        snake_body << snake_part
      end
    end
  end
end
