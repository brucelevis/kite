local kite = require 'kite'
local window = require 'kite.window'
local gfx = require 'kite.graphics'


local sp = {}

for i=1,1 do
	local helloworld = gfx.sprite{
		x = 480,
		y = 320,
		texname = 'resource/icon.png'
	}
	table.insert(sp, helloworld)	
end

local game = {}

function game.update(dt)
	-- print(kite.drawcall(), 1//dt)
end

function game.draw()
	gfx.clear(0)
	for i,v in ipairs(sp) do
		v.draw()
	end
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