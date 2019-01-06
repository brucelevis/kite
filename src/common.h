#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include <glfw/glfw3.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stb_image.h>

static inline void
ASSERT(int ok, const char * msg) {
	if (!ok) {
		fprintf(stderr, "%s\n", msg);
		exit(EXIT_FAILURE);
	}
}


#define FREE(p); if(p) {free(p); p = NULL;}


#endif