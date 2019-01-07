local vs = [[
#version 330 core
layout (location = 0) in vec4 vertex; // [pos, tex]

out vec2 texcoord;

uniform mat4 projection;

void main()
{
	gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);	
	texcoord = vertex.zw;
}
]]


local fs = [[
#version 330

out vec4 frag_color;
in vec2 texcoord;


uniform sampler2D texture0;
uniform vec4 color;


void main() {
	vec4 tmp = texture(texture0, texcoord);
	frag_color.xyz = tmp.xyz * color.xyz;
	frag_color.w = tmp.w;
	frag_color *= color.w;
}
]]

return {
	vs = vs,
	fs = fs
}