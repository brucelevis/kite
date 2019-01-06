#include "game.h"

Game *G;


void
game_run() {
	GLFWwindow *hwnd = G->window->handle;
	double now, dt;
	
	while(!glfwWindowShouldClose(hwnd)) {
		now = glfwGetTime();
		dt = now - G->time;
		G->time = now;
		G->kite->update(dt);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

		glfwPollEvents();
		glfwSwapBuffers(hwnd);
	}
	G->kite->exit();
}


void
game_destroy () {
	G->kite->destroy();
	G->window->destroy();
	free(G);
}


Game *
create_game(const char *gamedir) {
	G = malloc(sizeof(Game));

	G->drawcall = 0;
	G->time = 0.f;

	G->kite = create_kite(gamedir); 	if (G->kite == NULL)     {free(G); exit(EXIT_FAILURE);}
	G->window = create_window();		if (G->window == NULL)   {G->kite->destroy(); free(G); exit(EXIT_FAILURE);}

	if (G->kite->load()) {
		G->kite->destroy();
		G->window->destroy();
		free(G);
		exit(EXIT_FAILURE);
	}
	G->run = game_run;
	G->destroy = game_destroy;
	return G;
}
