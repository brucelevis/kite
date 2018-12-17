local function Move(world)

	local self = {}
	
	local function get_moveing()
		return world.get_entities(function (e)
			return e.has['move'] and e.speed ~= 0
		end)
	end

	local bird = world.find_entity('bird')
	local camera = world.find_entity('camera')

	function self.update(dt)
		local entities = get_moveing()

		for _,e in ipairs(entities) do
			local distance = e.speed * dt
			e.x = e.x + distance * math.cos(e.direction * math.pi/180)
			e.y = e.y + distance * math.sin(e.direction * math.pi/180)		
		end

		camera.x = bird.x+bird.w/2 - 480
	end

	return self
end


return function ()
	return function (world)
		return Move(world)
	end
end