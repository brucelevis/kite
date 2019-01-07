#ifndef RENDERER_H
#define RENDERER_H

#include "common.h"
#include "lsprite2d.h"

#define MAX_BATCH_SLOT 1024



typedef struct
{
	GLuint texture;
	uint32_t count;
	float vertices[];	
} Batch;


typedef struct
{	
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	
	uint32_t drawc;

	GLuint cur_texture;
	void(*bind_texture)(GLuint);
	void(*draw)(Sprite2D *);
	void(*flush)(void);
	void(*commit)(void);
	void(*destroy)(void);

	Batch batch;
} Renderer;



Renderer *
create_renderer();

#endif