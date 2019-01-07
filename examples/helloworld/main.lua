local kite = require 'kite'
local window = require 'kite.window'
local gfx = require 'kite.graphics'


local helloworld = gfx.sprite{
	x = 100,
	y = 100,
	texname = 'examples/asset/icon.png'
}

local game = {}

function game.update(dt)
end

function game.draw()
	gfx.clear(0)
	helloworld.draw()
end

function game.mouse(what, x, y, who)
end

function game.keyboard(key, what)
end

function game.textinput(char)
end

function game.scroll(ox, xy)
end

function game.pause()
	print('pause')
end

function game.resume()
	print('resume')
end

function game.exit()
end



kite.start(game)