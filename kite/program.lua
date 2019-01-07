-- local core = require "program.core"

-- local M = {}


-- function M.create(vs, fs)
-- 	local self = {}

-- 	self.id = core.create(vs, fs)

-- 	function self.uniform_location(name)
-- 		return core.uniform_location(self.id, name)
-- 	end

-- 	function self.uniform_matrix4fv(mat)
-- 		core.uniform_matrix4fv(self.id, mat)
-- 	end

-- 	function self.uniform_1i(n)
-- 		core.uniform_1i(self.id, n)
-- 	end

-- 	function self.uniform_4f(a, b, c, d)
-- 		core.uniform_4f(self.id, a, b, c, d)
-- 	end

-- 	return self
-- end


-- return setmetatable(M, {__index = core})