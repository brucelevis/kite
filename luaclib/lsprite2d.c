#include "game.h"
#include "lsprite2d.h"



static int
lset_texcoord(lua_State *L) {
	Sprite2D *sprite2d = lua_touserdata(L, 1);
	sprite2d->p0[2] = lua_tonumber(L, 2);
	sprite2d->p0[3] = lua_tonumber(L, 3);
	sprite2d->p1[2] = lua_tonumber(L, 4);
	sprite2d->p1[3] = lua_tonumber(L, 5);
	sprite2d->p2[2] = lua_tonumber(L, 6);
	sprite2d->p2[3] = lua_tonumber(L, 7);
	sprite2d->p3[2] = lua_tonumber(L, 8);
	sprite2d->p3[3] = lua_tonumber(L, 9);
	return 0;
}


static int
lset_position(lua_State *L) {
	Sprite2D *sprite2d = lua_touserdata(L, 1);
	sprite2d->p0[0] = lua_tonumber(L, 2);
	sprite2d->p0[1] = lua_tonumber(L, 3);
	sprite2d->p1[0] = lua_tonumber(L, 4);
	sprite2d->p1[1] = lua_tonumber(L, 5);
	sprite2d->p2[0] = lua_tonumber(L, 6);
	sprite2d->p2[1] = lua_tonumber(L, 7);
	sprite2d->p3[0] = lua_tonumber(L, 8);
	sprite2d->p3[1] = lua_tonumber(L, 9);
	return 0;
}


static int
lset_texture(lua_State *L) {
	Sprite2D *sprite2d = lua_touserdata(L, 1);
	GLuint texture = lua_tointeger(L, 2);
	sprite2d->texture = texture;
	return 0;
}


static int
lcreate(lua_State *L) {
	uint32_t texture = luaL_checkinteger(L, 1);

	Sprite2D *sprite2d = lua_newuserdata(L, sizeof(Sprite2D));
	sprite2d->texture = texture;
	// position (let-top Anti-clockwise)
	sprite2d->p0[0] = lua_tonumber(L, 2);
	sprite2d->p0[1] = lua_tonumber(L, 3);
	sprite2d->p1[0] = lua_tonumber(L, 4);
	sprite2d->p1[1] = lua_tonumber(L, 5);
	sprite2d->p2[0] = lua_tonumber(L, 6);
	sprite2d->p2[1] = lua_tonumber(L, 7);
	sprite2d->p3[0] = lua_tonumber(L, 8);
	sprite2d->p3[1] = lua_tonumber(L, 9);
	// texcoord (let-top Anti-clockwise)
	sprite2d->p0[2] = lua_tonumber(L, 10);
	sprite2d->p0[3] = lua_tonumber(L, 11);
	sprite2d->p1[2] = lua_tonumber(L, 12);
	sprite2d->p1[3] = lua_tonumber(L, 13);
	sprite2d->p2[2] = lua_tonumber(L, 14);
	sprite2d->p2[3] = lua_tonumber(L, 15);
	sprite2d->p3[2] = lua_tonumber(L, 16);
	sprite2d->p3[3] = lua_tonumber(L, 17);

	return 1;
}

int
lib_sprite2d(lua_State *L)
{
	luaL_Reg l[] = {
		{"set_texcoord", lset_texcoord},
		{"set_position", lset_position},
		{"set_texture", lset_texture},
		{"create", lcreate},
		{NULL, NULL}
	};
	luaL_newlib(L, l);
	return 1;
}