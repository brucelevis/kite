local kite = require "kite"
local gfx = require "kite.graphics"
local progmgr = require "kite.manager.program"
local fontmgr = require "kite.manager.font"
local widget = require "kite.miss.widget"
local program = (require "kite.manager.program").get_sprite_program()


-- load
fontmgr.load('generic', 'examples/asset/generic.fnt', 'examples/asset/generic_0.png')


local helloworld = gfx.test_sprite {
		x = 960,
		y = 640,
		w = 100,
		h = 100,
		ax = 1,
		ay = 1,
		texname = 'resource/icon.png'
	}


local label = widget.text{ font = 'generic', x = 480, y = 320, align = 'center', text = 'Hello World!', size = 32, color=0xbe2137ff }

local button = widget.button { x = 480-100/2, y = 200, w = 100, h = 32, text='button' }


local game = {}

function game.update(dt)
	-- print(kite.drawcall(), 1//dt)
end

function game.draw()
	gfx.clear(0xf5f5f5ff)

	program.set_color(0xffffffff)
	helloworld.draw()

	label.draw()
	button.draw()
end

function game.mouse(what, x, y, who)
end

function game.keyboard(key, what)
	if what == 'release' and key == 'escape' then
		kite.exit()
	end

	if what == 'release' then
		if key == 'a' then
			button('mouse_enter')
		elseif key == 'b' then
			button('mouse_leave')
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