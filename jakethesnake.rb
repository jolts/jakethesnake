#!/usr/bin/env ruby

require 'lib/abstract_state'
require 'lib/collision_handler'
require 'lib/gameover_state'
require 'lib/game'
require 'lib/highscore_state'
require 'lib/menu_state'
require 'lib/multi_state'
require 'lib/obstacles'
require 'lib/single_state'
require 'lib/snake_engine'
require 'lib/snake'
require 'lib/sprite'

require 'sdl'

module JakeTheSnake
  class Game
    def initalize
    end

    def run
      engine = Snake_Engine.new(640, 480, false)
      state = Menu_State.new
      engine.set_state(state)
      engine.set_tick_interval(100)
      engine.loop
    end

    # Run the game!
    begin
      run
    rescue StandardError => err
      $stderr.puts "\033[0;31mStandardError!: \n\n>\033[0m#{err.message}"
    rescue Exception => exp
      $stderr.puts "\033[0;31mException!: \n\n>\033[0m#{exp.message}"
    end
  end
end
