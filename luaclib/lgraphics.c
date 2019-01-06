#include <math.h>

#include "lgraphics.h"
#include "game.h"
#include "util.h"


extern Game * G;


static void
ROTATE(float x0, float y0, float a, float x1, float y1, float *x, float *y) {
	*x = (x1 - x0)*cos(a) - (y1 - y0)*sin(a) + x0;
	*y = (x1 - x0)*sin(a) + (y1 - y0)*cos(a) + y0;
}


static int
ldraw(lua_State *L) {
	GLuint texture;
	float x, y, w, h, ax, ay, rotate, posx, posy;
	uint32_t color;
	float vertices[4][4];

	texture = luaL_checkinteger(L, 1);
	x = floor(luaL_checknumber(L,2));
	y = floor(luaL_checknumber(L,3));
	ax = luaL_checknumber(L, 4);
	ay = luaL_checknumber(L, 5);
	rotate = luaL_checknumber(L, 6) * M_PI/180.f;
	color = luaL_checkinteger(L, 7);
	w = luaL_checknumber(L, 8);
	h = luaL_checknumber(L, 9);

	vertices[0][2] = luaL_checknumber(L, 10);
	vertices[0][3] = luaL_checknumber(L, 11);
	vertices[1][2] = luaL_checknumber(L, 12);
	vertices[1][3] = luaL_checknumber(L, 13);
	vertices[2][2] = luaL_checknumber(L, 14);
	vertices[2][3] = luaL_checknumber(L, 15);
	vertices[3][2] = luaL_checknumber(L, 16);
	vertices[3][3] = luaL_checknumber(L, 17);

	// 左下角的世界坐标
	posx = x - ax * w;
	posy = y - ay * h;

	ROTATE(x, y, rotate, posx, posy+h,   &vertices[0][0], &vertices[0][1]);
	ROTATE(x, y, rotate, posx, posy,     &vertices[1][0], &vertices[1][1]);
	ROTATE(x, y, rotate, posx+w, posy,   &vertices[2][0], &vertices[2][1]);
	ROTATE(x, y, rotate, posx+w, posy+h, &vertices[3][0], &vertices[3][1]);

	G->renderer->draw(&vertices[0][0], texture, color, PROGRAM_SPRITE);
	return 0;
}


static int
lclear(lua_State *L) {
	uint32_t c;
	c = luaL_checkinteger(L, 1);
	glClearColor(R(c), G(c), B(c), A(c));
	return 0;
}


static int
ltexture(lua_State *L) {
	GLuint texture;
	const char *filename;
	int width, height, channel;
	unsigned char *data;

	filename = luaL_checkstring(L, 1);
	data = load_image(filename, &width, &height, &channel, true);

	glGenTextures(1, &texture);
	G->renderer->bind_texture(texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	
	destroy_image(data);

	lua_pushinteger(L, texture);
	lua_pushinteger(L, width);
	lua_pushinteger(L, height);
	return 3;
}


int
lib_graphics(lua_State *L)
{
	luaL_Reg l[] = {
		{"draw", ldraw},
		{"clear", lclear},
		{"texture", ltexture},
		{NULL, NULL}
	};
	luaL_newlib(L, l);
	return 1;
}