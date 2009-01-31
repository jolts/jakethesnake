#!/usr/bin/env ruby
require 'abstract_state'
require 'snake_engine'
require 'menu_state'

module JakeTheSnake
  class GameoverState < Abstract_State
    def key_pressed(key)
      if (key == SDL::SDKL_RETURN) 
        # When user presses return we go back to menu
        get_engine.set_state(Menu_State.new)
      end
    end
  end
end
