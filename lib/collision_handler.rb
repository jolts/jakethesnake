#!/usr/bin/env ruby
require 'sdl'
require 'sprite'
require 'snake'

module JakeTheSnake
  class CollisionHandler
    
    def is_wall_collision(snake_head, wall)
      if (snake_head.x < wall.x or snake_head.y < wall.y or
          snake_head.x + 16 > wall.x + wall.w 
          or snake_head.y + 16 > wall.y + wall.h)
        return true
      end
      return false
    end

    def is_obstacles_collision(jake_body, obstacles)
      # iterator snake_part
      jake_body.each do |body_part|
        if body_part.x == obstacles.x and body_part.y == obstacles.y
          return true
        end
        false
      end
    end

    def is_self_snake_collision(

    
  end
