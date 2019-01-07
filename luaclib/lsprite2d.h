#ifndef LSPRITE2D_H
#define LSPRITE2D_H

#include "common.h"


typedef struct
{
	GLuint texture;
	float p0[4]; 	//{x, y, u, v}  (let-top Anti-clockwise)
	float p1[4];
	float p2[4];
	float p3[4];
} Sprite2D;


int
lib_sprite2d(lua_State *L);



#endif