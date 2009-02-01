#!/usr/bin/env ruby
require 'abstract_state'
require 'collision_handler'
require 'obstacles'
require 'snake'
require 'snake_engine'

module JakeTheSnake
  class SingleState < AbstractState
    attr_accessor :apple, :carrot, :pacman, :ghost
    def initalize
      @@high_score_list = Array.new
      @@apple = Obstacles.new
      @@carrot = Obstacles.new
      @@pacman = Obstacles.new
      @@ghost = Obstacles.new
      @@rotten_carrot = Array.new
      @@apples = Array.new
      @@player1 = Snake.new
      collision_handler = Collision_Handler.new
      green_background = SDL::SDL_Rect
      @@pacman_is_alive = true
      @@player1.init(1)

      @@apple = Obstacles(Snake_Engine.new.load_image("./img/apple.bmp"))
      @@carrot = Obstacles(Snake_Engine.new.load_image("./img/carrot.bmp"))
      @@pacman = Obstacles(Snake_Engine.new.load_image("./img/pacman.bmp"))
      @@ghost = Obstacles(Snake_Engine.new.load_image("./img/ghost.bmp"))

      # Spawns 10 apples.
      # Get a random position until we find a free one
      10.times {
        begin
          sprite_x = (rand(1..608)+16).to_i
          sprite_y = (rand(1..448)+16).to_i
        end while (is_free(sprite_x, sprite_y) == false)
        @@apple.x = sprite_x
        @@apple.y = sprite_y
        @@apples << apple
      }
      apple_tick = 0

      # Tries to find a free coordinate for the ghost sprite.
      begin
        sprite_x = (rand(1..608)+16).to_i
        sprite_y = (rand(1..448)+16).to_i
      end while(is_free(sprite_x, sprite_y) == false)
      ghost.x = sprite_x
      ghost.y = sprite_y
      ghost_tick = 0

      # Tries to find a free coordinate for the ghost sprite.
      begin
        sprite_x = (rand(1..608)+16).to_i
        sprite_y = (rand(1..448)+16).to_i
      end while(is_free(sprite_x, sprite_y) == false)
      pacman.x = sprite_x
      pacman.y = sprite_y
      pacman_tick = 0

      25.times do {
          begin
            sprite_x = (rand(1..608)+16).to_i
            sprite_y = (rand(1..448)+16).to_i
          end while(is_free(sprite_x, sprite_y) == false)
          carrot.x = sprite_x
          carrot.y = sprite_y
          rotten_carrots << carrot
        }
        carrot_tick = 0

        green_background.x = 16
        green_background.y = 16
        green_background.w = 608
        green_background.h = 448

        finished = false

        # Sets the initial direction to the right

        @@p1dir = 2
        @@p1points = 0

        # Everything a event happens that increases size, 3 parts are added
        @@p1_parts_to_add = 3
      end

      def is_free(x, y) 
        @@apples.each do |apple|
          if apple.x == x and apple.y == y
            false
          end
        end

        rotten_carrots.each do |rotten_carrot|
          if rotten_carrot.x = x and rotten_carrot.y == y
            false
          end
        end

        player1.snake_body.each do |body_part|
          if body_part.x == x and body_part.y == y
            false
          end
        end

        if ghost.x == x and ghost.y == y
          false
        end
        true
      end
    end

    def key_pressed(key)
      case key
      when SDL::SDLK_UP
        # The != handles that there isnt a opposite direction
        # that for example, if he's going up he can't go down.
        if player1.direction != 3
          @@p1dir = 1
        end
        break
      when SDL::SDLK_RIGHT
        if player1.direction != 4
          @@p1dir = 2
        end
        break
      when SDL::SDLK_DOWN
        if player.direction != 1
          @@p1dir = 3
        end
        break
      when SDL::SDLK_LEFT
        if player1.direction != 2
          @@p1dir = 4
        end
        break
      end
    end

    def clock_tick
      player1.move(@@p1dir)
      check_collisions

      if p1_parts_to_add != 0
        # If theres body to add, add one
        player1.add_parts(1)
        p1_parts_to_add -= 1
      end

      move_carrot
      move_apple
      move_ghost
      #move_pacman
    end

    def draw(surface)
      # Draws all the sprites for a single player
      SDL::SDL_FillRect(surface, green_background, 
                        SDL::SDL_MapRGB(surface.format, 0x61,0xAD, 0x2F))
      player1.draw(surface)

      # Draw carrots
      rotten_carrots.each do |rotten_carrot|
        rotten_carrot.draw(surface)
      end

      # Draw apples
      @@apples.each do |apple|
        apple.draw(surface)
      end

      ghost.draw(surface)

      if pacman_is_alive
        pacman.draw(surface)
      end

      if finished
        SDL::Delay(2000)
        high_score(@@p1points)
        get_engine.set_state(Highscore_State.new)
      end
    end

    def check_collisions
      # Defines temporary sprite x,y coordinates
      sprite_x = Integer.new
      sprite_y = Integer.new

      if collision_handler.is_wall_collision(player1.snake_body[0], green_background)
        finished = true
      end

      if collision_handler.is_self_snake_collision(player1.snake_body)
        finished = true
      end

      if collision_handler.is_obstacles_collision(player1.snake_body, ghost)
        if player1.snake_body.length == 2
          finished = true
        else
          player1.remove_parts((player1.snake_body.length / 2))
          begin
            sprite_x = rand((1..608)+16).to_i
            sprite_y = rand((1..448)+16).to_i
          end while is_free_ghost(sprite_x, sprite_y) == false
          ghost.x = sprite_x
          ghost.y = sprite_y
        end
        player1.rainbow = false
        @@p1points -= 15
      end

      rotten_carrots.each do |rotten_carrot|
        if collision_handler.is_obstacles_collision(player1.snake_body, rotten_carrot)
          if player1.snake_body.length == 2
            finished = true
          else
            player1.remove_parts((player1.snake_body.length / 3))
            begin
              sprite_x = (rand(1..608)+16)
              sprite_y = (rand(1..448)+16)
            end while (is_free(sprite_x, sprite_y) == false)
            rotten_carrot.x = sprite_x
            rotten_carrot.y = sprite_y
          end
          player1.rainbow = false
          @@p1points -= 10
        end
      end

      @@apples.each do |apple|
        if collision_handler.is_obstacles_collision(player1.snake_body, apple)
          if player1.rainbow
            p1points += 10
          else
            p1points += 5
          end
          p1parts_to_add += 3
          begin
            sprite_x = (rand(1..608)+16)
            sprite_y = (rand(1..448)+16)
          end while (is_free(sprite_x, sprite_y) == false)
          apple.x = sprite_x
          apple.y = sprite_y
        end
      end

      apples.each do |apple|
        if apple.x == ghost.x and apple.y == ghost.y
          begin 
            sprite_x = (rand(1..608)+16)
            sprite_y = (rand(1..448)+16)
          end while (is_free(sprite_x, sprite_y) == false)
          apple.x = sprite_x
          apple.y = sprite_y
        end
      end

      rotten_carrots.each do |rotten_carrot|
        if rotten_carrot.x == ghost.x and rotten_carrot.y == ghost.y
          begin 
            sprite_x == (rand(1..608)+16)
            sprite_y == (rand(1..448)+16)
          end while (is_free(sprite_x, sprite_y) == false)
          rotten_carrot.x = sprite_x
          rotten_carrot.y = sprite_y
        end
      end

      if collision_handler.is_obstacles_collision(player1.snake_body, @@pacman)
        player1.rainbow = true
        p1points += 25
        @@pacman.x = -16
        @@pacman.y = -16
        pacman_is_alive = false
      end
    end

    def high_score(score)
      in_score = Float.new
      in_score = 0.1 + score
      filename = "high_score.txt"
      input = File.open(filename, 'a+')

      input.each_line do |line|
        high_score_list << line
      end

      high_score_list << in_score
      high_score_list.sort
      high_score_list.reverse # Highest score on top
      input.close

      output = File.open(filename, 'a+')
      i = 0

      high_score_list.each do |score|
        if score < 5
          output.write(score + '\n')
          i += 1
        end
      end
      output.close
    end

    def is_free_ghost(x, y)
      @@apples.each do |apple|
        if apple.x == x and apple.y == y
          false
        end
      end

      rotten_carrots.each do |rotten_carrot|
        if rotten_carrot.x == x and rotten_carrot.y == y
          false
        end
      end

      player1.snake_body.each do |body_part|
        if body_part.x == x and body_part.y == y
          false
        end
      end
      true
    end

    def move_carrot
      carrot_tick +=1 # Is added every tick
      if carrot_tick == 10 # When it updates every 10th tick
        carrot = rotten_carrots[-2]
        rotten_carrots.pop
        begin
          sprite_x = (rand(1..608)+16)
          sprite_y = (rand(1..448)+16)
        end while (is_free(sprite_x, sprite_y) == false)
        @@carrot.x = sprite_x
        @@carrot.y = sprite_y

        rotten_carrots[0] = carrot
        carrot_tick = 0
      end
    end

    def move_apple
      apple_tick += 1
      if apple_tick == 20
        apple = @@apples[-2]
        apples.pop
        begin
          sprite_x = (rand(1..608)+16).to_i
          sprite_y = (rand(1..448)+16).to_i
        end while (is_free(sprite_x, sprite_y) == false)
        @@apple.x = sprite_x
        @@apple.y = sprite_y

        apples[0] = apple
        apple_tick = 0
      end
    end

    def move_ghost
      ghost_tick +=1
      if ghost_tick == 5
        if player1.snake_body[0].x < @@ghost.x 
          @@ghost.x -= 16
        elsif player1.snake_body[0].x > @@ghost.x
          @@ghost.x += 16
        end

        if player1.snake_body[0].y < @@ghost.y
          @@ghost.y -= 16
        elsif player1.snake_body[0].y > @@ghost.y
          @@ghost.y += 16
        end
        ghost_tick = 0
      end
    end
  end
end
