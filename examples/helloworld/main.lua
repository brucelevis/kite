local kite = require 'kite'
local window = require 'kite.window'
local gfx = require 'kite.graphics'


local game = {}

function game.update(dt)
end

function game.draw()
	gfx.clear(0xffffffff)
	gfx.draw('examples/asset/icon.png', 100, 100)
end

function game.mouse(what, x, y, who)
end

function game.keyboard(key, what)
	if what == 'press' then
		if key == 'q' then
			window.set_icon('examples/asset/icon.png')
		elseif key == 'a' then
			window.set_title('HHHHHHHHHHHHHH')
		elseif key == 'r' then
			window.resize(800, 300)
		elseif key == 'f' then
			window.fullscreen()
		end
	end
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