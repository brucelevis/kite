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
uniform uint color;


void main() {

	vec4 tmp = texture(texture0, texcoord);

	float r = float(int(color >> 24) & 0xff)/255;
	float g = float(int(color >> 16) & 0xff)/255;
	float b = float(int(color >> 8) & 0xff)/255;
	float a = float(int(color) & 0xff)/255;

	frag_color.xyz = tmp.xyz * vec3(r, g, b);
	frag_color.w = tmp.w;
	frag_color *= a;
}
]]

return {
	vs = vs,
	fs = fs
}