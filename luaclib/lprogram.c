#include "lmatrix.h"
#include "lprogram.h"



static int
luniform_4f(lua_State *L) {
	uint32_t id;
	float a, b, c, d;
	id = luaL_checkinteger(L, 1);
	a = lua_tonumber(L, 2);
	b = lua_tonumber(L, 3);
	c = lua_tonumber(L, 4);
	d = lua_tonumber(L, 5);
	glUniform4f(id, a, b, c, d);
	return 0;
}



static int
luniform_1i(lua_State *L) {
	uint32_t id;
	int n;
	id = luaL_checkinteger(L, 1);
	n = lua_tointeger(L, 2);
	glUniform1i(id, n);
	return 0;
}


static int
luniform_matrix4fv(lua_State *L) {
	uint32_t id;
	mat4x4 *m;
	id = luaL_checkinteger(L, 1);
	m = lua_touserdata(L, 2);
	glUniformMatrix4fv(id, 1, GL_FALSE, (const float *)m);
	return 0;
}


static int
luniform_location(lua_State *L) {
	uint32_t prog, id;
	const char *name;
	prog = luaL_checkinteger(L, 1);
	name = luaL_checkstring(L, 2);
	id = glGetUniformLocation(prog, name);
	lua_pushinteger(L, id);
	return 1;
}


uint32_t
create_shader(GLenum type, const char *data, int sz) {
	GLuint shader = glCreateShader(type);
	ASSERT(shader != 0, "failed to create shader\n");
	glShaderSource(shader, 1, &data, &sz);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar info[1024];
		glGetShaderInfoLog(shader, 1024, NULL, info);
		fprintf(stderr, "faield to compile shader[%d], '%s'\n", type, info);
		exit(1);
	}
	return shader;
}


static int
lcreate(lua_State *L) {
	uint32_t program, vs, fs;
	const char *vs_text;
	const char *fs_text;
	size_t vsz, fsz;
	vs_text = luaL_checklstring(L, 1, &vsz);
	fs_text = luaL_checklstring(L, 2, &fsz);

	vs = create_shader(GL_VERTEX_SHADER, vs_text, vsz);
	fs = create_shader(GL_FRAGMENT_SHADER, fs_text, fsz);
	program = glCreateProgram();
	glAttachShader(program, fs);
	glAttachShader(program, vs);
	glLinkProgram(program);

	GLint success = 0;
	GLchar err_info[1024] = { 0 };
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, sizeof(err_info), NULL, err_info);
		fprintf(stderr, "failed to link shader program: '%s'\n", err_info);
		exit(1);
	}
	glDeleteShader(vs);
	glDeleteShader(fs);
	lua_pushinteger(L, program);
	return 1;
}


int
lib_program(lua_State *L)
{
	luaL_Reg l[] = {
		{"uniform_4f", luniform_4f},
		{"uniform_1i", luniform_1i},
		{"uniform_matrix4fv", luniform_matrix4fv},
		{"uniform_location", luniform_location},
		{"create", lcreate},
		{NULL, NULL}
	};
	luaL_newlib(L, l);
	return 1;
}