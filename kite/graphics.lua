local core = require 'graphics.core'
local sprite2d = require "sprite2d.core"
local mgr = require "kite.manager"
local shader = mgr.program.sprite


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
		color = t.color or 0xffffffff,
		texcoord = t.texcoord or {0,1, 0,0, 1,0, 1,1},

		border = t.border
	}

	local x1 = self.x - self.ax*self.w
	local y1 = self.y - self.ay*self.h

	self.id = sprite2d.create(tex.id,
		x1, y1 + self.h,
		x1, y1,
		x1 + self.w, y1,
		x1 + self.w, y1 + self.h,
		table.unpack(self.texcoord))

	function self.pos(x, y)
		if x == self.x and y == self.y then return end
		self.x = x
		self.y = y
		local x1 = self.x - self.ax*self.w
		local y1 = self.y - self.ay*self.h
		
		sprite2d.set_position(
				self.id,
				x1, y1 + self.h,
				x1, y1,
				x1 + self.w, y1,
				x1 + self.w, y1 + self.h
			)
	end

	function self.draw()
		if self.border then
			local x = self.x
			local y = self.y
			shader.set_color(self.border.color)

			self.pos(x-self.border.size, y)
			core.draw(self.id)
			
			self.pos(x+self.border.size, y)
			core.draw(self.id)
			
			self.pos(x, y-self.border.size)
			core.draw(self.id)
			
			self.pos(x, y+self.border.size)
			core.draw(self.id)
		end

		shader.set_color(self.color)
		M.draw(self.id)
	end

	return self
end

return setmetatable(M, {__index = core})