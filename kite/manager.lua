----------------------------------------------------------------------
--
-- program manager
--
----------------------------------------------------------------------
local core = require "program.core"
local matrix = require "matrix.core"
local gfx = require "graphics.core"
local window = require "kite.window"


local M = {}

local current	-- active program

local function use_program(id)
	if current ~= id then
		gfx.use(id)
		current = id
	end
	return id
end

----------------------------------------------------------------
-- default shader program
----------------------------------------------------------------
function M.create_sprite_program()
	local shader = require "kite.shader.sprite"
	local mat_p = matrix.ortho(0, window.width, 0, window.height, -1, 1)
	local id =  use_program(core.create(shader.vs, shader.fs))

	-- props index
	local i_texture0 = core.uniform_location(id, "texture0")
	local i_projection = core.uniform_location(id, "projection")
	local i_color = core.uniform_location(id, "color")

	-- init
	core.uniform_1i(i_texture0, 0)
	core.uniform_matrix4fv(i_projection, mat_p)
	core.uniform_1ui(i_color, 0xffffffff)

	-- current
	local cur_color = 0xffffffff


	-- interface
	local self = {}

	function self.active()
		use_program(id)
		return self
	end

	function self.set_projection(mat_p)
		assert(current == id)
		core.uniform_matrix4fv(i_projection, mat_p)
		return self
	end

	function self.set_color(color)
		assert(current == id)
		if color ~= cur_color then
			core.uniform_1ui(i_color, color)
			cur_color = color
		end
		return self
	end

	return self
end

----------------------------------------------------------------
-- your shader program here
----------------------------------------------------------------




----------------------------------------------------------------
-- loaded program
----------------------------------------------------------------
M.program = {
	sprite = M.create_sprite_program()
	--
	-- your program here
	--
}

return setmetatable(M, {__index = core})