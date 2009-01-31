#!/usr/bin/env ruby
require 'sprite'

module JakeTheSnake
  class Obstacles < Sprite
    def initalize(image)
      self.image = image
    end

    def draw(screen)
      apply_surface(x, y, self.image, screen)
    end

    private
    @@image = SDL::Surface
  end
end
