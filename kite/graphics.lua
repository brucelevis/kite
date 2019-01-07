local core = require 'graphics.core'
local sprite2d = require "sprite2d.core"
local program = require "program.core"
local matrix = require "matrix.core"
local window = require "kite.window"

local function create_sprite_program()
	local shader = require "kite.shader.sprite"
	local mat = matrix.ortho(0, window.width, 0, window.height, -1, 1)

	local id = program.create(shader.vs, shader.fs)
	core.use(id)
	local texture0 = program.uniform_location(id, "texture0")
	local projection = program.uniform_location(id, "projection")
	local color = program.uniform_location(id, "color")
	
	program.uniform_1i(texture0, 0)
	program.uniform_matrix4fv(projection, mat)
	program.uniform_4f(color, 1, 1, 1, 1)

	return id
end


create_sprite_program()


local M = {}

local textures = {}


function M.texture(name)
	local tex = textures[name]
	if tex then
		return tex
	end

	local id, w, h = core.texture(name)

	textures[name] = { id = id, name = name,  w = w, h = h }
	return textures[name]
end


function M.sprite(t)
	local tex = M.texture(t.texname or 'resource/white.png')
	local self = {
		x = t.x or 0,
		y = t.y or 0,
		ax = t.ax or 0.5,
		ay = t.ay or 0.5,
		w = t.w or tex.w,
		h = t.h or tex.h,
		texcoord = t.texcoord or {0,1, 0,0, 1,0, 1,1}
	}

	local x1 = self.x - self.ax*self.w
	local y1 = self.y - self.ay*self.h

	self.id = sprite2d.create(tex.id,
		x1, y1 + self.h,
		x1, y1,
		x1 + self.w, y1,
		x1 + self.w, y1 + self.h,
		table.unpack(self.texcoord))

	function self.draw()
		M.draw(self.id)
	end

	return self
end

return setmetatable(M, {__index = core})