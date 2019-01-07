#include "game.h"
#include "renderer.h"

#define ITEM_SIZE sizeof(float)*4*4

extern Game *G;
static Renderer *renderer;


void
renderer_bind_texture(GLuint texture) {
	if (texture != renderer->cur_texture) {
		glBindTexture(GL_TEXTURE_2D, texture);
		renderer->cur_texture = texture;
	}
}


void
renderer_flush() {
	if (renderer->batch.count == 0) return;
	renderer_bind_texture(renderer->batch.texture);
	glBufferSubData(GL_ARRAY_BUFFER, 0, ITEM_SIZE*renderer->batch.count, renderer->batch.vertices);
	glDrawElements(GL_TRIANGLES, 6 * renderer->batch.count, GL_UNSIGNED_INT, 0);
	renderer->batch.count = 0;
	renderer->drawc += 1;
}


void
renderer_draw(Sprite2D *sprite) {
	if ((sprite->texture != renderer->batch.texture) || (renderer->batch.count == MAX_BATCH_SLOT)) {
		renderer_flush();
	}
	renderer->batch.texture = sprite->texture;

	memcpy(renderer->batch.vertices + ITEM_SIZE/sizeof(float) * renderer->batch.count, sprite->p0, ITEM_SIZE);
	renderer->batch.count += 1;
}


void
renderer_commit() {
	renderer_flush();
	G->drawcall = renderer->drawc;
	renderer->drawc = 0;
}


static void
on_window_resize(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}


static int
renderer_init() {

	// init opengl
	glfwMakeContextCurrent(G->window->handle);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		fprintf(stderr, "failed to init glad!\n");
		return 1;
	}
	glViewport(0, 0, G->window->width, G->window->height);
	glfwSetFramebufferSizeCallback(G->window->handle, on_window_resize);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// create draw resource
	GLuint vao, vbo, ebo;

	static GLuint indices[6 * MAX_BATCH_SLOT];

	for (int i = 0; i < MAX_BATCH_SLOT; ++i)
	{
		indices[i*6 + 0] = 0 + i*4;
		indices[i*6 + 1] = 1 + i*4;
		indices[i*6 + 2] = 2 + i*4;
		indices[i*6 + 3] = 0 + i*4;
		indices[i*6 + 4] = 2 + i*4;
		indices[i*6 + 5] = 3 + i*4;
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, ITEM_SIZE* MAX_BATCH_SLOT, NULL, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);

	renderer->vao = vao;
	renderer->vbo = vbo;
	renderer->ebo = ebo;
	return 0;
}


void
renderer_destroy() {
	glDeleteVertexArrays(1, &renderer->vao);
	glDeleteBuffers(1, &renderer->vbo);
	glDeleteBuffers(1, &renderer->ebo);
	free(renderer);
}


Renderer *
create_renderer() {
	renderer = malloc(sizeof(Renderer) +  ITEM_SIZE * MAX_BATCH_SLOT);

	if (renderer_init()) {
		free(renderer);
		return NULL;
	}

	renderer->batch.count = 0;
	renderer->batch.texture = 0;

	renderer->cur_texture = 0;
	renderer->drawc = 0;

	renderer->bind_texture = renderer_bind_texture;
	renderer->draw = renderer_draw;
	renderer->flush = renderer_flush;
	renderer->commit = renderer_commit;
	renderer->destroy = renderer_destroy;
	return renderer;
}