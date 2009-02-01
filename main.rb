#!/usr/bin/env ruby

require 'lib/abstract_state'
require 'lib/collision_handler'
require 'lib/gameover_state'
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
      # FIXME?
    end

    def run
      engine = Snake_Engine.new(640, 480, false)
      state = MenuState.new
      engine.set_state(state)
      engine.set_tick_interval(100)
      engine.loop
    end

    # Run the game!
    begin
      run or raise LolError # Just trying :D
    rescue LolError
      $stderr.puts "\033[0;31mError! \n\n\033[0m"+lolerr.message.each_line { |lines| puts "> "+lines }
    rescue Exception => except
      $stderr.puts "\033[0;31mException! \n\n\033[0m"+except.message.each_line { |lines| puts "> "+lines }
    end
  end
end
