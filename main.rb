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
      run
    rescue StandardError => stderr
      $stderr.puts "\033[0;31mStandardError! \n\n\033[0m"+stderr.message.each_line { |lines| puts "> "+lines }
    rescue Exception => except
      $stderr.puts "\033[0;31mException! \n\n\033[0m"+except.message.each_line { |lines| puts "> "+lines }
    rescue TypeError => typerr
      $stderr.puts "\003[0;31mTypeError! \n\n\033[0m"+typerr.message.each_line { |lines| puts "> "+lines }
    end
  end
end
