local kite = require 'kite'


local game = {}

function game.update(dt)
end

function game.draw()
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