#!/usr/bin/env ruby
require 'sdl'
require 'sprite'
require 'snake'

module JakeTheSnake
  class CollisionHandler
    def is_wall_collision(snake_head, wall)
      if (snake_head.x < wall.x) || (snake_head.y < wall.y) 
        || (snake_head.x + 16 > wall.x + wall.w) 
        || (snake_head.y + 16 > wall.y + wall.h)
        true
      else 
        false
      end
    end


    def is_obstacles_collision(jake_body, obstacles)
      # iterator snake_part
      jake_body.each do |body_part|
        if body_part.x == obstacles.x && body_part.y == obstacles.y
          true
        else
          false
        end
      end
    end

    def is_self_snake_collision(snake)
      # Checks whether one part of the snake
      # collides with another part.
      snake.each do |first_part|
        snake.each do |second_part|
          second_part +=1
          if first_part.x == second_part.x or 
              first_part.y == second_part.y
            return true
          else
            return false
          end
        end
      end
    end

    def is_player1_player2_collision(player1, player2)
      if player1[0].x == player2[0].x && player1[0].y == player2[0].y
        3 # Head to head collision
      end

      player1.each do |player|
        if player.x == player2[0].x && player.y == player2[0].y
          2 # Player 2 looose
        end
      end

      player2.each do |player|
        if player.x == player1[0].x && player.y == player1[0].y
          1 # Player 1 loose
        end
      end
      0 # No collision
    end
  end


