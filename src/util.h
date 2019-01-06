#ifndef UTIL_H
#define UTIL_H

#include "common.h"


typedef float mat4x4[4][4];




unsigned char *
load_image(const char *, int *, int *, int *, bool);


#define destroy_image stbi_image_free


GLuint
program_from_file(const char*, const char*);


void
mat4x4_ortho(mat4x4 M, float l, float r, float b, float t, float n, float f);



#endif