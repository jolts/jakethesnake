#!/usr/bin/env ruby
require 'snake_engine'
require 'sdl'

module JakeTheSnake
  class Abstract_State
    attr_accessor :engine, :screen
    def initalize
      engine = SnakeEngine.new
      self.engine = 0
    end

    def draw(surface)
    end

    def clock_tick
    end

    def key_pressed(key)
    end
  end
end
