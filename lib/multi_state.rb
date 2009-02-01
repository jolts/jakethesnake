#!/usr/bin/env ruby
require 'abstract_state'
require 'collision_handler'
require 'obstacles'
require 'snake'
require 'snake_engine'

module JakeTheSnake
  class MultiState < AbstractState
    attr_accessor :apple, :carrot
    def initialize
      @@high_score_list = Array.new
      @@apple = Obstacles.new
      @@carrot = Obstacles.new
      @@rotten_carrot = Array.new

      @@apple = Obstacles(Snake_Engine.new.load_image("./img/apple.bmp"))
      @@carrot = Obstacles(Snake_Engine.new.load_image("./img/carrot.bmp"))

      @@player1.init(1)
      @@player2.init(2)

      # Spawns 35 carrots.
      # Get a random position until we find a free one
      35.times {
        begin
          sprite_x = (rand(1..608)+16).to_i
          sprite_y = (rand(1..448)+16).to_i
        end while (is_free(sprite_x, sprite_y) == false)
        @@carrot.x = sprite_x
        @@carrot.y = sprite_y
        @@rotten_carrot << carrot
      }
      apple_tick = 0

      # FIXME
      #
      #
      #
    end
  end
end
