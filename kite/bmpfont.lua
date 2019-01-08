local gfx = require "kite.graphics"
local mgr = require "kite.manager"


local function load(name)
	local f = assert(io.open(name, 'r'), name)
	local i = 0
	local font = { char = {}, kerning = {} }
	
	local char = font.char
	local kerning = font.kerning

	while true do
		i = i + 1
		local text = f:read('l')
		if text then

			local prop = string.match(text, "(%w+)")

			local t = {}
			for k, v in string.gmatch(text, "(%w+)=(-?%d+)") do
				t[k] = tonumber(v)
			end
			for k, v in string.gmatch(text, '(%w+)="([^"]*)') do
				t[k] = v
			end

			if prop == 'char' then
				t.id = tonumber(t.id)
				char[t.id] = t
			elseif prop == 'kerning' then 
				kerning[t.first] = kerning[t.first] or {}
				kerning[t.first][t.second] = t.amount 
			else
				font[prop] = t
			end
		else
			f:close()
			break
		end
	end
	return font
end


local M = {}


function M.create(name, bitmap, scale)
	scale = scale or 1
	local font = load(name)
	local tex = gfx.texture(bitmap)

	local width = tex.w
	local height = tex.h

	for _,c in pairs(font.char) do
		local sp = gfx.sprite{
			ax = 0,
			ay = 1,
			w = c.width * scale,
			h = c.height * scale,
			texname = bitmap,
			texcoord = {
				c.x/width, (height-c.y)/height,
				c.x/width, (height-c.y-c.height)/height,
				(c.x+c.width)/width, (height-c.y-c.height)/height,
				(c.x+c.width)/width, (height-c.y)/height
			}
		}
		c.sprite = sp
	end

	local self = {}
	
	function self.print(text, x, y, color, border)
		
		-- this font y offset is 1 * scal
		y = y - math.floor(scale)

		color = color or 0xffffffff
		local first
		for _,id in utf8.codes(text) do
			local c = assert(font.char[id], 'no this char '..tostring(id))
			
			local mx = x + c.xoffset * scale
			local my = y - c.yoffset * scale

			if first then
				local amount = font.kerning[first] and font.kerning[first][id]
				if amount then
					mx = mx + amount
				end
			end

			local sp = c.sprite
			sp.color = color
			sp.border = border
			sp.pos(mx, my)
			sp.draw()
			
			x = mx + c.xadvance * scale
			first = id
		end
	end

	return self
end


return M