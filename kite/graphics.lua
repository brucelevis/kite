local core = require 'graphics.core'


local M = {}

local textures = {}


function M.texture(name)
	local tex = textures[name]
	if tex then
		return tex
	end

	local id, w, h = core.texture(name)
	textures[name] = { id = id, w = w, h = h }
	return textures[name]
end


local default_texcoord = {0,1, 0,0, 1,0, 1,1}

function M.draw(texname, x, y, ax, ay, rotate, color, w, h, texcoord)
	local tex = M.texture(texname)
	ax = ax or 0.5
	ay = ay or 0.5
	rotate = rotate or 0
	color = color or 0xffffffff
	w = w or tex.w
	h = h or tex.h
	texcoord = texcoord or default_texcoord
	core.draw(tex.id, x, y, ax, ay, rotate, color, w, h, table.unpack(texcoord))
end


return setmetatable(M, {__index = core})