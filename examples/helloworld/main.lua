local kite = require 'kite'
local window = require 'kite.window'
local gfx = require 'kite.graphics'
local bmpfont = require "kite.bmpfont"


-- the scale should be uint, this font size is 16px
local generic = bmpfont.create('examples/asset/generic.fnt', 'examples/asset/generic_0.png', 3)


local helloworld = gfx.sprite{
	x = 480,
	y = 420,
	texname = 'resource/icon.png'
}

local game = {}

function game.update(dt)
	-- print(kite.drawcall(), 1//dt)
end

function game.draw()
	
	gfx.clear(0x000000ff)
	helloworld.draw()
	generic.print('Hello World!', 480-100, 200)
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