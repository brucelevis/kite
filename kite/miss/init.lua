-------------------------------------------------------------------
--
-- miss is ui framework like web
--
-------------------------------------------------------------------
local window = require "kite.window"
local gfx = require "kite.graphics"


local M = {}

function M.update()
end

local ui = {
	type = 'div', id = 'app',
	{type='img', src='resource/icon.png', width=100, height=100, style={float='left'}},
	{type='img', src='resource/icon.png', width=100, height=100, style={float='left'}}
}

local draw = {}
local sprites = {}

function draw.div(style, e)
	local color = e.style and e.style.color
	if not color then return style end

	local sp = sprites[e]
	if not sp then
		sprites[e] = gfx.sprite{x=window.width/2, y=window.height/2, w=window.width, h=window.height}
		sp = sprites[e]
	end
	sp.draw()
	return style
end

function draw.img(style, e)
	local sp = sprites[e]
	if not sp then
		local x = style.x
		local y = style.y
		if e.style.float == 'left' and style.float == 'left' then
			x = x + style.w
		else
			x = 0
			y = y - style.h
		end

		sprites[e] = gfx.sprite{x=x, y=y, ax=0, ay=1, texname=e.src, w=e.width, h=e.height}
		sp = sprites[e]
	end
	sp.draw()
	return {x=style.x, y=style.y, float=e.style.float, w=sp.w, h=sp.h}
end


local function draw_widget(style, widget)
	local f = draw[widget.type]
	local new_style = f(style, widget)
	for _,w in ipairs(widget) do
		local f = draw[w.type]
		new_style = f(new_style, w)
	end
end

function M.draw()
	local style = {x=0, y=window.height, w=0, h=0}
	draw_widget(style, ui)
end


return M